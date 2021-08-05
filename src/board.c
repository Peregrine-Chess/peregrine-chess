/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>

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

void parsefen(char *fen) {
  memset(bitboards, 0ULL, sizeof(bitboards));
  memset(occupancies, 0ULL, sizeof(occupancies));

  side = 0;
  en_passant = no_sq;
  castle = 0;
  
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int square = rank * 8 + file;
    
      if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z')) {
        int piece = char_pieces[*fen];

        set_bit(bitboards[piece], square);

        *fen++;
      }
      
      if (*fen >= '0' && *fen <= '9') {
        int offset = *fen - '0';

        int piece = -1;

        for (int bb_piece = P; bb_piece <= k; bb_piece++) {
          if (get_bit(bitboards[bb_piece], square))
            piece = bb_piece;
        }   

        if (piece == -1)
          file--;
        
        file += offset;
        
        *fen++;
      }
      
      if (*fen == '/')
        *fen++;
    }
  }
  
  *fen++;

  (*fen == 'w') ? (side = WHITE) : (side = BLACK);

  fen += 2;

  while (*fen != ' ') {
    switch (*fen) {
      case 'K': castle |= WK; break;
      case 'Q': castle |= WQ; break;
      case 'k': castle |= BK; break;
      case 'q': castle |= BQ; break;
      case '-': break;
    }

    *fen++;
  }
  
  *fen++;

  if (*fen != '-') {
    int file = fen[0] - 'a';
    int rank = 8 - (fen[1] - '0');

    en_passant = rank * 8 + file;
  }

  else
    en_passant = no_sq;

  for (int piece = P; piece <= K; piece++)
    occupancies[WHITE] |= bitboards[piece];

  for (int piece = p; piece <= k; piece++)
    occupancies[BLACK] |= bitboards[piece];
  
  occupancies[BOTH] |= occupancies[WHITE];
  occupancies[BOTH] |= occupancies[BLACK];
}
