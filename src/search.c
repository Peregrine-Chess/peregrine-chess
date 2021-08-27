/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <search.h>

int piece_value[12] = {
    100,
    320,
    350,
    500,
    900,
    100000,
    -100,
    -320,
    -350,
    -500,
    -900,
    -100000
};

int eval_position() {
    int result = 0;

    for (int j = 0; j < 64; j ++) {
        if (get_bit(occupancies[BOTH], j)) {
            if (get_bit(occupancies[WHITE], j)) {
                if (get_bit(bitboards[P], j)) result += piece_value[0];
                else if (get_bit(bitboards[N], j)) result += piece_value[1];
                else if (get_bit(bitboards[B], j)) result += piece_value[2];
                else if (get_bit(bitboards[R], j)) result += piece_value[3];
                else if (get_bit(bitboards[Q], j)) result += piece_value[4];
                else result += piece_value[5];
            } else {
                if (get_bit(bitboards[p], j)) result -= piece_value[6];
                else if (get_bit(bitboards[n], j)) result -= piece_value[7];
                else if (get_bit(bitboards[b], j)) result -= piece_value[8];
                else if (get_bit(bitboards[r], j)) result -= piece_value[9];
                else if (get_bit(bitboards[q], j)) result -= piece_value[10];
                else result -= piece_value[11];
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
    int move = minimax_root(2, ((side == WHITE) ? 1 : 0));
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
