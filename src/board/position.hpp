#pragma once

#include <string>
#include "../core/types.hpp"


struct StateInfo {
    Move lastMove;
    int castlingRights;
    Square epSquare;
    int halfMoveClock;
    uint64_t zobristKey;
    StateInfo* previous;
};


class Position {
private:
    BitBoard pieces[COLOR_NB][PIECE_TYPE_NB];
    BitBoard occupancy[COLOR_NB];
    uint64_t zobristKey;

    Color sideToMove;
    Square enPassantSquare;
    int castlingRights;
    int halfMoveClock;
    BitBoard combinedOccupancy;

    StateInfo* st;
public:
    void makeMove(Move m);
    void parseFen(std::string fen);
    BitBoard getAttacksTo(Square sq, Color side);
};