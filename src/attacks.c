/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <attacks.h>
#include <validate.h>

const int king_direction[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int rook_direction[4] = { -1, -10, 1, 10 };
const int bishop_direction[4] = { -9, -11, 11, 9 };
const int knight_direction[8] = { -1, -10, 1, 10, -9, -11, 11, 9 };

int piece_knight[13] = { FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE };
int piece_king[13] =   { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };
int piece_rook_queen[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE };
int piece_bishop_queen[13] = { FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE }; 

int is_square_attacked(const int sq, const int side, BOARD *pos) {
  ASSERT(square_on_board(sq));
  ASSERT(side_valid(side));
  ASSERT(check_board(pos));
  
  if (side == WHITE) {
    if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP) {
      return TRUE;
    } else if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP) {
      return TRUE;
    }
  }

  for (int index = 0; index < 8; index ++) {
    int piece = pos->pieces[sq + knight_direction[index]];
    if (IS_KNIGHT(piece) && piece_color[piece] == side) {
      return TRUE;
    }
  }

  for (int index = 0; index < 4; index ++) {
    int dir = rook_direction[index];
    int t_sq = sq + dir;
    int piece = pos->pieces[t_sq];
    while(piece != OFFBOARD) {
      if (piece != EMPTY) {
        if (IS_ROOK_QUEEN(piece) && piece_color[piece] == side) {
          return TRUE;
        }
        break;
      }
    }
    t_sq += dir;
    piece = pos->pieces[t_sq];
  }

  for (int index = 0; index < 4; index ++) {
    int dir = bishop_direction[index];
    int t_sq = sq + dir;
    int piece = pos->pieces[t_sq];
    while (piece != OFFBOARD) {
      if (piece != EMPTY) {
        if (IS_BISHOP_QUEEN(piece) && piece_color[piece] == side) {
          return TRUE;
        }
        break;
      }
      t_sq += dir;
      piece = pos->pieces[t_sq];
    }
  }

  for (int index = 0; index < 8; index ++) {
    int piece = pos->pieces[sq + king_direction[index]];
    if (IS_KING(piece) && piece_color[piece] == side) {
      return TRUE;
    }
  }

  return FALSE;
}
