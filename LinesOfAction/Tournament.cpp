#include "Tournament.h"

/* *********************************************************************
Function Name: initiate_tournament
Purpose: Handles the start and loop of a tournament
Parameters: none
Return Value: none
Algorithm:
            1) Define a boolean loaded, set to false
			2) Check if player wants to create new tournament (1) or load an ongoing match (2)
			3) If response was not 1 and was not 2 we go back to step 1
			4) If response was 2, loaded assigned to true
			5) Iterate through player member and clear color values
			6) Start a new round and pass in loaded as a parameter
			7) Display player scores and wins
			8) Check if player wants to start a new round (y/n)
			9) If response is not y or n, go back to step 8
			10) If response was y, go back to step 5
			11) If response was n, determine and output tournament outcome and winners
Reference: none
********************************************************************* */
void Tournament::initiate_tournament() {

    // response holds the user input inside the tournament logic
	char response;
    // loaded holds the truth statement for if a match has been loaded in 
    // assigned to false for now
	bool loaded = false;

	do {
		std::cout << "Create a new tournament (1)" << std::endl;
		std::cout << "Load an ongoing tournament (2)" << std::endl;
        // assigned user input to response
		std::cin >> response;
	} while (response != '1' && response != '2');

    // Load tournament
	if (response == '2') {
        // assign true to loaded, player wants to load a save file
		loaded = true;
	}
    
    do {

        // Reset player information
        for (int i = 0; i < 2; ++i) {
            players[i]->setColor('\0');
        }

        // round holds a new Round class object which passes in the player roster as a parameter
		Round round = Round(players);

        round.initiate_round(loaded);

        // Display player scores and wins
        for (int i = 0; i < 2; ++i) {
            std::cout << players[i]->getIdentity() << "'s score: " << players[i]->getScore() << std::endl;
            std::cout << players[i]->getIdentity() << " wins: " << players[i]->getWins() << std::endl;
            std::cout << std::endl;
        }

        std::cout << std::endl;
        // Prompt user to start a new round
        do {
            std::cout << "Would you like to start a new round? Yes or no? (Y/N): ";
            // assign new round user input to response
            std::cin >> response;
            // assign upper case version of response to response
            response = toupper(response); // Corrected toupper usage
        } while (response != 'Y' && response != 'N'); // Corrected logical condition

        if (response == 'N') {
            break;
        }

		// After we load in the round once, we do not need to load it again
        // Assign false to loaded
		loaded = false;

    } while (response == 'Y');

    std::cout << std::endl;
    // Determine tournament winner
    if (players[0]->getWins() > players[1]->getWins()) {
        std::cout << "Human wins the tournament!" << std::endl;
    }
    else if (players[0]->getWins() < players[1]->getWins()) {
        std::cout << "The computer wins the tournament!" << std::endl;
    }
    else {
        std::cout << "This tournament was a tie!" << std::endl;
    }
    // Display final wins for each player
    for (int i = 0; i < 2; ++i) {
        std::cout << players[i]->getIdentity() << " wins: " << players[i]->getWins() << std::endl;
		std::cout << players[i]->getIdentity() << "'s score: " << players[i]->getScore() << std::endl;
        std::cout << std::endl;
    }
}

/* *********************************************************************
Function Name: getPlayers
Purpose: To obtain the list of players in a tournament
Parameters: none
Return Value: The memory address of the players array, double pointer Player value
Algorithm: none
Reference: none
********************************************************************* */
Player** Tournament::getPlayers() {
	return this->players;
}