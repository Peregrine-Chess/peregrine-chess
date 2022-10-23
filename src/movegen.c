/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <movegen.h>

void gen_moves(moves *move_list) {
    move_list->count = 0;
    int start_square, target_square;
    
    Bitboard bitboard, attacks;

    for (int piece = P; piece <= k; piece++) {
        bitboard = bitboards[piece];
        
        if (side == WHITE) { 
            if (piece == P) { 
                while (bitboard) {
                    start_square = get_least_significant_first_bit(bitboard);
                    
                    target_square = start_square - 8;
                    
                    if (!(target_square < a8) && !get_bit(occupancies[BOTH], target_square)) {
                        if (start_square >= a7 && start_square <= h7) {                            
                            add_move(move_list, encode_move(start_square, target_square, piece, Q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, R, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, B, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, N, 0, 0, 0, 0));
                        } else { 
                            add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                            
                            if ((start_square >= a2 && start_square <= h2) && !get_bit(occupancies[BOTH], (target_square - 8)))
                                add_move(move_list, encode_move(start_square, (target_square - 8), piece, 0, 0, 1, 0, 0));
                        }
                    }
                    
                    attacks = pawn_attacks[side][start_square] & occupancies[BLACK];
                    
                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);
                        
                        if (start_square >= a7 && start_square <= h7) {
                            add_move(move_list, encode_move(start_square, target_square, piece, Q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, R, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, B, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, N, 1, 0, 0, 0));
                        } else
                            add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                        
                        pop_bit(attacks, target_square);
                    }
                    
                    if (en_passant != no_sq) {
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);
                        
                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            add_move(move_list, encode_move(start_square, target_en_passant, piece, 0, 1, 0, 1, 0));
                        }
                    }
                    
                    pop_bit(bitboard, start_square);
                }
            }
            
            
            if (piece == K) {
                if (castle & WK) {
                    if (!get_bit(occupancies[BOTH], f1) && !get_bit(occupancies[BOTH], g1)) {
                        if (!is_square_attacked(f1, BLACK) && !is_square_attacked(g1, BLACK))
                            add_move(move_list, encode_move(e1, g1, piece, 0, 0, 0, 0, 1));
                    }
                }
                
                if (castle & WQ) {
                    if (!get_bit(occupancies[BOTH], d1) && !get_bit(occupancies[BOTH], c1)) {
                        if (!is_square_attacked(d1, BLACK) && !is_square_attacked(c1, BLACK))
                            add_move(move_list, encode_move(e1, c1, piece, 0, 0, 0, 0, 1));
                    }
                }
            }
        } else {
            if (piece == p) {
                while (bitboard) {
                    start_square = get_least_significant_first_bit(bitboard);
                
                    target_square = start_square + 8;
                        
                    if (!(target_square > h1) && !get_bit(occupancies[BOTH], target_square)) {
                        if (start_square >= a2 && start_square <= h2) {
                            add_move(move_list, encode_move(start_square, target_square, piece, q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, r, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, b, 0, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, n, 0, 0, 0, 0));
                        } else {
                            add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
    
                            if ((start_square >= a7 && start_square <= h7) && !get_bit(occupancies[BOTH], (target_square + 8)))
                                add_move(move_list, encode_move(start_square, (target_square + 8), piece, 0, 0, 1, 0, 0));
                        }
                    }

                    attacks = pawn_attacks[side][start_square] & occupancies[WHITE];
   
                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);
                    
                        if (start_square >= a2 && start_square <= h2) {
                            add_move(move_list, encode_move(start_square, target_square, piece, q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, r, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, b, 1, 0, 0, 0));
                            add_move(move_list, encode_move(start_square, target_square, piece, n, 1, 0, 0, 0));
                        } else  
                            add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                        
                        pop_bit(attacks, target_square);
                    }
                    
                    if (en_passant != no_sq) {  
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);

                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            add_move(move_list, encode_move(start_square, target_en_passant, piece, 0, 1, 0, 1, 0));
                        }
                    }
                    
                    pop_bit(bitboard, start_square);
                }
            }

            if (piece == k) {
                if (castle & BK) {
                    if (!get_bit(occupancies[BOTH], f8) && !get_bit(occupancies[BOTH], g8)) {
                        if (!is_square_attacked(f8, WHITE) && !is_square_attacked(g8, WHITE))
                            add_move(move_list, encode_move(e8, g8, piece, 0, 0, 0, 0, 1));
                    }
                }
                
                if (castle & BQ) {
                    if (!get_bit(occupancies[BOTH], d8) && !get_bit(occupancies[BOTH], c8)) { 
                        if (!is_square_attacked(d8, WHITE) && !is_square_attacked(c8, WHITE))
                            add_move(move_list, encode_move(e8, c8, piece, 0, 0, 0, 0, 1));
                    }
                }
            }
        }
    
        if ((side == WHITE) ? piece == N : piece == n) {
            while (bitboard) {
                start_square = get_least_significant_first_bit(bitboard);
                
                attacks = knight_attacks[start_square] & ((side == WHITE) ? ~occupancies[WHITE] : ~occupancies[BLACK]);
                
                while (attacks) {
                    target_square = get_least_significant_first_bit(attacks);    
                     
                    if (!get_bit(((side == WHITE) ? occupancies[BLACK] : occupancies[WHITE]), target_square))
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                    else    
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                    
                    pop_bit(attacks, target_square);
                }
                
                pop_bit(bitboard, start_square);
            }
        }
        
        if ((side == WHITE) ? piece == B : piece == b) {
            while (bitboard) {
                start_square = get_least_significant_first_bit(bitboard);
                
                attacks = get_bishop_attacks(start_square, occupancies[BOTH]) & ((side == WHITE) ? ~occupancies[WHITE] : ~occupancies[BLACK]);
                
                while (attacks) {
                    target_square = get_least_significant_first_bit(attacks);    
                    
                    if (!get_bit(((side == WHITE) ? occupancies[BLACK] : occupancies[WHITE]), target_square))
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                    else
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                
                    pop_bit(attacks, target_square);
                }
            
                pop_bit(bitboard, start_square);
            }
        }
        
        if ((side == WHITE) ? piece == R : piece == r) {
            while (bitboard) {
                start_square = get_least_significant_first_bit(bitboard);
                
                attacks = get_rook_attacks(start_square, occupancies[BOTH]) & ((side == WHITE) ? ~occupancies[WHITE] : ~occupancies[BLACK]);
                
                while (attacks) {
                    target_square = get_least_significant_first_bit(attacks);    
                    
                    if (!get_bit(((side == WHITE) ? occupancies[BLACK] : occupancies[WHITE]), target_square))
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                    else    
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                    
                    pop_bit(attacks, target_square);
                }
                
                pop_bit(bitboard, start_square);
            }
        }
    
        if ((side == WHITE) ? piece == Q : piece == q) {
            while (bitboard) {
                start_square = get_least_significant_first_bit(bitboard);
                
                attacks = get_queen_attacks(start_square, occupancies[BOTH]) & ((side == WHITE) ? ~occupancies[WHITE] : ~occupancies[BLACK]);
                
                while (attacks) {
                    target_square = get_least_significant_first_bit(attacks);    
                    
                    if (!get_bit(((side == WHITE) ? occupancies[BLACK] : occupancies[WHITE]), target_square))
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                    else    
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                    
                    pop_bit(attacks, target_square);
                }
                
                pop_bit(bitboard, start_square);
            }
        }

        if ((side == WHITE) ? piece == K : piece == k) {
            while (bitboard) {
                start_square = get_least_significant_first_bit(bitboard);
                
                attacks = king_attacks[start_square] & ((side == WHITE) ? ~occupancies[WHITE] : ~occupancies[BLACK]);
            
                while (attacks) {
                    target_square = get_least_significant_first_bit(attacks);    
                    
                    if (!get_bit(((side == WHITE) ? occupancies[BLACK] : occupancies[WHITE]), target_square))
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 0, 0, 0, 0));
                    else
                        add_move(move_list, encode_move(start_square, target_square, piece, 0, 1, 0, 0, 0));
                    
                    pop_bit(attacks, target_square);
                }

                pop_bit(bitboard, start_square);
            }
        }
    }
}
