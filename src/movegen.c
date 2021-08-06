/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
                            printf("pawn promotion: %s%sq\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sr\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sb\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sn\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("pawn push: %s%s\n", square_to_coords[start_square], square_to_coords[target_square]);
                            if ((start_square >= a2 && start_square <= h2) && !get_bit(occupancies[BOTH], (target_square - 8)))
                                printf("double pawn push: %s%s\n", square_to_coords[start_square], square_to_coords[target_square - 8]);
                        }
                    }

                    attacks = pawn_attacks[side][start_square] & occupancies[BLACK];

                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);

                        if (start_square >= a7 && start_square <= h7) {
                            printf("pawn promotion capture: %s%sq\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sr\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sb\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sn\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else
                            printf("pawn capture: %s%s\n", square_to_coords[start_square], square_to_coords[target_square]);
                        
                        pop_bit(attacks, target_square);
                    }

                    if (en_passant != no_sq) {
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);
                        
                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            printf("pawn en_passant capture: %s%s\n", square_to_coords[start_square], square_to_coords[target_en_passant]);
                        }
                    }
                    
                    pop_bit(bitboard, start_square);
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
                            printf("pawn promotion: %s%sq\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sr\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sb\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion: %s%sn\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("pawn push: %s%s\n", square_to_coords[start_square], square_to_coords[target_square]);
                            
                            if ((start_square >= a7 && start_square <= h7) && !get_bit(occupancies[BOTH], (target_square + 8)))
                                printf("double pawn push: %s%s\n", square_to_coords[start_square], square_to_coords[target_square + 8]);
                        }
                    }

                    attacks = pawn_attacks[side][start_square] & occupancies[WHITE];

                    while (attacks) {
                        target_square = get_least_significant_first_bit(attacks);
                        
                        if (start_square >= a2 && start_square <= h2)
                        {
                            printf("pawn promotion capture: %s%sq\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sr\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sb\n", square_to_coords[start_square], square_to_coords[target_square]);
                            printf("pawn promotion capture: %s%sn\n", square_to_coords[start_square], square_to_coords[target_square]);
                        } else {
                            printf("pawn capture: %s%s\n", square_to_coords[start_square], square_to_coords[target_square]);
                        }
                        pop_bit(attacks, target_square);
                    }

                    if (en_passant != no_sq) {
                        Bitboard en_passant_attacks = pawn_attacks[side][start_square] & (1ULL << en_passant);

                        if (en_passant_attacks) {
                            int target_en_passant = get_least_significant_first_bit(en_passant_attacks);
                            printf("pawn en_passant capture: %s%s\n", square_to_coords[start_square], square_to_coords[target_en_passant]);
                        }
                    }

                    pop_bit(bitboard, start_square);
                }
            }
        }
        
        // TODO genarate knight moves
        
        // TODO generate bishop moves
        
        // TODO generate rook moves
        
        // TODO generate queen moves
        
        // TODO generate king moves
    }
}