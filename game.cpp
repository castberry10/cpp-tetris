#include "game.h"
#include <iostream>
#include "console/console.h"
#include <chrono>
Game::Game(){
  gamestate = gamestate::PLAY;
  for(int i = 0; i<BOARD_WIDTH; i++){
    for(int j = 0; j<BOARD_HEIGHT; j++){
      board_[j][i] = false;
    }
  }
  frameCount = 0;
  currentTetrominoX = BOARD_WIDTH / 2;
  currentTetrominoY = 0;
  eraseLine = 0;
  canHold = true;
  // holdTetrominoObject = NULL; 해결해야함
  createTetromino();
  currentTetrominoObject = nextTetrominoObject;
  createTetromino();
  holded = false;
  startTime = std::chrono::system_clock::now();

}
// 테트로미노가 쌓인다면 실행되는 함수
// 테트로미노를 초기화한다.
// 성공하면 true 실패하면 false
bool Game::initTetromino(){
  
  currentTetrominoX = BOARD_WIDTH / 2;
  currentTetrominoY = 0;
  
  currentTetrominoObject = nextTetrominoObject;
  createTetromino();
  currentTetrominoX = BOARD_WIDTH / 2 - 1;
  currentTetrominoY = 0;
  if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
    gamestate = gamestate::GAMEOVER_SAD;
    return false;
  }
  return true;
}
// 테트리스가 쌓이는 조건
// 소프트드롭
// 하드드롭
// 자연스럽게 떨어지는 것

// 게임의 한 프레임을 처리한다.
void Game::update(){
  keyEvent();
  if(frameCount >= DROP_DELAY){
    if(eraseLine >= LINES){
      gamestate = gamestate::GAMEOVER_HAPPY;
      return;
    }
    //테트로미노가 바닥
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY + 1)){
      markTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY);
      canHold = true;
      initTetromino();
    }else{ // 바닥이 아니라면 
      currentTetrominoY++;
    }
    frameCount = 0;
    return;
  }
  frameCount++;
  // if(currentTetrominoObject)
}
void Game::markTetromino(Tetromino t, int x, int y){
  for (int i = 0; i < t.size(); i++) { 
    for (int j = 0; j < t.size(); j++) { 
      if (t.check(i, j)) {
        board_[y + i][x + j] = true;
      }
    }
  }
  canHold = true;
}
  // 그림자 테트로미노 그리기
