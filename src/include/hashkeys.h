/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __HASHKEYS_H__
#define __HASHKEYS_H__

#include <bitboard.h>
#include <stdlib.h>
#include <board.h>

#define RAND_64 (((Bitboard)rand()) | ((Bitboard)rand() << 15) | ((Bitboard)rand() << 30) | ((Bitboard)rand() << 45) | (((Bitboard)rand() & 0xf) << 60))

extern Bitboard piece_keys[13][120];
extern Bitboard side_key;
extern Bitboard castle_keys[16];

Bitboard generate_pos_key(const BOARD *pos);

#endif
