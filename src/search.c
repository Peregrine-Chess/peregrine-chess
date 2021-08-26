/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <search.h>

int search_position(int depth) {
    srand(get_time_ms());

    moves move_list[1];

    gen_moves(move_list);

    int random = (rand() % (move_list->count - 1));
    int rand_move = move_list->moves[random];

    int move = make_move(rand_move, all_moves);
    if (move) {
        const char *start_square = square_to_coords[get_move_start(rand_move)];
        const char *target_square = square_to_coords[get_move_target(rand_move)];
        char promoted_piece = promoted_pieces[get_move_promoted(rand_move)];
        int piece = get_move_piece(move);

        if (promoted_piece) {
            printf("bestmove %s%s%c\n", start_square, target_square, promoted_piece);
        } else {
            printf("bestmove %s%s\n", start_square, target_square);
        }

        return 1;
    } else {
        return 0;
    }
}
