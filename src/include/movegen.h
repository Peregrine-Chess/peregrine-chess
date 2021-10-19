/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>
#include <move.h>

#define ENCODE_MOVE(from, to, capture, promotion, flag) (((from) | ((to) << 7) | ((capture) << 14)) | ((promotion) << 20) | (flag))
#define SQ_OFFBOARD(sq) (files_board[(sq)] == OFFBOARD)

void add_quiet_move(const BOARD *pos, int move, MOVELIST *list);
void add_capture_move(const BOARD *pos, int move, MOVELIST *list);
void add_en_passant_move(const BOARD *pos, int move, MOVELIST *list);

void add_white_pawn_capture_move(const BOARD *pos, const int from, const int to, const int capture, MOVELIST *list);
void add_white_pawn_move(const BOARD *pos, const int from, const int to, MOVELIST *list);

void add_black_pawn_capture_move(const BOARD *pos, const int from, const int to, const int capture, MOVELIST *list);
void add_black_pawn_move(const BOARD *pos, const int from, const int to, MOVELIST *list);

void generate_all_moves(BOARD *pos, MOVELIST *list);
