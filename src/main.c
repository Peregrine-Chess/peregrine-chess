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

int main() {
    // init EVERYTHING
    init_all();
    
    parsefen("r3k2r/p1ppRpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1 ");
    printboard();

    moves move_list[1];
    move_list->count = 0;

    gen_moves(move_list);

    int start = get_time_ms();

    for (int move_count = 0; move_count < move_list->count; move_count++) {
        int move = move_list->moves[move_count];
        
        copy_board();

        if (!make_move(move, all_moves))
            continue;
        
        printboard();
        getchar();
        
        restore_board();
        printboard();
        
        getchar();
    }

    printf("time taken to execute: %d ms\n", get_time_ms() - start);
    getchar();
}
