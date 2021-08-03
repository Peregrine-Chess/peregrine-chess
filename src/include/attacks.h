/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <bitboard.h>

#define not_file 0ULL

// Piece attack bitboards, initialized in attacks.c

extern Bitboard pawn_attacks[2][64];
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];

// Relevant occupancy bits bitboards
extern const int relevant_bishop_bits[64];
extern const int relevant_rook_bits[64];

// Function to initialize attack bitboards

void init_attacks();

// Functions to generate piece attacks for each 
// square/color

Bitboard get_pawn_attacks(int square, int color);
Bitboard get_knight_attacks(int square);
Bitboard get_king_attacks(int square);
Bitboard get_bishop_attacks(int square);
Bitboard get_rook_attacks(int square);
Bitboard get_queen_attacks(int square);

// Functions to generate piece attacks on the fly 
// (legal attacks)

Bitboard bishop_attacks_otf(int square, Bitboard block);
Bitboard rook_attacks_otf(int square, Bitboard block);

// Functions to initialize piece attack bitboards, 
// used by the init_attacks() function

void init_pawn_attacks();
void init_knight_attacks();
void init_king_attacks();

#endif