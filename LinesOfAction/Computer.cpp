#include "Computer.h"
#include <ctime>

/* *********************************************************************
Function Name: play
Purpose: Handles the computer movement for a player
Parameters: board, a Board class object passed by reference, has the 
            board 2D Piece array member named piece modified. board 
			
			self, a Player pointer passed by value, has the memory address of 
			the current player (computer)

			nextPlayer, a Player pointer passed by value, has the memory address of 
			the next player (human)
	        
Return Value: the coordinates of where the player has moved the selected piece,
              a string value
Algorithm: none
Reference: none
********************************************************************* */
std::string Computer::play(Board& board, Player* self, Player* nextPlayer) {

	Piece bestPiece = strategize(board, self, nextPlayer);	
	// Makes a move based on the piece with the best strategy
	board.move_piece(bestPiece.getOrigin(), bestPiece.getStratCoords());
	return bestPiece.getStratCoords();

}