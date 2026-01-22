#pragma once
#include <cstdint>

namespace Zobrist {
    extern uint64_t pieceKeys[2][6][64];
    extern uint64_t sideKey;
    extern uint64_t castleKeys[16];
    extern uint64_t enPassantKeys[8];
    void init();
}

