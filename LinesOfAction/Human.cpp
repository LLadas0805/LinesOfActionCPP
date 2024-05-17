#include "Human.h"

/* *********************************************************************
Function Name: play
Purpose: Handles the human movement for a player
Parameters: board, a Board class object passed by reference, has the
			board 2D Piece array member named piece modified. board

			self, a Player pointer passed by value, has the memory address of
			the current player (human)

			nextPlayer, a Player pointer passed by value, has the memory address of
			the next player (computer)

Return Value: the coordinates of where the player has moved the selected piece,
			  a string value
Algorithm:
			1) Declare two strings, origin and destination
			2) Assign user input to origin and check if origin is a valid piece
			   on the board or if user input was HELP
			3) If origin was equal to HELP, display best possible moves and their strategies.
			   Go back to step 2
			4) If the piece located at origin was out of bounds or not the same color as player,
			   go back to step 2
			5) Assign user input to destination and check if destination is a valid location
			   on the board or if user input was HELP
			6) If destination was equal to HELP, display best possible moves and their strategies.
			   Go back to step 5
			7) If the piece located at destination was out of bounds or out of range, go back to step 5
			8) move your piece on the board from origin to destination

Reference: none
********************************************************************* */
std::string Human::play(Board &board, Player *self, Player *nextPlayer) {

	std::string origin;
	std::string destination;

	do {

		std::cout << "Please select a valid piece on the board to move or type \"HELP\" for strategies" << std::endl;
		std::cin >> origin;

		for (char& letter : origin) {
			letter = std::toupper(letter);
		}

		if (origin == "HELP") {
			strategize(board, self, nextPlayer);
		}

	} while (!board.validate_piece(getColor(), origin));

	do {
		std::cout << "Select a destination for piece " << origin << " to land on or type \"HELP\" for strategies" << std::endl;
		std::cin >> destination;

		for (char& letter : destination) {
			letter = std::toupper(letter);
		}

		if (destination == "HELP") {
			strategize(board, self, nextPlayer);
		}

	} while (!board.validate_moveset(origin, destination));

	board.move_piece(origin, destination);
	std::cout << "Piece " << origin << " was moved to the destination " << destination << std::endl;

	return destination;
}