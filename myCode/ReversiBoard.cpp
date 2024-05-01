/*
 * ReversiBoard.cpp
 *
 *  Created on: 26-Oct-2023
 *      Author: Rakshitha Kukke Prakash
 */

#include <iostream>
#include "ReversiBoard.h"
using namespace std;

/**
 * Default constructor that initializes row number and column number to 0,
 * default state to EMPTY.
 * Also initializes all the pieces on the board with EMPTY
 * Sets the initial positions of the user pieces.
 * Here dynamic memory is not allocated as the size of the board of
 * Reversi game is fixed, that is 8
 */
ReversiBoard::ReversiBoard(): rowNum(0), colNum(0), state{EMPTY}
{
	// TODO Auto-generated constructor stub
	for (unsigned int index=0; index<boardSize * boardSize;index++){
			pBoard[index] = EMPTY;
		}

	int centerPiece = boardSize / 2 - 1;
	pBoard[centerPiece * boardSize + centerPiece] =
			pBoard[(centerPiece + 1) * boardSize + (centerPiece + 1)]=PLAYER1;
	pBoard[centerPiece * boardSize + (centerPiece + 1)] =
			pBoard[(centerPiece + 1) * boardSize + centerPiece]=PLAYER2;
}

/**
 * This method checks if all the positions of the Reversi board are occupied
 * by an element other than the EMPTY piece, which means the board is full
 * and the game has to be terminated.
 * \return false if board is fully occupied, else true
 */
bool ReversiBoard::boardNotFull()
{
	int count =0;
	for (unsigned int index=0; index<boardSize * boardSize;index++){
		if(getFieldState(index) != EMPTY){
			count++;
		}
	}
	if (count==boardSize*boardSize){
		cout<<"Game over"<<endl;
		return false;
	}
	return true;
}

/**
 * Translates a row and a column into a array index
 * \param int row		: [IN] row number
 * \param int column	: [IN] column number
 * \return Index of the array based on the row and column number
 */
int ReversiBoard::getIndex(int row, int column)
{
	return (row-1)* boardSize + (column-1);
}

/**
 * Returns the field state of an index on the Reversi board
 * \param int index			 		 : [IN] the index from which the piece
 * 										needs to be returned/printed
 * \return FIELDSTATE_t pBoard[index]: [OUT] enum for PLAYER1,PLAYER2 or
 * 									EMPTY at position 'index' of the board
 */
ReversiBoard::FIELDSTATE_t ReversiBoard::getFieldState(int index)
{
	return pBoard[index];
}

/**
 * Setting a field position 'index' on the Reversi board with the enum for
 * the corresponding player state, (PLAYER1, PLAYER2) or EMPTY
 * \param int index			: [IN] the index at which the piece
 * 									needs to be set
 */
void ReversiBoard::setFieldState(int index)
{
	pBoard[index] = state;
}

/**
 * The setField method checks if the row and column entered are
 * valid inputs (i.e., row and column values are less than 8 and greater than
 * 0 and also if their corresponding position/move is valid.
 * If yes, sets that field by the player's coin also updates board
 * with corresponding coins in 8 directions if atleast one valid move
 * is identified.
 * \param int row		: [IN] row at which player's piece is to be set
 * \param int column	: [IN] column at which player's piece is to be set
 * \returns true if the position of entered rows and columns are valid,
 * and move is valid else returns false until
 *  the player re-enters a valid position
 */
bool ReversiBoard::setField(int row, int column, bool player)
{
	rowNum = row;
	colNum = column;
	state = player? PLAYER1:PLAYER2;
	if(rowNum >0 && rowNum <=boardSize && colNum >0 && colNum <=boardSize){
		if(validMove()){
			setFieldState(getIndex(rowNum, colNum));
			return true;
		}
		else{
			cout<<"Invalid move. Enter another position"<<endl;
		}
	}
	else{
		cout<<"Row and column index needs to be above 0 and below "
				"the size of the board, ie 8";
	}
	return false;
}

