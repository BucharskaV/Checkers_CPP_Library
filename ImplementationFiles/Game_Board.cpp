#include <jni.h>
#include <string>
#include <vector>
class Board{
    std::vector<std::vector<std::string>> board = {
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {"PBP", " ", "PBP", " ", "PBP", " ", "PBP", " "},
            {" ", "PBP", " ", "PBP", " ", "PBP", " ", "PBP"},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {" ", " ", " ", " ", " ", " ", " ", " "},
            {"PRB", " ", "PRB", " ", "PRB", " ", "PRB", " "},
            {" ", "PRB", " ", "PRB", " ", "PRB", " ", "PRB"},
            {"PRB", " ", "PRB", " ", "PRB", " ", "PRB", " "}
    };

    int boardWidth = 8;
    int boardHeight = 8;
/*    std::string currentPlayer = "RED";
public:
    const std::string &getCurrentPlayer() const {
        return currentPlayer;
    }

    void setCurrentPlayer(const std::string &currentPlayer) {
        Board::currentPlayer = currentPlayer;
    }*/

    JNIEXPORT jstring JNICALL
    Java_Game_Board_getBoardCellState(JNIEnv *env, jobject obj, jint row, jint col) {
        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth) {
            std::string cellState = board[row][col];
            return env->NewStringUTF(cellState.c_str());
        }
        return env->NewStringUTF(" ");
    }


    JNIEXPORT jint JNICALL
    Java_Game_Board_getBoardWidth(JNIEnv *env, jobject obj) {
        return boardWidth;
    }


    JNIEXPORT jint JNICALL
    Java_Game_Board_getBoardHeight(JNIEnv *env, jobject obj) {
        return boardHeight;
    }


    JNIEXPORT void JNICALL
    Java_Game_Board_movePiece(JNIEnv *env, jobject obj, jint fromRow, jint fromCol, jint toRow, jint toCol) {
        if (fromRow >= 0 && fromRow < boardHeight && fromCol >= 0 && fromCol < boardWidth &&
            toRow >= 0 && toRow < boardHeight && toCol >= 0 && toCol < boardWidth) {

            std::string piece = board[fromRow][fromCol];

            if (piece != " ") {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = " ";
            }
        }
    }
};
