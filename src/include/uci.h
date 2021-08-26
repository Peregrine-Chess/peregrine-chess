/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef __UCI_H__
#define __UCI_H__

#include <move.h>
#include <movegen.h>
#include <bitboard.h>
#include <string.h>

int uci_parse_move(char *move_string);
void uci_parse_position(char *pos);
void uci_parse_go(char *command);

#endif
