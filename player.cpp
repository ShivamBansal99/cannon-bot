#include <bits/stdc++.h>
#include<iostream>
#include "Game.h"
using namespace std;
int player = 0;
float minimax(int depth,Game game,float alpha,float beta,bool isMax) {
    if (depth == 0) {
        return player==0?game.eval_function(game.board(),isMax?player:1-player):((-1)*game.eval_function(game.board(),isMax?player:1-player));
    }
  	unordered_map<int,int> attack_space_of_cannons_black;
  	unordered_map<int,int> attack_space_of_soldiers_black;
  	vector<int> space_of_soldiers_black;
  	unordered_map<int,int> cannon_pos_black;

    if (isMax) {
        vector<vector<int> > newGameMoves = game.valid_moves(player,
      		attack_space_of_cannons_black,attack_space_of_soldiers_black,space_of_soldiers_black,cannon_pos_black);
        float bestMove = INT_MIN;
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
      vector<vector<int> > newGameMoves = game.valid_moves(1-player,
    		attack_space_of_cannons_black,attack_space_of_soldiers_black,space_of_soldiers_black,cannon_pos_black);
        float bestMove = INT_MAX;
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
void play(Game game){
  string move;
  int depp=2;
  int initial_count=count_soldiers(game.current_board);
  int num_soldiers=0;
  if(player == 1){
    game.move(move_to_array());
  }
  while(1){
    num_soldiers=count_soldiers(game.current_board);
    if(num_soldiers==(initial_count/2)){
      depp=depp+1;
      initial_count=num_soldiers;
    }
    unordered_map<int,int> attack_space_of_cannons_black;
    unordered_map<int,int> attack_space_of_soldiers_black;
    vector<int> space_of_soldiers_black;
    unordered_map<int,int> cannon_pos_black;
    vector<vector<int> > validMoves = game.valid_moves(player,
      attack_space_of_cannons_black,attack_space_of_soldiers_black,space_of_soldiers_black,cannon_pos_black);
    ////////////////////////////////////////////
    float bestValue=INT_MIN;
    int index = 0;
    for(int i=0;i<validMoves.size();i++){
      game.move(validMoves[i]);
      float temp = minimax(depp, game, INT_MIN, INT_MAX, false);
      //cout<<"a "<<validMoves[i][0]<<" "<<validMoves[i][1]<<" "<<validMoves[i][2]<<" "<<validMoves[i][3]<<" "<<validMoves[i][4]<<" "<<temp<<endl;
      index = bestValue<temp?i:index;
      bestValue = max(bestValue, temp);
      game.undo();
    }
    game.move(validMoves[index]);
    play_move_seq(validMoves[index]);
    game.move(move_to_array());
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
