#pragma once
#include "Player.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"

class Tournament
{

	public:
		Tournament() {

			players[0] = new Human("Human");
			players[1] = new Computer("Computer");
			
		}

		~Tournament() {
			delete players[0];
			delete players[1];
		}

		void initiate_tournament();
		Player** getPlayers();

	private:
		Player* players[2];

		
};

