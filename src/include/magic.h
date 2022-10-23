/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <bitboard.h>
#include <attacks.h>
#include <random.h>

#include <string.h>

extern Bitboard rook_magic_numbers[64];
extern Bitboard bishop_magic_numbers[64];

Bitboard find_magic(int square, int relevant_bits, int is_bishop);
void init_magic_numbers();

#endif
