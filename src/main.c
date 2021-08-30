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
    // init EVERYTHING
    init_all();

    /*
    parsefen("rn2k2r/ppp2ppp/8/3p4/5pb1/4b3/PPPnP1B1/RNBQK1N1 b kq - 3 12");
    moves move_list[1];
    gen_moves(move_list);
    print_move_list(move_list);
    */

    uci_loop();
}
