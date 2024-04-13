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
  /*
  지운 라인이 게임 종료 조건을 만족하는가?{
    게임 상태를 GAMEOVER_HAPPY로 변경한다.
    return;
  }
  현재테트로미노가 존재하는가?{
    현재 테트로미노가 바닥인가?{
      현재 테트로미노를 보드에 고정시킨다.
      canHold를 true로 변경한다.
      지워야하는 라인을 체크한다.
      현재 테트로미노를 다음 테트로미노로 바꾼다.
    }바닥이 아니라면{
      현재 테트로미노를 한칸 아래로 이동시킨다.
    }

  }존재하지않는다면{
    next테트로미노가 존재하는가?{
      현재테트로미노에 next테트로미노를 넣는다.
    }없다면{
      next테트로미노에 새로운 테트로미노를 넣는다.
      현재테트로미노에 next테트로미노를 넣는다.
    }
    새로운 테트로미노를 만들고 next테트로미노에 넣는다.
    currentTetrominoX를 BOARD_WIDTH / 2로 초기화한다.
    currentTetrominoY를 BOARD_HEIGHT로 초기화한다.
    테트리스 만드는 자리에 테트로미노가 있는가?{
      게임 상태를 GAMEOVER_SAD로 변경한다.
      return;
    }
  }
  keyEvent();
  */
}
void Game::drawShadowTetromino(){
  // 그림자 테트로미노 그리기
  int shadowY = currentTetrominoY;
  while(true){
    // 테트로미노가 바닥인가? 
    // 바닥이라면 
    // 쉐도우 테트로미노를 그린다. break;
    // 바닥이 아니라면
    // shadowY를 1만큼 증가시킨다.
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
void Game::createTetromino(){
  int type = rand() % 7;
  switch (trype)
  {
  case tetrominoTypes::I:
    nextTetrominoObject = Tetromino::I;
    break;
  case tetrominoTypes::O:
    nextTetrominoObject = Tetromino::O;
    break;
  case tetrominoTypes::T:
    nextTetrominoObject = Tetromino::T;
    break;
  case tetrominoTypes::S:
    nextTetrominoObject = Tetromino::S;
    break;
  case tetrominoTypes::Z:
    nextTetrominoObject = Tetromino::Z;
    break;
  case tetrominoTypes::J:
    nextTetrominoObject = Tetromino::J;
    break;
  case tetrominoTypes::L:
    nextTetrominoObject = Tetromino::L;
    break;
  default:
    break;
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
    /*
     while(1){
      if(현재테트로미노가 바닥인가?){
        현재 테트로미노를 보드에 고정시킨다.
        canHold를 true로 변경한다.
        지워야하는 라인을 체크한다.
        현재 테트로미노를 다음 테트로미노로 바꾼다.
        break;
      }바닥이 아니라면{
        현재테트로미노를 한칸 아래로 이동시킨다. (currentTetrominoY++)
      }
     }
    */
  }
  else if(console::key(console::K_DOWN)){
    //소프트 드롭
    this->currentTetrominoY--;
  }
  else if(console::key(console::K_ESC)){
    //게임 종료 // 문제가 있다면 여기서 esc 처리 안해도 되긴함
    gamestate = gamestate::GAMEOVER_ENDKEY;
    exit(0);
  }
  else if(console::key(console::K_SPACE)){
    /* 홀드
    만약 canHold가 true라면{
      만약 holdTetromino가 없다면{
        holdTetromino에 currentTetromino를 넣는다.
        currentTetromino를 다음 테트로미노로 바꾼다.
      }있다면{
        holdTetromino와 currentTetromino를 교체한다.
      }
    }아니라면{
      키 입력을 무시한다. 
    }
    */
   if(canHold){

   }
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
    console::draw(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT + 2 + 1, std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec));
  }if(n == 1){ // n = 1 : 게임 종료시의 시간 출력
    console::draw(BOARD_WIDTH / 2 + 1, (BOARD_HEIGHT / 2) + 2, std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec));
  }
}
void Game::drawBoard(){
  for(int i = 0; i<BOARD_WIDTH; i++){
    for(int j = 0; j<BOARD_HEIGHT; j++){
      if(board_[i][j]){
        console::draw(i, j, BLOCK_STRING);
      }
    }
  }
}
// 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0, 0, BOARD_WIDTH + 2, BOARD_HEIGHT + 2);
  console::drawBox(14, 0, 20, 6);
  console::drawBox(22, 0, 28, 6);
  Game::drawBoard();
  currentTetromino.drawAt(BLOCK_STRING, currentTetrominoX, currentTetrominoY);
  nextTetrominoObject.drawAt(BLOCK_STRING, 15, 1);
  holdTetrominoObject.drawAt(BLOCK_STRING, 23, 1);
  drawEraseLine();
  drawTime(0);
}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit(){
  if(console::key(console::K_ESC) || gamestate == gamestate::GAMEOVER_ENDKEY){
    gamestate = gamestate::GAMEOVER_ENDKEY;
    return true;
  }
  else if(gamestate == gamestate::GAMEOVER_HAPPY){
    drawEnd(0);
    drawTime(1);
    return true;
  }
  else if(gamestate == gamestate::GAMEOVER_SAD){
    drawEnd(1);
    return true;
  }
  else{
    return false;
  }
}
