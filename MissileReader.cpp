#include "MissileReader.h"
#include "Offsets.h"
#include "Point.h"
#include "WorldToScreen.h"
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

std::string reverseString(const std::string& input) {
    std::string reversed;
    for (int i = input.length() - 1; i >= 0; i--) {
        reversed += input[i];
    }
    return reversed;
}

std::string getEntityCaster(LoLProcessInfo lolInfo, DWORD64 addr) {
    DWORD64 MissleSpellInfo;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(addr + Offset::MissileSpellInfo), &MissleSpellInfo, Offset::ByteOffset, NULL);

    DWORD64 entityCaster;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(MissleSpellInfo + Offset::SpellEntityCaster), &entityCaster, Offset::ByteOffset, NULL);

    std::stringstream hexStream;
    hexStream << std::hex << entityCaster;
    std::string hexString = hexStream.str();

    // Convert hexadecimal string to ASCII string
    std::string asciiString;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        std::string byte = hexString.substr(i, 2);
        char character = static_cast<char>(std::stoi(byte, nullptr, 16));
        asciiString += character;
    }

    // Reverse the ASCII string
    std::string reversedAsciiString = reverseString(asciiString);
    return reversedAsciiString;
}

std::vector<std::pair<Point, Point>> ReadMissiles(LoLProcessInfo lolInfo) {
    DWORD64 missileMapPtr;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(lolInfo.baseAddress + Offset::MissileClient), &missileMapPtr, Offset::ByteOffset, NULL);
    
    DWORD64 numMissiles, rootNode;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(missileMapPtr + Offset::MissileMapCount), &numMissiles, Offset::ByteOffset, NULL);
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(missileMapPtr + Offset::MissileMapRoot), &rootNode, Offset::ByteOffset, NULL);

    std::queue<DWORD64> nodesToVisit;
	std::set<DWORD64> visitedNodes;
	nodesToVisit.push(rootNode);
     
	DWORD64 childNode1, childNode2, childNode3, node;
    std::vector<std::pair<Point, Point>> listOfMissiles;
    while (nodesToVisit.size() > 0 && visitedNodes.size() < numMissiles * 2) {
        node = nodesToVisit.front();
		nodesToVisit.pop();
		visitedNodes.insert(node);

        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(node), &childNode1, Offset::ByteOffset, NULL);
        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(node + 0x8), &childNode2, Offset::ByteOffset, NULL);
        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(node + 0x10), &childNode3, Offset::ByteOffset, NULL);
        
        if (visitedNodes.find(childNode1) == visitedNodes.end())
			nodesToVisit.push(childNode1);
		if (visitedNodes.find(childNode2) == visitedNodes.end())
			nodesToVisit.push(childNode2);
		if (visitedNodes.find(childNode3) == visitedNodes.end())
			nodesToVisit.push(childNode3);

        DWORD64 netId = 0;
        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(node + Offset::MissileMapKey), &netId, Offset::ByteOffset, NULL);
        if (netId - 0xffffffff40000000 > 0x100000) {
            continue;
        }

        DWORD64 addr = 0;
        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(node + Offset::MissileMapVal), &addr, Offset::ByteOffset, NULL);
        if (addr == 0) {
            continue;
        }

        std::string entityCaster = getEntityCaster(lolInfo, addr);
        if (entityCaster.size() > 2 && ((unsigned char)entityCaster[0] <= 255) && isalnum(entityCaster[0]) && entityCaster.find('$') == std::string::npos && entityCaster.find(':') == std::string::npos) {
            Point MissleStartPos;
            ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(addr + Offset::MissileStartPos), &MissleStartPos, sizeof(MissleStartPos), NULL);

            Point MissleEndPos;
            ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(addr + Offset::MissileEndPos), &MissleEndPos, sizeof(MissleEndPos), NULL);

            listOfMissiles.push_back(std::make_pair(WorldToScreen(MissleStartPos), WorldToScreen(MissleEndPos)));
        }
    }

    return listOfMissiles;
}