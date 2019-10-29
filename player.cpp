#include <bits/stdc++.h>
#include<iostream>
#include "Game.h"
using namespace std;
int player = 0;
float minimax(int depth,Game &game,float alpha,float beta,bool isMax) {
    if (depth == 0) {
        return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
    }
    float bestMove ;
    if (isMax) {
        unordered_set<int> newGameMoves = game.validMoves(player);
        bestMove = INT_MIN;
        if(newGameMoves.size()==0) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
        for (auto i = newGameMoves.begin(); i != newGameMoves.end(); i++) {
            char prev_player=game.move(*i);
            bestMove = max(bestMove, minimax(depth - 1, game, alpha, beta, !isMax));
            game.undo(*i,prev_player);
            alpha = max(alpha, bestMove);
            if (beta <= alpha) {
                return bestMove;
            }
        }
        return bestMove;
    } else {
      unordered_set<int> newGameMoves = game.validMoves(1-player);
        bestMove = INT_MAX;
        if(newGameMoves.size()==0) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
        for (auto i = newGameMoves.begin(); i != newGameMoves.end(); i++) {
            char prev_player=game.move(*i);
            bestMove = min(bestMove, minimax(depth - 1, game, alpha, beta, !isMax));
            game.undo(*i,prev_player);
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
vector<int> move_to_array(){
  vector<int> moveVector;
  char temp;
  int x,y;
  cin>>temp;
  cin>>x;
  cin>>y;
  moveVector.push_back(0);
  moveVector.push_back(y);
  moveVector.push_back(x);
  cin>>temp;
  int type = temp=='B'?1:0;
  moveVector[0]=type;
  cin>>x;
  cin>>y;
  moveVector.push_back(y);
  moveVector.push_back(x);
  return moveVector;
}
int count_soldiers(vector<string> boards){
  int count=0;
  for(int i=0;i<boards.size();i++){
    for(int j=0;j<boards[i].length();j++){
      if(boards[i][j]=='B'||boards[i][j]=='W'){
        count++;
      }
    }
  }
  return count;
}
void play(Game &game){
  string move;
  int depp=0;
  int movess=0;
  int initial_count=count_soldiers(game.the_board);
  int num_soldiers=0;
  if(player == 1){
    char prev_player=game.move(game.encode_vector_move(move_to_array()));
    movess++;
  }
  while(1){
    num_soldiers=count_soldiers(game.the_board);
    if(num_soldiers<=(initial_count/1.8)){
      depp=depp+1;
      initial_count=num_soldiers;
    }
    if(movess==2||movess==3){
      depp=1;
    }
    if(movess==4||movess==5){
      depp=2;
    }
    unordered_set<int> validMoves = game.validMoves(player);
    ////////////////////////////////////////////
    float bestValue=INT_MIN;
    int best_move = 0;
    for(auto i = validMoves.begin();i!=validMoves.end();i++){
      char prev_player=game.move(*i);
      float temp = minimax(depp, game, INT_MIN, INT_MAX, false);
      //cout<<"a "<<validMoves[i][0]<<" "<<validMoves[i][1]<<" "<<validMoves[i][2]<<" "<<validMoves[i][3]<<" "<<validMoves[i][4]<<" "<<temp<<endl;
      best_move = bestValue<temp?*i:best_move;
      bestValue = max(bestValue, temp);
      game.undo(*i,prev_player);
    }
    char prev_player=game.move(best_move);
    movess++;
    play_move_seq(game.decode_move(best_move));
    game.move(game.encode_vector_move(move_to_array()));
    movess++;
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
