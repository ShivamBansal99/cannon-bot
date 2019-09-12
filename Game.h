#ifndef GAME_H
#define GAME_H
#include <bits/stdc++.h>
#include<iostream>
using namespace std;
class Game {
public:
  vector<string > current_board;
  vector<string > prev_board;
  int m;
  int n;
  void move(vector<int> mov);
  void undo();
  vector<vector<int>> valid_moves(int color,unordered_map<int,int> &num_attacks_onOpp_byCannon,
unordered_map<int,int> &num_attacks_onOpp_bySoldiers,unordered_map<int,int> &attack_space_of_cannons,unordered_map<int,int> &attack_space_of_soldiers,
vector<int> &space_of_soldiers,bool &townhall_is_under_attack,vector<int> &cannon_pos);
  vector<string> board();
  Game(int n, int m);
  float eval_function(vector<string> board_status);
private:
  vector<string> load_new_board();
  vector<string> load_data();
  void print_board();
  vector<int> create_vector(int type,int xs,int ys,int x,int y,int num_attacks);
  vector<vector<int>> valid_moves2(vector<string> &current_board,char player,char opp_player,char townhall,char opp_townhall,
unordered_map<int,int> &num_attacks_onOpp_byCannon,unordered_map<int,int> &num_attacks_onOpp_bySoldiers,unordered_map<int,int> &attack_space_of_cannons,
unordered_map<int,int> &attack_space_of_soldiers,vector<int> &space_of_soldiers,bool &townhall_is_under_attack,vector<int> &cannon_pos);

};
#endif
