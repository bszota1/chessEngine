#include "position.hpp"

#include <sstream>
#include <cctype>
#include "../core/bitboard.hpp"
#include "../core/zobrist.hpp"

void Position::parseFen(const std::string& fen) {
    for (int i{}; i < 2; i++) {
        for (int j{}; j < 6; j++) {
            pieces[i][j] = 0ULL;
        }
            occupancy[i] = 0ULL;
    }
    zobristKey = 0ULL;

    sideToMove = WHITE;
    enPassantSquare = SQ_NONE;
    castlingRights = 0;
    halfMoveClock = 0;

    if (st) delete st;
    st = new StateInfo();
    st -> previous = nullptr;

    std::stringstream ss(fen);
    std::string piecesPart , sidePart , castlePart , epPart;
    int halfMove , fullMove;
    ss >> piecesPart >> sidePart >> castlePart >> epPart >> halfMove >> fullMove;

    int rank = 7;
    int file = 0;

    for (char c : piecesPart) {
        if (c == '/') {
            rank--;
            file = 0;
        } else if (isdigit(c)) {
            file += (c - '0');
        } else {
            Color side = isupper(c) ? WHITE : BLACK;
            PieceType type;
            char lowerC = tolower(c);

            if (lowerC == 'p')      type = PAWN;
            else if (lowerC == 'n') type = KNIGHT;
            else if (lowerC == 'b') type = BISHOP;
            else if (lowerC == 'r') type = ROOK;
            else if (lowerC == 'q') type = QUEEN;
            else if (lowerC == 'k') type = KING;
            else continue;

            Square sq = static_cast<Square>(rank * 8 + file);
            putPiece(side, type, sq);
            file++;
        }
    }

    sideToMove = (sidePart == "w") ? WHITE : BLACK;
    if (sideToMove == BLACK) zobristKey ^= Zobrist::sideKey;

    if (castlePart != "-") {
        for (char c : castlePart) {
            if (c == 'K') castlingRights |= WHITE_SHORT;
            if (c == 'Q') castlingRights |= WHITE_LONG;
            if (c == 'k') castlingRights |= BLACK_SHORT;
            if (c == 'q') castlingRights |= BLACK_LONG;
        }
    }
    zobristKey ^= Zobrist::castleKeys[castlingRights];


    if (epPart != "-") {
        int f = epPart[0] - 'a';
        int r = epPart[1] - '1';
        enPassantSquare = static_cast<Square>(r * 8 + f);
        zobristKey ^= Zobrist::enPassantKeys[f];
    }


    halfMoveClock = halfMove;
    combinedOccupancy = occupancy[WHITE] | occupancy[BLACK];

    st->castlingRights = castlingRights;
    st->epSquare = enPassantSquare;
    st->halfMoveClock = halfMoveClock;
    st->zobristKey = zobristKey;

}

void Position::putPiece(Color side, PieceType type, Square sq) {
    Bitboards::setBit(pieces[side][type], sq);
    Bitboards::setBit(occupancy[side], sq);
    zobristKey ^= Zobrist::pieceKeys[side][type][sq];
}

BitBoard Position::getAttacksTo(Square sq, Color side) {
    BitBoard attacks = 0ULL;
    Color opp = (side == WHITE) ? BLACK : WHITE;

    attacks |= (PawnAttacks[side][sq] & pieces[opp][PAWN]);
    attacks |= (KnightAttacks[sq] & pieces[opp][KNIGHT]);
    attacks |= (KingAttacks[sq] & pieces[opp][KING]);

    return attacks;
}

