/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <bitboard.h>
#include <board.h>
#include <log.h>

#define not_file 0ULL

extern const Bitboard not_a_file;
extern const Bitboard not_h_file;
extern const Bitboard not_hg_file; 
extern const Bitboard not_ab_file;

extern Bitboard pawn_attacks[2][64];
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];

Bitboard get_pawn_attacks(int square, int color);
Bitboard get_knight_attacks(int square);
Bitboard get_king_attacks(int square);
Bitboard get_bishop_attacks(int square, Bitboard block);
Bitboard get_rook_attacks(int square, Bitboard block);

void init_all();

#endif
