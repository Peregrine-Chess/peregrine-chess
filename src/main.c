/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <board.h>
#include <attacks.h>
#include <log.h>

int main(void) {
    // This stuff is just for testing purposes
    init_all();

    parse_fen(start_position);

    print_board();
    print_attacked_squares(BLACK);
}
