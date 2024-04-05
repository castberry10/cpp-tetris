#include "game.h"
#include <iostream>
#include "console/console.h"
#include <time.h>

Game::Game(){
  
}

  // 게임의 한 프레임을 처리한다.
void Game::update(){
  // 바보
}

  // 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0, 0, 12, 22);
  console::drawBox(14, 0, 20, 6);
  console::drawBox(22, 0, 28, 6);
    
}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit(){
  if(console::key(console::K_ESC)){
    return true;
  }

}
