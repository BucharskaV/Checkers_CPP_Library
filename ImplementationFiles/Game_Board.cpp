#include <jni.h>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/Game_Board.h"
#include "../Headers/Board.h"

static Board boardInstance;

extern "C" {
JNIEXPORT jstring JNICALL
Java_Game_Board_getBoardCellState(JNIEnv *env, jobject obj, jint row, jint col) {
    std::string cellState = boardInstance.getBoardCellState(row, col);
    return env->NewStringUTF(cellState.c_str());
}

JNIEXPORT jint JNICALL
Java_Game_Board_getBoardWidth(JNIEnv *env, jobject obj) {
    return boardInstance.getBoardWidth();
}

JNIEXPORT jint JNICALL
Java_Game_Board_getBoardHeight(JNIEnv *env, jobject obj) {
    return boardInstance.getBoardHeight();
}

JNIEXPORT void JNICALL
Java_Game_Board_resetParameters(JNIEnv *env, jobject obj) {
    boardInstance.resetParameters();
}

JNIEXPORT jboolean JNICALL
Java_Game_Board_setCurrentPiece(JNIEnv *env, jobject obj, jint x, jint y){
    return boardInstance.setCurrentPiece(x, y);
}

JNIEXPORT jboolean JNICALL
Java_Game_Board_movePiece(JNIEnv *env, jobject obj, jint x1, jint y1){
    return boardInstance.movePiece(x1, y1);
}

JNIEXPORT jchar JNICALL
Java_Game_Board_getCurrentPlayer(JNIEnv *env, jobject obj){
    return boardInstance.getCurrentPlayer();
}

JNIEXPORT jboolean JNICALL
Java_Game_Board_isGameOver(JNIEnv *env, jobject obj){
    return boardInstance.isGameOver();
}

JNIEXPORT jstring JNICALL
Java_Game_Board_getWinner(JNIEnv *env, jobject obj){
    std::string winner = boardInstance.getWinner();
    return env->NewStringUTF(winner.c_str());
}
JNIEXPORT jboolean JNICALL
Java_Game_Board_possibleJumps(JNIEnv *env, jobject obj){
    return boardInstance.possibleJumps();
}
}