void Game::drawShadowTetromino(){

  int shadowY = currentTetrominoY;
  // if(shadowY < 1){
  //   return;
  // }
  while(true){
    // 테트로미노가 바닥이거나 다른 블록과 겹치는가?  
    // 바닥이라면 
    // 쉐도우 테트로미노를 그린다. break;
    // 바닥이 아니라면
    // shadowY를 1만큼 증가시킨다.
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, shadowY)){
      currentTetrominoObject.drawAt(SHADOW_STRING, currentTetrominoX+1, shadowY);
      break;
    }
    else{
      shadowY++;
    }
  }
}
void Game::checkLine(){
  // for(int i = 0; i<BOARD_HEIGHT; i++){
  //   bool isFull = true;
  //   for(int j = 0; j<BOARD_WIDTH; j++){
  //     if(!board_[j][i]){
  //       isFull = false;
  //       break;
  //     }
  //   }
  //   if(isFull){
  //     for(int j = 0; j<BOARD_WIDTH; j++){
  //       board_[j][i] = false;
  //     }
  //     for(int k = i; k<BOARD_HEIGHT; k++){
  //       for(int j = 0; j<BOARD_WIDTH; j++){
  //         if(k == BOARD_HEIGHT - 1){
  //           board_[j][k] = false;
  //         }
  //         else{
  //           board_[j][k] = board_[j][k - 1];
  //         }
  //       }
  //     }
  //     eraseLine++;
  //   }
  // }
  // for(int i = 0; i < BOARD_HEIGHT; i++){
  //   bool isFull = true;
  //   for(int j = 0; j<BOARD_WIDTH; j++){
  //     if(!board_[i][j]){
  //       isFull = false;
  //       break;
  //     }
  //   }
  //   if(isFull){
  //     for(int j = 0; j<BOARD_WIDTH; j++){
  //       board_[i][j] = false;
  //     }
  //     for(int k = i; k<BOARD_HEIGHT; k++){
  //       for(int j = 0; j<BOARD_WIDTH; j++){
  //         if(k == BOARD_HEIGHT - 1){
  //           board_[k][j] = false;
  //         }
  //         else{
  //           board_[k][j] = board_[k-1][j];
  //         }
  //       }
  //     }
  //     ++eraseLine;
  //   }
  // }
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    bool isFull = true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
        if (!board_[i][j]) {
            isFull = false;
            break;
        }
    }
    if (isFull) {
        // 현재 줄을 비우기
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board_[i][j] = false;
        }
        // 위의 모든 줄을 한 줄씩 아래로 내리기
        for (int k = i; k > 0; k--) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board_[k][j] = board_[k-1][j];
            }
        }
        // 가장 윗 줄을 비우기
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board_[0][j] = false;
        }
        ++eraseLine;
        --i; // 현재 지운 줄을 다시 검사하기 위해 인덱스 감소
    }
  }
}
//next테트로미노의 랜덤한 테트로미노를 넣는다.
void Game::createTetromino(){
  int type = rand() % 7;
  switch (type)
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
  // 테트로미노가 바닥에 닿았는지 확인
  // 바닥이라면 True 바닥이 아니라면 false
bool Game::checkFloorTetromino(Tetromino t, int x, int y){
for(int i = 0; i < t.size(); i++){ // i - > y로 
    for(int j = 0; j < t.size(); j++){ // j -> x로 
      if(t.check(j, i)){
        if(y + i >= BOARD_HEIGHT){
          return true;
        }
        if(x + j < 0 || x + j >= BOARD_WIDTH){
          return true;
        }
        if(board_[x + i][y + j]){
          return true;
        }
      }
    }
  }
  return false;
}

  // 테트로미노가 벽이나 블록과 겹치는가? 
  // x 움직일때 체크
  // 왜 있는가? 그것은 테트로미노가 회전될때마다 벽에 붙을 수 있는 
  // 수준이 다르니 이걸로 체크해줘야할 듯 
bool Game::checkWallTetromino(Tetromino t, int x, int y){

 for(int i = 0; i < t.size(); i++){ // i - > y로 
    for(int j = 0; j < t.size(); j++){ // j -> x로 
      if(t.check(i, j)){
        if(x + j < 0 || x + j >= BOARD_WIDTH){
          return true;
        }
        if(board_[y + j][x + i]){
          return true;
        }
      }
    }
  }
  return false;

}

  // 생각해보니 x 움직일때도 움직일때도 해야할 듯? 
  // 그냥 벽체크 + 바닥체크 합쳐서 만드는 것도
  // 테트로미노가 회전되었을때 실행
  // 벽이나 테트로미노가 있으면 True, 문제가 없으면 False 
bool Game::checkProblemTetromino(Tetromino t, int x, int y){
  for(int i = 0; i < t.size(); i++){ // i - > y로 
    for(int j = 0; j < t.size(); j++){ // j -> x로 
      if(t.check(i, j)){
        if(y + i >= BOARD_HEIGHT){
          return true;
        }
        if(x + j < 0 || x + j >= BOARD_WIDTH){
          return true;
        }
        if(board_[y + i][x + j]){
          return true;
        }
      }
    }
  }
  return false;
}
void Game::keyEvent(){
  if(console::key(console::K_LEFT)){
    //왼쪽 이동
    this->currentTetrominoX--;
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      this->currentTetrominoX++;
    }
  }
  else if(console::key(console::K_RIGHT)){
    //오른쪽 이동
    this->currentTetrominoX++;
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      this->currentTetrominoX--;
    }
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
   while(1){
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      // for(int i = 0; i<currentTetrominoObject.size(); i++){
      //   for(int j = 0; j<currentTetrominoObject.size(); j++){
      //     board_[currentTetrominoX + i][currentTetrominoY + j] = true;
      //   }
      // }
      markTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY - 1);
      this->canHold = true;
      checkLine();
      initTetromino();
      break;
    }
    else{
      currentTetrominoY++;
    }
   }
  }
  else if(console::key(console::K_DOWN)){
    //소프트 드롭
    this->currentTetrominoY++;
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      this->currentTetrominoY--;
    }
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
    if(holded==false){
      holded = true;
      holdTetrominoObject = *(currentTetrominoObject.original());
      currentTetrominoObject = nextTetrominoObject;
      createTetromino();
      canHold = false; 
    }
    Tetromino temp = holdTetrominoObject;
    holdTetrominoObject = *(currentTetrominoObject.original());
    currentTetrominoObject = temp;
    canHold = false;
    initTetromino();
   }
  }
  else if(console::key(console::K_Z)){
    //반시계 방향 회전
    currentTetrominoObject = currentTetrominoObject.rotatedCCW();
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      currentTetrominoObject = currentTetrominoObject.rotatedCW();
    }
  }
  else if(console::key(console::K_X)){
    //시계 방향 회전
    currentTetrominoObject = currentTetrominoObject.rotatedCW();
    if(checkProblemTetromino(currentTetrominoObject, currentTetrominoX, currentTetrominoY)){
      currentTetrominoObject = currentTetrominoObject.rotatedCCW();
    }
  }
}
// 지워진 라인 개수를 그린다.
void Game::drawEraseLine(){
  console::draw(0, BOARD_HEIGHT + 2, std::to_string(LINES - eraseLine)+ " lines left");
}
  // 게임 끝 (n = 0: 승리, n = 1: 패배)
