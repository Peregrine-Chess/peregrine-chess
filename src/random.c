/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <random.h>

// Random number generation to find magic number for magic bitboard.
unsigned int state = 1804289383;


// 32 bit pseudo-random numbers
unsigned int generate_random_number32() {
    unsigned int number = state;

    // XOR shift algorithm
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;

    state = number;

    return number;
}

// 64 bit peudo-random numbers
Bitboard generate_random_number64() {
    Bitboard n1, n2, n3, n4;

    n1 = (Bitboard)(generate_random_number32() & 0xFFFF);
    n2 = (Bitboard)(generate_random_number32() & 0xFFFF);
    n3 = (Bitboard)(generate_random_number32() & 0xFFFF);
    n4 = (Bitboard)(generate_random_number32() & 0xFFFF);

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

// Generate magic number candidates
Bitboard generate_magic_number() {
    return generate_random_number64() & generate_random_number64() & generate_random_number64();
}