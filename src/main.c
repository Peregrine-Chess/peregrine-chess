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

    copy_board();
    parsefen(empty_board);
    printboard();

    restore_board();
    printboard();
    
    return 0;
}
