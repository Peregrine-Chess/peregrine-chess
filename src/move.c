/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <move.h>
#include <attacks.h>

char *print_square(const int square) {
  static char square_string[3];

  int file = files_board[square];
  int rank = ranks_board[square];

  sprintf(square_string, "%c%c", ('a' + file), ('1' + rank));

  return square_string;
}

char *print_move(const int move) {
  static char move_string[6];
  
  int file_from = files_board[FROM_SQ(move)];
  int rank_from = ranks_board[FROM_SQ(move)];
  int file_to = files_board[TO_SQ(move)];
  int rank_to = ranks_board[TO_SQ(move)];

  int promoted = PROMOTED(move);

  if (promoted) {
    char promotion_char = 'q';
    if (IS_KNIGHT(promoted)) {
      promotion_char = 'n';
    } else if (IS_ROOK_QUEEN(promoted) && !IS_BISHOP_QUEEN(promoted)) {
      promotion_char = 'r';
    } else if (IS_BISHOP_QUEEN(promoted) && !IS_ROOK_QUEEN(promoted)) {
      promotion_char = 'b';
    }
    sprintf(move_string, "%c%c%c%c%c", ('a' + file_from), ('1' + rank_from), ('a' + file_to), ('1' + rank_to), promotion_char);
  } else {
    sprintf(move_string, "%c%c%c%c", ('a' + file_from), ('1' + rank_from), ('a' + file_to), ('1' + rank_to));
  }

  return move_string;
}

void print_move_list(const MOVELIST *list) {
  printf("Move List: \n");

  for (int i = 0; i < list->count; i ++) {
    int move = list->moves[i].move;
    int score = list->moves[i].score;

    printf("Move: %d => %s (score: %d)\n", i + 1, print_move(move), score);
  }

  printf("Move list total: %d moves\n", list->count);
}
