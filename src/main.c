/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>
#include <random.h>
#include <magic.h>
#include <log.h>
#include <board.h>
#include <misc.h>
#include <movegen.h>
#include <move.h>
#include <time.h>
#include <perft.h>
#include <uci.h>

int main() {
    init_all();

    /*
    parsefen("rn2k2r/p1p4p/1p3p2/2b3p1/3p1p2/5b2/PPPPP3/RNBnKB1R w kq - 0 1");

    moves move_list[1];
    legal_moves(move_list);

    printboard();

    print_attacked_squares(BLACK);

    print_move_list(move_list);
  */    

    uci_loop();

    return 0;
}
