/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>

// Square (int) to coords (char *)
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

// Count the number of "on" bits
int pop_count(Bitboard bitboard) {
  int count = 0;
  while (bitboard) count += bitboard & 1, bitboard >>= 1;

  return count;
}

// Print bitboard in a user-friendly way (for debugging)
void print_bitboard(Bitboard bitboard) {
  printf("\n");
  for (int rank = 0; rank < 8; rank ++) {
    for (int file = 0; file < 8; file ++) {
      int square = rank * 8 + file;

      if (!file) {
        printf("  %d  ", 8 - rank);
      }

      printf(" %d", get_bit(bitboard, square) ? 1 : 0);
    }
    printf("\n");
  }
  printf("\n      a b c d e f g h\n");
}

// Get least significant bit index (lsb)
int get_lsb_index(Bitboard bitboard) {
  if (bitboard) {
    return pop_count((bitboard & -bitboard) - 1);
  } else {
    return -1;
  }
}
