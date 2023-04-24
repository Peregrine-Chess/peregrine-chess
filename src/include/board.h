/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitboard.h>
#include <attacks.h>
#include <string.h>

// FEN dedug positions
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

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

// Copies for board preservation stuff
extern Bitboard bitboards_copy[12];
extern Bitboard occupancies_copy[3];
extern int side_copy, en_passant_copy, castle_copy;

/*
    bin  dec
    
   0001    1  white king can castle to the king side
   0010    2  white king can castle to the queen side
   0100    4  black king can castle to the king side
   1000    8  black king can castle to the queen side
   examples
   1111       both sides can castle both directions
   1000       black king => queen side
   0001       white king => king side
*/

enum { WK = 1, WQ = 2, BK = 4, BQ = 8 };

// pieces
enum { P, N, B, R, Q, K, p, n, b, r, q, k };

extern char ascii_pieces[];
extern char *unicode_pieces[12];
extern int char_pieces[];

void printboard();

// parse FEN strings
void parsefen(char *fen);

// Preserve board
void copy_board();

void restore_board();
#endif
