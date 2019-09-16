#include<bits/stdc++.h>
#include<iostream>
#include"Game.h"
using namespace std;
    Game::Game(int n, int m){
      Game::n=n;
      Game::m=m;
      Game::current_board = load_new_board();
      Game::prev_board = load_new_board();
    }
    void Game::move(vector<int> mov){
        for(int i=0;i<current_board.size();i++){
          prev_board[i]=current_board[i];
        }
        if(mov[0]==1){
          current_board[mov[3]][mov[4]]='-';
        }else{
          current_board[mov[3]][mov[4]]=current_board[mov[1]][mov[2]];
          current_board[mov[1]][mov[2]]='-';
        }
        return;
        //print_board();
    }
    void Game::undo(){
      for(int i=0;i<current_board.size();i++){
        current_board[i]=prev_board[i];
      }
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
            //////////////cout<<1<<endl;
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
                    ////////////cout<<current_board[i]<<"\n";
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
    vector<vector<int>> Game::valid_moves2(vector<string> &current_board,char player,char opp_player,char townhall,char opp_townhall,
	unordered_map<int,int> &attack_space_of_cannons,unordered_map<int,int> &attack_space_of_soldiers,vector<int> &space_of_soldiers,
	unordered_map<int,int> &cannon_pos){
	vector<vector<int>> possible_moves;
	vector<int> possible_move;
	int position=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(current_board[i][j]==player){
				space_of_soldiers.push_back(i*m+j);
				///////////Cannon fires && Cannon moves
				if(i>0&&i<(n-1)){
					if(current_board[i-1][j]==player&&current_board[i+1][j]==player){
						cannon_pos[(i-1)*m+j]++;
						cannon_pos[(i+1)*m+j]++;
						cannon_pos[(i)*m+j]++;
						if(i-2>=0&&current_board[i-2][j]=='-'){
							possible_move=create_vector(0,i+1,j,i-2,j);
							possible_moves.push_back(possible_move);
							if(i-3>=0){
								position=(i-3)*m+j;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-3][j]==player||current_board[i-3][j]==townhall)){
									possible_move=create_vector(1,i,j,i-3,j);
									possible_moves.push_back(possible_move);
								}
							}
							if(i-4>=0){
								position=(i-4)*m+j;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-4][j]==player||current_board[i-4][j]==townhall)){
									possible_move=create_vector(1,i,j,i-4,j);
									possible_moves.push_back(possible_move);
								}
							}
						}
						if(i+2<=(n-1)&&current_board[i+2][j]=='-'){
							possible_move=create_vector(0,i-1,j,i+2,j);
							possible_moves.push_back(possible_move);
							if(i+3<=n-1){
								position=(i+3)*m+j;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+3][j]==player||current_board[i+3][j]==townhall)){
									possible_move=create_vector(1,i,j,i+3,j);
									possible_moves.push_back(possible_move);
								}
							}
							if(i+4<=n-1){
								position=(i+4)*m+j;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+4][j]==player||current_board[i+4][j]==townhall)){
									possible_move=create_vector(1,i,j,i+4,j);
									possible_moves.push_back(possible_move);
								}
							}
						}
					}
				}
				if(j>0&&j<(m-1)){
					if(current_board[i][j-1]==player&&current_board[i][j+1]==player){
						cannon_pos[(i)*m+j-1]++;
						cannon_pos[(i)*m+j+1]++;
						cannon_pos[(i)*m+j]++;
						if(j-2>=0&&current_board[i][j-2]=='-'){
							possible_move=create_vector(0,i,j+1,i,j-2);
							possible_moves.push_back(possible_move);
							if(j-3>=0){
								position=(i*m)+j-3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i][j-3]==player||current_board[i][j-3]==townhall)){
									possible_move=create_vector(1,i,j,i,j-3);
									possible_moves.push_back(possible_move);
								}
							}
							if(j-4>=0){
								position=(i*m)+j-4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i][j-4]==player||current_board[i][j-4]==townhall)){
									possible_move=create_vector(1,i,j,i,j-4);
									possible_moves.push_back(possible_move);
								}
							}
						}
						if(j+2<=(m-1)&&current_board[i][j+2]=='-'){
							possible_move=create_vector(0,i,j-1,i,j+2);
							possible_moves.push_back(possible_move);
							if(j+3<=m-1){
								position=(i*m)+j+3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i][j+3]==player||current_board[i][j+3]==townhall)){
									possible_move=create_vector(1,i,j,i,j+3);
									possible_moves.push_back(possible_move);
								}
							}
							if(j+4<=m-1){
								position=(i*m)+j+4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i][j+4]==player||current_board[i][j+4]==townhall)){
									possible_move=create_vector(1,i,j,i,j+4);
									possible_moves.push_back(possible_move);
								}
							}
						}
					}
				}
				if(i>0&&j>0&&i<(n-1)&&j<(m-1)){
					if(current_board[i-1][j+1]==player&&current_board[i+1][j-1]==player){
						cannon_pos[(i-1)*m+j+1]++;
						cannon_pos[(i+1)*m+j-1]++;
						cannon_pos[(i)*m+j]++;
						if(i-2>=0&&j+2<=m-1&&current_board[i-2][j+2]=='-'){
							possible_move=create_vector(0,i+1,j-1,i-2,j+2);
							possible_moves.push_back(possible_move);
							if(i-3>=0&&j+3<=m-1){
								position=((i-3)*m)+j+3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-3][j+3]==player||current_board[i-3][j+3]==townhall)){
									possible_move=create_vector(1,i,j,i-3,j+3);
									possible_moves.push_back(possible_move);
								}
							}
							if(i-4>=0&&j+4<=m-1){
								position=((i-4)*m)+j+4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-4][j+4]==player||current_board[i-4][j+4]==townhall)){
									possible_move=create_vector(1,i,j,i-4,j+4);
									possible_moves.push_back(possible_move);
								}
							}
						}
						if(i+2<=(n-1)&&j-2>=0&&current_board[i+2][j-2]=='-'){
							possible_move=create_vector(0,i-1,j+1,i+2,j-2);
							possible_moves.push_back(possible_move);
							if(i+3<=n-1&&j-3>=0){
								position=((i+3)*m)+j-3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+3][j-3]==player||current_board[i+3][j-3]==townhall)){
									possible_move=create_vector(1,i,j,i+3,j-3);
									possible_moves.push_back(possible_move);
								}
							}
							if(i+4<=n-1&&j-4>=0){
								position=((i+4)*m)+j-4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+4][j-4]==player||current_board[i+4][j-4]==townhall)){
									possible_move=create_vector(1,i,j,i+4,j-4);
									possible_moves.push_back(possible_move);
								}
							}
						}
					}
					if(current_board[i+1][j+1]==player&&current_board[i-1][j-1]==player){
						cannon_pos[(i-1)*m+j-1]++;
						cannon_pos[(i+1)*m+j+1]++;
						cannon_pos[(i)*m+j]++;
						if(i-2>=0&&j-2>=0&&current_board[i-2][j-2]=='-'){
							possible_move=create_vector(0,i+1,j+1,i-2,j-2);
							possible_moves.push_back(possible_move);
							if(i-3>=0&&j-3>=0){
								position=((i-3)*m)+j-3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-3][j-3]==player||current_board[i-3][j-3]==townhall)){
									possible_move=create_vector(1,i,j,i-3,j-3);
									possible_moves.push_back(possible_move);
								}
							}
							if(i-4>=0&&j-4>=0){
								position=((i-4)*m)+j-4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i-4][j-4]==player||current_board[i-4][j-4]==townhall)){
									possible_move=create_vector(1,i,j,i-4,j-4);
									possible_moves.push_back(possible_move);
								}
							}
						}
						if(i+2<=(n-1)&&j+2<=m-1&&current_board[i+2][j+2]=='-'){
							possible_move=create_vector(0,i-1,j-1,i+2,j+2);
							possible_moves.push_back(possible_move);
							if(i+3<=n-1&&j+3<=m-1){
								position=((i+3)*m)+j+3;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+3][j+3]==player||current_board[i+3][j+3]==townhall)){
									possible_move=create_vector(1,i,j,i+3,j+3);
									possible_moves.push_back(possible_move);
								}
							}
							if(i+4<=n-1&&j+4<=m-1){
								position=((i+4)*m)+j+4;
								attack_space_of_cannons[position]++;
								if(!(current_board[i+4][j+4]==player||current_board[i+4][j+4]==townhall)){
									possible_move=create_vector(1,i,j,i+4,j+4);
									possible_moves.push_back(possible_move);
								}
							}
						}
					}
				}
				////////////////retreat moves
				if(i==0){
					if(j==0){
						if(current_board[i][j+1]==opp_player){
							position=((i+2)*m)+j;
							attack_space_of_soldiers[position]++;
							if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
								possible_move=create_vector(0,i,j,i+2,j);
								possible_moves.push_back(possible_move);
							}
							position=((i+2)*m)+j+2;
							attack_space_of_soldiers[position]++;
							if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
								possible_move=create_vector(0,i,j,i+2,j+2);
								possible_moves.push_back(possible_move);
							}
						}
					}
					else{
						if(j==m-1){
							if(current_board[i][j-1]==opp_player){
								position=((i+2)*m)+j;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
									possible_move=create_vector(0,i,j,i+2,j);
									possible_moves.push_back(possible_move);
								}
								position=((i+2)*m)+j-2;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
									possible_move=create_vector(0,i,j,i+2,j-2);
									possible_moves.push_back(possible_move);
								}
							}
						}
						else{
							if(current_board[i][j-1]==opp_player||current_board[i][j+1]==opp_player){
								position=((i+2)*m)+j;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
									possible_move=create_vector(0,i,j,i+2,j);
									possible_moves.push_back(possible_move);
								}
								position=((i+2)*m)+j-2;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
									possible_move=create_vector(0,i,j,i+2,j-2);
									possible_moves.push_back(possible_move);
								}
								position=((i+2)*m)+j+2;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
									possible_move=create_vector(0,i,j,i+2,j+2);
									possible_moves.push_back(possible_move);
								}
							}
						}
					}
				}
				else if(i<=n-3){
					if(j==0){
						if(current_board[i][j+1]==opp_player||current_board[i-1][j+1]==opp_player||current_board[i-1][j]==opp_player){
							position=((i+2)*m)+j;
							attack_space_of_soldiers[position]++;
							if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
								possible_move=create_vector(0,i,j,i+2,j);
								possible_moves.push_back(possible_move);
							}
							position=((i+2)*m)+j+2;
							attack_space_of_soldiers[position]++;
							if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
								possible_move=create_vector(0,i,j,i+2,j+2);
								possible_moves.push_back(possible_move);
							}
						}
					}
					else{
						if(j==m-1){
							if(current_board[i][j-1]==opp_player||current_board[i-1][j-1]==opp_player||current_board[i-1][j]==opp_player){
								position=((i+2)*m)+j;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
								    possible_move=create_vector(0,i,j,i+2,j);
								    possible_moves.push_back(possible_move);
							    }
							    position=((i+2)*m)+j-2;
							    attack_space_of_soldiers[position]++;
							    if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
							    	possible_move=create_vector(0,i,j,i+2,j-2);
							    	possible_moves.push_back(possible_move);
							    }
							}
						}
						else{
							if(current_board[i][j+1]==opp_player||current_board[i][j-1]==opp_player||current_board[i-1][j]==opp_player||current_board[i-1][j+1]==opp_player||current_board[i-1][j-1]==opp_player){
								position=((i+2)*m)+j;
							    attack_space_of_soldiers[position]++;
								if((current_board[i+2][j]=='-'||current_board[i+2][j]==opp_player)){
								    possible_move=create_vector(0,i,j,i+2,j);
								    possible_moves.push_back(possible_move);
							    }
							    position=((i+2)*m)+j-2;
							    attack_space_of_soldiers[position]++;
							    if((current_board[i+2][j-2]=='-'||current_board[i+2][j-2]==opp_player)){
							    	possible_move=create_vector(0,i,j,i+2,j-2);
							    	possible_moves.push_back(possible_move);
							    }
							    position=((i+2)*m)+j+2;
							    attack_space_of_soldiers[position]++;
							    if((current_board[i+2][j+2]=='-'||current_board[i+2][j+2]==opp_player)){
							    	possible_move=create_vector(0,i,j,i+2,j+2);
							    	possible_moves.push_back(possible_move);
							    }
							}
						}
					}
				}
				//Sideways moves
				if(j==0){
					position=(i*m)+j+1;
				    attack_space_of_soldiers[position]++;
					if(current_board[i][j+1]==opp_player||current_board[i][j+1]==opp_townhall){
						possible_move=create_vector(0,i,j,i,j+1);
						possible_moves.push_back(possible_move);
					}
				}
				else{
					if(j==m-1){
						position=(i*m)+j-1;
				        attack_space_of_soldiers[position]++;
						if(current_board[i][j-1]==opp_player||current_board[i][j-1]==opp_townhall){
							possible_move=create_vector(0,i,j,i,j-1);
							possible_moves.push_back(possible_move);
						}
					}
					else{
						position=(i*m)+j-1;
					    attack_space_of_soldiers[position]++;
						if(current_board[i][j-1]==opp_player||current_board[i][j-1]==opp_townhall){
							possible_move=create_vector(0,i,j,i,j-1);
							possible_moves.push_back(possible_move);
						}
						position=(i*m)+j+1;
					    attack_space_of_soldiers[position]++;
						if(current_board[i][j+1]==opp_player||current_board[i][j+1]==opp_townhall){
							possible_move=create_vector(0,i,j,i,j+1);
							possible_moves.push_back(possible_move);
						}
					}
				}
				//Soldier forward moves
				if(i>0){
					if(j==0){
						position=((i-1)*m)+j+1;
					    attack_space_of_soldiers[position]++;
						if(current_board[i-1][j+1]==opp_player||current_board[i-1][j+1]==opp_townhall||current_board[i-1][j+1]=='-'){
							possible_move=create_vector(0,i,j,i-1,j+1);
							possible_moves.push_back(possible_move);
						}
						position=((i-1)*m)+j;
					    attack_space_of_soldiers[position]++;
						if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
							possible_move=create_vector(0,i,j,i-1,j);
							possible_moves.push_back(possible_move);
						}
					}
					else{
						if(j==m-1){
							position=((i-1)*m)+j-1;
					        attack_space_of_soldiers[position]++;
							if(current_board[i-1][j-1]==opp_player||current_board[i-1][j-1]==opp_townhall||current_board[i-1][j-1]=='-'){
								possible_move=create_vector(0,i,j,i-1,j-1);
								possible_moves.push_back(possible_move);
							}
							position=((i-1)*m)+j;
					        attack_space_of_soldiers[position]++;
							if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
								possible_move=create_vector(0,i,j,i-1,j);
								possible_moves.push_back(possible_move);
							}
						}
						else{
							position=((i-1)*m)+j-1;
					        attack_space_of_soldiers[position]++;
							if(current_board[i-1][j-1]==opp_player||current_board[i-1][j-1]==opp_townhall||current_board[i-1][j-1]=='-'){
								possible_move=create_vector(0,i,j,i-1,j-1);
								possible_moves.push_back(possible_move);
							}
							position=((i-1)*m)+j+1;
					        attack_space_of_soldiers[position]++;
							if(current_board[i-1][j+1]==opp_player||current_board[i-1][j+1]==opp_townhall||current_board[i-1][j+1]=='-'){
								possible_move=create_vector(0,i,j,i-1,j+1);
								possible_moves.push_back(possible_move);
							}
							position=((i-1)*m)+j;
					        attack_space_of_soldiers[position]++;
							if(current_board[i-1][j]==opp_player||current_board[i-1][j]==opp_townhall||current_board[i-1][j]=='-'){
								possible_move=create_vector(0,i,j,i-1,j);
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
    vector<vector<int>> Game::valid_moves(int color,unordered_map<int,int> &attack_space_of_cannons,
	unordered_map<int,int> &attack_space_of_soldiers,vector<int> &space_of_soldiers,unordered_map<int,int> &cannon_pos){
	vector<vector<int>> possible_moves;
	char player;char opp_player;char townhall;char opp_townhall;
	if(color==0){
		player='B';opp_player='W';townhall='#';opp_townhall='O';
	}
	else{
		player='W';opp_player='B';townhall='O';opp_townhall='#';
	}
	int num_white_townhalls=0;
	int num_black_townhalls=0;
	//////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<m;i=i+2){
		if(current_board[0][i]=='O'){
			num_white_townhalls++;
		}
	}
	for(int i=1;i<m;i=i+2){
		if(current_board[n-1][i]=='#'){
			num_black_townhalls++;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////
	if(num_black_townhalls>2&&num_white_townhalls>2){
		if(color==0){
			possible_moves=valid_moves2(current_board,player,opp_player,townhall,opp_townhall,
				attack_space_of_cannons,attack_space_of_soldiers,space_of_soldiers,cannon_pos);
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
			possible_moves=valid_moves2(current_board_t,player,opp_player,townhall,opp_townhall,
				attack_space_of_cannons,attack_space_of_soldiers,space_of_soldiers,cannon_pos);
			for(int i=0;i<possible_moves.size();i++){
				possible_moves[i][1]=n-1-possible_moves[i][1];
				possible_moves[i][3]=n-1-possible_moves[i][3];
				possible_moves[i][2]=m-1-possible_moves[i][2];
				possible_moves[i][4]=m-1-possible_moves[i][4];
			}
		}
	}
	return possible_moves;
}
    float Game::eval_function(vector<string> board_status,int move){
	float value=0;
	int num_black_soldiers=0;
	int num_white_soldiers=0;
	int black_y_sum=0;
	int white_y_sum=0;
	int num_white_townhalls=0;
	int num_black_townhalls=0;


	unordered_map<int,int> attack_space_of_cannons_black;
	unordered_map<int,int> attack_space_of_soldiers_black;
	vector<int> space_of_soldiers_black;
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
	unordered_map<int,int> cannon_pos_black;


	vector<vector<int>> black_valid_positions=valid_moves(0,attack_space_of_cannons_black,attack_space_of_soldiers_black,
		space_of_soldiers_black,cannon_pos_black);


	unordered_map<int,int> attack_space_of_cannons_white;
	unordered_map<int,int> attack_space_of_soldiers_white;
	vector<int> space_of_soldiers_white;
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
	unordered_map<int,int> cannon_pos_white;


	vector<vector<int>> white_valid_positions=valid_moves(1,attack_space_of_cannons_white,attack_space_of_soldiers_white,
		space_of_soldiers_white,cannon_pos_white);

	int cann=0;
	int sold=0;
	int position=0;
	int xxa=0;
	int xxb=0;
	int positiont=0;

	for(int i=0;i<space_of_soldiers_black.size();i++){
		position=space_of_soldiers_black[i];
		positiont=(m*n)-1-position;
		if(attack_space_of_cannons_white.find(positiont)==attack_space_of_cannons_white.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_cannons_white[positiont];
			opp_attacked_by_whiteCannons[positiont]=sold;
			num_opp_attacked_by_whiteCannons+=1;
		}
	}

	for(int i=0;i<space_of_soldiers_white.size();i++){
		position=space_of_soldiers_white[i];
		positiont=(m*n)-1-position;
		if(attack_space_of_cannons_black.find(positiont)==attack_space_of_cannons_black.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_cannons_black[positiont];
			opp_attacked_by_blackCannons[positiont]=sold;
			num_opp_attacked_by_blackCannons+=1;
		}
	}

	for(int i=0;i<space_of_soldiers_black.size();i++){
		position=space_of_soldiers_black[i];
		positiont=(m*n)-1-position;
		if(attack_space_of_soldiers_white.find(positiont)==attack_space_of_soldiers_white.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_soldiers_white[positiont];
		}
		attack_on_each_soldier_black.insert(make_pair(position,sold));
	}

	for(int i=0;i<space_of_soldiers_black.size();i++){
		position=space_of_soldiers_black[i];
		positiont=(m*n)-1-position;
		if(attack_space_of_soldiers_white.find(positiont)==attack_space_of_soldiers_white.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_soldiers_white[positiont];
		}
		attack_on_each_soldier_black.insert(make_pair(position,sold));
	}

	for(int i=0;i<space_of_soldiers_white.size();i++){
		position=space_of_soldiers_white[i];
		positiont=(m*n)-1-position;
		if(attack_space_of_soldiers_black.find(positiont)==attack_space_of_soldiers_black.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_soldiers_black[positiont];
		}
		attack_on_each_soldier_white.insert(make_pair(position,sold));
	}



	for(int i=0;i<space_of_soldiers_black.size();i++){
		position=space_of_soldiers_black[i];
		xxa=position/m;
		xxb=position%m;
		if(attack_space_of_soldiers_black.find(position)==attack_space_of_soldiers_black.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_soldiers_black[position];
		}
		if(attack_space_of_cannons_black.find(position)==attack_space_of_cannons_black.end()){
			cann=0;
		}
		else{
			cann=attack_space_of_cannons_black[position];
		}
		backup_on_each_soldier_black.insert(make_pair(position,cann+sold));
	}

	for(int i=0;i<space_of_soldiers_white.size();i++){
		position=space_of_soldiers_white[i];
		xxa=position/m;
		xxb=position%m;
		if(attack_space_of_soldiers_white.find(position)==attack_space_of_soldiers_white.end()){
			sold=0;
		}
		else{
			sold=attack_space_of_soldiers_white[position];
		}
		if(attack_space_of_cannons_white.find(position)==attack_space_of_cannons_white.end()){
			cann=0;
		}
		else{
			cann=attack_space_of_cannons_white[position];
		}
		backup_on_each_soldier_white.insert(make_pair(position,cann+sold));
	}
	int temp_value=0;

	for(int i=0;i<space_of_soldiers_black.size();i++){
		position=space_of_soldiers_black[i];
		temp_value=backup_on_each_soldier_black[position]- attack_on_each_soldier_black[position];
		xxa=position/m;
		xxb=position%m;
		black_y_sum+=n-1-xxa;
		if(temp_value<0&&move==1){
			value_of_all_soldiers_black+=temp_value*60;
		}
	}

	for(int i=0;i<space_of_soldiers_white.size();i++){
		position=space_of_soldiers_white[i];
		temp_value=backup_on_each_soldier_white[position]- attack_on_each_soldier_white[position];
		xxa=position/m;
		xxb=position%m;
		white_y_sum+=n-1-xxa;
		if(temp_value<0&&move==0){
			value_of_all_soldiers_white+=temp_value*60;
		}
	}
	for(auto itr=cannon_pos_black.begin();itr!=cannon_pos_black.end();itr++){
		position=(*itr).first;
		positiont=(m*n)-1-position;
		temp_value=backup_on_each_soldier_black[position]- attack_on_each_soldier_black[position];
		xxa=position/m;
		xxb=position%m;
		if(temp_value<0&&move==1){
			value_of_all_cannons_black+=temp_value*30;
		}
		else{
			if((attack_on_each_soldier_black[position]>0||opp_attacked_by_whiteCannons.find(positiont)!=opp_attacked_by_whiteCannons.end())&&move==1){
				value_of_all_cannons_black-=15;
			}
		}
	}
	for(auto itr=cannon_pos_white.begin();itr!=cannon_pos_white.end();itr++){
		position=(*itr).first;
		positiont=(m*n)-1-position;
		temp_value=backup_on_each_soldier_white[position]- attack_on_each_soldier_white[position];
		xxa=position/m;
		xxb=position%m;
		if(temp_value<0&&move==0){
			value_of_all_cannons_white+=temp_value*30;
		}
		else{
			if((attack_on_each_soldier_white[position]>0||opp_attacked_by_blackCannons.find(positiont)!=opp_attacked_by_blackCannons.end())&&move==0){
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
		if(board_status[0][i]=='O'){
			position=i;
			if(attack_space_of_cannons_black.find(position)!=attack_space_of_cannons_black.end()){
				num_attack_on_white_townhall+=2;
			}
			if(attack_space_of_soldiers_black.find(position)!=attack_space_of_soldiers_black.end()){
				num_attack_on_white_townhall++;
			}
			num_white_townhalls++;
		}
	}

	for(int i=1;i<m;i=i+2){
		if(board_status[n-1][i]=='#'){
			position=(n-1)*m+i;
			positiont=(n*m)-1-position;
			if(attack_space_of_cannons_white.find(positiont)!=attack_space_of_cannons_white.end()){
				num_attack_on_black_townhall+=2;
			}
			if(attack_space_of_soldiers_white.find(positiont)!=attack_space_of_soldiers_white.end()){
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


	value+=num_opp_attacked_by_blackCannons*24;
	////////cout<<value<<endl;
	value-=num_opp_attacked_by_whiteCannons*24;
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
// int main(){
//         vector<string> current_board=load_data();
//         //current_board=load_new_board();
//         //////////////cout<<"\n";
//         print_board(current_board);
//         ////////////cout<<"\n";
//         vector<vector<int>> possible_moves=valid_moves(current_board,0);
//         for(int i=0;i<possible_moves.size();i++){
//                 for(int j=0;j<possible_moves[i].size();j++){
//                         ////////////cout<<possible_moves[i][j]<<" ";
//                 }
//                 ////////////cout<<"\n";
//         }
//         ////////////cout<<possible_moves.size()<<"\n";
//         return 0;
// }
