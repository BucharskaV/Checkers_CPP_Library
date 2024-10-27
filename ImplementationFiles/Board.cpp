//
// Created by User on 10/27/2024.
//

#include <iostream>
#include "../Headers/Board.h"

Board::Board() : boardWidth(8), boardHeight(8) {
    resetParameters();
}

std::string Board::getBoardCellState(int row, int col) {
    if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth) {
        return board[row][col];
    }
    return " ";
}

int Board::getBoardWidth() const {
    return boardWidth;
}

int Board::getBoardHeight() const {
    return boardHeight;
}

void Board::resetParameters() {
    board = {
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {"PBP", " ", "PBP", " ", "PBP", " ", "PBP", " "},
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {"PRP", " ", "PRP", " ", "PRP", " ", "PRP", " "},
            {" ", "PRP", " ", "PRP", " ", "PRP", " ", "PRP"},
            {"PRP", " ", "PRP", " ", "PRP", " ", "PRP", " "}
    };
    currentPlayer = 'R';
}

bool Board::setCurrentPiece(int x, int y) {
    if(x < 0 && x >= boardHeight && y > 0 && y >= boardWidth && board[x][y]!= " " && currentPlayer == board[x][y][1]){
        currentPiece = Piece(x, y, currentPlayer);
        return true;
    }
    return false;
}

Board::~Board() {
}

const char &Board::getCurrentPlayer() const {
    return currentPlayer;
}

void Board::setCurrentPlayer(const char &currentPlayer) {
    Board::currentPlayer = currentPlayer;
}

bool Board::movePiece(int x1, int y1) {
    if (isMoveValid(x1, y1)) {
        std::swap(board[currentPiece.getRow()][currentPiece.getCol()], board[x1][y1]);
        isTimeBecomeAKing(x1, y1);
        changePlayer();
        return true;
    } else if (abs(x1 - currentPiece.getRow()) == 2 && abs(y1 - currentPiece.getCol()) == 2) {
        if (isJump(x1, y1)) {
            std::swap(board[currentPiece.getRow()][currentPiece.getCol()], board[x1][y1]);
            isTimeBecomeAKing(x1, y1);
            changePlayer();
            return true;
        }
    }
    return false;
}

bool Board::isMoveValid(int x1, int y1) {
    if (x1 < 0 && x1 >= boardHeight && y1 > 0 && y1 >= boardWidth && board[x1][y1] != " " && (x1 + y1) != 0) {
        return false;
    }

    std::string value = board[currentPiece.getRow()][currentPiece.getCol()];

    if(currentPlayer == 'B'){
        return (x1 == currentPiece.getRow() + 1 && abs(y1 - currentPiece.getCol()) == 1);
    }else if(currentPlayer == 'R'){
        return (x1 == currentPiece.getRow() - 1 && abs(y1 - currentPiece.getCol()) == 1);
    } else if(value=="PBK" ||value=="PRK"){
        return (abs(x1 - currentPiece.getRow()) == 1 && abs(x1 - currentPiece.getCol()) == 1);
    }
    return false;
}

bool Board::isJump(int x1, int y1) {
    int opponentPieceRow = (currentPiece.getRow() + y1) / 2;
    int opponentPieceCol = (currentPiece.getCol() + y1) / 2;

    std::string opponent, opponentK;
    if (currentPlayer == 'B') {
        opponent = "PRP";
        opponentK = "PRK";
    } else {
        opponent = "PBP";
        opponentK = "PBK";
    }
    if (board[opponentPieceRow][opponentPieceCol].find(opponent) != -1) {
        board[opponentPieceRow][opponentPieceCol] = " ";
        return true;
    }
    return false;
}

void Board::isTimeBecomeAKing(int x, int y) {
    if (x == 0 && board[x][y] == "PRP") {
        board[x][y] = "PRK";
    } else if (x == boardHeight - 1 && board[x][y] == "PBP") {
        board[x][y] = "PBK";
    }
}

void Board::changePlayer() {
    if(currentPlayer == 'R') currentPlayer = 'B';
    else currentPlayer = 'R';
}

