/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include <board.h>
#include <data.h>

#define IS_BISHOP_QUEEN(p) (piece_bishop_queen[p])
#define IS_ROOK_QUEEN(p) (piece_bishop_queen[p])
#define IS_KING(p) (piece_king[p])
#define IS_KNIGHT(p) (piece_knight[p])

extern const int king_direction[8];
extern const int rook_direction[4];
extern const int bishop_direction[4];
extern const int knight_direction[8];

extern int piece_knight[13];
extern int piece_king[13];
extern int piece_rook_queen[13];
extern int piece_bishop_queen[13];

int is_square_attacked(const int sq, const int side, const BOARD *pos);

#endif
