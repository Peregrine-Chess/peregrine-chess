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
    
    parsefen(tricky_position);
    printboard();

    moves move_list[1];

    gen_moves(move_list);

    for (int count = 0; count < move_list->count; count ++) {
        int move = move_list->moves[count];
        copy_board();

        make_move(move, all_moves);
        printboard();
        getchar();

        restore_board();
        printboard();
        getchar();
    }

    return 0;
}
