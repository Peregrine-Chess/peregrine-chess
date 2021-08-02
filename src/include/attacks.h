#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <bitboard.h>

#define not_file 0ULL

extern Bitboard pawn_attacks[2][64];
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];
extern Bitboard bishop_attacks[64];
extern Bitboard rook_attacks[64];

void init_attacks();

Bitboard get_pawn_attacks(int square, int color);
Bitboard get_knight_attacks(int square);
Bitboard get_king_attacks(int square);
Bitboard get_bishop_attacks(int square);
Bitboard get_rook_attacks(int square);

void init_pawn_attacks();
void init_knight_attacks();
void init_king_attacks();
void init_bishop_attacks();
void init_rook_attacks();

#endif