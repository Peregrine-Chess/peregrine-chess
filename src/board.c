/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <board.h>
#include <hashkeys.h>
#include <data.h>

int sq_120_sq_64[BOARD_NUM_SQUARES];
int sq_64_sq_120[64];

int files_board[BOARD_NUM_SQUARES];
int ranks_board[BOARD_NUM_SQUARES];

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
    pos->material[i] = 0;
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

  update_list_material(pos);

  return 0;
}

void update_list_material(BOARD *pos) {
  for (int i = 0; i < BOARD_NUM_SQUARES; i ++) {
    int sq = i;
    int piece = pos->pieces[i];
    if (piece != OFFBOARD && piece != EMPTY) {
      int color = piece_color[piece];
      if (piece_big[piece] == TRUE) pos->big_pieces[color] ++;
      if (piece_minor[piece] == TRUE) pos -> minor_pieces[color] ++;
      if (piece_major[piece] == TRUE) pos -> major_pieces[color] ++;
    
      pos->material[color] += piece_value[piece];

      pos->piece_list[piece][pos->piece_num[piece]] = sq;
      pos->piece_num[piece] ++;

      if (piece == wK) pos->king_sq[WHITE] = sq;
      if (piece == bK) pos->king_sq[BLACK] = sq;

      if (piece == wP) {
        SET_BIT_MASK(pos->pawns[WHITE], sq_120_sq_64[sq]);
        SET_BIT_MASK(pos->pawns[BOTH], sq_120_sq_64[sq]);
      } else if (piece == bP) {
        SET_BIT_MASK(pos->pawns[BLACK], sq_120_sq_64[sq]);
        SET_BIT_MASK(pos->pawns[BOTH], sq_120_sq_64[sq]);
      }
    }
  }
}

int check_board(BOARD *pos) {
  int t_piece_num[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int t_big_pieces[2] = { 0, 0 };
  int t_major_pieces[2] = { 0, 0 };
  int t_minor_pieces[2] = { 0, 0 };
  int t_material[2] = { 0, 0 };

  int sq64, t_piece, t_pce_num, sq120, color;

  Bitboard t_pawns[3] = { 0ULL, 0ULL, 0ULL };

  t_pawns[WHITE] = pos->pawns[WHITE];
  t_pawns[BLACK] = pos->pawns[BLACK];
  t_pawns[BOTH] = pos->pawns[BOTH];

  for (t_piece = wP; t_piece < bK; t_piece ++) {
    for (t_pce_num = 0; t_pce_num < pos->piece_num[t_piece]; t_pce_num ++) {
      sq120 = pos->piece_list[t_piece][t_pce_num];
      ASSERT(pos->pieces[sq120] == t_piece);
    }
  }

  for (sq64 = 0; sq64 < 64; sq64 ++) {
    sq120 = sq_64_sq_120[sq64];
    t_piece = pos->pieces[sq120];
    t_piece_num[t_piece] ++;
    color = piece_color[t_piece];
    if (piece_big[t_piece] == TRUE) t_big_pieces[color] ++;
    if (piece_minor[t_piece] == TRUE) t_minor_pieces[color] ++;
    if (piece_major[t_piece] == TRUE) t_major_pieces[color] ++;

    t_material[color] += piece_value[t_piece];
  }

  for (t_piece = wP; t_piece <= bK; t_piece ++) {
    ASSERT(t_piece_num[t_piece] == pos->piece_num[t_piece]);
  }

  int pawn_count = pop_count(t_pawns[WHITE]);
  ASSERT(pawn_count == pos->piece_num[wP]);
  pawn_count = pop_count(t_pawns[BLACK]);
  ASSERT(pawn_count == pos->piece_num[bP]);
  pawn_count = pop_count(t_pawns[BOTH]);
  ASSERT(pawn_count == (pos->piece_num[bP] + pos->piece_num[wP]));

  while (t_pawns[WHITE]) {
    sq64 = pop_lsb(&t_pawns[WHITE]);
    ASSERT(pos->pieces[sq_64_sq_120[sq64]] == wP);
  }

  while (t_pawns[BLACK]) {
    sq64 = pop_lsb(&t_pawns[BLACK]);
    ASSERT(pos->pieces[sq_64_sq_120[sq64]] == bP);
  }

  while (t_pawns[BOTH]) {
    sq64 = pop_lsb(&t_pawns[BOTH]);
    ASSERT((pos->pieces[sq_64_sq_120[sq64]] == bP) || (pos->pieces[sq_64_sq_120[sq64]] == wP));
  }

  ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
  ASSERT(t_minor_pieces[WHITE] == pos->minor_pieces[WHITE] && t_minor_pieces[BLACK] == pos->minor_pieces[BLACK]);
  ASSERT(t_major_pieces[WHITE] == pos->major_pieces[WHITE] && t_major_pieces[BLACK] == pos->major_pieces[BLACK]);
  ASSERT(t_big_pieces[WHITE] == pos->big_pieces[WHITE] && t_big_pieces[BLACK] == pos->big_pieces[BLACK]);

  ASSERT(pos->side == WHITE || pos->side == BLACK);
  ASSERT(generate_pos_key(pos) == pos->pos_key);

  ASSERT(pos->en_passant == no_sq || (ranks_board[pos->en_passant] == RANK_6 && pos->side == WHITE) 
        || (ranks_board[pos->en_passant] == RANK_3 && pos->side == BLACK));

  ASSERT(pos->pieces[pos->king_sq[WHITE]]== wK);
  ASSERT(pos->pieces[pos->king_sq[BLACK]] == bK);

  return TRUE;
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
