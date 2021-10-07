/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <init.h>
#include <board.h>
#include <bitboard.h>
#include <hashkeys.h>

int main(void) {
  init_all();

  BOARD board[1];

  parse_fen(KILLER_POSITION, board);
  print_board(board);

  ASSERT(check_board(board));
}
