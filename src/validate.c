/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <validate.h>

int square_on_board(const int square) {
  return files_board[square] == OFFBOARD ? 0 : 1;
}

int side_valid(const int side) {
  return (side == WHITE || side == BLACK) ? 1 : 0;
}

int file_rank_valid(const int file_rank) {
  return (file_rank >= 0 && file_rank <= 7) ? 1 : 0;
}

int piece_valid_empty(const int piece) {
  return (piece >= EMPTY && piece <= bK) ? 1 : 0;
}

int piece_valid(const int piece) {
  return (piece >= wP && piece <= bK) ? 1 : 0;
}
