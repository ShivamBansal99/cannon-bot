#include<bits/stdc++.h>
#include<iostream>
#include"Game.h"
using namespace std;
Game::Game(int n, int m){
  Game::n=n;
  Game::m=m;
  load_new_board();
}
void Game::move(int mov){
	current_move.push_back(mov);
	vector<int > move = decode_move(mov);
	player_at_new_pos.push_back(the_board[move[3]][move[4]]);
	if(player_at_new_pos.back() !='-'){
		letsdel(move[3]*m+move[4],player_at_new_pos.back(),true);
		the_board[move[3]][move[4]]='-';
	}
	if(move[0]==0){
		char player_at_this = the_board[move[1]][move[2]];
		letsdel(move[1]*m+move[2],player_at_this,true);
		the_board[move[1]][move[2]] = '-';
		letsdel(move[3]*m+move[4],player_at_this,false);
		the_board[move[3]][move[4]] = player_at_this;
	}
	return ;
}
void Game::undo(int mov){
	vector<int > move = decode_move(current_move.back());
	if(move[0]==0){
		char player_at_this = the_board[move[3]][move[4]];
		letsdel(move[3]*m+move[4],player_at_this,true);
		the_board[move[3]][move[4]] = '-';
		letsdel(move[1]*m+move[2],player_at_this,false);
		the_board[move[1]][move[2]] = player_at_this;
	}
	if(player_at_new_pos.back() !='-'){
		letsdel(move[3]*m+move[4],player_at_new_pos.back(),false);
		the_board[move[3]][move[4]] = player_at_new_pos.back();
	}
	current_move.pop_back();
	player_at_new_pos.pop_back();
	return;
}
vector<string> Game::board(){
  return the_board;
}
bool  Game::check_ne(int x1,int y1,char player,vector<string> &current_board,bool opp){
	bool pp=false;int xd=0;
	opp?xd=(x1+1):xd=(x1-1);
	if(y1-1>=0&&current_board[x1][y1-1]==player){
		pp=true;
	}
	if(y1+1<=(m-1)&&current_board[x1][y1+1]==player){
		pp=true;
	}
	if(xd<=(n-1)&&xd>=0){
		if(current_board[xd][y1]==player){
			pp=true;
		}
		if(y1-1>=0&&current_board[xd][y1-1]==player){
			pp=true;
		}
		if(y1+1<=(m-1)&&current_board[xd][y1+1]==player){
			pp=true;
		}
	}
	return pp;
}
int  Game::encode_vector_move(vector<int> move){
	return encode_move(move[0],move[1],move[2],move[3],move[4]);
}
int  Game::encode_move(int type,int xs,int ys,int x,int y){
	int pro=m*n;int proo=pro*pro;
	return ((type)*proo)+((((xs*m)+ys)*pro)+((x*m)+y));
}
vector<int>  Game::decode_move(int mov){
	vector<int> the_move;
	int pro=m*n;int proo=pro*pro;int a1=mov/proo;mov=mov%proo;int m1=mov/pro;int m2=mov%pro;int xs=m1/m;int ys=m1%m;int x=m2/m;int y=m2%m;
	the_move.push_back(a1);
	the_move.push_back(xs);
	the_move.push_back(ys);
	the_move.push_back(x);
	the_move.push_back(y);
	return the_move;
}
void Game::attack_move1(bool del,int color1,int color2,int x,int y){
	if(color1==1){
		x=n-1-x;y=m-1-y;
	}
	if(color2==0){
		if(del){
			attack_space_of_soldiers_black[x][y]--;
		}
		else{
			attack_space_of_soldiers_black[x][y]++;
		}
	}
	else{
		if(del){
			attack_space_of_soldiers_white[x][y]--;
		}
		else{
			attack_space_of_soldiers_white[x][y]++;
		}
	}
	return;
}
void Game::attack_move2(bool del,int color1,int color2,int x,int y){
	if(color1==1){
		x=n-1-x;y=m-1-y;
	}
	if(color2==0){
		if(del){
			attack_space_of_cannons_black[x][y]--;
		}
		else{
			attack_space_of_cannons_black[x][y]++;
		}
	}
	else{
		if(del){
			attack_space_of_cannons_white[x][y]--;
		}
		else{
			attack_space_of_cannons_white[x][y]++;
		}
	}
	return;
}
void  Game::insert_move(int color1,int color2,int type,int xs,int ys,int x,int y){
	int mov;
	color1==0?mov=encode_move(type,xs,ys,x,y):mov=encode_move(type,n-1-xs,m-1-ys,n-1-x,m-1-y);
	color2==0?possible_moves_black.insert(mov):possible_moves_white.insert(mov);
	return;
}
void  Game::delete_move(int color1,int color2,int type,int xs,int ys,int x,int y){
	int mov;
	color1==0?mov=encode_move(type,xs,ys,x,y):mov=encode_move(type,n-1-xs,m-1-ys,n-1-x,m-1-y);
	color2==0?possible_moves_black.erase(mov):possible_moves_white.erase(mov);
	return;
}
void  Game::add_retreat_moves(int color1,int color2,int x1,int y1,char player,vector<string> &current_board){
	if(x1-2>=0&&(current_board[x1-2][y1]=='-'||current_board[x1-2][y1]==player))
		insert_move(color1,color2,0,x1,y1,x1-2,y1);
	if(x1-2>=0&&y1-2>=0&&(current_board[x1-2][y1-2]=='-'||current_board[x1-2][y1-2]==player))
		insert_move(color1,color2,0,x1,y1,x1-2,y1-2);
	if(x1-2>=0&&y1+2<=(m-1)&&(current_board[x1-2][y1+2]=='-'||current_board[x1-2][y1+2]==player))
		insert_move(color1,color2,0,x1,y1,x1-2,y1+2);
	return;
}
void  Game::delete_retreat_moves(int color1,int color2,int x1,int y1,char player,vector<string> &current_board){
	if(x1-2>=0&&(current_board[x1-2][y1]=='-'||current_board[x1-2][y1]==player))
		delete_move(color1,color2,0,x1,y1,x1-2,y1);
	if(x1-2>=0&&y1-2>=0&&(current_board[x1-2][y1-2]=='-'||current_board[x1-2][y1-2]==player))
		delete_move(color1,color2,0,x1,y1,x1-2,y1-2);
	if(x1-2>=0&&y1+2<=(m-1)&&(current_board[x1-2][y1+2]=='-'||current_board[x1-2][y1+2]==player))
		delete_move(color1,color2,0,x1,y1,x1-2,y1+2);
	return;
}
void  Game::letsdel(int init_pos,char player,bool del){
	char opp_player;char townhall;char opp_townhall;
	vector<string> current_board;
	int color=0;
	bool is_townhall=false;
	if(player=='#'||player=='O'){
		is_townhall=true;
	}
	if(player=='B'||player=='#'){
		color=0;
		if(!is_townhall)
			if(del)
				space_of_soldiers_black.erase(init_pos);
			else
				space_of_soldiers_black.insert(init_pos);
		player='B';opp_player='W';townhall='#';opp_townhall='O';
		for(int i=0;i<n;i++){
			current_board.push_back(the_board[i]);
		}
	}
	else{
		color=1;
		if(!is_townhall)
			if(del)
				space_of_soldiers_white.erase(init_pos);
			else
				space_of_soldiers_white.insert(init_pos);
		init_pos=m*n-1-init_pos;
		player='W';opp_player='B';townhall='O';opp_townhall='#';
		for(int i=0;i<n;i++){
			string temp="";
			for(int j=0;j<m;j++){
				temp+=the_board[n-1-i][m-1-j];
			}
			current_board.push_back(temp);
		}
	}
	int xx=init_pos/m;
	int yy=init_pos%m;
	//cout<<"d1";
	//////Forward of same player
	if(!is_townhall){
		if(xx-1>=0){
			attack_move1(del,color,color,xx-1,yy);
			if(!(current_board[xx-1][yy]==player||current_board[xx-1][yy]==townhall)){
				del?delete_move(color,color,0,xx,yy,xx-1,yy):insert_move(color,color,0,xx,yy,xx-1,yy);
			}
			if(yy-1>=0){
				attack_move1(del,color,color,xx-1,yy-1);
				if(!(current_board[xx-1][yy-1]==player||current_board[xx-1][yy-1]==townhall)){
					del?delete_move(color,color,0,xx,yy,xx-1,yy-1):insert_move(color,color,0,xx,yy,xx-1,yy-1);
				}
			}
			if(yy+1<=(m-1)){
				attack_move1(del,color,color,xx-1,yy+1);
				if(!(current_board[xx-1][yy+1]==player||current_board[xx-1][yy+1]==townhall)){
					del?delete_move(color,color,0,xx,yy,xx-1,yy+1):insert_move(color,color,0,xx,yy,xx-1,yy+1); 
				}
			}
		}
	}
	//cout<<"d2";
	//////////Side of same player
	if(!is_townhall){
		if((yy-1)>=0){
			attack_move1(del,color,color,xx,yy-1);
			if(current_board[xx][yy-1]==opp_player||current_board[xx][yy-1]==opp_townhall){
				del?delete_move(color,color,0,xx,yy,xx,yy-1):insert_move(color,color,0,xx,yy,xx,yy-1);
			}
		}
		if((yy+1)<=(m-1)){
			attack_move1(del,color,color,xx,yy+1);
			if(current_board[xx][yy+1]==opp_player||current_board[xx][yy+1]==opp_townhall){
				del?delete_move(color,color,0,xx,yy,xx,yy+1):insert_move(color,color,0,xx,yy,xx,yy+1);
			}
		}
	}
	//cout<<"d3";
	///////////Retreat of same player
	if(!is_townhall){
		if((xx+2)<=(n-1)&&check_ne(xx,yy,opp_player,current_board,false)){
			attack_move1(del,color,color,xx+2,yy);
			if(!(current_board[xx+2][yy]==player||current_board[xx+2][yy]==townhall)){
				del?delete_move(color,color,0,xx,yy,xx+2,yy):insert_move(color,color,0,xx,yy,xx+2,yy);
			}
			if((yy+2)<=(m-1)){
				attack_move1(del,color,color,xx+2,yy+2);
				if(!(current_board[xx+2][yy+2]==player||current_board[xx+2][yy+2]==townhall)){
					del?delete_move(color,color,0,xx,yy,xx+2,yy+2):insert_move(color,color,0,xx,yy,xx+2,yy+2);
				}
			}
			if((yy-2)>=0){
				attack_move1(del,color,color,xx+2,yy-2);
				if(!(current_board[xx+2][yy-2]==player||current_board[xx+2][yy-2]==townhall)){
					del?delete_move(color,color,0,xx,yy,xx+2,yy-2):insert_move(color,color,0,xx,yy,xx+2,yy-2);
				}
			}
		}
	}
	//cout<<"d4";
	/////////////Cannon using that player at centre
	if(!is_townhall){
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				if(i==0&&j==0){
					continue;
				}
				if((xx-i)<=(n-1)&&(xx-i)>=0&&(yy-j)<=(m-1)&&(yy-j)>=0&&(xx+3*i)<=(n-1)&&(xx+3*i)>=0&&(yy+3*j)<=(m-1)&&(yy+3*j)>=0&&
					current_board[xx+i][yy+j]==player&&current_board[xx-i][yy-j]==player&&current_board[xx+2*i][yy+2*j]=='-')
				{
					attack_move2(del,color,color,xx+3*i,yy+3*j);
					if(!(current_board[xx+3*i][yy+3*j]==player||current_board[xx+3*i][yy+3*j]==townhall)){
						del?delete_move(color,color,1,xx,yy,xx+3*i,yy+3*j):insert_move(color,color,1,xx,yy,xx+3*i,yy+3*j);
					}
					if((xx+4*i)<=(n-1)&&(xx+4*i)>=0&&(yy+4*j)<=(m-1)&&(yy+4*j)>=0){
						attack_move2(del,color,color,xx+4*i,yy+4*j);
						if(!(current_board[xx+4*i][yy+4*j]==player||current_board[xx+4*i][yy+4*j]==townhall)){
							del?delete_move(color,color,1,xx,yy,xx+4*i,yy+4*j):insert_move(color,color,1,xx,yy,xx+4*i,yy+4*j);
						}
					}
				}
			}
		}
	}
	//cout<<"d5";
	////////////At end of cannon same player
	if(!is_townhall){
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				if(i==0&&j==0){
					continue;
				}
				if((xx+3*i)<=(n-1)&&(xx+3*i)>=0&&(yy+3*j)<=(m-1)&&(yy+3*j)>=0&&current_board[xx+i][yy+j]==player&&
					current_board[xx+2*i][yy+2*j]==player&&current_board[xx+3*i][yy+3*j]=='-')
				{
					del?delete_move(color,color,0,xx,yy,xx+3*i,yy+3*j):insert_move(color,color,0,xx,yy,xx+3*i,yy+3*j);
				}
			}
		}
	}
	//cout<<"d6";
	//////////////Player at the fire of nearby cannons
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0&&j==0){
				continue;
			}
			if((xx+4*i)<=(n-1)&&(xx+4*i)>=0&&(yy+4*j)<=(m-1)&&(yy+4*j)>=0&&current_board[xx+4*i][yy+4*j]==player&&
				current_board[xx+3*i][yy+3*j]==player&&current_board[xx+2*i][yy+2*j]==player&&current_board[xx+i][yy+j]=='-')
			{
				del?insert_move(color,color,1,xx+3*i,yy+3*j,xx,yy):delete_move(color,color,1,xx+3*i,yy+3*j,xx,yy);
			}
			if((xx+5*i)<=(n-1)&&(xx+5*i)>=0&&(yy+5*j)<=(m-1)&&(yy+5*j)>=0&&current_board[xx+5*i][yy+5*j]==player&&
				current_board[xx+4*i][yy+4*j]==player&&current_board[xx+3*i][yy+3*j]==player&&current_board[xx+2*i][yy+2*j]=='-')
			{
				del?insert_move(color,color,1,xx+4*i,yy+4*j,xx,yy):delete_move(color,color,1,xx+4*i,yy+4*j,xx,yy);
			}
		}
	}
	//cout<<"d7";
	//////////////////////At the centre but delete movements of nearby players
	if(!is_townhall){
		if(xx>0&&xx<(n-1)){
			if(current_board[xx-1][yy]==player&&current_board[xx+1][yy]==player){
				if(xx-2>=0&&current_board[xx-2][yy]=='-'){
					del?delete_move(color,color,0,xx+1,yy,xx-2,yy):insert_move(color,color,0,xx+1,yy,xx-2,yy);
				}
				if(xx+2<=n-1&&current_board[xx+2][yy]=='-'){
					del?delete_move(color,color,0,xx-1,yy,xx+2,yy):insert_move(color,color,0,xx-1,yy,xx+2,yy);
				}
			}
		}
		if(yy>0&&yy<(m-1)){
			if(current_board[xx][yy-1]==player&&current_board[xx][yy+1]==player){
				if(yy-2>=0&&current_board[xx][yy-2]=='-'){
					del?delete_move(color,color,0,xx,yy+1,xx,yy-2):insert_move(color,color,0,xx,yy+1,xx,yy-2);
				}
				if(yy+2<=m-1&&current_board[xx][yy+2]=='-'){
					del?delete_move(color,color,0,xx,yy-1,xx,yy+2):insert_move(color,color,0,xx,yy-1,xx,yy+2);
				}
			}
		}
		if(xx>0&&yy>0&&xx<(n-1)&&yy<(m-1)){
			if(current_board[xx+1][yy-1]==player&&current_board[xx-1][yy+1]==player){
				if((yy-2)>=0&&(xx+2)<=(n-1)&&current_board[xx+2][yy-2]=='-'){
					del?delete_move(color,color,0,xx-1,yy+1,xx+2,yy-2):insert_move(color,color,0,xx-1,yy+1,xx+2,yy-2);
				}
				if((yy+2)<=(m-1)&&(xx-2)>=0&&current_board[xx-2][yy+2]=='-'){
					del?delete_move(color,color,0,xx+1,yy-1,xx-2,yy+2):insert_move(color,color,0,xx+1,yy-1,xx-2,yy+2);
				}
			}
			if(current_board[xx-1][yy-1]==player&&current_board[xx+1][yy+1]==player){
				if(yy-2>=0&&xx-2>=0&&current_board[xx-2][yy-2]=='-'){
					del?delete_move(color,color,0,xx+1,yy+1,xx-2,yy-2):insert_move(color,color,0,xx+1,yy+1,xx-2,yy-2);
				}
				if((yy+2)<=(m-1)&&(xx+2)<=(n-1)&&current_board[xx+2][yy+2]=='-'){
					del?delete_move(color,color,0,xx-1,yy-1,xx+2,yy+2):insert_move(color,color,0,xx-1,yy-1,xx+2,yy+2);
				}
			}
		}
	}
	//cout<<"d8";
	////////////////////At the side of old cannons but delete movements of nearby players
	if(!is_townhall){
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				if(i==0&&j==0){
					continue;
				}
				if((xx+4*i)>=0&&(yy+4*j)>=0&&(xx+4*i)<=(n-1)&&(yy+4*j)<=(m-1)&&current_board[xx+2*i][yy+2*j]==player&&current_board[xx+i][yy+j]==player
					&&current_board[xx+3*i][yy+3*j]=='-'){
					attack_move2(del,color,color,xx+4*i,yy+4*j);
					if(!(current_board[xx+4*i][yy+4*j]==player||current_board[xx+4*i][yy+4*j]==townhall))	
						del?delete_move(color,color,1,xx+i,yy+j,xx+4*i,yy+4*j):insert_move(color,color,1,xx+i,yy+j,xx+4*i,yy+4*j);
				}
				if((xx+5*i)>=0&&(yy+5*j)>=0&&(xx+5*i)<=(n-1)&&(yy+5*j)<=(m-1)&&current_board[xx+2*i][yy+2*j]==player&&current_board[xx+i][yy+j]==player
					&&current_board[xx+3*i][yy+3*j]=='-'){
					attack_move2(del,color,color,xx+5*i,yy+5*j);
					if(!(current_board[xx+5*i][yy+5*j]==player||current_board[xx+5*i][yy+5*j]==townhall))	
						del?delete_move(color,color,1,xx+i,yy+j,xx+5*i,yy+5*j):insert_move(color,color,1,xx+i,yy+j,xx+5*i,yy+5*j);
				}
				if((xx+2*i)>=0&&(yy+2*j)>=0&&(xx+2*i)<=(n-1)&&(yy+2*j)<=(m-1)&&(xx-2*i)>=0&&(yy-2*j)>=0&&(xx-2*i)<=(n-1)&&(yy-2*j)<=(m-1)
					&&current_board[xx+2*i][yy+2*j]==player&&current_board[xx+i][yy+j]==player
					&&current_board[xx-i][yy-j]=='-'){
					attack_move2(del,color,color,xx-2*i,yy-2*j);
					if(!(current_board[xx-2*i][yy-2*j]==player||current_board[xx-2*i][yy-2*j]==townhall))	
						del?delete_move(color,color,1,xx+i,yy+j,xx-2*i,yy-2*j):insert_move(color,color,1,xx+i,yy+j,xx-2*i,yy-2*j);
				}
				if((xx+2*i)>=0&&(yy+2*j)>=0&&(xx+2*i)<=(n-1)&&(yy+2*j)<=(m-1)&&(xx-3*i)>=0&&(yy-3*j)>=0&&(xx-3*i)<=(n-1)&&(yy-3*j)<=(m-1)
					&&current_board[xx+2*i][yy+2*j]==player&&current_board[xx+i][yy+j]==player
					&&current_board[xx-i][yy-j]=='-'){
					attack_move2(del,color,color,xx-3*i,yy-3*j);
					if(!(current_board[xx-3*i][yy-3*j]==player||current_board[xx-3*i][yy-3*j]==townhall))	
						del?delete_move(color,color,1,xx+i,yy+j,xx-3*i,yy-3*j):insert_move(color,color,1,xx+i,yy+j,xx-3*i,yy-3*j);
				}
				if((xx+i)>=0&&(yy+j)>=0&&(xx+i)<=(n-1)&&(yy+j)<=(m-1)&&(xx-2*i)>=0&&(yy-2*j)>=0&&(xx-2*i)<=(n-1)&&(yy-2*j)<=(m-1)
					&&current_board[xx-2*i][yy-2*j]==player&&current_board[xx-i][yy-j]==player
					&&current_board[xx+i][yy+j]=='-'){
					del?delete_move(color,color,0,xx-2*i,yy-2*j,xx+i,yy+j):insert_move(color,color,0,xx-2*i,yy-2*j,xx+i,yy+j);
				}
			}
		}
	}
	//cout<<"d9";
	/////////Players on prev
	if(!is_townhall){
		if(xx<n-1){
			if(yy+1<=(m-1)&&current_board[xx+1][yy+1]==player){
				del?insert_move(color,color,0,xx+1,yy+1,xx,yy):delete_move(color,color,0,xx+1,yy+1,xx,yy);
			}
			if(current_board[xx+1][yy]==player){
				del?insert_move(color,color,0,xx+1,yy,xx,yy):delete_move(color,color,0,xx+1,yy,xx,yy);
			}
			if(yy-1>=0&&current_board[xx+1][yy-1]==player){
				del?insert_move(color,color,0,xx+1,yy-1,xx,yy):delete_move(color,color,0,xx+1,yy-1,xx,yy);
			}
		}
	}
	///////Retreat now possible at that pos
	if(xx-2>=0&&current_board[xx-2][yy]==player&&check_ne(xx-2,yy,opp_player,current_board,false)){
		del?insert_move(color,color,0,xx-2,yy,xx,yy):delete_move(color,color,0,xx-2,yy,xx,yy);
	}
	if(xx-2>=0&&yy-2>=0&&current_board[xx-2][yy-2]==player&&check_ne(xx-2,yy-2,opp_player,current_board,false)){
		del?insert_move(color,color,0,xx-2,yy-2,xx,yy):delete_move(color,color,0,xx-2,yy-2,xx,yy);
	}
	if(xx-2>=0&&yy+2<=(m-1)&&current_board[xx-2][yy+2]==player&&check_ne(xx-2,yy+2,opp_player,current_board,false)){
		del?insert_move(color,color,0,xx-2,yy+2,xx,yy):delete_move(color,color,0,xx-2,yy+2,xx,yy);
	}
	////////////////Cannon is created
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0&&j==0){
				continue;
			}
			if((xx+3*i)>=0&&(yy+3*j)>=0&&(xx+3*i)<=(n-1)&&(yy+3*j)<=(m-1)&&
				current_board[xx+i][yy+j]==player&&current_board[xx+(2*i)][yy+(2*j)]==player&&current_board[xx+(3*i)][yy+(3*j)]==player){
				attack_move1(!del,color,color,xx,yy);
				del?insert_move(color,color,0,xx+(3*i),yy+(3*j),xx,yy):delete_move(color,color,0,xx+(3*i),yy+(3*j),xx,yy);
				if((xx-i)<=(n-1)&&(yy-j)<=(m-1)&&(xx-i)>=0&&(yy-j)>=0){
					attack_move2(!del,color,color,xx-i,yy-j);
					if(!(current_board[xx-i][yy-j]==player||current_board[xx-i][yy-j]==townhall))
						del?insert_move(color,color,1,xx+2*i,yy+2*j,xx-i,yy-j):delete_move(color,color,1,xx+2*i,yy+2*j,xx-i,yy-j);
				}
				if((xx-2*i)<=(n-1)&&(yy-2*j)<=(m-1)&&(xx-2*i)>=0&&(yy-2*j)>=0){
					attack_move2(!del,color,color,xx-2*i,yy-2*j);
					if(!(current_board[xx-2*i][yy-2*j]==player||current_board[xx-2*i][yy-2*j]==townhall))
						del?insert_move(color,color,1,xx+2*i,yy+2*j,xx-2*i,yy-2*j):delete_move(color,color,1,xx+2*i,yy+2*j,xx-2*i,yy-2*j);
				}
			}
		}
	}
	///////////////Opp team
	////////////////////////////Sideways moves
	if(yy-1>=0&&current_board[xx][yy-1]==opp_player){
		attack_move1(del,color,1-color,xx,yy);
		del?delete_move(color,1-color,0,xx,yy-1,xx,yy):insert_move(color,1-color,0,xx,yy-1,xx,yy);
	}
	if(yy+1<=(m-1)&&current_board[xx][yy+1]==opp_player){
		attack_move1(del,color,1-color,xx,yy);
		del?delete_move(color,1-color,0,xx,yy+1,xx,yy):insert_move(color,1-color,0,xx,yy+1,xx,yy);
	}
	////////////////Cannon now free
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0&&j==0){
				continue;
			}
			if(xx+(3*i)>=0&&yy+(3*j)>=0&&xx+3*i<=(n-1)&&yy+(3*j)<=(m-1)&&
				current_board[xx+i][yy+j]==opp_player&&current_board[xx+(2*i)][yy+(2*j)]==opp_player&&current_board[xx+(3*i)][yy+(3*j)]==opp_player){
				attack_move1(!del,color,1-color,xx,yy);
				del?insert_move(color,1-color,0,xx+(3*i),yy+(3*j),xx,yy):delete_move(color,1-color,0,xx+(3*i),yy+(3*j),xx,yy);
				if((xx-i)<=(n-1)&&(yy-j)<=(m-1)&&(xx-i)>=0&&(yy-j)>=0){
					attack_move2(!del,color,1-color,xx-i,yy-j);
					if(!(current_board[xx-i][yy-j]==opp_player||current_board[xx-i][yy-j]==opp_townhall))
						del?insert_move(color,1-color,1,xx+2*i,yy+2*j,xx-i,yy-j):delete_move(color,1-color,1,xx+2*i,yy+2*j,xx-i,yy-j);
				}
				if((xx-2*i)<=(n-1)&&(yy-2*j)<=(m-1)&&(xx-2*i)>=0&&(yy-2*j)>=0){
					attack_move2(!del,color,1-color,xx-2*i,yy-2*j);
					if(!(current_board[xx-2*i][yy-2*j]==opp_player||current_board[xx-2*i][yy-2*j]==opp_townhall))
						del?insert_move(color,1-color,1,xx+2*i,yy+2*j,xx-2*i,yy-2*j):delete_move(color,1-color,1,xx+2*i,yy+2*j,xx-2*i,yy-2*j);
				}
			}
		}
	}
	//////////////Retreat moves
	////////////Check if 5 players around it are affected
	if(!is_townhall){
		char tempp=current_board[xx][yy];
		current_board[xx][yy]='-';
		if(xx-2>=0){
			if(yy-1>=0&&current_board[xx][yy-1]==opp_player&&(!check_ne(xx,yy-1,player,current_board,true))){
				del?delete_retreat_moves(color,1-color,xx,yy-1,player,current_board):add_retreat_moves(color,1-color,xx,yy-1,player,current_board);
			}
			if(yy+1<=(m-1)&&current_board[xx][yy+1]==opp_player&&(!check_ne(xx,yy+1,player,current_board,true))){
				del?delete_retreat_moves(color,1-color,xx,yy+1,player,current_board):add_retreat_moves(color,1-color,xx,yy+1,player,current_board);
			}
		}
		if(xx-3>=0){
			if(current_board[xx-1][yy]==opp_player&&(!check_ne(xx-1,yy,player,current_board,true))){
				del?delete_retreat_moves(color,1-color,xx-1,yy,player,current_board):add_retreat_moves(color,1-color,xx-1,yy,player,current_board);
			}
			if(yy-1>=0&&current_board[xx-1][yy-1]==opp_player&&(!check_ne(xx-1,yy-1,player,current_board,true))){
				del?delete_retreat_moves(color,1-color,xx-1,yy-1,player,current_board):add_retreat_moves(color,1-color,xx-1,yy-1,player,current_board);
			}
			if(yy+1<=(m-1)&&current_board[xx-1][yy+1]==opp_player&&(!check_ne(xx-1,yy+1,player,current_board,true))){
				del?delete_retreat_moves(color,1-color,xx-1,yy+1,player,current_board):add_retreat_moves(color,1-color,xx-1,yy+1,player,current_board);
			}
		}
		current_board[xx][yy]=tempp;
	}
	return;
}