/**
 * The validMove method makes sure there is no overwriting of pre-existing
 * pieces in the board and checks in 8 directions, Horizontal left, right,
 * Vertical up, down, Diagonal up left, up right, down left and down right if
 * the move is valid. Checks the result from each directions and even if one
 * of the outcomes is true, the row and column positions are valid
 * \returns false if a coin already exists in the position the user entered,
 * or true or false based on the individual result from each direction check.
 */
bool ReversiBoard::validMove()
{
	// Overwrite of pre-existing pieces is not allowed
	if (getFieldState(getIndex(rowNum,colNum)) != EMPTY){
		cout<<"Coin " <<getFieldState(getIndex(rowNum,colNum))<<
			" already exists in the position("<< rowNum<<","<<colNum<<
			")"<<endl;
		return false;
	}
	int currentIndex = getIndex(rowNum,colNum);
	bool validMoveHorRight = horRightCheckNUpdate(currentIndex);
	bool validMoveHorLeft = horLeftCheckNUpdate(currentIndex);
	bool validMoveVertUp = vertUpCheckNUpdate(currentIndex);
	bool validMoveVertDown = vertDownCheckNUpdate(currentIndex);
	bool validMoveDiagUpRight = diagUpRightCheckNUpdate(currentIndex);
	bool validMoveDiagDownRight =
			diagDownRightCheckNUpdate(currentIndex);
	bool validMoveDiagUpLeft = diagUpLeftCheckNUpdate(currentIndex);
	bool validMoveDiagDownLeft =
			diagDownLeftCheckNUpdate(currentIndex);

	bool validMove = validMoveHorRight || validMoveHorLeft ||
					   validMoveVertUp || validMoveVertDown ||
					   validMoveDiagUpRight ||validMoveDiagDownRight ||
					   validMoveDiagUpLeft ||validMoveDiagDownLeft;

	return validMove;
}

/**
 * The horRightCheckNUpdate method checks if the given row and column input
 * positions are valid to horizontal right direction.
 * If an empty position is found to the right of the current position
 * or an element of same type occurs, false is returned, meaning
 * the move is invalid.
 * Else if a piece of opponent occurs to the right, it continues to check if
 * an element of current player's type occurs in same row, if yes
 * all the coin inbetween are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the neighboring element is of same type of current
 * 			player or empty position.
 */
bool ReversiBoard::horRightCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	for (int index = currentIndex+1;
			index <= ((rowNum-1)*boardSize)+boardSize;index++){
		FIELDSTATE_t nxtEle = getFieldState(index);
		if(nxtEle!=EMPTY){
			if(nxtEle != state){
				opponentPlayerPiece++;
			}
			else{
				if(opponentPlayerPiece>0){
					for(int flipIndex = currentIndex; flipIndex < index;
							flipIndex++){
						setFieldState(flipIndex);
					}
					return true;
				}
				else{
					break;			// if neighboring element is of same type
				}
			}
		}
		else{
			break;
		}
	}
	return false;
}

/**
 * The horLeftCheckNUpdate method checks if the given row and column input
 * positions are valid to horizontal left direction.
 * If an empty position is found to the left of the current position
 * or an element of same type occurs, false is returned, meaning
 * the move is invalid.
 * Else if a piece of opponent occurs to the left, it continues to check if
 * an element of current player's type occurs in same row to left, if yes
 * all the coin inbetween are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the neighboring element is of same type of current
 * 			player or empty position.
 */
bool ReversiBoard::horLeftCheckNUpdate(int currentIndex)
{

	int opponentPlayerPiece = 0;
	for (int index = currentIndex-1; index >= (rowNum-1) * boardSize;
			index--){
		FIELDSTATE_t nxtEle = getFieldState(index);
		if(nxtEle!=EMPTY){
			if(nxtEle != state){
				opponentPlayerPiece++;
			}
			else{
				if(opponentPlayerPiece>0){
					for(int flipIndex = index; flipIndex < currentIndex;
							flipIndex++) {
						setFieldState(flipIndex);
					}
					return true;
				}
				else{
					break;		// if neighboring element is of same type
				}
			}
		}
		else{
			break;
		}
	}
	return false;
}

