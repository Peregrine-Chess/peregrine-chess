/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>

int main() {
    // Nothing here currently, just used for debugging purposes.

    init_attacks();

    Bitboard block = 0ULL;

    set_bit(block, d7);
    set_bit(block, d2);
    set_bit(block, d1);
    set_bit(block, b4);
    set_bit(block, g4);

    printbitboard(block);

    printf("\n\nindex: %d  | coordinates: %s\n\n", get_least_significant_first_bit(block), square_to_coords[get_least_significant_first_bit(block)]);

    Bitboard test = 0ULL;

    set_bit(test, get_least_significant_first_bit(block));

    printbitboard(test);
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