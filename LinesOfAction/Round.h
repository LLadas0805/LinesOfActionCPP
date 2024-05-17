#pragma once
#include <iostream>
#include "Player.h"
#include <stdlib.h>
#include "BoardView.h"
#include "Board.h"
#include <cctype> 
#include <ctime>
#include <stdio.h>
#include <stdlib.h>


class Round
{
		
	public:

		Round(Player** players);

		// Decides who is the starting player of a round 
		void starting_player();

		// Sets up the round loop for lines of action
		void initiate_round(bool loaded);
		
		// Handles swaps for players every turn
		Player* swap();

		const bool getRoundWon();

		void setRoundWon(bool roundWon);

	private:
		bool roundWon;
		Player* currPlayer;
		Player** players;
};

