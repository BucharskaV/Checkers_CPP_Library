//
// Created by User on 10/27/2024.
//

#ifndef UTP_PRO1_S30853_C_BOARD_H
#define UTP_PRO1_S30853_C_BOARD_H

#include <vector>
#include <string>
#include "../Headers/Piece.h"
class Board {
private:
    std::vector<std::vector<std::string>> board;
    int boardWidth;
    int boardHeight;
    Piece currentPiece;
    char currentPlayer;
    std::string opponent, opponentK;
    std::string winner;
public:
    Board();
    ~Board();
    std::string getBoardCellState(int row, int col) ;
    int getBoardWidth() const;
    int getBoardHeight() const;
    void resetParameters();
    bool isMoveValid(int x1, int y1);
    bool isJump(int x1, int y1);
    void isTimeBecomeAKing(int x, int y);
    bool movePiece(int x1, int y1);
    void changePlayer();
    bool isGameOver();
    bool findPiece(std::string piece);
    bool setCurrentPiece();

    const char &getCurrentPlayer() const;

    void setCurrentPlayer(const char &currentPlayer);

    bool setCurrentPiece(int x, int y);

    const std::string &getWinner() const;

    void setWinner(const std::string &winner);
};


#endif //UTP_PRO1_S30853_C_BOARD_H
