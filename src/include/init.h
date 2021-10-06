/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __INIT_H__
#define __INIT_H__

#include <stdio.h>
#include <hashkeys.h>
#include <board.h>

void logger(int status, char *message);

int init_hash_keys();
int init_files_ranks_board();
int init_bit_mask();
int init_sq_120_sq_64();

void init_all();

#endif
