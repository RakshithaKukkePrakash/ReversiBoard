/*
 * ReversiConsoleView.cpp
 *
 *  Created on: 26-Oct-2023
 *      Author: Rakshitha Kukke Prakash
 */

#include "ReversiConsoleView.h"
#include <iostream>
using namespace std;

/**
 * Constructor for class ReversiConsoleView
 * \param const ReversiBoard* revboard :[IN] pointer to reversi board
 */
ReversiConsoleView::ReversiConsoleView(ReversiBoard* revboard):
		board(revboard)
{
}

/**
 * Prints the field states of the whole Reversi board
 * const since the below method does not modify the object
 *
 */
void ReversiConsoleView::print() const
{
	for (int row = 1; row <= board->boardSize; row++) {
	    cout << endl;
	    for (int column = 1; column <= board->boardSize; column++) {
	        int index = board->getIndex(row, column);
	        ReversiBoard::FIELDSTATE_t state = board->getFieldState(index);
	        char coin;

	        switch (state) {
	            case ReversiBoard::EMPTY:
	                coin = '.';
	                break;
	            case ReversiBoard::PLAYER1:
	                coin = 'X';
	                break;
	            case ReversiBoard::PLAYER2:
	                coin = 'O';
	                break;
	            default:
	                coin = ' ';
	        }

	        cout << coin << "\t";
	    }
	}

		cout<<endl;
}

/**
 * Destructor of class ReversiConsoleView, destroys the object
 */
ReversiConsoleView::~ReversiConsoleView()
{
}

