/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>
#include <move.h>

typedef struct MOVELIST {
  MOVE moves[MAX_POSITION_MOVES];
  int count;
} MOVELIST;

void add_quiet_move(const BOARD *pos, int move, MOVELIST *list);
void add_capture_move(const BOARD *pos, int move, MOVELIST *list);
void add_en_passant_move(const BOARD *pos, int move, MOVELIST *list);

void generate_all_moves(const BOARD *pos, MOVELIST *list);
