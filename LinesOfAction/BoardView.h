#include "Board.h"
#include <array>
#pragma once
class BoardView
{
	public:
		void display_board(std::array<std::array<Piece, 8>, 8> board);
};

