/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <board.h>
#include <attacks.h>
#include <log.h>
#include <move.h>
#include <movegen.h>

int main(void) {
  // This stuff is just for testing purposes
  init_all();

  parse_fen(start_position);
  moves move_list[1];

  gen_moves(move_list);

  print_move_list(move_list);
}