void Game::drawEnd(int n){
  //게임이 끝났을 때 / 승리
  if(n == 0){
    console::draw(0, (BOARD_HEIGHT / 2) + 1, "YOU WIN");
  }
  //게임이 끝났을 때 / 패배
  else if(n == 1){
    console::draw(0, (BOARD_HEIGHT / 2) + 1, "YOU LOSE");
  }
}

// 현재 시간을 그린다.
void Game::drawTime(int n){
  
  std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> dis = endTime - startTime;

  long long total = dis.count();
  int min = total / 60000;
  int sec = (total % 60000) / 1000;
  int milsec = (total % 1000) / 10;
    
  std::string strmin = std::to_string(min);
  std::string strsec = std::to_string(sec % 60);
  std::string strmilsec = std::to_string(milsec % 100);
  if(min < 10){
    strmin = "0" + strmin;
  }
  if(sec < 10){
    strsec = "0" + strsec;
  } 
  if(milsec < 10){
    strmilsec = "0" + strmilsec;
  }
  if(n == 0){ // n = 0 : 보드 밑에 시간 출력
    console::draw((BOARD_WIDTH / 2) - ((2 + 1 + 2 + 1 + 2) / 2) + 1, BOARD_HEIGHT + 3, strmin + ":" + strsec + ":" + strmilsec);
  }
  // }if(n == 1){ // n = 1 : 게임 종료시의 시간 출력
  //   console::draw((BOARD_WIDTH / 2) - ((2 + 1 + 2 + 1 + 2) / 2) + 2, (BOARD_HEIGHT / 2) + 2, strmin + ":"  + strsec + ":" + strmilsec);
  // }
}
void Game::drawBoard(){
  for(int i = 0; i<BOARD_HEIGHT; i++){
    for(int j = 0; j<BOARD_WIDTH; j++){
      if(board_[i][j]){
        console::draw(j + 1, i + 1, BLOCK_STRING);
      }
    }
  }
}
// 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0, 0, BOARD_WIDTH + 1, BOARD_HEIGHT + 1);
  console::drawBox(13, 0, 19, 5);
  console::drawBox(20, 0, 26, 5);
  console::draw(14, 0, "next");
  console::draw(21, 0, "hold");
  drawShadowTetromino();
  drawBoard();
  currentTetrominoObject.drawAt(BLOCK_STRING, currentTetrominoX + 1, currentTetrominoY + 1);

  if(nextTetrominoObject.size() == 4){
    nextTetrominoObject.drawAt(BLOCK_STRING, 15, 1);
  }else{
    nextTetrominoObject.drawAt(BLOCK_STRING, 15, 2);
  }
  
  if(holded){
    if(holdTetrominoObject.size() == 4){
      holdTetrominoObject.drawAt(BLOCK_STRING, 22, 1);
    }else{
      holdTetrominoObject.drawAt(BLOCK_STRING, 22, 2);
    }
  }
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
