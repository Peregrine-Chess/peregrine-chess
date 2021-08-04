/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>
#include <random.h>
#include <magic.h>
#include <log.h>

int main() {
    // Nothing here currently, just used for debugging purposes.
    logger(init_attacks(), "Initializing knight, king, and pawn attacks....");
    logger(init_slider_attacks(1), "Initializing bishop attacks....");
    logger(init_slider_attacks(0), "Initializing rook attacs....");
    //printf("Initializing magic bitboards....\n");
    //init_magic_numbers(); // <--- This will take some time.
    printf("Done!!!\n");
    // define test bitboard
    Bitboard occupancy = 0ULL;
    
    // set blocker pieces on board
    set_bit(occupancy, c5);
    set_bit(occupancy, f2);
    set_bit(occupancy, g7);
    set_bit(occupancy, b2);
    set_bit(occupancy, g5);
    set_bit(occupancy, e2);
    set_bit(occupancy, e7);
    
    // print occupancies
    printbitboard(occupancy);
    
    // print rook attacks
    printbitboard(get_rook_attacks(e5, occupancy));
    
    // print bishop attacks
    printbitboard(get_bishop_attacks(d4, occupancy));
}