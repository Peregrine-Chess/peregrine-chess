/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>

int main() {
    // Nothing here currently, just used for debugging purposes.

    init_attacks();

    Bitboard attack_mask = get_bishop_attacks(d4);

    for (int i = 0; i < 4096; i ++) {
        printbitboard(set_occupancy(i, popcount(attack_mask), attack_mask));
        getchar();
    }

}