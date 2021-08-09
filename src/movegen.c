/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https:
*/

#include <movegen.h>

void gen_moves() {
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
                            printf("%s%sq  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sr  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sb  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sn  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("%s%s   pawn push\n", square_to_coords[start_square], square_to_coords[target_square]);
                            if ((start_square >= a2 && start_square <= h2) && !get_bit(occupancies[BOTH], (target_square - 8)))
                                printf("%s%s   double pawn push\n", square_to_coords[start_square], square_to_coords[target_square - 8]);
                        }
                    }

                    attacks = pawn_attacks[side][start_square] & occupancies[BLACK];

                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);

                        if (start_square >= a7 && start_square <= h7) {
                            printf("%s%sq  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sr  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sb  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sn  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else
                            printf("%s%s   pawn capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                        
                        pop_bit(attacks, target_square);
                    }

                    if (en_passant != no_sq) {
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);
                        
                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            printf("%s%s  pawn en_passant capture\n", square_to_coords[start_square], square_to_coords[target_en_passant]);
                        }
                    }
                    
                    pop_bit(bitboard, start_square);
                }
            }
            
            if (piece == K) {
                
                if (castle & WK) {
                    
                    if (!get_bit(occupancies[BOTH], f1) && !get_bit(occupancies[BOTH], g1)) {
                        
                        if (!is_square_attacked(e1, BLACK) && !is_square_attacked(f1, BLACK) && !is_square_attacked(g1, BLACK)) {
                            printf("e1g1   castling move\n");
                        }
                    }
                }
                
                if (castle & WQ) {
                    if (!get_bit(occupancies[BOTH], d1) && !get_bit(occupancies[BOTH], c1) && !get_bit(occupancies[BOTH], b1)) {
                        if (!is_square_attacked(d1, BLACK) && !is_square_attacked(c1, BLACK) && !is_square_attacked(e1, BLACK)) {
                            printf("e1c1   castling move\n");
                        }
                    }
                }
            }
        } else {
            if (piece == p) {
                while (bitboard) {
                    start_square = get_least_significant_first_bit(bitboard);
                    
                    target_square = start_square + 8;
                    
                    if (!(target_square > h1) && !get_bit(occupancies[BOTH], target_square)) {
                        if (start_square >= a2 && start_square <= h2)
                        {
                            printf("%s%sq  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sr  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sb  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sn  pawn promotion\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("%s%s   pawn push\n", square_to_coords[start_square], square_to_coords[target_square]);
                            
                            if ((start_square >= a7 && start_square <= h7) && !get_bit(occupancies[BOTH], (target_square + 8)))
                                printf("%s%s   double pawn push\n", square_to_coords[start_square], square_to_coords[target_square + 8]);
                        }
                    }

                    attacks = pawn_attacks[side][start_square] & occupancies[WHITE];

                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);
                        
                        if (start_square >= a2 && start_square <= h2)
                        {
                            printf("%s%sq  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sr  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sb  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("%s%sn  pawn promotion capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("%s%s   pawn capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                        }
                        pop_bit(attacks, target_square);
                    }

                    if (en_passant != no_sq) {
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);

                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            printf("%s%s  pawn en_passant capture\n", square_to_coords[start_square], square_to_coords[target_en_passant]);
                        }
                    }

                    pop_bit(bitboard, start_square);
                }
            }

            if (piece == k) {
                
                if (castle & BK) {
                    
                    if (!get_bit(occupancies[BOTH], f8) && !get_bit(occupancies[BOTH], g8)) {
                        
                        if (!is_square_attacked(e8, WHITE) && !is_square_attacked(f8, WHITE) && !is_square_attacked(g8, WHITE)) {
                            printf("e8g8 castling move\n");
                        }
                    }
                }
                
                if (castle & BQ) {
                    if (!get_bit(occupancies[BOTH], d8) && !get_bit(occupancies[BOTH], c8) && !get_bit(occupancies[BOTH], b8)) {
                        if (!is_square_attacked(d8, WHITE) && !is_square_attacked(c8, WHITE) && !is_square_attacked(e8, WHITE)) {
                            printf("e8c8 castling move\n");
                        }
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
                        printf("%s%s   piece quiet move\n", square_to_coords[start_square], square_to_coords[target_square]);
                    else
                        printf("%s%s   piece capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                
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
                        printf("%s%s   piece quiet move\n", square_to_coords[start_square], square_to_coords[target_square]);
                    else
                        printf("%s%s   piece capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                    
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
                        printf("%s%s   piece quiet move\n", square_to_coords[start_square], square_to_coords[target_square]);
                    else
                        printf("%s%s   piece capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                    
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
                        printf("%s%s   piece quiet move\n", square_to_coords[start_square], square_to_coords[target_square]);
                    else
                        printf("%s%s   piece capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                    
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
                        printf("%s%s   piece quiet move\n", square_to_coords[start_square], square_to_coords[target_square]);
                    else
                        printf("%s%s   piece capture\n", square_to_coords[start_square], square_to_coords[target_square]);
                    
                    pop_bit(attacks, target_square);
                }

                pop_bit(bitboard, start_square);
            }
        }
    }
}