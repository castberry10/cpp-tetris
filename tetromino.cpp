#include "tetromino.h"
#include <iostream>
#include "console/console.h"

// Tetromino I("I", 4, "XXXXOOOOXXXXXXXX")
Tetromino::Tetromino(std::string name, int size, std::string shape)
{
    name_ = name;     // 디버그용 이름
    size_ = size;     // 테트로미노의 사이즈
    original_ = this; // 회전되지 않은 원래 테트로미노 객체를 저장하는 포인터
    int index = 0;    // shape 문자열의 인덱스
    for (int y = 0; y < size; y++)
    { //
        for (int x = 0; x < size; x++)
        {
            shape_[x][y] = (shape[index] == 'O'); // 블록이 존재한다면 O를 통해 표시하고 아니라면 X를 통해 표시한다.
            index++;
        }
    }
}
// 각 테트로미노 종류에 대한 선언
// cpp 파일에서 Tetromino Tetromino::I(...); 와 같이 구현한다
// static Tetromino I, O, T, S, Z, J, L;
Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");

// 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCW(){
    bool data[4][4] = {false}; // 모든 크기의 테트로미노를 처리하기 위해 최대 크기로 초기화
    std::string createString = "";
    // 테트로미노 회전 로직
    for (int row = 0; row < size_; ++row) {
        for (int col = 0; col < size_; ++col) {
            data[col][size_ - 1 - row] = shape_[row][col];
        }
    }
    // 회전된 테트로미노의 모양을 문자열로 변환
    for(int i = 0; i<size_; i++){
        for(int j = 0; j<size_; j++){
            if(data[i][j]){
                createString += "O";
            }else{
                createString += "X";
            }
        }
    } 
    // 회전된 테트로미노의 모양을 기반으로 새로운 Tetromino 객체 생성
    return Tetromino(*this);
}

// 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCCW(){
    bool data[4][4] = {false}; // 모든 크기의 테트로미노를 처리하기 위해 최대 크기로 초기화
    std::string createString = "";
    // 테트로미노 회전 로직
    for (int row = 0; row < size_; ++row) {
        for (int col = 0; col < size_; ++col) {
            data[size_ - 1 - col][row] = shape_[row][col];
        }
    }
    // 회전된 테트로미노의 모양을 문자열로 변환
    for(int i = 0; i<size_; i++){
        for(int j = 0; j<size_; j++){

            
            if(data[i][j]){
                createString += "O";
            }else{
                createString += "X";
            }
        }
    } 
    // 회전된 테트로미노의 모양을 기반으로 새로운 Tetromino 객체 생성
    return Tetromino(*this);
}

// 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
// x y 가 테트로미노의 좌측 상단이라 한다면. 
void Tetromino::drawAt(std::string s, int x, int y){ 
    for(int i = 0; i < size_ ; i++){
        for(int j = 0; j < size_; j++){
            if(shape_[i][j]){
                console::draw(j + x, i + y, s); // 이거 실제로 이 좌표가 맞는지는 확인해봐야함
            }
        }
    }
}
// static Tetromino I =
