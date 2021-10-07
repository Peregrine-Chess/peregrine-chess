/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitboard.h>
#include <stdlib.h>

#ifndef ASSERT
#define ASSERT(n) \
if (!(n)) { \
printf("%s - Failed\nOn %s\nAt %s\nIn File %s\nAt Line %d\n", #n, __DATE__, __TIME__, __FILE__, __LINE__); \
exit(1); } 
#endif

#define EMPTY_BOARD "8/8/8/8/8/8/8/8 w - - "
#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define TRICKY_POSITION "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define KILLER_POSITION "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define CMK_POSITION "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

#define NAME "Peregrine"
#define VERSION "0.1"
#define AUTHORS "aa2006 and contributors"

#define BOARD_NUM_SQUARES 120
#define MAX_GAME_MOVES 2048

#define INDEX(f, r) ((21 + f) + (r * 10))
#define GET_BIT(bitboard, square) (bitboard & (1ULL << sq_120_sq_64[square]))
#define SET_BIT(bitboard, square) (bitboard |= (1ULL << sq_120_sq_64[square]))
#define POP_BIT(bitboard, square) ((bitboard) &= ~(1ULL << (sq_120_sq_64[square])))
#define CLEAR_BIT_MASK(bitboard, square) ((bitboard) &= clear_mask[(square)])
#define SET_BIT_MASK(bitboard, square) ((bitboard) |= set_mask[(square)])

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };

enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

enum { WHITE, BLACK, BOTH };

enum {
  a1 = 21, b1, c1, d1, e1, f1, g1, h1,
  a2 = 31, b2, c2, d2, e2, f2, g2, h2,
  a3 = 41, b3, c3, d3, e3, f3, g3, h3,
  a4 = 51, b4, c4, d4, e4, f4, g4, h4,
  a5 = 61, b5, c5, d5, e5, f5, g5, h5,
  a6 = 71, b6, c6, d6, e6, f6, g6, h6,
  a7 = 81, b7, c7, d7, e7, f7, g7, h7,
  a8 = 91, b8, c8, d8, e8, f8, g8, h8, no_sq, OFFBOARD
};

enum { FALSE, TRUE };

enum { WHITE_OO = 1, WHITE_OOO = 2, BLACK_OO = 4, BLACK_OOO = 8 };

typedef struct UNDO {
  int move;
  int castle_perms;
  int en_passant;
  int fifty_move;
  Bitboard pos_key;
} UNDO;

typedef struct BOARD {
  int pieces[BOARD_NUM_SQUARES];
  Bitboard pawns[3];
  
  int king_sq[2];
  int side, en_passant, fifty_move;

  int castle_perms;

  int ply, his_ply;

  Bitboard pos_key;

  int piece_num[13];
  int big_pieces[2];
  int major_pieces[2];
  int minor_pieces[2];
  int material[2];

  UNDO history[MAX_GAME_MOVES];

  int piece_list[13][10];
} BOARD;

extern int sq_120_sq_64[BOARD_NUM_SQUARES];
extern int sq_64_sq_120[64];

extern int files_board[BOARD_NUM_SQUARES];
extern int ranks_board[BOARD_NUM_SQUARES];

void reset_board(BOARD *pos);
int parse_fen(char *fen, BOARD *pos);

void update_list_material(BOARD *pos);

int check_board(BOARD *pos);

void print_board(const BOARD *pos);

#endif
