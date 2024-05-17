#include "Piece.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <array>
#include <stack>
#include <vector>
#pragma once

class Board
{
		
	public:

		Board() {
			initial_state();
		}

		~Board() {
		}

		// Default placements of pieces on the board
		void initial_state();

		// Checks to see if board input is in the right syntax/format and range
		bool validate_range(std::string coordinates);

		int calcPiecesHori(int row);

		int calcPiecesVert(int col);

		int calcPiecesDiag(int begRow, int begCol, int slope_X, int slope_Y);

		bool validate_piece(char color, std::string coordinates);

		bool validate_moveset(std::string origin, std::string destination);

		bool validate_vertical(std::string origin, std::string destination);

		bool validate_horizontal(std::string origin, std::string destination);

		bool validate_diagonal(std::string origin, std::string destination);

		// If we have done all of our validation, we can move the piece to it's destination
		void move_piece(std::string origin, std::string destination);

		std::vector<std::string> getGroupPieces(std::string coordinates, char color);

		int isGrouped(int row, int col, char color, std::array<std::array<bool, 8>, 8> & visited, std::vector<std::string>& pieces);

		bool winCondition(char color, std::string coordinates, int pieceCount);
		
		std::array<std::array<Piece, 8>, 8> getBoard();

		void setBoard(std::array<std::array<Piece, 8>, 8> board);
		
	private:
		std::array<std::array<Piece, 8>, 8> board;

};

