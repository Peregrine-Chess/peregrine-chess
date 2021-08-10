/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>
#include <random.h>
#include <magic.h>
#include <log.h>
#include <board.h>
#include <misc.h>
#include <movegen.h>

int main() {
  init_all(); // INIT *EVERYTHING*

    parsefen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 ");
    printboard();

    int move = 0;
    
    move = (move | 63) << 6;
    
    printbitboard(move);
    
    int target_square = (move & 0xfc0) >> 6;
    
    printf("target square: %d   %s\n", target_square, square_to_coords[target_square]);
}