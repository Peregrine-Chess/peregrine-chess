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

    parsefen("rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1");
    
    moves *move_list;
    gen_moves(move_list);
    print_move_list(move_list);
    
    //printf("%ld\n", Perft(2));
}
