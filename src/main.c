/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <bitboard.h>
#include <attacks.h>
#include <random.h>
#include <magic.h>
#include <log.h>
#include <board.h>
#include <misc.h>
#include <movegen.h>
#include <move.h>

int main() {
    // init EVERYTHING
    init_all();
    
    int move = encode_move(d7, e8, P, Q, 1, 0, 0, 0);

    int start_square = get_move_source(move);
    int target_square = get_move_target(move);
    int piece = get_move_piece(move);
    int promoted_piece = get_move_promoted(move);

    printf("start square: %s\n", square_to_coords[start_square]);
    printf("target square: %s\n", square_to_coords[target_square]);
    printf("piece: %c\n", ascii_pieces[piece]);
    printf("piece: %c\n", ascii_pieces[promoted_piece]);
    printf("capture flag: %d\n", get_move_capture(move) ? 1 : 0);
    printf("double pawn push flag: %d\n", get_move_double(move) ? 1 : 0);
    printf("enpassant flag: %d\n", get_move_enpassant(move) ? 1 : 0);
    printf("castling flag: %d\n", get_move_castling(move) ? 1 : 0);
    
    return 0;
}
