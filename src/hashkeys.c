/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <hashkeys.h>

Bitboard piece_keys[13][120];
Bitboard side_key;
Bitboard castle_keys[16];

Bitboard generate_pos_key(const BOARD *pos) {
  Bitboard key = 0;
  int piece = EMPTY;

  for (int sq = 0; sq < BOARD_NUM_SQUARES; sq ++) {
    piece = pos->pieces[sq];
    if (piece != no_sq && piece != EMPTY) {
      ASSERT(piece >= wP && piece <= bK);
      key ^= piece_keys[piece][sq];
    }
  }

  if (pos->side == WHITE) {
    key ^= side_key;
  }

  if (pos->en_passant != no_sq) {
    ASSERT(pos->en_passant >= 0 && pos->en_passant < BOARD_NUM_SQUARES);
    key ^= piece_keys[EMPTY][pos->en_passant];
  }

  ASSERT(pos->castle_perms >= 0 && pos->castle_perms <= 15);

  key ^= castle_keys[pos->castle_perms];

  return key;
}
