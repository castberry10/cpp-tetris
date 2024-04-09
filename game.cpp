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
  
}

void Game::keyEvent(){
  if(console::key(console::K_LEFT)){
    //왼쪽 이동
    console::log("LEFT");
  }
  else if(console::key(console::K_RIGHT)){
    //오른쪽 이동
    console::log("RIGHT");
  }
  else if(console::key(console::K_UP)){
    //하드 드롭
    console::log("UP");
  }
  else if(console::key(console::K_DOWN)){
    //소프트 드롭
    console::log("DOWN");
  }
  else if(console::key(console::K_ESC)){
    //게임 종료
    console::log("ESC");
  }
  else if(console::key(console::K_SPACE)){
    //hold
    console::log("SPACE");
  }
  else if(console::key(console::K_Z)){
    //반시계 방향 회전
    console::log("Z");
  }
  else if(console::key(console::K_X)){
    //시계 방향 회전
    console::log("X");
  }
  else{
    console::log("OTHER");
  }
}
// 지워진 라인 개수를 그린다.
void Game::drawEraseLine(){
  console::draw(14, 1, "ERASE LINE : " + std::to_string(eraseLine));
}
  // 게임 끝 (n = 0: 승리, n = 1: 패배)
  void drawEnd(int n){

  }
// 현재 시간을 그린다.
void Game::drawTime(){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  console::draw(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT + 2 + 1, std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec));
}

// 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0, 0, BOARD_WIDTH + 2, BOARD_HEIGHT + 2);
  console::drawBox(14, 0, 20, 6);
  console::drawBox(22, 0, 28, 6);
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
