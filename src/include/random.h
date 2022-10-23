/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdlib.h>
#include <bitboard.h>

extern unsigned int state;

unsigned int generate_random_number32();
Bitboard generate_random_number64();
Bitboard generate_magic_number();

#endif
