/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>

int main() {
    // Nothing here currently, just used for debugging purposes.

    init_attacks();

    for (int rank = 0; rank < 8; rank ++) {
        for (int file = 0; file < 8; file ++) {
            int square = rank * 8 + file;

            printf(" %d,", popcount(get_king_attacks(square))); 
        }
        printf("\n");
    }

    printbitboard(get_king_attacks(h6));

}