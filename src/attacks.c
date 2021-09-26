/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <attacks.h>

const Bitboard not_a_file = 18374403900871474942ULL;
const Bitboard not_h_file = 9187201950435737471ULL;
const Bitboard not_hg_file = 4557430888798830399ULL;
const Bitboard not_ab_file = 18229723555195321596ULL;

Bitboard get_pawn_attacks(int square, int color) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    if (color) {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    } else {
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    }

    return attacks;
}

Bitboard get_knight_attacks(int square) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    if ((bitboard >> 17) & not_h_file)  attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file)  attacks |= (bitboard >> 15);
    if ((bitboard >> 6) & not_ab_file)  attacks |= (bitboard >> 6);
    if ((bitboard >> 10) & not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard << 17) & not_a_file)  attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file)  attacks |= (bitboard << 15);
    if ((bitboard << 6) & not_hg_file)  attacks |= (bitboard << 6);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);

    return attacks;
}
