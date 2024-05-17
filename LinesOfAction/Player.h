#pragma once
#include <string>
#include <iostream>
#include "Piece.h"
#include <array>
#include "board.h"

class Player
{
	
	public:

		Player(std::string identity, char color = '\0', int score = 0, int wins = 0);

		~Player() {
		}

		virtual std::string play(Board& board, Player* self, Player* nextPlayer);

		char getColor();

		void setColor(char color);

		int getPieces(std::array<std::array<Piece, 8>, 8> board);

		int getScore();

		void setScore(int score);

		int getWins();

		void setWins(int wins);

		std::string getIdentity();

		Piece strategize(Board board, Player* self, Player* nextPlayer);
		
		bool comparePiecesByStrategy(Piece& piece1, Piece& piece2);
		
		Piece pieceStrategy(Board& board, std::string origin, Player* self, Player* nextPlayer);

		int strategyToRank(std::string strategy);

		std::string rankToStrategy(int rank);

		bool scoreCheck(std::array<std::array<Piece, 8>, 8> board, Player* nextPlayer);

		bool colorCheck(char coordColor);

		bool isOccupied(std::array<std::array<Piece, 8>, 8> board, std::string coordinates);

		bool canCapture(std::array<std::array<Piece, 8>, 8> board, std::string coordinates, Player* nextPlayer);

		bool canWin(Board board, std::string origin, std::string destination);

		bool canDelay(int strategy, std::array<std::array<Piece, 8>, 8> board,  Player* nextPlayer);

		bool canBlock( std::array<std::array<Piece, 8>, 8> board, std::string coordinates);

		bool canGroup(Board board, std::string origin, std::string destination);

		bool imminentWin(Board board, std::vector<std::string>& winningCoords);

		bool boundsCheck(int row, int col);

		bool canThwart(Board board, std::string coordinates, Player* self, Player* nextPlayer);

	private:

		char color;
		int score;
		int wins;
		std::string identity;

};