/**
 * The vertUpCheckNUpdate method checks if the given row and column input
 * positions are valid in Vertical up direction.
 * If an empty position is found above the current position, or an element
 * of same type occurs, false is returned, meaning the move is invalid.
 * Else if a piece of opponent occurs above, it continues to check if
 * an element of current player's type occurs in same column till the first
 * element in that column, if yes corresponding coins
 * in that column are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element above is of same type of current
 * 			player or empty position.
 */
bool ReversiBoard::vertUpCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	for(int index=currentIndex-boardSize; index >=0;index-=boardSize){
		FIELDSTATE_t nxtEle = getFieldState(index);
		if(nxtEle!=EMPTY){
			if(nxtEle != state){
				opponentPlayerPiece++;
			}
			else{
				if(opponentPlayerPiece>0){
					for(int flipIndex = index; flipIndex < currentIndex;
							flipIndex+=boardSize) {
						setFieldState(flipIndex);
					}
					return true;
				}
				else{
					break;			// if neighboring element is of same type
				}
			}
		}
		else{
			break;
		}
	}
	return false;
}

/**
 * The vertDownCheckNUpdate method checks if the given row and column input
 * positions are valid in Vertical down direction.
 * If an empty position is found below the current position, or an element
 * of same type occurs, false is returned, meaning the move is invalid.
 * Else if a piece of opponent occurs above, it continues to check if
 * an element of current player's type occurs in same column till the last
 * element in that column, if yes corresponding coins
 * in that column are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element below is of same type of current
 * 			player or empty position.
 */
bool ReversiBoard::vertDownCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	for(int index=currentIndex+boardSize; index<boardSize*boardSize;
							index+=boardSize){
		FIELDSTATE_t nxtEle = getFieldState(index);
		if(nxtEle!=EMPTY){
			if(nxtEle != state){
				opponentPlayerPiece++;
			}
			else{
				if(opponentPlayerPiece>0){
					for(int flipIndex = currentIndex; flipIndex <index ;
							flipIndex+=boardSize) {
						setFieldState(flipIndex);
					}
					return true;
				}
				else{
					break;			// if neighboring element is of same type
				}
			}
		}
		else{
			break;
		}
	}
	return false;
}

/**
 * The diagUpRightCheckNUpdate method checks if the given row and column
 * input positions are valid in Diagonal direction.
 * If an empty position is found diagonal up and to the right of the
 * current position, or an element of same type occurs, false is returned,
 * meaning the move is invalid.
 * Else if a piece of opponent occurs diagonal up and to the right, it
 * continues to check if an element of current player's type occurs
 * diagonally till the last element in that diagonal,
 * if yes corresponding coins
 * in that diagonal are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element diagonal up and to the right is of same
 * 			type of current player or empty position.
 */
bool ReversiBoard::diagUpRightCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	int validColRow=0;
	if(validColRow<=(boardSize - colNum)){
		for(int index=currentIndex-boardSize+1; index >=0;
				index-=(boardSize-1)){
			FIELDSTATE_t nxtEle = getFieldState(index);
			if(nxtEle!=EMPTY){
				if(nxtEle != state){
					opponentPlayerPiece++;
				}
				else{
					if(opponentPlayerPiece>0){
						for(int flipIndex = index; flipIndex < currentIndex;
								flipIndex+=(boardSize-1)) {
							setFieldState(flipIndex);
						}
						return true;
					}
					else{
						break;		// if neighboring element is of same type
					}
				}
			}
			else{
				break;
			}
		}
	}
	return false;
}

/**
 * The diagDownRightCheckNUpdate method checks if the given row and column
 * input positions are valid in Diagonal direction.
 * If an empty position is found diagonal up and to the right of the
 * current position, or an element of same type occurs, false is returned,
 * meaning the move is invalid.
 * Else if a piece of opponent occurs diagonal down and to the right, it
 * continues to check if an element of current player's type occurs
 * diagonally till the last element in that direction,
 * if yes corresponding coins
 * in that diagonal are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element diagonal down and to the right is of same
 * 			type of current player or empty position.
 */
