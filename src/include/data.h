/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __DATA_H__
#define __DATA_H__

#include <board.h>

extern char piece_char[];
extern char rank_char[];
extern char side_char[];
extern char file_char[];

extern int piece_big[13];
extern int piece_major[13];
extern int piece_minor[13];
extern int piece_value[13];
extern int piece_color[13];

extern int piece_slides[13];

#endif
