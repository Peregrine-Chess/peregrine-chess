/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitboard.h>
#include <attacks.h>

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

/*
    bin  dec
    
   0001    1  white king can castle to the king side
   0010    2  white king can castle to the queen side
   0100    4  black king can castle to the king side
   1000    8  black king can castle to the queen side
   examples
   1111       both sides an castle both directions
   1001       black king => queen side
              white king => king side
*/

enum { WK = 1, WQ = 2, BK = 3, BQ = 4 };
#endif