#include "bitboard.hpp"

BitBoard KnightAttacks[64];
BitBoard KingAttacks[64];
BitBoard PawnAttacks[COLOR_NB][64];

BitBoard genKnightAttacks(Square sq) {
    BitBoard attacks = 0;
    BitBoard b = 1ULL << sq;

    if (b & ~(FileHMask))  attacks |= (b << 17);
    if (b & ~(FileAMask)) attacks |= (b << 15);
    if (b & ~(FileGMask | FileHMask)) attacks |= (b << 10);
    if (b & ~(FileAMask | FileBMask)) attacks |= (b << 6);

    if (b & ~(FileAMask))                attacks |= (b >> 17);
    if (b & ~(FileHMask))                attacks |= (b >> 15);
    if (b & ~(FileAMask | FileBMask))    attacks |= (b >> 10);
    if (b & ~(FileGMask | FileHMask))    attacks |= (b >> 6);

    return attacks;
}

BitBoard genKingAttacks(Square sq) {
    BitBoard attacks = 0;
    BitBoard b = 1ULL << sq;

    if (b & ~FileHMask) {
        attacks |= (b << 1) | (b <<9) | (b >> 7);
    }
    if (b & ~FileAMask) {
        attacks |= (b >> 1) | (b >> 9) | (b << 7);
    }
    attacks |= (b << 8) | (b >> 8);

    return attacks;
}

void initBitboards() {
    for (int i = 0; i < 64; ++i) {
        Square sq = static_cast<Square>(i);

        KnightAttacks[i] = genKnightAttacks(sq);
        KingAttacks[i] = genKingAttacks(sq);

        BitBoard b = 1ULL << sq;
        if (b & ~FileAMask) PawnAttacks[WHITE][i] |= (b << 7);
        if (b & ~FileHMask) PawnAttacks[WHITE][i] |= (b << 9);

        if (b & ~FileHMask) PawnAttacks[BLACK][i] |= (b >> 7);
        if (b & ~FileAMask) PawnAttacks[BLACK][i] |= (b >> 9);
    }

}