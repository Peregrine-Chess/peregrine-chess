/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>
#include <hashkeys.h>
#include <data.h>

int sq_120_sq_64[BOARD_NUM_SQUARES];
int sq_64_sq_120[64];

void reset_board(BOARD *pos) {
  for (int i = 0; i < BOARD_NUM_SQUARES; i ++) {
    pos->pieces[i] = EMPTY;
  }

  for (int i = 0; i < 64; i ++) {
    pos->pieces[sq_64_sq_120[i]] = EMPTY;
  }

  for (int i = 0; i < 3; i ++) {
    pos->big_pieces[i] = 0;
    pos->major_pieces[i] = 0;
    pos->minor_pieces[i] = 0;
    pos->pawns[i] = 0ULL;
  }

  for (int i = 0; i < 13; i ++) {
    pos->piece_num[i] = 0;
  }

  pos->king_sq[WHITE] = pos->king_sq[BLACK] = no_sq;

  pos->side = BOTH;
  pos->en_passant = no_sq;
  pos->fifty_move = 0;

  pos->ply = 0;
  pos->his_ply = 0;

  pos->castle_perms = 0;

  pos->pos_key = 0ULL;
}

int parse_fen(char *fen, BOARD *pos) {
  ASSERT(fen!=NULL);
  ASSERT(pos!=NULL);

  int rank = RANK_8;
  int file = FILE_A;
  int piece = 0;
  int count = 0;
  int i = 0;
  int sq64 = 0;
  int sq120 = 0;

  reset_board(pos);

  while ((rank >= RANK_1) && *fen) {
    count = 1;
    switch (*fen) {
      case 'p': piece = bP; break;
      case 'r': piece = bR; break;
      case 'n': piece = bN; break;
      case 'b': piece = bB; break;
      case 'k': piece = bK; break;
      case 'q': piece = bQ; break;
      case 'P': piece = wP; break;
      case 'R': piece = wR; break;
      case 'N': piece = wN; break;
      case 'B': piece = wB; break;
      case 'K': piece = wK; break;
      case 'Q': piece = wQ; break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        piece = EMPTY;
        count = *fen - '0';
        break;

      case '/':
      case ' ':
        rank --;
        file = FILE_A;
        fen ++;
        continue;

      default:
        printf("FEN error \n");
        return -1;
    }

    for (i = 0; i < count; i ++) {
      sq64 = rank * 8 + file;
      sq120 = sq_64_sq_120[sq64];
      if (piece != EMPTY) {
        pos->pieces[sq120] = piece;
      }
      file++;
    }
    fen++;
  }

  ASSERT(*fen == 'w' || *fen == 'b');

  pos->side = (*fen == 'w') ? WHITE : BLACK;
  fen += 2;

  for (i = 0; i < 4; i ++) {
    if (*fen == ' ') {
      break;
    }
      switch(*fen) {
        case 'K': pos->castle_perms |= WHITE_OO; break;
        case 'Q': pos->castle_perms |= WHITE_OOO; break;
        case 'k': pos->castle_perms |= BLACK_OO; break;
        case 'q': pos->castle_perms |= BLACK_OOO; break;
        default: break;
    }
    fen++;
  }
  fen++;

  ASSERT(pos->castle_perms >=0 && pos->castle_perms <= 15);

  if (*fen != '-') {
    file = fen[0] - 'a';
    rank = fen[1] - '1';

    ASSERT(file >= FILE_A && file <= FILE_H);
    ASSERT(rank >= RANK_1 && rank <= RANK_8);

    pos->en_passant = INDEX(file, rank);
  }

  pos->pos_key = generate_pos_key(pos);

  return 0;
}

void print_board(const BOARD *pos) {
  printf("\nGame Board:\n\n");

  for (int rank = RANK_8; rank >= RANK_1; rank --) {
    printf("%d  ", rank + 1);
    for (int file = FILE_A; file <= FILE_H; file ++) {
      int sq = INDEX(file, rank);
      int piece = pos->pieces[sq];
      printf("%2c", piece_char[piece]);
    }
    printf("\n");
  }

  printf("\n   ");
  for (int file = FILE_A; file <= FILE_H; file ++) {
    printf("%2c", 'a' + file);
  }
  printf("\n\n");

  printf("--> Side: %c\n", side_char[pos->side]);
  printf("--> En Passant: %d\n", pos->en_passant);
  printf("--> Castle: %c%c%c%c\n", pos->castle_perms & WHITE_OO ? 'K' : '-',
                               pos->castle_perms & WHITE_OOO ? 'Q' : '-',
                               pos->castle_perms & BLACK_OO ? 'k' : '-',
                               pos->castle_perms & BLACK_OOO ? 'q' : '-');
  printf("--> Position Key: %lX\n", pos->pos_key);
}
