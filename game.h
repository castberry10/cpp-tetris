
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_WIDTH][BOARD_HEIGHT];
  enum gamestate { PLAY, GAMEOVER_ENDKEY, GAMEOVER_HAPPY, GAMEOVER_SAD };

  // 게임 상태
  int gamestate;
  
  // hold된 테트로미노
  int holdTetromino;

  // 현재 테트로미노
  int currentTetromino;
  
  // 테트로미노의 X 좌표
  int currentTetrominoX;

  // 테트로미노의 Y 좌표
  int currentTetrominoY;
  
  // 테트로미노 종류 -> 7개 (0 ~ 6)
  enum tetromino { I, O, T, S, Z, J, L };

  // 지금까지 지운 라인의 개수
  int eraseLine;

public:

  // 키값을 받고 이벤트 처리를 한다. 
  void keyEvent();

  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  // 지워진 라인 개수를 그린다.
  void drawEraseLine();

  // 현재 시간을 그린다.
  void drawTime();

  // 게임 끝 (n = 0: 승리, n = 1: 패배)
  void drawEnd(int n);

  //생성자
  Game();
};
#endif