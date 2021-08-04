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

int main() {
    init_all(); // INIT *EVERYTHING*

    // set white pawns
    set_bit(bitboards[P], a2);
    set_bit(bitboards[P], b2);
    set_bit(bitboards[P], c2);
    set_bit(bitboards[P], d2);
    set_bit(bitboards[P], e2);
    set_bit(bitboards[P], f2);
    set_bit(bitboards[P], g2);
    set_bit(bitboards[P], h2);

    // set white knights
    set_bit(bitboards[N], b1);
    set_bit(bitboards[N], g1);

    // set white bishops
    set_bit(bitboards[B], c1);
    set_bit(bitboards[B], f1);

    // set white rooks
    set_bit(bitboards[R], a1);
    set_bit(bitboards[R], h1);

    // set white queen
    set_bit(bitboards[Q], d1);

    // set white king
    set_bit(bitboards[K], e1);

     // set black pawns
    set_bit(bitboards[p], a7);
    set_bit(bitboards[p], b7);
    set_bit(bitboards[p], c7);
    set_bit(bitboards[p], d7);
    set_bit(bitboards[p], e7);
    set_bit(bitboards[p], f7);
    set_bit(bitboards[p], g7);
    set_bit(bitboards[p], h7);

    // set black knights
    set_bit(bitboards[n], b8);
    set_bit(bitboards[n], g8);

    // set black bishops
    set_bit(bitboards[b], c8);
    set_bit(bitboards[b], f8);

    // set black rooks
    set_bit(bitboards[r], a8);
    set_bit(bitboards[r], h8);

    // set black queen
    set_bit(bitboards[q], d8);

    // set black king
    set_bit(bitboards[k], e8);

    // init side
    side = WHITE;

    // init en passant
    en_passant = e3;

    // init castling
    castle |= WK;
    castle |= WQ;
    castle |= BK;
    castle |= BQ;

    printbitboard(bitboards[P]);
    printboard();

    printf("--------------------------\n");

    for (int piece = P; piece <= k; piece ++) {
        printbitboard(bitboards[piece]);
    }
}