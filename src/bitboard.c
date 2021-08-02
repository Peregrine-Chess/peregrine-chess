/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>

// Count the number of 'on' bits in a bitboard

int popcount(Bitboard bitboard) {
  int count = 0;
  while (bitboard) count += bitboard & 1, bitboard >>= 1;

  return count;
}

// Prints the bitboard as a 64 bit binary number

void printbits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

// Prints the bitboard in a more user-friendly way,
// in an 8 by 8 grid with ranks and files.

void printbitboard(Bitboard bitboard) {
    printf("\n");
    for (int rank = 0; rank < 8; rank ++) {
        for (int file = 0; file < 8; file ++) {
            int square = rank * 8 + file;

            if (!file) {
                printf("  %d  ", 8 - rank);
            }

            printf(" %d ", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n      a  b  c  d  e  f  g  h\n");
}