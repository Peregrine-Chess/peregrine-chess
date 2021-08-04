/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <misc.h>

void init_all() {
    // Nothing here currently, just used for debugging purposes.
    logger(init_attacks(), "Initializing knight, king, and pawn attacks....");
    logger(init_slider_attacks(bishop), "Initializing bishop attacks....");
    logger(init_slider_attacks(rook), "Initializing rook attacks....");
    //printf("Initializing magic bitboards....\n");
    //init_magic_numbers(); // <--- This will take some time.
    fprintf(stderr, "Done!!!\n");
}