/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>

int main() {
    // Nothing here currently, just used for debugging purposes.

    init_attacks();

    Bitboard block = 0ULL;

    set_bit(block, g4);
    set_bit(block, e2);
    set_bit(block, c4);
    set_bit(block, e6);

    printbitboard(block);

    printbitboard(rook_attacks_otf(e4, block));

    /*
    // init bitboard
    Bitboard bitboard = 0ULL;

    // set some bits
    set_bit(bitboard, e4);
    set_bit(bitboard, d4);

    // Count number of bits
    int population = popcount(bitboard);
    printf("%d full bits.\n", population);

    // Print the board as a 64 bit binary number
    printbits(sizeof(bitboard), &bitboard);

    // Print the bitboard
    printbitboard(bitboard);
    */
}