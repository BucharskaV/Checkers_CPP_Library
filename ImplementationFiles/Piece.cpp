//
// Created by User on 10/27/2024.
//

#include "../Headers/Piece.h"


Piece::Piece(int row, int col, char player)
        : row(row), col(col), player(player) {}

Piece::Piece() {
}

int Piece::getRow() const {
    return row;
}

void Piece::setRow(int row) {
    Piece::row = row;
}

int Piece::getCol() const {
    return col;
}

void Piece::setCol(int col) {
    Piece::col = col;
}

const char &Piece::getPlayer() const {
    return player;
}

void Piece::setPlayer(const char &player) {
    Piece::player = player;
}

