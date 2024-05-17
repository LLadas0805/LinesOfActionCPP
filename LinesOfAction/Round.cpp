#include "Round.h"
#include "Board.h"
#include "Player.h"
#include "Serialization.h"

/* *********************************************************************
Function Name: Round
Purpose: To initialize private members of the Round class when a Round object is created
Parameters:
			players, a double Player pointer passed by value which stores the memory address
			of an array of players
Return Value: none
Algorithm: none
Reference: None
********************************************************************* */
Round::Round(Player** players) {
	this->players = players;
	this->currPlayer = NULL;
	roundWon = false;
}

/* *********************************************************************
Function Name: starting_player
Purpose: Determines which player will start first at the beginning of a round
Parameters: none
Return Value: none
Algorithm:
			1) Checks if first player in the tournament has more wins than the second
			2) If true, first player becomes the initial user to make a move.
			   First player gets assigned control over black pieces and second player
			   gets white pieces.
			3) When false, check if first player has less wins than the second
			4) If true, second player becomes initial user to make a move
			   First player gets assigned control over white pieces and second player
			   gets black pieces.
			5) When both conditions are false, this means we have reached a tie and
			   a coin toss is initiated generating either integers 1 or 2 randomly. 
			6) If first player entered invalid input, go back to step 5 
			7) If first player guesses correctly, follow step #2 
			8) If first player guesses incorrectly, follow step #4
Reference: C++ Standard Template Library Documentation
********************************************************************* */
void Round::starting_player() {

	// Picks first player in the tournament roster if they have the most round wins
	if (players[0]->getWins() > players[1]->getWins()) {
		players[0]->setColor('B');
		players[1]->setColor('W');
		currPlayer = players[0];
	}
	// Picks second player in the tournament roster if they have the most round wins
	else if (players[0]->getWins() < players[1]->getWins()) {
		players[0]->setColor('W');
		players[1]->setColor('B');
		currPlayer = players[1];
	}
	// If a tie, coin flip will occur to determine first turn
	else {
		// Seeds random number generator with current time
		srand(static_cast<unsigned int>(time(NULL)));
		// Declaring the variable coin, assigning it to a random integer 1 or 2 (1) heads or (2) tails
		int coin = rand() % 2 + 1;
		// Holds the predicted side for a coin toss (1) heads or (2) tails
		int coinflip;

		do {
			std::cout << "COIN TOSS\nEnter a valid input for whether this coin will land on heads (1) or tails (2): ";
			// assigns user input to coinflip
			std::cin >> coinflip;

			if (std::cin.fail()) {
				// Clear the error state
				std::cin.clear();

				// Ignore invalid input up to a newline character
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

		} while (coinflip < 1 || coinflip > 2);

		if (coin == 2) {
			std::cout << "Coin landed on tails, ";
		}
		else {
			std::cout << "Coin landed on heads, ";
		}

		// If player has guessed correctly, they will go first
		if (coinflip == coin) {
			std::cout << "Human goes first\n";
			players[0]->setColor('B');
			players[1]->setColor('W');
			currPlayer = players[0];
		}
		// If player has guessed incorrectly, the opponent goes first
		else {
			std::cout << "Computer goes first\n";
			players[0]->setColor('W');
			players[1]->setColor('B');
			currPlayer = players[1];
		}
	}
}


/* *********************************************************************
Function Name: intiate_round
Purpose: To start or load a round in a tournament and creates gameplay loop
Parameters:
			loaded, a boolean passed by value. It holds the truth value 
			for whether or not this current game session is new or has 
			been loaded in.
Return Value: none
Algorithm:
			1) Checks parameter loaded's truth value to see if our tournament will be loaded from a save or not
			2) If loaded is true, we parse the save file for the defintion of the 
			   round's board, current player, and player roster
			3) If false, we place all of the pieces in their default spot on the board, and 
			   determine our current/starting player based off of their round wins.
			4) Display game board  
			5) Current player selects a valid piece to move and places it somehwere on the board
			6) Checks if all of current player's pieces are in a single group
			7) If true, the current player has won and algorithm has been ended
			8) If false, we display the board
			9) The player is then asked if they would like to save the game or continue playing.
				Input 1 to continue or input 2 to save & quit
			10) If input is neither of these values, we repeat step 10
			11) If input is equal to 2, we save the tournament information as a text file and end the algorithm
			12) If input is equal to 1, swap players and go back to step 4
Reference: none
********************************************************************* */
void Round::initiate_round(bool loaded) {

	// board holds the round's board information
	Board board;
	// boardview displays the board as a text based grid
	BoardView boardview;
	// serial deals with handling save states for a tournament
	Serialization serial;
    // move holds the coordinates to a board piece
	std::string move;

	if (loaded) {
		serial.loadGame(players, currPlayer, board);
	}
	else {
		starting_player();
		board.initial_state();
	}
	
	
	// Displays board grid interface
	boardview.display_board(board.getBoard());

	// response holds the user input of a player
	char response;

	while (1) {
		std::cout << currPlayer->getIdentity() << "'s (" << currPlayer->getColor() << ") turn!" << std::endl;
		// assigning the coordinates to a piece moved by the current player to move
		move = currPlayer->play(board, currPlayer, swap());
		
		// Declaring the boolean winGroup, assigning truth value for whether all of current player's pieces are all grouped together 
		bool winGroup = board.winCondition(currPlayer->getColor(), move, currPlayer->getPieces(board.getBoard()));
		// Declaring the boolean wipePieces, assigning truth value for whether current player only has one piece left
		bool wipePieces = swap()->getPieces(board.getBoard()) <= 1;
		// Win condition has been met and the round has ended, current player wins
		if (winGroup || wipePieces) {
			currPlayer->setScore(currPlayer->getPieces(board.getBoard()) - swap()->getPieces(board.getBoard()));
			currPlayer->setWins(currPlayer->getWins() + 1);
			break;
		}

		// Displays board grid interface
		boardview.display_board(board.getBoard());

		std::cout << "Would you like to continue playing or take a break and save this tournament?" << std::endl;
		std::cout << "Keep playing (1)" << std::endl << "Save game (2)" << std::endl;

		do {
			// Assigning the user input (2) save game or (1) keep playing to response 
			std::cin >> response;
		} while (response != '1' && response != '2');

		if (response == '2') {
			serial.saveGame(players, swap(), board.getBoard());
			// Quits tournament 
			exit(0);

		}

		std::cout << std::endl;
		// Swaps players for upcoming turn
		currPlayer = swap();
		boardview.display_board(board.getBoard());
	}
	boardview.display_board(board.getBoard());
	std::cout << std::endl << currPlayer->getIdentity() << " wins the round!" << std::endl;
	std::cout << std::endl;

}

/* *********************************************************************
Function Name: swap
Purpose: Handles which player will have the next turn in a round. 
Parameters: none
Return Value: A Player class pointer, a memory address associated
			  with a declared Player class object
Algorithm: none
Reference: none
********************************************************************* */
Player* Round::swap() {

	if (currPlayer == players[0]) {
		return players[1];
	}
	else {
		return players[0];
	} 

}

/* *********************************************************************
Function Name: getRoundWon
Purpose: To obtain the current round in a Tournament's win state
Parameters: none
Return Value: The win condition of the current round, a truth value
Algorithm: none
Reference: none
********************************************************************* */
const bool Round::getRoundWon() {
	return roundWon;
}

/* *********************************************************************
Function Name: setRoundWon
Purpose: To assign a truth value to the roundWon private member boolean
Parameters:
			roundWon, a boolean passed by value. It holds the winning state 
			of the round
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Round::setRoundWon(bool roundWon) {
	this->roundWon = roundWon;
}