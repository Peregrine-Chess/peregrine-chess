/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>

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

      printf(" %d ", get_bit(bitboard, square) ? 1 : 0);
    }
    printf("\n");
  }
  printf("\n      a  b  c  d  e  f  g  h\n");
}
