/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>

// FEN dedug positions
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

Bitboard bitboards[12];
Bitboard occupancies[3];

int side = -1;
int en_passant = no_sq;
int castle;

char ascii_pieces[12] = "PNBRQKpnbrqk";
char *unicode_pieces[12] = {"♙", "♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚"};
int char_pieces[] = {
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k
};

void printboard() {
    printf("\n");
    for (int rank = 0; rank < 8; rank ++) {
        for (int file = 0; file < 8; file ++) {
            int square = rank * 8 + file, piece = -1;

            if (!file) {
                printf(" %d ", 8 - rank);
            }

            // Loop over all piece bitboards
            for (int i = P; i <= k; i ++) {
                if (get_bit(bitboards[i], square))
                    piece = i;
            }
            
            printf(" %c", (piece == -1) ? '.' : ascii_pieces[piece]);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n\n");

    printf("   Side : %s\n", (!side && (side != -1)) ? "white" : "black");
    printf("   En passant : %s\n", (en_passant != no_sq) ? square_to_coords[en_passant] : "no");
    printf("   Castle : %c%c%c%c\n\n", (castle & WK) ? 'K' : '-',
                                       (castle & WQ) ? 'Q' : '-',
                                       (castle & BK) ? 'k' : '-',
                                       (castle & BQ) ? 'q' : '-');
}