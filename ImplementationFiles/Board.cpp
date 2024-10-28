//
// Created by User on 10/27/2024.
//

#include <iostream>
#include <algorithm>
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
    opponent = "PBP";
    opponentK = "PBK";
}

bool Board::setCurrentPiece(int x, int y) {
    if(x >= 0 && x < boardHeight && y >= 0 && y < boardWidth && board[x][y]!= " " && currentPlayer == board[x][y][1]){
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
        board[x1][y1] = board[currentPiece.getRow()][currentPiece.getCol()];
        board[currentPiece.getRow()][currentPiece.getCol()] = " ";
        isTimeBecomeAKing(x1, y1);
        changePlayer();
        return true;
    } else if (abs(x1 - currentPiece.getRow()) == 2 && abs(y1 - currentPiece.getCol()) == 2) {
        if (isJump(x1, y1)) {
            board[x1][y1] = board[currentPiece.getRow()][currentPiece.getCol()];
            board[currentPiece.getRow()][currentPiece.getCol()] = " ";
            isTimeBecomeAKing(x1, y1);
            changePlayer();
            return true;
        }
    }
    return false;
}

bool Board::isMoveValid(int x1, int y1) {
    if (x1 < 0 && x1 >= boardWidth && y1 < 0 && y1 >= boardHeight && board[x1][y1] != " " && (x1 + y1) % 2 != 0) {
        return false;
    }

    std::string value = board[currentPiece.getRow()][currentPiece.getCol()];

    if(value == "PBP"){
        return (x1 == currentPiece.getRow() + 1 && abs(y1 - currentPiece.getCol()) == 1);
    }else if(value == "PRP"){
        return (x1 == currentPiece.getRow() - 1 && abs(y1 - currentPiece.getCol()) == 1);
    } else if(value=="PBK" ||value=="PRK"){
        return (abs(x1 - currentPiece.getRow()) == abs(y1 - currentPiece.getCol()));
    }
    return false;
}

bool Board::isJump(int x1, int y1) {
    int opponentPieceRow = (currentPiece.getRow() + x1) / 2;
    int opponentPieceCol = (currentPiece.getCol() + y1) / 2;

    if (board[opponentPieceRow][opponentPieceCol] == opponent || board[opponentPieceRow][opponentPieceCol] == opponentK) {
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
    if(currentPlayer == 'R') {
        currentPlayer = 'B';
        opponent = "PRP";
        opponentK = "PRK";
    }
    else {
        currentPlayer = 'R';
        opponent = "PBP";
        opponentK = "PBK";
    }
}

bool Board::isGameOver() {
    if(!findPiece("PBP") && !findPiece("PBK")){
        setWinner("Red");
        return true;
    } else if(!findPiece("PRP") && !findPiece("PRK")){
        setWinner("Black");
        return true;
    }
    return false;
}

const std::string &Board::getWinner() const {
    return winner;
}

void Board::setWinner(const std::string &winner) {
    Board::winner = winner;
}

bool Board::findPiece(std::string piece) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if(board[row][col] == piece){
                return true;
            }
        }
    }
    return false;
}

