/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <attacks.h>

// Bitboard constants

const Bitboard not_a_file = 18374403900871474942ULL;
const Bitboard not_h_file = 9187201950435737471ULL;
const Bitboard not_hg_file = 4557430888798830399ULL;
const Bitboard not_ab_file = 18229723555195321596ULL;

Bitboard pawn_attacks[2][64];
Bitboard knight_attacks[64];
Bitboard king_attacks[64];
Bitboard bishop_attacks[64];
Bitboard rook_attacks[64];
Bitboard queen_attacks[64];

// Initialize piece bitboards

void init_attacks() {
    init_pawn_attacks();
    init_knight_attacks();
    init_king_attacks();
    init_bishop_attacks();
    init_rook_attacks();
}

// Get pawn attacks for a specific square and color

Bitboard get_pawn_attacks(int square, int color) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    if (!color) {
        // Board limit checking, white pawn may not capture on
        // the A file if it is on its right (doesn't make any sense),
        // and the H file if it is on its left. Same for the black 
        // pawns, just mirrored.

        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    } else {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);    
    }

    return attacks;
}

// Get knight attacks for specific square

Bitboard get_knight_attacks(int square) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    // Same logic as the pawns, just a bit more complicated

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

// Get king attacks for a specific square

Bitboard get_king_attacks(int square) {
    Bitboard bitboard = 0ULL, attacks = 0ULL;

    set_bit(bitboard, square);

    // Same logic. ITS THE SAME STOP READING THESE THINGS

    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if ((bitboard >> 8) & not_a_file) attacks |= (bitboard >> 8);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);
    if ((bitboard << 9) & not_h_file) attacks |= (bitboard << 9);
    if ((bitboard << 8) & not_a_file) attacks |= (bitboard << 8);
    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);

    return attacks;
}

// Get bishop attacks for a specific square

Bitboard get_bishop_attacks(int square) {
    Bitboard attacks = 0ULL;

    int sq_rank = rank(square);
    int sq_file = file(square);

    // The bishop logic is a bit different as it moves diagonally,
    // we use for loops with two variables that we increment/decrement
    // in order for it to work. I don't know how it works, it just does.

    for (int r = sq_rank + 1, f = sq_file + 1; r <= 6 && f <= 6; r ++, f ++) 
        attacks |= (1ULL << (r * 8 + f));
    for (int r = sq_rank - 1, f = sq_file + 1; r >= 1 && f <= 6; r --, f ++) 
        attacks |= (1ULL << (r * 8 + f));
    for (int r = sq_rank + 1, f = sq_file - 1; r <= 6 && f >= 1; r ++, f --) 
        attacks |= (1ULL << (r * 8 + f));
    for (int r = sq_rank - 1, f = sq_file - 1; r >= 1 && f >= 1; r --, f --) 
        attacks |= (1ULL << (r * 8 + f));

    return attacks;
}

// Get rook attacks for a specific square

Bitboard get_rook_attacks(int square) {
    Bitboard attacks = 0ULL;

    int sq_rank = rank(square);
    int sq_file = file(square);

    // Rook logic is similar to the bishop one (both are
    // sliding pieces), but it is simpler because it can
    // move in straight lines (only one variable needed)

    for (int r = sq_rank + 1; r <= 6; r ++)
        attacks |= (1ULL << (r * 8 + sq_file));
    for (int f = sq_file + 1; f <= 6; f ++)
        attacks |= (1ULL << (sq_rank * 8 + f));
    for (int r = sq_rank - 1; r >= 1; r --) 
        attacks |= (1ULL << (r * 8 + sq_file));
    for (int f = sq_file - 1; f >= 1; f --)
        attacks |= (1ULL << (sq_rank * 8 + f));

    return attacks;
}

// Get queen attacks for a specific square

Bitboard get_queen_attacks(int square) {
    // The queen is easy, just combine rook and bishop (:
    return get_bishop_attacks(square) | get_rook_attacks(square);
}

// Get bishop attacks on the fly (legal moves for
// a specific square on a specific board)

Bitboard bishop_attacks_otf(int square, Bitboard block) {
    Bitboard attacks = 0ULL;

    int sq_rank = rank(square);
    int sq_file = file(square);

    // Almost the same logic as the normal bishop function
    // except if there is a piece on the square, we break
    // the loop.

    for (int r = sq_rank + 1, f = sq_file + 1; r <= 7 && f <= 7; r ++, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file + 1; r >= 0 && f <= 7; r --, f ++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank + 1, f = sq_file - 1; r <= 7 && f >= 0; r ++, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (int r = sq_rank - 1, f = sq_file - 1; r >= 0 && f >= 0; r --, f --) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }

    return attacks;
}

// Initialize pawn attacks

void init_pawn_attacks() {
    for (int i = 0; i < 64; i ++) {
        pawn_attacks[WHITE][i] = get_pawn_attacks(i, WHITE);
        pawn_attacks[BLACK][i] = get_pawn_attacks(i, BLACK);
    }
}

// Initialize knight attacks

void init_knight_attacks() {
    for (int i = 0; i < 64; i ++) {
        knight_attacks[i] = get_knight_attacks(i);
    }
}

// Initialize king attacks

void init_king_attacks() {
    for (int i = 0; i < 64; i ++) {
        king_attacks[i] = get_king_attacks(i);
    }
}

// Initialize bishop attacks

void init_bishop_attacks() {
    for (int i = 0; i < 64; i ++) {
        bishop_attacks[i] = get_bishop_attacks(i);
    }
}

// Initialize rook attacks

void init_rook_attacks() {
    for (int i = 0; i < 64; i ++) {
        rook_attacks[i] = get_rook_attacks(i);
    }
}

// Initialize queen attacks

void init_queen_attacks() {
    for (int i = 0; i < 64; i ++) {
        queen_attacks[i] = get_queen_attacks(i);
    }
}