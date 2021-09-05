/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <search.h>

int eval_position() {
    int result = 0;

    for (int j = 0; j < 64; j ++) {
        if (get_bit(occupancies[BOTH], j)) {
            if (get_bit(occupancies[WHITE], j)) {
                if (get_bit(bitboards[P], j)) result += 100;
                else if (get_bit(bitboards[N], j)) result += 320;
                else if (get_bit(bitboards[B], j)) result += 330;
                else if (get_bit(bitboards[R], j)) result += 500;
                else if (get_bit(bitboards[Q], j)) result += 900;
                else result += 1316134912;
            } else {
                if (get_bit(bitboards[p], j)) result -= 100;
                else if (get_bit(bitboards[n], j)) result -= 320;
                else if (get_bit(bitboards[b], j)) result -= 330;
                else if (get_bit(bitboards[r], j)) result -= 500;
                else if (get_bit(bitboards[q], j)) result -= 900;
                else result -= 1316134912;
            }
        }
    }
    return result;
}

int minimax(int depth, int is_max, int alpha, int beta) {
    if (depth == 0) return eval_position();

    moves list[1];
    list->count = 0;
    gen_moves(list);

    if (is_max) {
        int score = -1316134912;

        for (int i = 0; i < list->count; i ++) {
            copy_board();
            make_move(list->moves[i], all_moves);
            score = MAX(
                score, 
                minimax(depth - 1, ((is_max == 1) ? 0 : 1), alpha, beta)
            );
            restore_board();   
            fprintf(stderr, "depth %d, node %d, score %d\n", depth, i, score); 
            alpha = MAX(alpha, score);
            if (beta <= alpha) {
                return score;
            }        
        }
        return score;
    } else {
        int score = 1316134912;

        for (int i = 0; i < list->count; i ++) {
            copy_board();
            make_move(list->moves[i], all_moves);
            score = MIN(
                score,
                minimax(depth - 1, ((is_max == 1) ? 0 : 1), alpha, beta)
            );
            restore_board();    
            fprintf(stderr, "depth %d, node %d, score %d\n", depth, i, score);
            beta = MIN(beta, score);        
            if (beta <= alpha)
                return score;
        }
        return score;
    }
}

int minimax_root(int depth, int is_max) {
    int best_move, best_move_found;
    if (is_max) best_move = -1316134912;
    else best_move = 1316134912;
    moves move_list[1];
    move_list->count = 0;
    gen_moves(move_list);
    for (int i = 0; i < move_list->count; i ++) {
        copy_board();
        make_move(move_list->moves[i], all_moves);
        int value = minimax(depth - 1, ((is_max) ? 0 : 1), -1316134912, 1316134912);
        restore_board();
        if ((is_max == 1) && value >= best_move) {
            best_move = value;
            best_move_found = move_list->moves[i];
        } else if ((is_max == 0) && value <= best_move) {
            best_move = value;
            best_move_found = move_list->moves[i];
        }
    }

    return best_move_found;
}

int search_position(int depth) {
    int move = minimax_root(depth, ((side == WHITE) ? 1 : 0));
    int move_made = make_move(move, all_moves);
    if (move_made) {
        const char *start_square = square_to_coords[get_move_start(move)];
        const char *target_square = square_to_coords[get_move_target(move)];
        char promoted_piece = promoted_pieces[get_move_promoted(move)];

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
