/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>

const char *square_to_coords[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

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

// Set occupancy

Bitboard set_occupancy(int index, int bits_in_mask, Bitboard attack_mask) {
    Bitboard occupancy = 0ULL;

    for (int i = 0; i < bits_in_mask; i ++) {
        int square = get_least_significant_first_bit(attack_mask);
        pop_bit(attack_mask, square);

        if (index & (1 << i)) {
            occupancy |= (1ULL << square);
        }
    }

    return occupancy;
}

// Get the least significant first bit

int get_least_significant_first_bit(Bitboard bitboard) {
    if (bitboard) {
        return popcount((bitboard & -bitboard) - 1);
    } else {
        return -1;
    }
}