/**
 * @mainpage
 * Board for Reversi
 *
 * The program is for the game of Reversi, which is a 8x8 board game with two
 * players who alternate to play until the board is full. If an opponent's
 * piece is present between the the current player's then the coins in
 * between are to be flipped, before which a check has to be done if the move
 * is valid or not.
 */

/**
 * Standard (system) header files
 */
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * Project's header files
 */
#include "ReversiBoard.h"
#include "ReversiConsoleView.h"

/**
 * Main program
 */
int main ()
{
	int rowNum = 0;
	int colNum = 0;
	bool player1 = true;
	cout << "ReversiBoard game started." << endl;
	ReversiBoard b1;
	ReversiConsoleView b2(&b1);

	while(b1.boardNotFull()){
		b2.print();
		if (player1){
			cout << "PLAYER1, enter the position of your piece (row column): "
					<<endl;
		}
		else{
			cout << "PLAYER2, enter the position of your piece (row column): "
					<<endl;
		}
		cin >> rowNum >> colNum;

		while (!b1.setField(rowNum, colNum, player1)) {
		        cin >> rowNum >> colNum;
		    }

		    player1 = !player1;
	}
	return 0;
}
