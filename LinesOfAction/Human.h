#pragma once
#include "Player.h"
class Human : public Player
{
	public:

		using Player::Player;
		std::string play(Board& board, Player* self, Player* nextPlayer) override;

};

