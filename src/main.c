/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */


#include <bitboard.h>
#include <board.h>

int main(void) {
    // This stuff is just for testing purposes
    Bitboard bitboard = 0ULL;

    set_bit(bitboard, e4);
    set_bit(bitboard, h1);
    set_bit(bitboard, c7);

    print_bitboard(bitboard);

    printf("\n\n");
    printf("Number of 'on' bits: %d\n", pop_count(bitboard));

    set_bit(bitboards[p], a2);

    printf("\n\n");

    side = WHITE;
    print_board();

    print_bitboard(bitboards[p]);
}
