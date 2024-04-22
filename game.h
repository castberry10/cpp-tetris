
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include <chrono>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 1

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_HEIGHT][BOARD_WIDTH];
  enum gamestate { PLAY, GAMEOVER_ENDKEY, GAMEOVER_HAPPY, GAMEOVER_SAD };

  // 게임 상태
  int gamestate;
  
  // frame count
  int frameCount;

  std::chrono::system_clock::time_point startTime;
  // // 초기화 여부
  // bool init;

  // hold 가능 여부
  bool canHold;
  
  // 테트로미노의 X 좌표
  int currentTetrominoX;

  // 테트로미노의 Y 좌표
  int currentTetrominoY;

  // 홀드한 경험
  bool holded;

  // 현재 테트로미노 
  Tetromino currentTetrominoObject = Tetromino::I;

  // 다음 테트로미노
  Tetromino nextTetrominoObject = Tetromino::I;

  //홀드된 테트로미노
  Tetromino holdTetrominoObject = Tetromino::I;
  
  // 테트로미노 종류 -> 7개 (0 ~ 6)
  enum tetrominoTypes { I, O, T, S, Z, J, L };
  
  // 키값을 받고 이벤트 처리를 한다. 
  void keyEvent();

  // 지금까지 지운 라인의 개수
  int eraseLine;
  
  // 홀드된 테트로미노
  void drawHoldTetromino();
  
  // 테트로미노 생성
  void createTetromino();
  
  // 지워진 라인 개수를 그린다.
  void drawEraseLine();

  // 라인이 꽉 찼는지 확인하고 지운다.
  void checkLine();

  // 현재 맵을 그린다. 
  void drawBoard();
  
  // 현재 시간을 그린다.
  void drawTime(int n);

  // 게임 끝 (n = 0: 승리, n = 1: 패배)
  void drawEnd(int n);

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
  void drawShadowTetromino();

  // 테트로미노 맨 아래로 이동
  void hardDrop();

  // 현재 테트로미노를 맵에 박는다. 
  void markTetromino(Tetromino t, int x, int y);

  // 테트로미노가 바닥에 닿았는지 확인
  // 바닥이라면 True 바닥이 아니라면 false 
  bool checkFloorTetromino(Tetromino t, int x, int y);

  // 테트로미노가 벽에 붙었나? 
  // x 움직일때 체크
  // 왜 있는가? 그것은 테트로미노가 회전될때마다 벽에 붙을 수 있는 
  // 수준이 다르니 이걸로 체크해줘야할 듯 
  bool checkWallTetromino(Tetromino t, int x, int y);
  
  // 테트로미노가 회전되었을때 실행
  // 벽이나 테트로미노가 있으면 True, 문제가 없으면 False 
  bool checkProblemTetromino(Tetromino t, int x, int y);

  // 테트로미노가 쌓아지고 x와 y 초기화
  bool initTetromino();

public:
  // 게임의 한 프레임을 처리한다.
  void update();
  
  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();


  //생성자
  Game();
};
#endif