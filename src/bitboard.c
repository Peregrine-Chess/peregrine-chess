/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <board.h>

const int bit_table[64] = {
  63, 30,  3, 32, 25, 41, 22, 33,
  15, 50, 42, 13, 11, 53, 19, 34,
  61, 29,  2, 51, 21, 43, 45, 10,
  18, 47,  1, 54,  9, 57,  0, 35, 
  62, 31, 40,  4, 49,  5, 52, 26,
  60,  6, 23, 44, 46, 27, 56, 16,
   7, 39, 48, 24, 59, 14, 12, 55,
  38, 28, 58, 20, 37, 17, 36,  8
};

Bitboard set_mask[64];
Bitboard clear_mask[64];

int pop_count(Bitboard bitboard) {
  int count = 0;
  while (bitboard) count += bitboard & 1, bitboard >>= 1;

  return count;
}

int pop_lsb(Bitboard *bitboard) {
  Bitboard b = *bitboard ^ (*bitboard - 1ULL);

  unsigned int fold  = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bitboard &= (*bitboard - 1ULL);
  return bit_table[(fold * 0x783a9b23) >> 26];
}

void print_bitboard(Bitboard bitboard) {
  printf("\n");
  Bitboard shift = 1ULL;

  int sq = 0, sq64 = 0;

  for (int i = RANK_8; i >= RANK_1; i --) {
    for (int j = FILE_A; j <= FILE_H; j ++) {
      sq = INDEX(j, i);
      sq64 = sq_120_sq_64[sq];

      if ((shift << sq64) & bitboard) 
        printf("1 ");
      else 
        printf("0 ");
    }
    printf("\n");
  }
  printf("\n");
}
