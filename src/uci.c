/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <uci.h>

int uci_parse_move(char *move_string) {
    moves move_list[1];

    gen_moves(move_list);

    int start_square = (move_string[0] - 'a') + (8 - (move_string[1] - '0')) * 8;
    int target_square = (move_string[2] - 'a') + (8 - (move_string[3] - '0')) * 8;

    for (int i = 0; i < move_list->count; i ++) {
        int move = move_list->moves[i];

        if (start_square == get_move_start(move) && target_square == get_move_target(move)) {
            int promoted_piece = get_move_promoted(move);
            if (promoted_piece) {
                if ((promoted_piece == 'Q' || promoted_piece == 'q') && move_string[4] == 'q')
                    return move;
                else if ((promoted_piece == 'R' || promoted_piece == 'r') && move_string[4] == 'r')
                    return move;
                else if ((promoted_piece == 'N' || promoted_piece == 'n') && move_string[4] == 'n')
                    return move;
                else if ((promoted_piece == 'B' || promoted_piece == 'b') && move_string[4] == 'b')
                    return move;

                continue;
            }
            return move;
        }
    }
    return 0;
}
