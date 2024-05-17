#pragma once
#include <string>
class Piece
{
	
		
	public:
		Piece(char color = '.');
		char getColor();
		std::string getStrategy();
		void setStrategy(std::string strategy);
		std::string getStratCoords();
		void setStratCoords(std::string stratCoords);
		std::string getOrigin();
		void setOrigin(std::string origin);

	private:
		char color;
		std::string strategy;
		std::string stratCoords;
		std::string origin;
};

