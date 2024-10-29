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

        if(possibleJumps()){
            std::cout<<"Possible jump";
            setCurrentPiece(x1, y1);
        }
        else {
            changePlayer();
        }
        return true;
    }
    return false;
}

bool Board::isMoveValid(int x1, int y1) {
    if (x1 < 0 && x1 >= boardWidth && y1 < 0 && y1 >= boardHeight && board[x1][y1] != " " && (x1 + y1) % 2 != 0) {
        return false;
    }

    if(isKing()){
        return isMoveValidByKing(x1, y1);
    }else{
        return isMoveValidByPiece(x1, y1);
    }
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

bool Board::isMoveValidByKing(int x1, int y1) {
    int rowDirection = (x1 > currentPiece.getRow()) ? 1 : -1;
    int colDirection = (y1 > currentPiece.getCol()) ? 1 : -1;

    bool hasMetOpponent = false;
    int opponentPieceRow = -1;
    int opponentPieceCol = -1;

    if (std::abs(x1 - currentPiece.getRow()) != std::abs(y1 - currentPiece.getCol())) {
        return false;
    }

    int currentRow = currentPiece.getRow() + rowDirection;
    int currentCol = currentPiece.getCol() + colDirection;
    std::string piece = "P" + std::string(1, currentPlayer) + "P";
    std::string king = "P" + std::string(1, currentPlayer) + "K";

    while (currentRow != x1 && currentCol != y1) {
        if (board[currentRow][currentCol] != " ") {
            if (hasMetOpponent || board[currentRow][currentCol] == piece || board[currentRow][currentCol] == king) {
                return false;
            }
            hasMetOpponent = true;
            opponentPieceRow = currentRow;
            opponentPieceCol = currentCol;
        }
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    if (hasMetOpponent) {
        board[opponentPieceRow][opponentPieceCol] = " ";
    }

    return true;
}

bool Board::isMoveValidByPiece(int x1, int y1) {
    int step = (currentPlayer == 'B') ? 1 : -1;
    if(x1 == currentPiece.getRow() + step && abs(y1 - currentPiece.getCol()) == 1){
        return true;
    }
    if (abs(x1 - currentPiece.getRow()) == 2 && abs(y1 - currentPiece.getCol()) == 2) {
        if (isJump(x1, y1)) {
            return true;
        }
    }
    return false;
}

bool Board::possibleJumps() {
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (auto& direction : directions) {
        int dRow = direction[0];
        int dCol = direction[1];

        if (isKing()) {
            int currentRow = currentPiece.getRow() + dRow;
            int currentCol = currentPiece.getCol() + dCol;
            bool hasMetOpponent = false;

            while (currentRow >= 0 && currentRow < boardWidth && currentCol >= 0 && currentCol < boardHeight) {
                if (board[currentRow][currentCol] == opponent && board[currentRow][currentCol] == opponentK) {
                    if (hasMetOpponent) break;
                    hasMetOpponent = true;
                } else if (board[currentRow][currentCol] == " " && hasMetOpponent) {
                    return true;
                } else if (board[currentRow][currentCol] != " ") {
                    break;
                }

                currentRow += dRow;
                currentCol += dCol;
            }
        } else {
            int capRow = currentPiece.getRow() + dRow;
            int capCol = currentPiece.getCol() + dCol;
            int destRow = currentPiece.getRow() + 2 * dRow;
            int destCol = currentPiece.getCol() + 2 * dCol;

            if (destRow >= 0 && destRow < boardHeight && destCol >= 0 && destCol < boardWidth &&
                board[capRow][capCol] == opponent && board[capRow][capCol] == opponentK && board[destRow][destCol] == " ") {
                return true;
            }
        }
    }
    return false;
}

bool Board::isKing() {
    std::string value = board[currentPiece.getRow()][currentPiece.getCol()];
    if(value == "PBK" || value == "PRK"){
        return true;
    }
    return false;
}

