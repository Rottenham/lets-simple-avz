#include "SelectCardsPlus/SelectCardsPlus.h" // 22_08_05
#include "SimpleAvZ/lib.h"                   // v1.0.0
#include "avz.h"                             // 22_10_01

using namespace AvZ;

// ch6: PPDD | IPP-PP | PPDD | IPP-PP (601, 1150, 601, 1150) cs > 3475cs (cooldown for cobs)

// smallest game tick: 1cs --> 100 frames in each second
// 0.1cs --> doesn't make sense

const int leng1 = 1150;

void Script()
{
    SkipTick(1, 18);

    OpenMultipleEffective();
    SetErrorMode(CONSOLE);

    SetZombies({ZOMBIE, CONEHEAD_ZOMBIE, POLE_VAULTING_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, DOLPHIN_RIDER_ZOMBIE,
        JACK_IN_THE_BOX_ZOMBIE, BALLOON_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, LADDER_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});

    SetIce({{1, 2}, {6, 2}, {2, 1}, {5, 1}});
    SelectCardsPlus({ICE, M_ICE, COFFEE, CHERRY, SQUASH, PUFF, SUN, SCAREDY, POT, WALL_NUT});

    // PPDD, w1~w9, every 2 wave --> w1, w3, w5, w7, w9
    for (auto w : waves({1, 9}, {10, 19}, 2)) {
        PP(225);            // earliest time to make sure gargs are damaged
        DD(359, {2, 5}, 9); // earliest time to kill all pole-vaulting zombies // row1, row5
        I(601 + 100);       // 601

        if (w == 9) {
            SetIce(0, {{1, 2}, {6, 2}});
        }
    }

    // IPP-PP
    for (auto w : waves({2, 9}, {11, 19}, 2)) {
        PP(278); // killing zomboni, diggers

        PP(leng1 - 200); // kill most zombies, also trigger refresh
    }

    // wave 20
    for (auto w : waves(20)) {
        P(249, 4, 7.5);
        PP(310);
        PP(310);
        PP(410);
        PP(410);
    }
}
