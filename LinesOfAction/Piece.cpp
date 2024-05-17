#include "Piece.h"

/* *********************************************************************
Function Name: Piece
Purpose: To initialize private members of the Piece class when a Piece object is created
Parameters:
			color, a chararcter passed by value which holds what team a piece
			is associated with
Return Value: none
Algorithm: none
Reference: None
********************************************************************* */
Piece::Piece(char color) {
	this->color = color;
	this->strategy = "";
	this->stratCoords = "";
	this->origin = "";
}

/* *********************************************************************
Function Name: getColor
Purpose: To obtain the color that a piece is associated with
Parameters: none
Return Value: The team/side a piece is on, a char value
Algorithm: none
Reference: none
********************************************************************* */
char Piece::getColor() {
	return this->color;
}

/* *********************************************************************
Function Name: getStrategy
Purpose: To find the best move on the board that a piece can take
Parameters: none
Return Value: The method in which the piece will take in a given turn
              a string value
Algorithm: none
Reference: none
********************************************************************* */
std::string Piece::getStrategy() {
	return this->strategy;
}

/* *********************************************************************
Function Name: setStrategy
Purpose: To assign the best strategy to the strategy private member
Parameters:
			strategy, a string passed by value, which holds the 
			strategy that will be assigned to the private member
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Piece::setStrategy(std::string strategy) {
	this->strategy = strategy;
}

/* *********************************************************************
Function Name: getStratCoords
Purpose: To obtain the location on the board where the strategy will 
         cause the piece to move to
Parameters: none
Return Value: The coordinates associated with the best strategy, a string value
Algorithm: none
Reference: none
********************************************************************* */
std::string Piece::getStratCoords() {
	return this->stratCoords;
}

/* *********************************************************************
Function Name: setStratCoords
Purpose: To assign a destination value to the stratCoords private member string
Parameters:
			stratCoords, a string passed by value. It holds the coordinates
			that are associated with where a strategy will take a piece on 
			the board
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Piece::setStratCoords(std::string stratCoords) {
	this->stratCoords = stratCoords;
}

/* *********************************************************************
Function Name: getOrigin
Purpose: To obtain the start location of a piece on the board before making
		 a move
Parameters: none
Return Value: The coordinates associated with the starting position of a piece
              before a strategy is acted on, a string value
Algorithm: none
Reference: none
********************************************************************* */
std::string Piece::getOrigin() {
	return this->origin;
}

/* *********************************************************************
Function Name: setOrigin
Purpose: To set a new coordinates reference to the piece on the board before
         it makes a move
Parameters:
			origin, a string passed by value, it holds the intial location
			of the piece before it acts on a strategy
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Piece::setOrigin(std::string origin) {
	this->origin = origin;
}