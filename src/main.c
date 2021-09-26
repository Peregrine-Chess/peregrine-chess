/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <board.h>
#include <attacks.h>

int main(void) {
    // This stuff is just for testing purposes

    print_bitboard(get_knight_attacks(e4));
    print_bitboard(get_knight_attacks(a6));
    print_bitboard(get_knight_attacks(h2));
    print_bitboard(get_knight_attacks(d8));
}
