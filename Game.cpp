#include<bits/stdc++.h>
#include<iostream>
#include"Game.h"
using namespace std;
    Game::Game(int n, int m){
      Game::n=n;
      Game::m=m;
      Game::current_board = load_new_board();
    }
    void Game::move(vector<int> mov){

    }
    void Game::undo(){

    }
    vector<string> Game::board(){
      return current_board;
    }
    vector<string> Game::load_new_board(){
            vector<string> current_board;
            for(int i=0;i<n;i++){
                    string row;
                    for(int j=0;j<m;j++){
                            row+="-";
                    }
                    current_board.push_back(row);
            }
            for(int i=1;i<m;i=i+2){
                    current_board[n-1][i]='#';
            }
            for(int i=0;i<m;i=i+2){
                    current_board[0][i]='O';
            }
            for(int i=0;i<m;i=i+2){
                    current_board[n-1][i]='B';
                    current_board[n-2][i]='B';
                    current_board[n-3][i]='B';
            }
            for(int i=1;i<m;i=i+2){
                    current_board[0][i]='W';
                    current_board[1][i]='W';
                    current_board[2][i]='W';
            }
            return current_board;
    }
    vector<string> Game::load_data(){
            vector<string> current_board;
            ifstream inFile;
            inFile.open("sample_test0.txt");
            if(!inFile){
                    cerr<<"Not able to open";
                    exit(1);
            }
            else{
                    inFile>>n;
                    inFile>>m;
                    for(int i=0;i<n;i++){
                            string temp;
                            inFile>>temp;
                            current_board.push_back(temp);
                    }
            }
            return current_board;
    }
    void Game::print_board(){
            for(int i=0;i<n;i++){
                    cout<<current_board[i]<<"\n";
            }
            return;
    }
    vector<int> Game::create_vector(int type,int xs,int ys,int x,int y){
            vector<int> possible_move;
            possible_move.push_back(type);
            possible_move.push_back(xs);
            possible_move.push_back(ys);
            possible_move.push_back(x);
            possible_move.push_back(y);
            return possible_move;
    }
    //color
    //0 ->> Black
    //1 ->> White
    vector<vector<int>> Game::valid_moves2(vector<string> &current_board,char player,char opp_player,char townhall,char opp_townhall){
            vector<vector<int>> possible_moves;
            for(int i=0;i<n;i++){
                    for(int j=0;j<m;j++){
                            if(current_board[i][j]==player){
                                    ///////////Cannon moves
                                    if(i>0&&i<(n-1)){
                                            if(current_board[i-1][j]==player&&current_board[i+1][j]==player){
                                                    if(i-2>=0&&current_board[i-2][j]=='-'){
                                                            if(i-3>=0&&!(current_board[i-3][j]==player||current_board[i-3][j]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-3,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i-4>=0&&!(current_board[i-4][j]==player||current_board[i-4][j]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-4,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                                    if(i+2<=(n-1)&&current_board[i+2][j]=='-'){
                                                            if(i+3<=n-1&&!(current_board[i+3][j]==player||current_board[i+3][j]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+3,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i+4<=n-1&&!(current_board[i+4][j]==player||current_board[i+4][j]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+4,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                    }
                                    if(j>0&&j<(m-1)){
                                            if(current_board[i][j-1]==player&&current_board[i][j+1]==player){
                                                    if(j-2>=0&&current_board[i][j-2]=='-'){
                                                            if(j-3>=0&&!(current_board[i][j-3]==player||current_board[i][j-3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i,j-3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(j-4>=0&&!(current_board[i][j-4]==player||current_board[i][j-4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i,j-4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                                    if(j+2<=(m-1)&&current_board[i][j+2]=='-'){
                                                            if(j+3<=m-1&&!(current_board[i][j+3]==player||current_board[i][j+3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i,j+3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(j+4<=m-1&&!(current_board[i][j+4]==player||current_board[i][j+4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i,j+4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                    }
                                    if(i>0&&j>0&&i<(n-1)&&j<(m-1)){
                                            if(current_board[i-1][j+1]==player&&current_board[i+1][j-1]==player){
                                                    if(i-2>=0&&j+2<=m-1&&current_board[i-2][j+2]=='-'){
                                                            if(i-3>=0&&j+3<=m-1&&!(current_board[i-3][j+3]==player||current_board[i-3][j+3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-3,j+3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i-4>=0&&j+4<=m-1&&!(current_board[i-4][j+4]==player||current_board[i-4][j+4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-4,j+4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                                    if(i+2<=(n-1)&&j-2>=0&&current_board[i+2][j-2]=='-'){
                                                            if(i+3<=n-1&&j-3>=0&&!(current_board[i+3][j-3]==player||current_board[i+3][j-3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+3,j-3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i+4<=n-1&&j-4>=0&&!(current_board[i+4][j-4]==player||current_board[i+4][j-4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+4,j-4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                            if(current_board[i+1][j+1]==player&&current_board[i-1][j-1]==player){
                                                    if(i-2>=0&&j-2>=0&&current_board[i-2][j-2]=='-'){
                                                            if(i-3>=0&&j-3>=0&&!(current_board[i-3][j-3]==player||current_board[i-3][j-3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-3,j-3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i-4>=0&&j-4>=0&&!(current_board[i-4][j-4]==player||current_board[i-4][j-4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i-4,j-4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                                    if(i+2<=(n-1)&&j+2<=m-1&&current_board[i+2][j-2]=='-'){
                                                            if(i+3<=n-1&&j+3<=m-1&&!(current_board[i+3][j+3]==player||current_board[i+3][j+3]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+3,j+3);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(i+4<=n-1&&j+4<=m-1&&!(current_board[i+4][j+4]==player||current_board[i+4][j+4]==townhall)){
                                                                    vector<int> possible_move=create_vector(1,i,j,i+4,j+4);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                    }
                                    ////////////////retreat moves
                                    if(i==0){
                                            if(j==0){
                                                    if(current_board[i][j+1]==opp_player){
                                                            if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                    vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
                                                                    vector<int> possible_move=create_vector(0,i,j,i+2,j+2);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                            else{
                                                    if(j==m-1){
                                                            if(current_board[i][j-1]==opp_player){
                                                                    if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                            vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                            possible_moves.push_back(possible_move);
                                                                    }
                                                                    if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
                                                                            vector<int> possible_move=create_vector(0,i,j,i+2,j-2);
                                                                            possible_moves.push_back(possible_move);
                                                                    }
                                                            }
                                                    }
                                                    else{
                                                            if(current_board[i][j-1]==opp_player||current_board[i][j+1]==opp_player){
                                                                    if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                            vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                            possible_moves.push_back(possible_move);
                                                                    }
                                                                    if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
                                                                            vector<int> possible_move=create_vector(0,i,j,i+2,j-2);
                                                                            possible_moves.push_back(possible_move);
                                                                    }
                                                                    if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
                                                                            vector<int> possible_move=create_vector(0,i,j,i+2,j+2);
                                                                            possible_moves.push_back(possible_move);
                                                                    }
                                                            }
                                                    }
                                            }
                                    }
                                    else if(i<=n-3){
                                            if(j==0){
                                                    if(current_board[i][j+1]==opp_player||current_board[i-1][j+1]==opp_player||current_board[i-1][j]==opp_player){
                                                            if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                    vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
                                                                    vector<int> possible_move=create_vector(0,i,j,i+2,j+2);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                            else{
                                                    if(j==m-1){
                                                            if(current_board[i][j-1]==opp_player||current_board[i-1][j-1]==opp_player||current_board[i-1][j]==opp_player){
                                                                    if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                        vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                        possible_moves.push_back(possible_move);
                                                                }
                                                                if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
                                                                        vector<int> possible_move=create_vector(0,i,j,i+2,j-2);
                                                                        possible_moves.push_back(possible_move);
                                                                }
                                                            }
                                                    }
                                                    else{
                                                            if(current_board[i][j+1]==opp_player||current_board[i][j-1]==opp_player||current_board[i-1][j]==opp_player||current_board[i-1][j+1]==opp_player||current_board[i-1][j-1]==opp_player){
                                                                    if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
                                                                        vector<int> possible_move=create_vector(0,i,j,i+2,j);
                                                                        possible_moves.push_back(possible_move);
                                                                }
                                                                if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
                                                                        vector<int> possible_move=create_vector(0,i,j,i+2,j-2);
                                                                        possible_moves.push_back(possible_move);
                                                                }
                                                                if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
                                                                        vector<int> possible_move=create_vector(0,i,j,i+2,j+2);
                                                                        possible_moves.push_back(possible_move);
                                                                }
                                                            }
                                                    }
                                            }
                                    }
                                    //Sideways moves
                                    if(j==0){
                                            if(current_board[i][j+1]==opp_player||current_board[i][j+1]==opp_townhall){
                                                    vector<int> possible_move=create_vector(0,i,j,i,j+1);
                                                    possible_moves.push_back(possible_move);
                                            }
                                    }
                                    else{
                                            if(j==m-1){
                                                    if(current_board[i][j-1]==opp_player||current_board[i][j-1]==opp_townhall){
                                                            vector<int> possible_move=create_vector(0,i,j,i,j-1);
                                                            possible_moves.push_back(possible_move);
                                                    }
                                            }
                                            else{
                                                    if(current_board[i][j-1]==opp_player||current_board[i][j-1]==opp_townhall){
                                                            vector<int> possible_move=create_vector(0,i,j,i,j-1);
                                                            possible_moves.push_back(possible_move);
                                                    }
                                                    if(current_board[i][j+1]==opp_player||current_board[i][j+1]==opp_townhall){
                                                            vector<int> possible_move=create_vector(0,i,j,i,j+1);
                                                            possible_moves.push_back(possible_move);
                                                    }
                                            }
                                    }
                                    //Soldier forward moves
                                    if(i>0){
                                            if(j==0){
                                                    if(current_board[i-1][j+1]==opp_player||current_board[i-1][j+1]==opp_townhall||current_board[i-1][j+1]=='-'){
                                                            vector<int> possible_move=create_vector(0,i,j,i-1,j+1);
                                                            possible_moves.push_back(possible_move);
                                                    }
                                                    if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
                                                            vector<int> possible_move=create_vector(0,i,j,i-1,j);
                                                            possible_moves.push_back(possible_move);
                                                    }
                                            }
                                            else{
                                                    if(j==m-1){
                                                            if(current_board[i-1][j-1]==opp_player||current_board[i-1][j-1]==opp_townhall||current_board[i-1][j-1]=='-'){
                                                                    vector<int> possible_move=create_vector(0,i,j,i-1,j-1);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
                                                                    vector<int> possible_move=create_vector(0,i,j,i-1,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                                    else{
                                                            if(current_board[i-1][j-1]==opp_player||current_board[i-1][j-1]==opp_townhall||current_board[i-1][j-1]=='-'){
                                                                    vector<int> possible_move=create_vector(0,i,j,i-1,j-1);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(current_board[i-1][j+1]==opp_player||current_board[i-1][j+1]==opp_townhall||current_board[i-1][j+1]=='-'){
                                                                    vector<int> possible_move=create_vector(0,i,j,i-1,j+1);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                            if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
                                                                    vector<int> possible_move=create_vector(0,i,j,i-1,j);
                                                                    possible_moves.push_back(possible_move);
                                                            }
                                                    }
                                            }
                                    }
                            }
                    }
            }
            return possible_moves;

    }
    vector<vector<int>> Game::valid_moves(int color){
            vector<vector<int>> possible_moves;
            char player;char opp_player;char townhall;char opp_townhall;
            if(color==0){
                    player='B';opp_player='W';townhall='#';opp_townhall='O';
            }
            else{
                    player='W';opp_player='B';townhall='O';opp_townhall='#';
            }
            if(color==0){
                    possible_moves=valid_moves2(current_board,player,opp_player,townhall,opp_townhall);
            }
            else{
                    vector<string> current_board_t;
                    for(int i=0;i<n;i++){
                            string temp="";
                            for(int j=0;j<m;j++){
                                    temp+=current_board[n-1-i][m-1-j];
                            }
                            current_board_t.push_back(temp);
                    }
                    possible_moves=valid_moves2(current_board_t,player,opp_player,townhall,opp_townhall);
                    for(int i=0;i<possible_moves.size();i++){
                            possible_moves[i][1]=n-1-possible_moves[i][1];
                            possible_moves[i][3]=n-1-possible_moves[i][3];
                            possible_moves[i][2]=m-1-possible_moves[i][2];
                            possible_moves[i][4]=m-1-possible_moves[i][4];
                    }
            }
            return possible_moves;
    }
// int main(){
//         vector<string> current_board=load_data();
//         //current_board=load_new_board();
//         //cout<<"\n";
//         print_board(current_board);
//         cout<<"\n";
//         vector<vector<int>> possible_moves=valid_moves(current_board,0);
//         for(int i=0;i<possible_moves.size();i++){
//                 for(int j=0;j<possible_moves[i].size();j++){
//                         cout<<possible_moves[i][j]<<" ";
//                 }
//                 cout<<"\n";
//         }
//         cout<<possible_moves.size()<<"\n";
//         return 0;
// }
