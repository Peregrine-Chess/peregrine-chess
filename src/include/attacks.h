/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <bitboard.h>
#include <board.h>

extern const Bitboard not_a_file;
extern const Bitboard not_h_file;
extern const Bitboard not_hg_file; 
extern const Bitboard not_ab_file;

Bitboard get_pawn_attacks(int square, int color);
Bitboard get_knight_attacks(int square);

#endif
