#include "BoardView.h"
#include <iostream>
#include <iomanip>

/* *********************************************************************
Function Name: display_board
Purpose: Handles the visual representation of the game board
Parameters: board[][], a double array passed by value. Each element holds 
			a piece class object which contains the piece color that will be displayed.  
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void BoardView::display_board(std::array<std::array<Piece, 8>, 8> board) {
	// Outputs the the top border of the board
	std::cout << "  " << "+" << std::setfill('-') << std::setw(18) << "+" << std::endl;
	for (int i = 8; i > 0; i--) {
		// Outputs the label for each row
		std::cout << i << " | ";
		// Outputs the piece at the given row and column positions
		for (int j = 0; j < 8; j++) {
			std::cout << board[8 - i][j].getColor() << " ";
		}
		std::cout << "| ";
		std::cout << std::endl;
	}
	// Outputs the the bottom border of the board
	std::cout << "  " << "+" << std::setfill('-') << std::setw(18) << "+" << std::endl;

	std::cout << "    ";
	// Outputs the labels for each column
	for (int j = 0; j < 8; j++) {
		std::cout << static_cast<char>(65 + j) << " ";
	}
	std::cout << std::endl;
}
