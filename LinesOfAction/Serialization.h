#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Piece.h"	
#include <filesystem>
#include <array>
#include <sstream>
#include "Board.h"

namespace fs = std::filesystem;

class Serialization
{

	public:

		Serialization();

		~Serialization() {
			
		}

		void saveGame(Player** players, Player* nextPlayer, std::array<std::array<Piece, 8>, 8> board); 

		void loadGame(Player** players, Player*& nextPlayer, Board& board);

		void getFiles();

		std::string toLower(const std::string& str);

		std::string isUnique(std::string fileName);

		bool isAlphaNum(std::string fileName);

		void listFiles();

	private:
		std::vector<std::string> textFiles;

};

