#ifndef GAME_H
#define GAME_H
#include <bits/stdc++.h>
#include<iostream>
using namespace std;
class Game {
public:
  vector<int> current_move;
  vector<char> player_at_new_pos;
  void move(int mov);
  void undo(int mov);
  vector<string> board();
  Game(int n, int m);
  float eval_function(int move);
  unordered_set<int> possible_moves_white;
  unordered_set<int> possible_moves_black;
  unordered_set<int> space_of_soldiers_white;
  unordered_set<int> space_of_soldiers_black;
  vector<vector<int>> attack_space_of_cannons_white;
  vector<vector<int>> attack_space_of_cannons_black;
  vector<vector<int>> attack_space_of_soldiers_white;
  vector<vector<int>> attack_space_of_soldiers_black;
  unordered_map<int,int> cannon_pos_white;
  unordered_map<int,int> cannon_pos_black;
  vector<string> the_board;
  bool check_ne(int x1,int y1,char player,vector<string> &current_board,bool opp);
  int encode_move(int type,int xs,int ys,int x,int y);
  vector<int> decode_move(int mov);
  void attack_move1(bool del,int color1,int color2,int x,int y);
  void attack_move2(bool del,int color1,int color2,int x,int y);
  void insert_move(int color1,int color2,int type,int xs,int ys,int x,int y);
  void delete_move(int color1,int color2,int type,int xs,int ys,int x,int y);
  void add_retreat_moves(int color1,int color2,int x1,int y1,char player,vector<string> &current_board);
  void delete_retreat_moves(int color1,int color2,int x1,int y1,char player,vector<string> &current_board);
  void letsdel(int init_pos,char player,bool del);
  int m;
  int n;
  unordered_set<int> validMoves(int player);
  int  encode_vector_move(vector<int> move);
  void print_moves();
  void print_board();
private:
  void load_new_board();
  void load_data();
  vector<int> create_vector(int type,int xs,int ys,int x,int y);

};
#endif
