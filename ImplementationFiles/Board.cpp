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
    } /*else if (abs(x1 - currentPiece.getRow()) == 2 && abs(y1 - currentPiece.getCol()) == 2) {
        if (isJump(x1, y1)) {
            board[x1][y1] = board[currentPiece.getRow()][currentPiece.getCol()];
            board[currentPiece.getRow()][currentPiece.getCol()] = " ";
            isTimeBecomeAKing(x1, y1);
            changePlayer();
            return true;
        }
    }*/
    return false;
}

bool Board::isMoveValid(int x1, int y1) {
    if (x1 < 0 && x1 >= boardWidth && y1 < 0 && y1 >= boardHeight && board[x1][y1] != " " && (x1 + y1) % 2 != 0) {
        return false;
    }

    std::string value = board[currentPiece.getRow()][currentPiece.getCol()];

    if(value == "PBK" || value == "PRK"){
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
    int startRow = currentPiece.getRow();
    int startCol = currentPiece.getCol();
    int rowDirection = (x1 > startRow) ? 1 : -1;
    int colDirection = (y1 > startCol) ? 1 : -1;

    // Track if we've encountered an opponent piece
    bool hasMetOpponent = false;
    int opponentPieceRow = -1;
    int opponentPieceCol = -1;

    // Check that the target cell is within the board and is empty
    if (x1 < 0 || x1 >= boardHeight || y1 < 0 || y1 >= boardWidth || board[x1][y1] != " ") {
        return false;
    }

    // Ensure we’re moving along a diagonal
    if (std::abs(x1 - startRow) != std::abs(y1 - startCol)) {
        return false;
    }

    int currentRow = startRow + rowDirection;
    int currentCol = startCol + colDirection;

    // Determine current player's piece and king identifiers
    std::string piece = "P" + std::string(1, currentPlayer) + "P";
    std::string king = "P" + std::string(1, currentPlayer) + "K";

    while (currentRow != x1 && currentCol != y1) {
        if (board[currentRow][currentCol] != " ") {
            // If own piece is encountered or another opponent after the first, move is invalid
            if (hasMetOpponent || board[currentRow][currentCol] == piece || board[currentRow][currentCol] == king) {
                return false;
            }

            // Record opponent position if first encounter
            hasMetOpponent = true;
            opponentPieceRow = currentRow;
            opponentPieceCol = currentCol;
        }

        // Move to next cell along the direction
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    // Clear the opponent's piece if a valid capture occurred
    if (hasMetOpponent) {
        board[opponentPieceRow][opponentPieceCol] = " ";
    }

    return true;
}

bool Board::isMoveValidByPiece(int x1, int y1) {
    int direction = (currentPlayer == 'B') ? 1 : -1;
    if(x1 == currentPiece.getRow() + direction && abs(y1 - currentPiece.getCol()) == 1){
        return true;
    }
    if (abs(x1 - currentPiece.getRow()) == 2 && abs(y1 - currentPiece.getCol()) == 2) {
        if (isJump(x1, y1)) {
            return true;
        }
    }
    return false;
}

