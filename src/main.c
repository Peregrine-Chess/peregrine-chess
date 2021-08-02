#include <bitboard.h>
#include <attacks.h>

int main() {
    init_attacks();

    Bitboard block = 0ULL;

    set_bit(block, c2);
    set_bit(block, f3);
    set_bit(block, g6);
    set_bit(block, b7);

    printbitboard(block);

    printbitboard(bishop_attacks_otf(e4, block));

    /*
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
    */
}