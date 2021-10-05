/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <init.h>

void logger(int status, char *message) {
  if (status) {
    fprintf(stderr, "\033[0;32m");
    fprintf(stderr, "[ OK ] ");
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "%s\n", message);
  } else {
    fprintf(stderr, "\033[0;31m");
    fprintf(stderr, "[ FAIL ] ");
    fprintf(stderr, "\033[0m");
    fprintf(stderr, "%s\n", message);
  }
}

int init_hash_keys() {
  for (int i = 0; i < 13; i ++) {
    for (int j = 0; j < 120; j ++) {
      piece_keys[i][j] = RAND_64;
    }
  }
  side_key = RAND_64;
  for (int i = 0; i < 16; i ++) {
    castle_keys[i] = RAND_64;
  }

  return 1;
}

int init_sq_120_sq_64() {
  int file = FILE_A, rank = RANK_1;
  int sq = a1, sq_64 = 0;

  for (int i = 0; i < BOARD_NUM_SQUARES; i ++) {
    sq_120_sq_64[i] = 65;
  }

  for (int i = 0; i < 64; i ++) {
    sq_64_sq_120[i] = 120;
  }

  for (rank = RANK_1; rank <= RANK_8; rank ++) {
    for (file = FILE_A; file <= FILE_H; file ++) {
      sq = INDEX(file, rank);
      sq_64_sq_120[sq_64] = sq;
      sq_120_sq_64[sq] = sq_64;
      sq_64 ++;
    }
  }

  return 1;
}

int init_bit_mask() {
  for (int i = 0; i < 64; i ++) {
    set_mask[i] = 0ULL;
    clear_mask[i] = 0ULL;
  }

  for (int i = 0; i < 64; i ++) {
    set_mask[i] |= (1ULL << i);
    clear_mask[i] = ~set_mask[i];
  }

  return 1;
}

void init_all() {
  logger(init_sq_120_sq_64(), "Initializing square indexes...");
  logger(init_bit_mask(), "Initializing bit mask...");
  logger(init_hash_keys(), "Initializing hash keys...");
}
