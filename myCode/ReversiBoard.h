/*
 * ReversiBoard.h
 *
 *  Created on: 26-Oct-2023
 *      Author: Rakshitha Kukke Prakash
 */

#ifndef REVERSIBOARD_H_
#define REVERSIBOARD_H_

class ReversiBoard
{
	/*
	* Enum to represent the field state in the board
	* Empty, Player 1 or Player 2
	*/
	enum FIELDSTATE_t{
		EMPTY,
		PLAYER1,
		PLAYER2,
	};

	/**
	 * Size of the Reversi game board, fixed to be 8
	 */
	static const int boardSize=8;

	/**
	 * Array of the board of size boardSize x boardSize
	 *
	 */
	FIELDSTATE_t pBoard[boardSize*boardSize];

	/**
	 * Row value entered by user is stored in rowNum
	 */
	int rowNum;

	/**
	 * Column value entered by user is stored in colNum
	 */
	int colNum;

	/**
	 * state represents the current player
	 */
	FIELDSTATE_t state;

	/**
	 * Allows the ReversiConsoleView to access private members of
	 * ReversiBoard class
	 */
	friend class ReversiConsoleView;

	/**
	 * Translates a row and a column into a array index
	 * \param int row		: [IN] row number
	 * \param int column	: [IN] column number
	 * \return Index of the array based on the row and column number
	 */
	int getIndex(int row, int column);

	/**
	 * The validMove method makes sure there is no overwriting of pre-existing
	 * pieces in the board and checks in 8 directions, Horizontal left, right,
	 * Vertical up, down, Diagonal up left, up right, down left and down right
	 * if the move is valid. Checks the result from each directions and even
	 * if one of the outcomes is true, the row and column positions are valid
	 * \returns false if a coin already exists in the position the user
	 * entered,or true or false based on the individual result from each
	 * direction check
	 */
	bool validMove();

	/**
	 * The horRightCheckNUpdate method checks if the given row and column
	 * input positions are valid to horizontal right direction.
	 * If an empty position is found to the right of the current position
	 * or an element of same type occurs, false is returned, meaning
	 * the move is invalid.
	 * Else if a piece of opponent occurs to the right, it continues to check
	 * if an element of current player's type occurs in same row, if yes
	 * all the coin inbetween are flipped and true is returned
	 * \param int currentIndex	:[IN] index of current player's coin to be set
	 * \returns true if move is valid as described above and opponent coins
	 * 			are flipped.
	 * \returns false if the neighboring element is of same type of current
	 * 			player or empty position.
	 */
	bool horRightCheckNUpdate(int currentIndex);

	/**
	 * The horLeftCheckNUpdate method checks if the given row and column input
	 * positions are valid to horizontal left direction.
	 * If an empty position is found to the left of the current position
	 * or an element of same type occurs, false is returned, meaning
	 * the move is invalid.
	 * Else if a piece of opponent occurs to the left, it continues to check
	 * if an element of current player's type occurs in same row to left, if
	 * yes all the coin inbetween are flipped and true is returned
	 * \param int currentIndex	:[IN] index of current player's coin to be set
	 * \returns true if move is valid as described above and opponent coins
	 * 			are flipped.
	 * \returns false if the neighboring element is of same type of current
	 * 			player or empty position.
	 */
	bool horLeftCheckNUpdate(int currentIndex);

	/**
	 * The vertUpCheckNUpdate method checks if the given row and column input
	 * positions are valid in Vertical up direction.
	 * If an empty position is found above the current position, or an element
	 * of same type occurs, false is returned, meaning the move is invalid.
	 * Else if a piece of opponent occurs above, it continues to check if
	 * an element of current player's type occurs in same column till the
	 * first element in that column, if yes corresponding coins
	 * in that column are flipped and true is returned
	 * \param int currentIndex	:[IN] index of current player's coin to be set
	 * \returns true if move is valid as described above and opponent coins
	 * 			are flipped.
	 * \returns false if the element above is of same type of current
	 * 			player or empty position.
	 */
	bool vertUpCheckNUpdate(int currentIndex);

	/**
	 * The vertDownCheckNUpdate method checks if the given row and column
	 * input positions are valid in Vertical down direction.
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
	bool vertDownCheckNUpdate(int currentIndex);

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
	bool diagUpRightCheckNUpdate(int currentIndex);

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
	bool diagDownRightCheckNUpdate(int currentIndex);

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
	bool diagUpLeftCheckNUpdate(int currentIndex);

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
	bool diagDownLeftCheckNUpdate(int currentIndex);

public:

	/**
	 * Default constructor that initializes row number and column number to 0,
	 * default state to EMPTY.
	 * Also initializes all the pieces on the board with EMPTY
	 * Sets the initial positions of the user pieces.
	 * Here dynamic memory is not allocated as the size of the board of
	 * Reversi game is fixed, that is 8
	 */
	ReversiBoard();


	/**
	 * This method checks if all the positions of the Reversi board are
	 * occupied by an element other than the EMPTY piece, which means the
	 * board is full and the game has to be terminated.
	 * \return false if board is fully occupied, else true
	 */
	bool boardNotFull();


	/**
	 * Returns the field state of an index on the Reversi board
	 * \param int index			 		 : [IN] the index from which the piece
	 * 										needs to be returned/printed
	 * \return FIELDSTATE_t pBoard[index]: [OUT] enum for PLAYER1,PLAYER2 or
	 * 									EMPTY at position 'index' of the board
	 */
	FIELDSTATE_t getFieldState(int index);

	/**
	 * Setting a field on the Reversi board with the enum for
	 * the corresponding player state, (PLAYER1, PLAYER2) or EMPTY
	 * \param int index			: [IN] the index at which the piece
	 * 									needs to be set
	 *
	 */
	void setFieldState(int index);

	/**
	 * The setField method checks if the row and column entered are
	 * valid inputs (i.e., row and column values are less than 8 and greater
	 * than 0 and also if their corresponding position/move is valid.
	 * If yes, sets that field by the player's coin also updates board
	 * with corresponding coins in 8 directions if atleast one valid move
	 * is identified.
	 * \param int row		: [IN] row at which player's piece is to be set
	 * \param int column	: [IN] column at which player's piece is to be set
	 * \returns true if the position of entered rows and columns are valid,
	 * and move is valid else returns false until
	 * the player re-enters a valid position
	 */
	bool setField(int row, int column, bool state);

	/**
	 * Destructor that deallocated/frees the dynamic memory and destroys the
	 * objects created. Here no dynamic memory is allocated as the size of the
	 * board of Reversi game is fixed, that is 8
	 */
	virtual ~ReversiBoard();

};

#endif /* REVERSIBOARD_H_ */
