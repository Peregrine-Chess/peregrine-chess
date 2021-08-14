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

void print_move(int move) {
    printf("%s%s%c\n",  square_to_coords[get_move_start(move)],
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
        
    } else {
        if (get_move_capture(move))
            make_move(move, all_moves);
        else return 0;
    }
}