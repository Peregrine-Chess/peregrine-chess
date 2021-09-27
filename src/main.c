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

    Bitboard bitboard = 0ULL;

    set_bit(bitboard, c4);
    print_bitboard(get_rook_attacks(e4, bitboard));
}
