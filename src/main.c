/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <init.h>
#include <board.h>
#include <bitboard.h>
#include <hashkeys.h>
#include <attacks.h>
#include <move.h>

int main(void) {
  init_all();

  BOARD board[1];

  parse_fen(KILLER_POSITION, board);
  print_board(board);

  ASSERT(check_board(board));

  int move = 0;

  int from = 6, to = 12;
  int cap = wR, prom = bR;
  move = (from) | (to << 7) | (cap << 14) | (prom << 20);
  printf("dec:%d\nhex:%X\n", move, move);

  printf("from:%d to:%d cap:%d prom:%d\n", FROM_SQ(move), TO_SQ(move), CAPTURED(move), PROMOTED(move));
  //move |= MFLAGPS;

  printf("is pawn start:%s\n", (move & MFLAGPS) ? "YES" : "NO");
}
