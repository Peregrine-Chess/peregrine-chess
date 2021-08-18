/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <perft.h>

uint64_t Perft(int depth) {
  moves move_list[1];
  int n_moves, i;
  long long nodes = 0;

  if (depth == 0) 
    return 1ULL;

  gen_moves(move_list);
  n_moves = move_list->count;

  for (i = 0; i < n_moves; i++) {
    copy_board();

    if (!make_move(move_list->moves[i], all_moves))
        continue;

    nodes += Perft(depth - 1);
    restore_board();
  }
  
  return nodes;
}