bool ReversiBoard::diagDownRightCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	int validColRow=0;
	if(validColRow<=(boardSize - colNum)){
		for(int index=currentIndex+boardSize+1; index <boardSize*boardSize;
						index+=(boardSize+1)){
			FIELDSTATE_t nxtEle = getFieldState(index);
			if(nxtEle!=EMPTY){
				if(nxtEle != state){
					opponentPlayerPiece++;
				}
				else{
					if(opponentPlayerPiece>0){
						for (int flipIndex = currentIndex; flipIndex < index;
								flipIndex+=(boardSize+1)){
							setFieldState(flipIndex);
						}
						return true;
					}
					else{
						break;		// if neighboring element is of same type
					}
				}
			}
			else{
				break;
			}
		}
	}
	return false;
}

/**
 * The diagUpLeftCheckNUpdate method checks if the given row and column
 * input positions are valid in Diagonal direction.
 * If an empty position is found diagonal up and to the left of the
 * current position, or an element of same type occurs, false is returned,
 * meaning the move is invalid.
 * Else if a piece of opponent occurs diagonal up and to the left, it
 * continues to check if an element of current player's type occurs
 * diagonally till the last element in that direction,
 * if yes corresponding coins
 * in that diagonal are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element diagonal up and to the left is of same
 * 			type of current player or empty position.
 */
bool ReversiBoard::diagUpLeftCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	int validColRow=0;
	if(validColRow<=(colNum)){
		for(int index=currentIndex-boardSize-1; index >=0;
				index-=(boardSize+1)){
			FIELDSTATE_t nxtEle = getFieldState(index);
			if(nxtEle!=EMPTY){
				if(nxtEle != state){
					opponentPlayerPiece++;
				}
				else{
					if(opponentPlayerPiece>0){
						for (int flipIndex = index; flipIndex < currentIndex;
								flipIndex+=(boardSize+1)){
							setFieldState(flipIndex);
						}
						return true;
					}
					else{
						break;		// if neighboring element is of same type
					}
				}
			}
			else{
				break;
			}
		}
	}
	return false;

}

/**
 * The diagDownLeftCheckNUpdate method checks if the given row and column
 * input positions are valid in Diagonal direction.
 * If an empty position is found diagonal down and to the left of the
 * current position, or an element of same type occurs, false is returned,
 * meaning the move is invalid.
 * Else if a piece of opponent occurs diagonal down and to the left, it
 * continues to check if an element of current player's type occurs
 * diagonally till the last element in that direction,
 * if yes corresponding coins
 * in that diagonal are flipped and true is returned
 * \param int currentIndex	:[IN] index of current player's coin to be set
 * \returns true if move is valid as described above and opponent coins
 * 			are flipped.
 * \returns false if the element diagonal down and to the left is of same
 * 			type of current player or empty position.
 */
bool ReversiBoard::diagDownLeftCheckNUpdate(int currentIndex)
{
	int opponentPlayerPiece = 0;
	int validColRow=0;
	if(validColRow<=(colNum)){
		for(int index=currentIndex+boardSize-1;
				index <boardSize*boardSize;index+=(boardSize-1)){
			FIELDSTATE_t nxtEle = getFieldState(index);
			if(nxtEle!=EMPTY){
				if(nxtEle != state){
					opponentPlayerPiece++;
				}
				else{
					if(opponentPlayerPiece>0){
						for (int flipIndex = currentIndex; flipIndex < index;
								flipIndex+=(boardSize-1)){
							setFieldState(flipIndex);
						}
						return true;
					}
					else{
						break;		// if neighboring element is of same type
					}
				}
			}
			else{
				break;
			}
		}
	}
	return false;
}

/**
 * Destructor that deallocated/frees the dynamic memory and destroys the
 * objects created. Here no dynamic memory is allocated as the size of the
 * board of Reversi game is fixed, that is 8
 */
ReversiBoard::~ReversiBoard()
{
}
