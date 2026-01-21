#pragma once

#include "types.hpp"

#ifdef _MSC_VER
#include <intrin.h>
#endif

const BitBoard FileAMask = 0x0101010101010101ULL;
const BitBoard FileBMask = FileAMask << 1;
const BitBoard FileGMask = FileAMask << 6;
const BitBoard FileHMask = FileAMask << 7;

const BitBoard Rank1Mask = 0xFFULL;
const BitBoard Rank4Mask = Rank1Mask << (8 * 3);
const BitBoard Rank5Mask = Rank1Mask << (8 * 4);
const BitBoard Rank8Mask = Rank1Mask << (8 * 7);

namespace Bitboards {

    inline bool getBit(BitBoard bb, Square sq) {
        return bb & (1ULL << sq);
    }

    inline void setBit(BitBoard& bb, Square sq) {
        bb |= (1ULL << sq);
    }

    inline void clearBit(BitBoard& bb, Square sq) {
        bb &= ~(1ULL << sq);
    }
    inline int count(BitBoard bb) {
#ifdef _MSC_VER
        return (int)__popcnt64(bb);
#else
        return __builtin_popcountll(bb);
#endif
    }
    inline Square lsb(BitBoard bb) {
#ifdef _MSC_VER
        unsigned long index;
        _BitScanForward64(&index, bb);
        return static_cast<Square>(index);
#else
        return static_cast<Square>(__builtin_ctzll(bb));
#endif
    }

    inline Square popLSB(BitBoard& bb) {
        Square s = lsb(bb);
        bb &= (bb - 1);
        return s;
    }
}

extern BitBoard KnightAttacks[64];
extern BitBoard KingAttacks[64];
extern BitBoard PawnAttacks[COLOR_NB][64];

void initBitboards();

