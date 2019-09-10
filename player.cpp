#include <bits/stdc++.h>
#include<iostream>
#include "Game.h"
using namespace std;
int player = 0;
float minimax(int depth,Game game,float alpha,float beta,bool isMax) {
    if (depth == 0) {
        return player==0?game.eval_function(game.board()):-1*game.eval_function(game.board());
    }


    if (isMax) {
        vector<vector<int> > newGameMoves = game.valid_moves(player);
        float bestMove = FLT_MIN;
        for (int i = 0; i < newGameMoves.size(); i++) {
            game.move(newGameMoves[i]);
            bestMove = max(bestMove, minimax(depth - 1, game, alpha, beta, !isMax));
            game.undo();
            alpha = max(alpha, bestMove);
            if (beta <= alpha) {
                return bestMove;
            }
        }
        return bestMove;
    } else {
      vector<vector<int> > newGameMoves = game.valid_moves(1-player);
        float bestMove = FLT_MAX;
        for (int i = 0; i < newGameMoves.size(); i++) {
            game.move(newGameMoves[i]);
            bestMove = min(bestMove, minimax(depth - 1, game, alpha, beta, !isMax));
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
  cout<<"S "<<move_sequence[2]<<' '<<move_sequence[1]<<' '<< select <<move_sequence[4]<<' '<<move_sequence[3] <<endl;
}
vector<int> move_to_array(string move){
  vector<int> moveVector;
  int type=move[6]=='M'?0:1;
  moveVector.push_back(type);
  moveVector.push_back((int)(move[4]-'0'));
  moveVector.push_back((int)(move[2]-'0'));
  moveVector.push_back((int)(move[8]-'0'));
  moveVector.push_back((int)(move[6]-'0'));
  return moveVector;
}
void play(Game game){
  string move;
  if(player == 1){
    char temp;
    cin>>temp;
    getline(cin,move);
    game.move(move_to_array(move));
  }
  while(1){
    vector<vector<int> > validMoves = game.valid_moves(player);
    float bestValue=FLT_MIN;
    int index = 0;
    for(int i=0;i<validMoves.size();i++){
      game.move(validMoves[i]);
      float temp = minimax(3, game, FLT_MAX, FLT_MIN, false);
      index = bestValue<temp?i:index;
      bestValue = max(bestValue, temp);
      game.undo();
    }
    game.move(validMoves[index]);
    play_move_seq(validMoves[index]);
    char temp;
    cin>>temp;
    getline(cin,move);
    game.move(move_to_array(move));
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
