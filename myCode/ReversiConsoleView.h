/*
 * ReversiConsoleView.h
 *
 *  Created on: 26-Oct-2023
 *      Author: Rakshitha Kukke Prakash
 */

#ifndef REVERSICONSOLEVIEW_H_
#define REVERSICONSOLEVIEW_H_
#include "ReversiBoard.h"

class ReversiConsoleView
{
	/**
	 * Pointer to the reversi board
	 */
	ReversiBoard* board;
public:

	/**
	 * Constructor for class ReversiConsoleView
	 * \param const ReversiBoard* revboard :[IN] pointer to reversi board
	 */
	ReversiConsoleView(ReversiBoard* revboard);

	/**
	 * Prints the field states of the whole Reversi board
	 * const since the below method does not modify the object
	 *
	 */
	void print() const;

	/**
	 * Destructor of class ReversiConsoleView, destroys the object
	 */
	virtual ~ReversiConsoleView();
};

#endif /* REVERSICONSOLEVIEW_H_ */

