#include "game.h"
#include <iostream>
#include "console/console.h"
#include <time.h>

Game::Game(){
  gamestate = gamestate::PLAY;
  for(int i = 0; i<BOARD_WIDTH; i++){
    for(int j = 0; j<BOARD_HEIGHT; j++){
      board_[i][j] = false;
    }
  }
}

// 게임의 한 프레임을 처리한다.
void Game::update(){
  // 테트로미노가 떨어지는 로직
  if(console::frameCount() % DROP_DELAY == 0){
    currentTetrominoY++;
  }
  // 테트로미노가 바닥에 닿았을 때
  if(currentTetrominoY == BOARD_HEIGHT){
    // 테트로미노를 보드에 고정
    for(int i = 0; i<currentTetrominoObject.size(); i++){
      for(int j = 0; j<currentTetrominoObject.size(); j++){
        if(currentTetrominoObject.shape()[i][j]){
          board_[currentTetrominoX + j][currentTetrominoY + i] = true;
        }
      }
    }
    // 라인이 꽉 찼는지 확인
    checkLine();
    // 다음 테트로미노 생성
    createTetromino();
  }
  // 키 이벤트 처리
  keyEvent();
  // 게임 오버 체크
  if(currentTetrominoY == 0){
    gamestate = gamestate::GAMEOVER_SAD;
  }
  // 게임 오버 시 화면에 시간 출력
  if(gamestate == gamestate::GAMEOVER_SAD){
    drawTime(0);
  }
  // 게임 오버 시 화면에 시간 출력
  if(gamestate == gamestate::GAMEOVER_ENDKEY){
    drawTime(1);
  }
  // 게임 오버 시 화면에 시간 출력
  if(gamestate == gamestate::GAMEOVER_HAPPY){
    drawTime(1);
  }
  // 홀드된 테트로미노 그리기
  drawHoldTetromino();
  // 지운 라인 개수 그리기
  drawEraseLine();
  // 그림자 테트로미노 그리기
  drawShadowTetromino();
  
}
void Game::drawShadowTetromino(){
  // 그림자 테트로미노 그리기
  int shadowY = currentTetrominoY;
  while(true){
    shadowY++;
    //구현해야함
  }
}
void Game::checkLine(){
  for(int i = 0; i<BOARD_HEIGHT; i++){
    bool isFull = true;
    for(int j = 0; j<BOARD_WIDTH; j++){
      if(!board_[j][i]){
        isFull = false;
        break;
      }
    }
    if(isFull){
      for(int j = 0; j<BOARD_WIDTH; j++){
        board_[j][i] = false;
      }
      for(int k = i; k<BOARD_HEIGHT; k++){
        for(int j = 0; j<BOARD_WIDTH; j++){
          if(k == BOARD_HEIGHT - 1){
            board_[j][k] = false;
          }
          else{
            board_[j][k] = board_[j][k + 1];
          }
        }
      }
      eraseLine++;
    }
  }
}
void Game::keyEvent(){
  if(console::key(console::K_LEFT)){
    //왼쪽 이동
    this->currentTetrominoX--;
  }
  else if(console::key(console::K_RIGHT)){
    //오른쪽 이동
    this->currentTetrominoX++;
  }
  else if(console::key(console::K_UP)){
    //하드 드롭
    console::log("UP");
  }
  else if(console::key(console::K_DOWN)){
    //소프트 드롭
    this->currentTetrominoY--;
  }
  else if(console::key(console::K_ESC)){
    //게임 종료
    exit(0);
  }
  else if(console::key(console::K_SPACE)){
    //hold
    console::log("SPACE");
  }
  else if(console::key(console::K_Z)){
    //반시계 방향 회전
    currentTetrominoObject = currentTetrominoObject.rotatedCCW();
  }
  else if(console::key(console::K_X)){
    //시계 방향 회전
    currentTetrominoObject = currentTetrominoObject.rotatedCW();
  }
  // else{
  //   console::log("OTHER");
  // }
}
// 지워진 라인 개수를 그린다.
void Game::drawEraseLine(){
  console::draw(14, 1, "ERASE LINE : " + std::to_string(eraseLine));
}
  // 게임 끝 (n = 0: 승리, n = 1: 패배)
void drawEnd(int n){
  //게임이 끝났을 때 / 승리
  if(n == 0){
    console::draw(BOARD_WIDTH / 2 + 1, (BOARD_HEIGHT / 2) + 1, "YOU WIN");
  }
  //게임이 끝났을 때 / 패배
  else if(n == 1){
    console::draw(BOARD_WIDTH / 2 + 1, (BOARD_HEIGHT / 2) + 1, "YOU LOSE");
  }
}
// 현재 시간을 그린다.
void Game::drawTime(int n){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  if(n == 0){ // n = 0 : 보드 밑에 시간 출력
    console::draw(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT + 2 + 1, std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + " (GAME OVER)"
  }if(n == 1){ // n = 1 : 게임 종료시의 시간 출력
    console::draw(BOARD_WIDTH / 2 + 1, (BOARD_HEIGHT / 2) + 2, std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec));
  }
}

// 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0, 0, BOARD_WIDTH + 2, BOARD_HEIGHT + 2);
  console::drawBox(14, 0, 20, 6);
  console::drawBox(22, 0, 28, 6);
  Tetromino::drawAt(BLOCK_STRING, currentTetrominoX, currentTetrominoY);
}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit(){
  if(console::key(console::K_ESC) || gamestate == gamestate::GAMEOVER_ENDKEY){
    gamestate = gamestate::GAMEOVER_ENDKEY;
    return true;
  }
  else if(gamestate == gamestate::GAMEOVER_HAPPY){
    return true;
  }
  else if(gamestate == gamestate::GAMEOVER_SAD){
    return true;
  }
  else{
    return false;
  }
}
