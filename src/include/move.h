/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __MOVE_H__
#define __MOVE_H__

#include <board.h>
#include <stdio.h>

#define FROM_SQ(m) ((m) & 0x7F)
#define TO_SQ(m) (((m) >> 7) & 0x7F)
#define CAPTURED(m) (((m) >> 14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7c000
#define MFLAGPROM 0xF00000

typedef struct MOVE {
  int move;
  int score;
} MOVE;

char *print_square(const int square);
char *print_move(const int move);

#endif
