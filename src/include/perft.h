/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __PERFT_H__
#define __PERFT_H__

#include <move.h>
#include <movegen.h>
#include <time.h>

extern long nodes;

void perft_driver(int depth);
void perft_test(int depth);

#endif