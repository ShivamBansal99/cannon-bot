#include <bits/stdc++.h>
#include<iostream>
#include "Game.h"
using namespace std;
int player = 0;
int max_queiscent=5;
int total_queiscent = 0;
int quis_depth=3;
bool some_deletion(vector<int> move, Game &game){
  if(game.the_board[move[3]][move[4]]!='-') return true;
  return false;
}


float minimax(Game &game,int depth,float alpha,float beta,bool isMax,bool check_quiescent) {
    if(game.board_states[game.the_board]>2) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));

    if (depth == 0 && (!check_quiescent || max_queiscent<total_queiscent)) {
        
        return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
    }
    if (depth == 0 && check_quiescent) {
      if(game.some_townhall_is_under_attack()){
        total_queiscent++;
        return minimax(game,quis_depth,alpha,beta,isMax,false);
      }else{
        return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
      }
    }

    float bestMove ;
    if (isMax) {
        unordered_set<int> newGameMoves = game.validMoves(player);
        bestMove = INT_MIN;
        if(newGameMoves.size()==0 || game.num_black_townhalls==game.m/2-2 || game.num_white_townhalls==game.m/2-2 || game.validMoves(1-player).size()==0) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
        //if(newGameMoves.size()==0 ) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));

        for (auto i = newGameMoves.begin(); i != newGameMoves.end(); i++) {
            game.move(*i);
            bestMove = max(bestMove, minimax(game,depth - 1, alpha, beta, !isMax,check_quiescent));
            game.undo(*i);
            alpha = max(alpha, bestMove);
            if (beta <= alpha) {
                return bestMove;
            }
        }
        return bestMove;
    } else {
      unordered_set<int> newGameMoves = game.validMoves(1-player);
        bestMove = INT_MAX;
        if(newGameMoves.size()==0 || game.num_black_townhalls==game.m/2-2 || game.num_white_townhalls==game.m/2-2 || game.validMoves(1-player).size()==0) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
        //if(newGameMoves.size()==0 ) return player==0?game.eval_function(isMax?player:1-player):((-1)*game.eval_function(isMax?player:1-player));
        for (auto i = newGameMoves.begin(); i != newGameMoves.end(); i++) {
            game.move(*i);
            bestMove = min(bestMove, minimax(game,depth - 1, alpha, beta, !isMax,check_quiescent));
            game.undo(*i);
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
void play(Game &game, int time_given, int start_time){
  string move;
  int depp=0;
  int movess=0;
  //int initial_count=count_soldiers(game.the_board);
  int num_soldiers=0;
  int time_left = time_given;
  int time_taken = 0;
  if(player == 1){
    game.move(game.encode_vector_move(move_to_array()));
    movess++;
  }
  int time_taken_in_one_move = unsigned(time(0));
  while(1){
    // num_soldiers=count_soldiers(game.the_board);
    // if(num_soldiers<=(initial_count/1.8)){
    //   depp=depp+1;
    //   initial_count=num_soldiers;
    // }
    // if(movess==2||movess==3){
    //   depp=2;
    // }
    // if(movess==4||movess==5){
    //   depp=3;
    // }
    unordered_set<int> validMoves = game.validMoves(player);
    depp = (12.57f/log10((float)validMoves.size()* (float)game.validMoves(1-player).size()));
    ////////////////////////////////////////////
    float bestValue=INT_MIN;
    int best_move = 0;
    // int ppp=game.possible_moves_white.size();
    // int qqq=game.possible_moves_black.size();
    //cerr<<endl<<ppp<<" "<<qqq<<endl;

    // int error_check = game.encode_move(0,3,3,2,4);

    time_left = time_given - (time_taken);
   // cerr<<time_left<<endl<<unsigned(time(0))<<endl;
    if(time_left<15){
      depp = 3;
      quis_depth = 2;
    }
    if(time_left<10){
      depp = 2;
      quis_depth = 1;
      max_queiscent = 2;
    }
    if(time_left<5){
      depp = 0;
      quis_depth = 0;
      max_queiscent = 0;
    }
    cerr<<depp<<endl;
    for(auto i = validMoves.begin();i!=validMoves.end();i++){
      game.move(*i);
      total_queiscent = 0;
      float temp = minimax(game,depp-1,  INT_MIN, INT_MAX, false,true);
      //cout<<"a "<<validMoves[i][0]<<" "<<validMoves[i][1]<<" "<<validMoves[i][2]<<" "<<validMoves[i][3]<<" "<<validMoves[i][4]<<" "<<temp<<endl;
      // vector<int> lil = game.decode_move(*i);
      // cerr<<lil[0]<<' '<<lil[1]<<' '<<lil[2]<<' '<<lil[3]<<' '<<lil[4]<<' '<<temp<<endl;
       // cerr<<depp<<endl;
      //cerr<<game.num_white_townhalls<<' '<<game.num_black_townhalls<<endl;
      best_move = bestValue<temp?*i:best_move;
      bestValue = max(bestValue, temp);
      game.undo(*i);
    }
    //cerr<<depp<<endl;

    // cerr<<bestValue<<endl;
    if(some_deletion(game.decode_move(best_move),game)){
      game.board_states.clear();
    }
    game.move(best_move);
    // cerr<<game.board_states.size()<<endl;
    // for(auto i = game.board_states.begin();i!=game.board_states.end();i++){
    //   cerr<<i->second<<' ';
    // }
    //cerr<<endl;
    movess++;
    
    play_move_seq(game.decode_move(best_move));
    // print_board();
    // cerr<<endl;
    // game.print_moves();
    // cerr<<endl;
    time_taken_in_one_move = unsigned(time(0)) - time_taken_in_one_move;
    time_taken +=time_taken_in_one_move;

    vector<int> other_move =move_to_array();

    time_taken_in_one_move = unsigned(time(0));
    
    if(some_deletion(other_move,game)){
      game.board_states.clear();
    }
    game.move(game.encode_vector_move(other_move));
    // print_board();
    // cerr<<endl;
    // game.print_moves();
    // cerr<<endl;
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
  Game game = Game(n,m);
  int time_given = data[3];
  int start_time = unsigned(time(0));
  play(game,time_given,start_time);
  return 0;
}