void  Game::load_new_board(){
	for(int i=0;i<n;i++){
		string row;
		vector<int> a1;
		vector<int> a2;
		vector<int> a3;
		vector<int> a4;
		for(int j=0;j<m;j++){
			row+="-";
			a1.push_back(0);
			a2.push_back(0);
			a3.push_back(0);
			a4.push_back(0);
		}
		attack_space_of_soldiers_black.push_back(a1);
		attack_space_of_soldiers_white.push_back(a2);
		attack_space_of_cannons_black.push_back(a3);
		attack_space_of_cannons_white.push_back(a4);
		the_board.push_back(row);
	}
	for(int i=1;i<m;i=i+2){
		letsdel((n-1)*m+i,'#',false);
		the_board[n-1][i]='#';
	}
	for(int i=0;i<m;i=i+2){
		the_board[0][i]='O';
		letsdel(i,'O',false);
	}
	for(int i=0;i<m;i=i+2){
		letsdel((n-1)*m+i,'B',false);
		the_board[n-1][i]='B';
		letsdel((n-2)*m+i,'B',false);
		the_board[n-2][i]='B';
		letsdel((n-3)*m+i,'B',false);
		the_board[n-3][i]='B';
	}
	for(int i=1;i<m;i=i+2){
		the_board[0][i]='W';
		letsdel(i,'W',false);
		the_board[1][i]='W';
		letsdel(m+i,'W',false);
		the_board[2][i]='W';
		letsdel(2*m+i,'W',false);
	}
	return;
}
void  Game::load_data(){
	ifstream inFile;
	inFile.open("sample_test1.txt");
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
			the_board.push_back(temp);
		}
	}
	return;
}
void  Game::print_board(){
	cerr<<endl;
	for(int i=0;i<n;i++){
		cerr<<the_board[i]<<endl;
	}
	cerr<<endl;
	return;
}
void  Game::print_moves(){
	cerr<<"Possible moves black: "<<possible_moves_black.size()<<endl;
	for(auto itr=possible_moves_black.begin();itr!=possible_moves_black.end();itr++){
		vector<int> nee=decode_move((*itr));
		for(int j=0;j<nee.size();j++){
			cerr<<nee[j]<<" ";
		}
		cerr<<endl;
	}
	cerr<<"Possible moves white: "<<possible_moves_white.size()<<endl;
	for(auto itr=possible_moves_white.begin();itr!=possible_moves_white.end();itr++){
		vector<int> nee=decode_move((*itr));
		for(int j=0;j<nee.size();j++){
			cerr<<nee[j]<<" ";
		}
		cerr<<endl;
	}
}
float Game::eval_function(int move){
	float value=0;
	int num_black_soldiers=0;
	int num_white_soldiers=0;
	int black_y_sum=0;
	int white_y_sum=0;
	int num_white_townhalls=0;
	int num_black_townhalls=0;


	unordered_map<int,int> backup_on_each_soldier_black;
	unordered_map<int,int> attack_on_each_soldier_black;
	unordered_map<int,int> opp_attacked_by_blackCannons;
	int num_attack_on_black_townhall=0;
	int num_blocks_attacked_by_black=0;
	int value_of_all_soldiers_black=0;
	int value_of_all_cannons_black=0;
	int num_opp_attacked_by_blackCannons=0;
	int num_pos_attacked_by_cannons_black=0;
	int num_cannons_black=0;




	unordered_map<int,int> backup_on_each_soldier_white;
	unordered_map<int,int> attack_on_each_soldier_white;
	unordered_map<int,int> opp_attacked_by_whiteCannons;
	int num_attack_on_white_townhall=0;
	int num_blocks_attacked_by_white=0;
	int value_of_all_soldiers_white=0;
	int value_of_all_cannons_white=0;
	int num_opp_attacked_by_whiteCannons=0;
	int num_pos_attacked_by_cannons_white=0;
	int num_cannons_white=0;



	int cann=0;
	int sold=0;
	int position=0;
	int xx=0;
	int yy=0;

	for(auto i=space_of_soldiers_black.begin();i!=space_of_soldiers_black.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_cannons_white[xx][yy];
		opp_attacked_by_whiteCannons[position]=sold;
		if(sold>0) num_opp_attacked_by_whiteCannons+=1;
	}

	for(auto i=space_of_soldiers_white.begin();i!=space_of_soldiers_white.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_cannons_black[xx][yy];
		opp_attacked_by_blackCannons[position]=sold;
		if(sold>0) num_opp_attacked_by_blackCannons+=1;
	}

	for(auto i=space_of_soldiers_black.begin();i!=space_of_soldiers_black.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_soldiers_white[xx][yy];
		attack_on_each_soldier_black.insert(make_pair(position,sold));
	}


	for(auto i=space_of_soldiers_white.begin();i!=space_of_soldiers_white.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_soldiers_black[xx][yy];
		attack_on_each_soldier_white.insert(make_pair(position,sold));
	}



	for(auto i=space_of_soldiers_black.begin();i!=space_of_soldiers_black.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_soldiers_black[xx][yy];
		cann=attack_space_of_cannons_black[xx][yy];
		backup_on_each_soldier_black.insert(make_pair(position,cann+sold));
	}

	for(auto i=space_of_soldiers_white.begin();i!=space_of_soldiers_white.end();i++){
		position=*i;
		xx=position/m;yy=position%m;
		sold=attack_space_of_soldiers_white[xx][yy];
		cann=attack_space_of_cannons_white[xx][yy];
		backup_on_each_soldier_white.insert(make_pair(position,cann+sold));
	}
	int temp_value=0;

	for(auto i=space_of_soldiers_black.begin();i!=space_of_soldiers_black.end();i++){
		position=*i;
		temp_value=backup_on_each_soldier_black[position]- attack_on_each_soldier_black[position];
		xx=position/m;yy=position%m;
		black_y_sum+=n-1-xx;
		if(temp_value<0&&move==1){
			value_of_all_soldiers_black+=temp_value*60;
		}
	}

	for(auto i=space_of_soldiers_white.begin();i!=space_of_soldiers_white.end();i++){
		position=*i;
		temp_value=backup_on_each_soldier_white[position]- attack_on_each_soldier_white[position];
		xx=position/m;yy=position%m;
		white_y_sum+=n-1-xx;
		if(temp_value<0&&move==0){
			value_of_all_soldiers_white+=temp_value*60;
		}
	}
	for(auto itr=cannon_pos_black.begin();itr!=cannon_pos_black.end();itr++){
		position=(*itr).first;
		xx=position/m;yy=position%m;
		temp_value=backup_on_each_soldier_black[position]- attack_on_each_soldier_black[position];
		if(temp_value<0&&move==1){
			value_of_all_cannons_black+=temp_value*30;
		}
		else{
			if((attack_on_each_soldier_black[position]>0||opp_attacked_by_whiteCannons.find(position)!=opp_attacked_by_whiteCannons.end())&&move==1){
				value_of_all_cannons_black-=15;
			}
		}
	}
	for(auto itr=cannon_pos_white.begin();itr!=cannon_pos_white.end();itr++){
		position=(*itr).first;
		temp_value=backup_on_each_soldier_white[position]- attack_on_each_soldier_white[position];
		xx=position/m;yy=position%m;
		if(temp_value<0&&move==0){
			value_of_all_cannons_white+=temp_value*30;
		}
		else{
			if((attack_on_each_soldier_white[position]>0||opp_attacked_by_blackCannons.find(position)!=opp_attacked_by_blackCannons.end())&&move==0){
				value_of_all_cannons_white-=15;
			}
		}
	}

	num_black_soldiers=space_of_soldiers_black.size();
	num_white_soldiers=space_of_soldiers_white.size();
	num_blocks_attacked_by_white=attack_space_of_soldiers_white.size();
	num_blocks_attacked_by_black=attack_space_of_soldiers_black.size();
	num_pos_attacked_by_cannons_white=attack_space_of_cannons_white.size();
	num_pos_attacked_by_cannons_black=attack_space_of_cannons_black.size();
	num_cannons_white=cannon_pos_white.size();
	num_cannons_black=cannon_pos_black.size();

	for(int i=0;i<m;i=i+2){
		if(the_board[0][i]=='O'){
			position=i;
			xx=position/m;yy=position%m;
			if(attack_space_of_cannons_black[xx][yy]!=0){
				num_attack_on_white_townhall+=2;
			}
			if(attack_space_of_soldiers_black[xx][yy]!=0){
				num_attack_on_white_townhall++;
			}
			num_white_townhalls++;
		}
	}

	for(int i=1;i<m;i=i+2){
		if(the_board[n-1][i]=='#'){
			position=(n-1)*m+i;
			xx=position/m;yy=position%m;
			if(attack_space_of_cannons_white[xx][yy]!=0){
				num_attack_on_black_townhall+=2;
			}
			if(attack_space_of_soldiers_white[xx][yy]!=0){
				num_attack_on_black_townhall++;
			}
			num_black_townhalls++;
		}
	}


	value+=value_of_all_soldiers_black;
	////cout<<value<<endl;
	value-=value_of_all_soldiers_white;
	//cout<<value<<endl;


	value-=num_attack_on_black_townhall*20;
	////cout<<value<<endl;
	value+=num_attack_on_white_townhall*20;
	//cout<<value<<endl;
	// if(num_attack_on_black_townhall>0){
	// 	value-=30;
	// }
	// else{
	// 	value+=30;
	// }
	


	value+=value_of_all_cannons_black;
	////cout<<value<<endl;
	value-=value_of_all_cannons_white;
	//cout<<value<<endl;

	//value+=num_cannons_black;
	////cout<<value<<endl;
	//value-=num_cannons_white;
	////cout<<value<<endl;


	value+=num_black_soldiers*50;
	////////cout<<value<<endl;
	value-=num_white_soldiers*50;
	//cout<<value<<endl;

	if(num_black_townhalls==3){
		value-=75;
	}
	////cout<<value<<endl;
	if(num_white_townhalls==3){
		value+=75;
	}
	//cout<<value<<endl;


	if(num_black_townhalls==2){
		value-=10000;
	}
	////cout<<value<<endl;
	if(num_white_townhalls==2){
		value+=10000;
	}
	//cout<<value<<endl;


	//value+=num_blocks_attacked_by_black;
	////cout<<value<<endl;
	//value-=num_blocks_attacked_by_white;
	////cout<<value<<endl;


	value+=num_opp_attacked_by_blackCannons*22;
	////////cout<<value<<endl;
	value-=num_opp_attacked_by_whiteCannons*22;
	//cout<<value<<endl;
	


	//value+=num_pos_attacked_by_cannons_black*12;
	////cout<<value<<endl;
	//value-=num_pos_attacked_by_cannons_white*12;
	////cout<<value<<endl;


	value+=black_y_sum*0.7f;
	////cout<<value<<endl;
	value-=white_y_sum*0.7f;
	//cout<<value<<endl;


	return value;
}
unordered_set<int> Game::validMoves(int player){
	if(player==1) return possible_moves_white;
	return possible_moves_black;
}
// int main(){
//         ////////////cout<<possible_moves.size()<<"\n";
//         return 0;
// }
