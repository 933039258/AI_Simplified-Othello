/*
 * MinimaxPlayer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */

#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "Player.h"
#include <vector>

/**
 * This class represents an AI player that uses the Minimax algorithm to play the game
 * intelligently.
 */
struct Coordinate{
   int row;
   int col;
};
class MinimaxPlayer : public Player {

public:

	/**
	 * @param symb This is the symbol for the minimax player's pieces
	 */
	MinimaxPlayer(char symb);

	/**
	 * Destructor
	 */
	virtual ~MinimaxPlayer();

	/**
	 * @param b The board object for the current state of the board
	 * @param col Holds the return value for the column of the move
	 * @param row Holds the return value for the row of the move
	 */
    void get_move(OthelloBoard* b, int& col, int& row);

    /**
     * @return A copy of the MinimaxPlayer object
     * This is a virtual copy constructor
     */
    MinimaxPlayer* clone();
    bool Islegal(OthelloBoard b, int col, int row, char symbol);
    bool Isterminal(OthelloBoard b);
    bool Issymbol(char symbol, OthelloBoard b);
    int Utility(OthelloBoard b);
    int Max_value(OthelloBoard b);
    int Min_value(OthelloBoard B);
    Coordinate Minimax_decision(OthelloBoard B);
    std::vector<std::pair<Coordinate, OthelloBoard>> Successor(char human, OthelloBoard b);
private:

};


#endif
