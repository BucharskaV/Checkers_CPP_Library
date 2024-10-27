//
// Created by User on 10/27/2024.
//

#ifndef UTP_PRO1_S30853_C_PIECE_H
#define UTP_PRO1_S30853_C_PIECE_H

#include <string>

class Piece {
private:
    int row;
    int col;
    char player;
public:
    Piece(int row, int col, char player);
    Piece();

    int getRow() const;

    void setRow(int row);

    int getCol() const;

    void setCol(int col);

    const char &getPlayer() const;

    void setPlayer(const char &player);
};


#endif //UTP_PRO1_S30853_C_PIECE_H
