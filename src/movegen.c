/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <movegen.h>

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

void generate_all_moves(const BOARD *pos, MOVELIST *list) {
  list->count = 0;
}
