/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <perft.h>

long nodes;

void perft_driver(int depth) {
    if (depth == 0) {
        nodes++;
        return ;
    }

    moves move_list[1];

    gen_moves(move_list);

    for (int move_count = 0; move_count < move_list->count; move_count++) {   
        copy_board();
        if (!make_move(move_list->moves[move_count], all_moves))
            continue;
        
        perft_driver(depth - 1);

        restore_board();
    }
}

void perft_test(int depth) {
    printf("\n     Performance test\n\n");

    moves move_list[1];

    gen_moves(move_list);

    long start = get_time_ms();
    
    for (int move_count = 0; move_count < move_list->count; move_count++) {   
        copy_board();
        
        if (!make_move(move_list->moves[move_count], all_moves))
            continue;
        
        long cummulative_nodes = nodes;
        
        perft_driver(depth - 1);
        
        long old_nodes = nodes - cummulative_nodes;
        
        restore_board();
        
        printf("     move: %s%s%c  nodes: %ld\n", square_to_coords[get_move_start(move_list->moves[move_count])],
                                                 square_to_coords[get_move_target(move_list->moves[move_count])],
                                                 get_move_promoted(move_list->moves[move_count]) ? promoted_pieces[get_move_promoted(move_list->moves[move_count])] : ' ',
                                                 old_nodes);
    }
    
    printf("\n    Depth: %d\n", depth);
    printf("    Nodes: %ld\n", nodes);
    printf("    Time: %ldms\n\n", get_time_ms() - start);
}