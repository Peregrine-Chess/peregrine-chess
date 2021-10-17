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

  int move = 0;
  int from = a2, to = h7;
  int cap = bN, prom = wB;

  move = ((from) | (to << 7) | (cap << 14) | (prom << 20));

  printf("from: %d to: %d capture: %d promotion: %d\n", FROM_SQ(move), TO_SQ(move), CAPTURED(move), PROMOTED(move));

  printf("\nAlgebraic from: %s\n", print_square(from));
  printf("Algebraic to: %s\n", print_square(to));
  printf("Algebraic move: %s\n", print_move(move));
}
