#include <jni.h>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/Game_Board.h"
class Board {
private:
    std::vector<std::vector<std::string>> board = {
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {"PBP", " ", "PBP", " ", "PBP", " ", "PBP", " "},
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {"PRP", " ", "PRP", " ", "PRP", " ", "PRP", " "},
            {" ", "PRP", " ", "PRP", " ", "PRP", " ", "PRP"},
            {"PRP", " ", "PRP", " ", "PRP", " ", "PRP", " "}
    };
    int boardWidth = 8;
    int boardHeight = 8;
public:
    Board() = default;
    std::string getBoardCellState(int row, int col) {
        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth) {
            return board[row][col];
        }
        return " ";
    }
    int getBoardWidth() const {
        return boardWidth;
    }
    int getBoardHeight() const {
        return boardHeight;
    }
};
JNIEXPORT jstring JNICALL
Java_Game_Board_getBoardCellState(JNIEnv *env, jobject obj, jint row, jint col) {
    Board board;
    std::string cellState = board.getBoardCellState(row, col);
    return env->NewStringUTF(cellState.c_str());
}
JNIEXPORT jint JNICALL
Java_Game_Board_getBoardWidth(JNIEnv *env, jobject obj) {
    Board board;
    return board.getBoardWidth();
}
JNIEXPORT jint JNICALL
Java_Game_Board_getBoardHeight(JNIEnv *env, jobject obj) {
    Board board;
    return board.getBoardHeight();
}