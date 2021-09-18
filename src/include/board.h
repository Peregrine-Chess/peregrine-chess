/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitboard.h>

// Piece bitboads, 12 in total (6 pieces for each color)
extern Bitboard bitboards[12];
// Occupancy bitboards, 3 in total, one for each color, and one for both.
extern Bitboard occupancies[3];
// Side to move
extern int side;
// En passant square
extern int en_passant;
// Castling rights
extern int castle;


enum { WK = 1, WQ = 2, BK = 3, BQ = 4 };
enum { P, N, B, R, Q, K, p, n, b, r, q, k };
enum { WHITE, BLACK };

extern char ascii_pieces[];
extern int char_pieces[];

void print_board();

#endif
