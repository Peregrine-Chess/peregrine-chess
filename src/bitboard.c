#include <bitboard.h>

int popcount(uint64_t bitboard) {
  int count = 0;
  while (bitboard) count += bitboard & 1, bitboard >>= 1;

  return count;
}

void printbits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void printbitboard(uint64_t bitboard) {
    printf("\n");
    for (int rank = 0; rank < 8; rank ++) {
        for (int file = 0; file < 8; file ++) {
            int square = rank * 8 + file;

            if (!file) {
                printf("  %d  ", 8 - rank);
            }

            printf(" %d ", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n      a  b  c  d  e  f  g  h\n");
}