#include <bitboard.h>

int main() {
    // init bitboard
    Bitboard bitboard = 0ULL;

    // set some bits
    set_bit(bitboard, e4);
    set_bit(bitboard, d4);

    // Count number of bits
    int population = popcount(bitboard);
    printf("%d full bits.\n", population);

    // Print the board as a 64 bit binary number
    printbits(sizeof(bitboard), &bitboard);

    // Print the bitboard
    printbitboard(bitboard);
}