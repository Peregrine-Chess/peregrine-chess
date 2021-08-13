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
    
    moves move_list[1];
    move_list->count = 0;

    add_move(move_list, encode_move(d7, e8, P, Q, 1, 0, 0, 0));

    print_move_list(move_list);
}
