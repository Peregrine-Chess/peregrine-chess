/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>

Board board;

const char *square_to_coords[] = {
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "--"
};

char ascii_pieces[12] = "PNBRQKpnbrqk";

void parse_fen(char *fen) {
  board.side = 0;
  board.en_passant = no_sq;
  board.castle = malloc(sizeof(char) * 4);

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int square = rank * 8 + file;

      if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z')) {
        board.pieces[square] = *fen;
        fen++;
      }
      
      if (*fen >= '0' && *fen <= '9') {
        int offset = *fen - '0';

        int piece = -1;

        for (int i = 0; i <= 12; i++) {
          if (board.pieces[i])
            piece = i;
        }   

        if (piece == -1)
          file--;
        
        file += offset;
        
        fen++;
      }
      
      if (*fen == '/')
        fen++;
    }
  }

  fen++;

  (*fen == 'w') ? (board.side = WHITE) : (board.side = BLACK);

  fen += 2;

  while (*fen != ' ') {
    switch (*fen) {
      case 'K': board.castle[0] = 'K'; break;
      case 'Q': board.castle[1] = 'Q'; break;
      case 'k': board.castle[2] = 'k'; break;
      case 'q': board.castle[3] = 'q'; break;
      case '-': break;
    }

    *fen++;
  }
  
  
  *fen++;

  if (*fen != '-') {
    int file = fen[0] - 'a';
    int rank = 8 - (fen[1] - '0');

    board.en_passant = rank * 8 + file;
  }

  else
    board.en_passant = no_sq;
}

void print_board() {
  printf("\n");
  for (int rank = 0; rank < 8; rank ++) {
    for (int file = 0; file < 8; file ++) {
      int square = rank * 8 + file, piece = -1;

      if (!file) {
        printf(" %d ", 8 - rank);
      }

      piece = board.pieces[square];

      printf(" %c", (!piece) ? '.' : piece);
    }
    printf("\n");
  }
  printf("\n    a b c d e f g h\n\n");

  printf("Side: %d\n", board.side);
  printf("Castle: %c%c%c%c\n", board.castle[0]
                             , board.castle[1]
                             , board.castle[2]
                             , board.castle[3]);
  printf("En Passant: %s\n", square_to_coords[board.en_passant]);  
}
