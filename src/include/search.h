/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <movegen.h>
#include <move.h>
#include <board.h>
#include <time.h>
#include <stdlib.h>
#include <bitboard.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

extern int piece_value[12];

int eval_position();
int minimax(int depth, int is_max, int alpha, int beta);
int minimax_root(int depth, int is_max);
int search_position(int depth);

#endif