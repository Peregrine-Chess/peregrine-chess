/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __BITBOARD_H__
#define __BITBOARD_H__

#include <stdint.h>
#include <stdio.h>

typedef uint64_t Bitboard;

extern const int bit_table[64];

extern Bitboard set_mask[64];
extern Bitboard clear_mask[64];

int pop_count(Bitboard bitboard);
int pop_lsb(Bitboard *bitboard);

void print_bitboard(Bitboard bitboard);

#endif
