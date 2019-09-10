#include <bits/stdc++.h>
#include<iostream>
#include "Game.h"
using namespace std;
int player = 0;
float eval(vector<string > board){
  return rand();
}
float minimax(int depth,Game game,float alpha,float beta,bool isMax) {
    if (depth == 0) {
        return -eval(game.board());
    }

    vector<vector<int> > newGameMoves = game.valid_moves(player);

    if (isMax) {
        float bestMove = FLT_MIN;
        for (int i = 0; i < newGameMoves.size(); i++) {
            game.move(newGameMoves[i]);
            bestMove = max(bestMove, minimax(depth - 1, game, alpha, beta, 1-player));
            game.undo();
            alpha = max(alpha, bestMove);
            if (beta <= alpha) {
                return bestMove;
            }
        }
        return bestMove;
    } else {
        float bestMove = FLT_MAX;
        for (int i = 0; i < newGameMoves.size(); i++) {
            game.move(newGameMoves[i]);
            bestMove = min(bestMove, minimax(depth - 1, game, alpha, beta, 1-player));
            game.undo();
            beta = min(beta, bestMove);
            if (beta <= alpha) {
                return bestMove;
            }
        }
        return bestMove;
    }
}


void play_move_seq(vector<int> move_sequence){
  string select = move_sequence[0]==0?"M ":"B ";
  cout<<"S "<<move_sequence[1]<<' '<<move_sequence[2]<<' '<< select <<move_sequence[3]<<' '<<move_sequence[4] <<endl;
}
vector<int> move_to_array(string move){
  vector<int> moveVector;
  moveVector.push_back(1);
  moveVector.push_back(0);
  moveVector.push_back(0);
  moveVector.push_back(0);
  moveVector.push_back(0);
  return moveVector;
}
void play(Game game){
  string move;
  if(player == 1){
    cin>>move;
    //game.move(move_to_array(move));
  }
  while(1){
    vector<vector<int> > validMoves = game.valid_moves(player);
    float bestValue=FLT_MIN;
    int index = 0;
    for(int i=0;i<validMoves.size();i++){
      game.move(validMoves[i]);
      float temp = minimax(3, game, FLT_MIN, FLT_MAX, player);
      index = bestValue<temp?i:index;
      bestValue = max(bestValue, temp);
      game.undo();
    }
    play_move_seq(validMoves[index]);

    cin>>move;
    //game.move(move_to_array(move));
  }
}




int main(){

  int data[4];
  for(int i=0;i<4;i++){
    cin>>data[i];
  }
  player = data[0] - 1;
  int n = data[1];
  int m = data[2];
  int time_left = data[3];
  Game game = Game(n,m);
  play(game);
  return 0;
}
