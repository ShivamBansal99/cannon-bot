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
  vector<vector<int>> valid_moves(int color);
  vector<string> board();
  Game(int n, int m);
private:
  vector<string> load_new_board();
  vector<string> load_data();
  void print_board();
  vector<int> create_vector(int type,int xs,int ys,int x,int y);
  vector<vector<int>> valid_moves2(vector<string> &current_board,char player,char opp_player,char townhall,char opp_townhall);

};
#endif
