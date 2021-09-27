/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <attacks.h>

const Bitboard not_a_file = 18374403900871474942ULL;
const Bitboard not_h_file = 9187201950435737471ULL;
const Bitboard not_hg_file = 4557430888798830399ULL;
const Bitboard not_ab_file = 18229723555195321596ULL;

Bitboard pawn_attacks[2][64];
Bitboard knight_attacks[64];
Bitboard king_attacks[64];

Bitboard get_pawn_attacks(int square, int color) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    if (color) {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    } else {
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    }

    return attacks;
}

Bitboard get_knight_attacks(int square) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    if ((bitboard >> 17) & not_h_file)  attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file)  attacks |= (bitboard >> 15);
    if ((bitboard >> 6) & not_ab_file)  attacks |= (bitboard >> 6);
    if ((bitboard >> 10) & not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard << 17) & not_a_file)  attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file)  attacks |= (bitboard << 15);
    if ((bitboard << 6) & not_hg_file)  attacks |= (bitboard << 6);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);

    return attacks;
}

Bitboard get_king_attacks(int square) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);
  
    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if (bitboard >> 8) attacks |= (bitboard >> 8);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);
    if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    if (bitboard << 8) attacks |= (bitboard << 8);
    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);

    return attacks;
}

Bitboard get_bishop_attacks(int square, Bitboard block) {
    Bitboard attacks = 0ULL;

    int sq_rank = rank(square);
    int sq_file = file(square);

    for (int r = sq_rank + 1, f = sq_file + 1; r <= 7 && f <= 7; r ++, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file + 1; r >= 0 && f <= 7; r --, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank + 1, f = sq_file - 1; r <= 7 && f >= 0; r ++, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file - 1; r >= 0 && f >= 0; r --, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }

    return attacks;
}


Bitboard get_rook_attacks(int square, Bitboard block) {
  Bitboard attacks = 0ULL;

  int sq_rank = rank(square);
  int sq_file = file(square);

  for (int r = sq_rank + 1; r <= 7; r ++) {
    attacks |= (1ULL << (r * 8 + sq_file));
    if ((1ULL << (r * 8 + sq_file)) & block) break;
  }
  for (int f = sq_file + 1; f <= 7; f ++) {
    attacks |= (1ULL << (sq_rank * 8 + f));
    if ((1ULL << (sq_rank * 8 + f)) & block) break;
  }
  for (int r = sq_rank - 1; r >= 0; r --) {
    attacks |= (1ULL << (r * 8 + sq_file));
    if ((1ULL << (r * 8 + sq_file)) & block) break;
  }
  for (int f = sq_file - 1; f >= 0; f --) {
    attacks |= (1ULL << (sq_rank * 8 + f));
    if ((1ULL << (sq_rank * 8 + f)) & block) break;
  }

  return attacks;
}

Bitboard get_queen_attacks(int square, Bitboard block) {
    Bitboard attacks = 0ULL;

    int sq_rank = rank(square);
    int sq_file = file(square);

    for (int r = sq_rank + 1; r <= 7; r ++) {
        attacks |= (1ULL << (r * 8 + sq_file));
        if ((1ULL << (r * 8 + sq_file)) & block) break;
    }
    for (int f = sq_file + 1; f <= 7; f ++) {
        attacks |= (1ULL << (sq_rank * 8 + f));
        if ((1ULL << (sq_rank * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1; r >= 0; r --) {
        attacks |= (1ULL << (r * 8 + sq_file));
        if ((1ULL << (r * 8 + sq_file)) & block) break;
    }
    for (int f = sq_file - 1; f >= 0; f --) {
        attacks |= (1ULL << (sq_rank * 8 + f));
        if ((1ULL << (sq_rank * 8 + f)) & block) break;
    }
        for (int r = sq_rank + 1, f = sq_file + 1; r <= 7 && f <= 7; r ++, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file + 1; r >= 0 && f <= 7; r --, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank + 1, f = sq_file - 1; r <= 7 && f >= 0; r ++, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file - 1; r >= 0 && f >= 0; r --, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    
    return attacks;
}

int init_pawn_attacks() {
    for (int i = 0; i < 64; i ++) {
        pawn_attacks[WHITE][i] = get_pawn_attacks(i, WHITE);
        pawn_attacks[BLACK][i] = get_pawn_attacks(i, BLACK);
    }
    return 1;
}

int init_knight_attacks() {
    for (int i = 0; i < 64; i ++) {
        knight_attacks[i] = get_knight_attacks(i);
    }
    return 1;
}

int init_king_attacks() {
    for (int i = 0; i < 64; i ++) {
        king_attacks[i] = get_king_attacks(i);
    }
    return 1;
}

void init_all() {
    logger(init_pawn_attacks(), "Initializing pawn attacks...");
    logger(init_king_attacks(), "Initializing king attacks...");
    logger(init_knight_attacks(), "Initializing knight attacks...");
    fprintf(stderr, "Done!!!\n");
}

int is_square_attacked(int square, int color) {
  if ((color == WHITE) && (pawn_attacks[BLACK][square]) & bitboards[P]) return 1;
  if ((color == BLACK) && (pawn_attacks[WHITE][square]) & bitboards[p]) return 1;
  if (knight_attacks[square] & ((color == WHITE) ? bitboards[N] : bitboards[n])) return 1;
  if (get_bishop_attacks(square, occupancies[BOTH]) & ((color == WHITE) ? bitboards[B] : bitboards[b])) return 1;
  if (get_rook_attacks(square, occupancies[BOTH]) & ((color == WHITE) ? bitboards[R] : bitboards[r])) return 1;    
  if (get_queen_attacks(square, occupancies[BOTH]) & ((color == WHITE) ? bitboards[Q] : bitboards[q])) return 1;
  if (king_attacks[square] & ((color == WHITE) ? bitboards[K] : bitboards[k])) return 1;
  
  return 0;
}

void print_attacked_squares(int color) {
  for (int rank = 0; rank < 8; rank ++) {
    for (int file = 0; file < 8; file ++) {
      int square = rank * 8 + file;

      if (!file) {
        printf(" %d ", 8 - rank);
      }

      printf(" %d", is_square_attacked(square, color));
    }
    printf("\n");
  }
  printf("\n    a b c d e f g h\n\n");
}
