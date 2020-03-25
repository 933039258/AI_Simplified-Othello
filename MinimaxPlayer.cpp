/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"
#include <limits.h>
using std::vector;

bool MinimaxPlayer::Isterminal(OthelloBoard b){
   if(!(b.has_legal_moves_remaining(b.get_p1_symbol())) && !(b.has_legal_moves_remaining(b.get_p2_symbol()))){
      return true;
   }
   return false;
}
int MinimaxPlayer::Utility(OthelloBoard b){
   int p1, p2, utility;
   p1 = b.count_score(b.get_p1_symbol()); 
   p2 = b.count_score(b.get_p2_symbol());
   utility = p1-p2;
   return utility;
}
bool MinimaxPlayer::Islegal(OthelloBoard b, int col, int row, char symbol){
   if(b.is_legal_move(col,row,symbol)){
      return true;
   }
   return false;
}
bool MinimaxPlayer::Issymbol(char symbol, OthelloBoard b){
   if(symbol == b.get_p1_symbol()){
      return true;
   }
   return false;
}
//define successor
vector<std::pair<Coordinate, OthelloBoard>> MinimaxPlayer::Successor(char symbol, OthelloBoard b){
   Coordinate act;
   vector<std::pair<Coordinate,OthelloBoard>> succor;
   int bc,br;
   bc = b.get_num_cols(); 
   br = b.get_num_rows();
   for(int i=0;i<bc;i++){
      for(int j=0;j<br;j++){
	 if(Islegal(b,i,j,symbol)){
	    OthelloBoard temp = b;
	    temp.play_move(i,j,symbol);
	    act.col = i;
	    act.row = j;
	    Coordinate act_temp = act; 
	    succor.push_back(std::pair<Coordinate,OthelloBoard>(act_temp,temp));
	 }
      }
   }
   return succor;
}

Coordinate MinimaxPlayer::Minimax_decision(OthelloBoard b){
   Coordinate action;
   int utility;
   int min = INT_MAX;
   int max = INT_MIN;
   vector<std::pair<Coordinate, OthelloBoard>> succor;
   for (int i=0;i<Successor(symbol,b).size();i++){
      succor.push_back((Successor(symbol,b))[i]);
   }
   for(int i=0;i<succor.size();i++){
      if(Issymbol(symbol, b)){
         utility = Min_value(succor[i].second);
	 if(utility >= max){
	    max = utility;
	    action = succor[i].first;
	 }
      }else{
         utility = Max_value(succor[i].second);
	 if(utility < min){
	    min = utility;
	    action = succor[i].first;
	 
	 }
      
      }
   }
   return action;

}


//define min value function;
int MinimaxPlayer::Min_value(OthelloBoard b){
   if(Isterminal(b)){
      return Utility(b);
   }
   int v = INT_MAX;
   int temp;
   vector<std::pair<Coordinate, OthelloBoard>> succor;
   for (int i=0;i<Successor(symbol,b).size();i++){
      succor.push_back((Successor(symbol,b))[i]);
   }
  
   for(int i=0;i<succor.size();i++){
      temp = Max_value(succor[i].second);
      if(v>=temp){
         v=temp;
      }
   }
   
   return v;
}

int MinimaxPlayer::Max_value(OthelloBoard b){
   if(Isterminal(b)){
      return Utility(b);
   }	
   int v = INT_MIN;
   int temp;
   vector<std::pair<Coordinate, OthelloBoard>> succor;
   for (int i=0;i<Successor(symbol,b).size();i++){
      succor.push_back((Successor(symbol,b))[i]);
   }
   for(int i=0;i<succor.size();i++){
      temp = Min_value(succor[i].second);
      if(v<temp){
         v=temp;
      }
   }
   return v;
}

MinimaxPlayer::MinimaxPlayer(char symb) :
   Player(symb) {

   }

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
   // To be filled in by you
    Coordinate action;
    action = Minimax_decision(*b);
    col = action.col;
    row = action.row;
    //row = Minimax_decision(*b).row;
    //col = Minimax_decision(*b).col;
   }

MinimaxPlayer* MinimaxPlayer::clone() {
   MinimaxPlayer* result = new MinimaxPlayer(symbol);
   return result;
}
