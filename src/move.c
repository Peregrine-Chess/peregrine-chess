/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <move.h>

char promoted_pieces[] = {
    [Q] = 'Q',
    [R] = 'R',
    [B] = 'B',
    [N] = 'N',
    [q] = 'q',
    [r] = 'r',
    [b] = 'b',
    [n] = 'n'
};

const int castling_rights[64] = {
     7, 15, 15, 15,  3, 15, 15, 11,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    13, 15, 15, 15, 12, 15, 15, 14
};

void print_move(int move) {
    printf("%s%s%c",  square_to_coords[get_move_start(move)],
                        square_to_coords[get_move_target(move)],
                        promoted_pieces[get_move_promoted(move)]);
}

void print_move_list(moves *move_list) {
    printf("\n    move    piece   capture   double    enpass    castling\n\n");
    
    for (int move_count = 0; move_count < move_list->count; move_count++) {
        int move = move_list->moves[move_count];
        
        printf("    %s%s%c   %c       %d         %d         %d         %d\n", square_to_coords[get_move_start(move)],
                                                                                square_to_coords[get_move_target(move)],
                                                                                promoted_pieces[get_move_promoted(move)],
                                                                                ascii_pieces[get_move_piece(move)],
                                                                                get_move_capture(move) ? 1 : 0,
                                                                                get_move_double(move) ? 1 : 0,
                                                                                get_move_enpassant(move) ? 1 : 0,
                                                                                get_move_castling(move) ? 1 : 0);
    }
    printf("\n\n    Total number of moves: %d\n\n", move_list->count);
}

void add_move(moves *move_list, int move) {
    move_list->moves[move_list->count] = move;

    move_list->count ++;
}

int make_move(int move, int move_flag) {
    if (move_flag == all_moves) {
        copy_board();

        int start_square = get_move_start(move);
        int target_square = get_move_target(move);
        int piece = get_move_piece(move);
        int promoted = get_move_promoted(move);
        int capture = get_move_capture(move);
        int is_double = get_move_double(move);
        int enpass = get_move_enpassant(move);
        int castling = get_move_castling(move);

        pop_bit(bitboards[piece], start_square);
        set_bit(bitboards[piece], target_square);

        if (capture) {
            int start_piece, end_piece;

            if (side == WHITE) {
                start_piece = p;
                end_piece = k;
            } else {
                start_piece = P;
                end_piece = K;
            }

            for (int piece = start_piece; piece <= end_piece; piece ++) {
                if (get_bit(bitboards[piece], target_square)) {
                    pop_bit(bitboards[piece], target_square);
                    break;
                }
            }
        }

        if (promoted) {
            pop_bit(bitboards[(side == WHITE) ? P : p], target_square);
            set_bit(bitboards[promoted], target_square);
        }

        if (enpass) {
            if (side == WHITE) {
                pop_bit(bitboards[p], target_square + 8);
            } else {
                pop_bit(bitboards[P], target_square - 8);
            }
        }

        en_passant = no_sq;

        if (is_double) {
            if (side == WHITE) {
                en_passant = target_square + 8;
            } else {
                en_passant = target_square - 8;
            }
        }

        if (castling) {
            switch (target_square) {
                case (g1):
                    pop_bit(bitboards[R], h1);
                    set_bit(bitboards[R], f1);
                    break;
                case (c1):
                    pop_bit(bitboards[R], a1);
                    set_bit(bitboards[R], d1);
                    break;
                case (g8):
                    pop_bit(bitboards[r], h8);
                    set_bit(bitboards[r], f8);
                    break;
                case (c8):
                    pop_bit(bitboards[r], a8);
                    set_bit(bitboards[r], d8);
                    break;
            }
        }

        castle &= castling_rights[start_square];
        castle &= castling_rights[target_square];

        memset(occupancies, 0ULL, sizeof(occupancies));
        for (int piece = P; piece <= K; piece ++)
            occupancies[WHITE] |= bitboards[piece];

        for (int piece = p; piece <= k; piece ++)
            occupancies[BLACK] |= bitboards[piece];

        occupancies[BOTH] |= occupancies[WHITE];
        occupancies[BOTH] |= occupancies[BLACK];

        if(promoted != Q && promoted != q
        && promoted != R && promoted != r
        && promoted != B && promoted != b) side ^= 1;

        if (is_square_attacked((side == WHITE) ? get_least_significant_first_bit(bitboards[k]) : get_least_significant_first_bit(bitboards[K]), side)) {
            restore_board();
            return 0;
        } else {
            return 1;
        }
    } else {
        if (get_move_capture(move))
            make_move(move, all_moves);
        else return 0;
    }
}
