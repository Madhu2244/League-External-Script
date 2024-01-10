#include "GetLoLProcessBase.h"
#include "Orbwalker.h"
#include "MissileUI.h"
#include <thread>
#include <functional>

int main() {
    LoLProcessInfo lolInfo = GetLeagueOfLegendsInfo();
    std::thread thread1(DrawMissiles, std::ref(lolInfo));

    Orbwalker orbwalker = Orbwalker(lolInfo);
    std::thread thread2(std::bind(&Orbwalker::Orbwalk, &orbwalker));

    //thread1.join();
    thread2.join();
}