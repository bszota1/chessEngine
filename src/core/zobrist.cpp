#include "zobrist.hpp"
#include <random>

void Zobrist::init() {
    std::mt19937_64 rng(1234567);

    for (int i{}; i<2; i++) {
        for (int j{}; j<6; j++) {
            for (int k{}; k<64; k++) {
                pieceKeys[i][j][k] = rng();
            }
        }
    }

    sideKey = rng();
    for (int i{}; i<16; i++) {
        castleKeys[i] = rng();
    }

    for (int i{}; i<8; i++) {
        enPassantKeys[i] = rng();
    }
}
