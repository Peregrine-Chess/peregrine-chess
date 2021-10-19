/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <movegen.h>
#include <validate.h>
#include <data.h>

void add_quiet_move(const BOARD *pos, int move, MOVELIST *list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  list->count ++;
}

void add_capture_move(const BOARD *pos, int move, MOVELIST *list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  list->count ++;
}

void add_en_passant_move(const BOARD *pos, int move, MOVELIST *list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  list->count ++;
}

void add_white_pawn_capture_move(const BOARD *pos, const int from, const int to, const int capture, MOVELIST *list) {
  if (ranks_board[from] == RANK_7) {
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, wQ, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, wR, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, wB, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, wN, 0), list);
  } else {
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, EMPTY, 0), list);
  }
}

void add_white_pawn_move(const BOARD *pos, const int from, const int to, MOVELIST *list) {
  if (ranks_board[from] == RANK_7) {
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, wQ, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, wR, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, wB, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, wN, 0), list);
  } else {
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, EMPTY, 0), list);
  }
}

void add_black_pawn_capture_move(const BOARD *pos, const int from, const int to, const int capture, MOVELIST *list) {
  if (ranks_board[from] == RANK_2) {
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, bQ, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, bR, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, bB, 0), list);
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, bN, 0), list);
  } else {
    add_capture_move(pos, ENCODE_MOVE(from, to, capture, EMPTY, 0), list);
  }
}

void add_black_pawn_move(const BOARD *pos, const int from, const int to, MOVELIST *list) {
  if (ranks_board[from] == RANK_2) {
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, bQ, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, bR, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, bB, 0), list);
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, bN, 0), list);
  } else {
    add_quiet_move(pos, ENCODE_MOVE(from, to, EMPTY, EMPTY, 0), list);
  }
}

void generate_all_moves(BOARD *pos, MOVELIST *list) {
  ASSERT(check_board(pos));

  list->count = 0;

  int side = pos->side;
  int piece = EMPTY, sq = 0, t_sq = 0;

  if (side == WHITE) {
    // WHITE PAWNS
    for (int piece_num = 0; piece_num < pos->piece_num[wP]; piece_num ++) {
      sq = pos->piece_list[wP][piece_num];
      ASSERT(square_on_board(sq));

      if (pos->pieces[sq + 10] == EMPTY) {
        add_white_pawn_move(pos, sq, sq + 10, list);
        if (ranks_board[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY) {
          add_quiet_move(pos, ENCODE_MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
        }
      }

      if (!SQ_OFFBOARD(sq + 9) && piece_color[pos->pieces[sq + 9]] == BLACK) {
        add_white_pawn_capture_move(pos, sq, sq + 9, pos->pieces[sq + 9], list);
      }

      if (!SQ_OFFBOARD(sq + 11) && piece_color[pos->pieces[sq + 11]] == BLACK) {
        add_white_pawn_capture_move(pos, sq, sq + 11, pos->pieces[sq + 11], list);
      }

      if (sq + 9 == pos->en_passant) {
        add_capture_move(pos, ENCODE_MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), list);
      }

      if (sq + 11 == pos->en_passant) {
        add_capture_move(pos, ENCODE_MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), list);
      }
    }
  } else {
    // BLACK PAWNS
    for (int piece_num = 0; piece_num < pos->piece_num[bP]; piece_num ++) {
      sq = pos->piece_list[bP][piece_num];
      ASSERT(square_on_board(sq));

      if (pos->pieces[sq - 10] == EMPTY) {
        add_black_pawn_move(pos, sq, sq - 10, list);
        if (ranks_board[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY) {
          add_quiet_move(pos, ENCODE_MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
        }
      }

      if (!SQ_OFFBOARD(sq - 9) && piece_color[pos->pieces[sq - 9]] == WHITE) {
        add_black_pawn_capture_move(pos, sq, sq - 9, pos->pieces[sq - 9], list);
      }

      if (!SQ_OFFBOARD(sq - 11) && piece_color[pos->pieces[sq - 11]] == WHITE) {
        add_black_pawn_capture_move(pos, sq, sq - 11, pos->pieces[sq - 11], list);
      }

      if (sq - 9 == pos->en_passant) {
        add_capture_move(pos, ENCODE_MOVE(sq, sq - 9, EMPTY, EMPTY, MFLAGEP), list);
      }

      if (sq - 11 == pos->en_passant) {
        add_capture_move(pos, ENCODE_MOVE(sq, sq - 11, EMPTY, EMPTY, MFLAGEP), list);
      }
    }
  }
}
