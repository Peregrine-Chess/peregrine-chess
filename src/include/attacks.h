#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <bitboard.h>

#define not_file 0ULL

extern Bitboard pawn_attacks[2][64];

void init_attacks();

Bitboard get_pawn_attacks(int square, int color);
void init_pawn_attacks();

#endif