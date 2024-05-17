#include "Serialization.h"

/* *********************************************************************
Function Name: Serialization
Purpose: Default constructor for serialization class objects
Parameters: none
Return Value: none
Algorithm: none
Reference: None
********************************************************************* */
Serialization::Serialization() {
	// Empty constructor
}

/* *********************************************************************
Function Name: saveGame
Purpose: Creates and formats a new save state text file for a tournament/round to load in
Parameters:
			players, a double Player pointer passed by value which stores the memory address
			of an array of players in a round

			nextPlayer, a Player pointer passed by value, has the memory address of
			which Player will go next when the game loads in

			board, a 2D array of Piece objects passed by value, holds information
			such as piece locations and how many pieces are on each side

Return Value: none
Algorithm:
			1) Get a list of all of the current files in the project directory
			2) Player inputs a name for the save they want to create
			3) If name is not unique, go back to step 2
			4) If name contains special characters, go back to step 2
			5) If name is greater than 32 characters go back to step 2
			6) After name is valid, create a file output stream 
			7) Loop through each column and row in the board 2D array to write each 
			   piece into the text grid format
			8) Write human player information such as score and round wins into the 
			   human info format
			9) Write computer player information such as score and round wins into the 
			   human info format
			10) Write next player information such as which player goes and their color
			    the next player info format
			11) Close the saved file
Reference: C++ documentation standard template library
********************************************************************* */
void Serialization::saveGame(Player** players, Player* nextPlayer, std::array<std::array<Piece, 8>, 8> board) {

	
	getFiles();

	// fileName holds the text file we want to read and parse
	std::string fileName;
	// uniqueness holds truth value for fileName being equal to an existing file in directory or not
	bool uniqueness;
	// range holds truth value of fileName being less than 32 or not
	bool range;
	// alphaNum holds the truth value of fileName being alphanumeric
	bool alphaNum;

	do {
		std::cout << "Please enter a valid name for your save file, name cannot have special characters and should be no more than 32 characters:" << std::endl;
		// assigns user's input to fileName 
		std::cin >> fileName;
		// assigns the truth value of user's input being original to uniqueness
		uniqueness = (isUnique(fileName).compare("true") != 0);
		// assigns the truth value of user's input being alphanumeric to alphaNum
		alphaNum = (!isAlphaNum(fileName));
		// assigns the truth value of user's input being greater than 32 or 0
		range = (fileName.length() == 0 || fileName.length() > 32);

	} while (uniqueness || alphaNum || range);

	// assigns the valid file name to itself appended with ".txt" for valid reading
	fileName = fileName + ".txt";
	std::ofstream savedFile(fileName);

	// Handles board save information
	savedFile << "Board:\n";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getColor() == '.') {
				savedFile << "x ";
			}
			else {
				// stores piece color into the board text grid
				savedFile << static_cast<char>(tolower(board[i][j].getColor()));
				savedFile << " ";
			}

		}
		savedFile << "\n";
	}
	
	savedFile << "\n";
	
	// Handles human save information
	savedFile << "Human:\n";
	savedFile << "Rounds won: " << players[0]->getWins() << "\n";
	savedFile << "Score: " << players[0]->getScore() << "\n";

	savedFile << "\n";

	// Handles computer save information
	savedFile << "Computer:\n";
	savedFile << "Rounds won: " << players[1]->getWins() << "\n";
	savedFile << "Score: " << players[1]->getScore() << "\n";

	savedFile << "\n";

	// Handles next player save information
	savedFile << "Next player: " << nextPlayer->getIdentity() << "\n";
	
	if (nextPlayer->getColor() == 'b') {
		savedFile << "Color: Black\n";
	}
	else {
		savedFile << "Color: White\n";
	}

	savedFile << "\n";
	savedFile.close();

}

/* *********************************************************************
Function Name: loadGame
Purpose: Selects a save state and parses the information to store inside the
         round parameters
Parameters:
			players, a double Player pointer passed by value which stores the memory address
			of an array of players in a round

			nextPlayer, a Player pointer passed by reference, has the memory address of
			which Player will go next when the game loads in. Player object will be changed 

			board, a Board class object passed by reference, has the
			board 2D Piece array member named piece modified. board
			
Return Value: none
Algorithm:
			1) Get all text files in the project director and output their names
			2) Check player input for a matching name to use for parsing information
			3) If player input has no matches to an existing file name, go back to step 2
			4) If name matches, create file input stream and
			   proceed to iterate through each line in the text file
			5) Check if line is equal to "Board:"
			6) If true, go through the next 8 lines and their respective 8 characters
			   to parse and put inside a two dimensional Piece array
			7)  Store array inside the board reference
			8)  Check if line is equal to "Human:"
			9)  If true, parse information from the relative lines and store them inside the 
			    first player element in the double pointer players
			10) Check if line is equal to "Computer:"
			11) If true, parse information from the relative lines and store them inside the 
			    second player element in the double pointer players
			12) Check if line is equal to "Next player: (identifier)"
			13) If true, we parse all information associated with and set the nextPlayer
			    pointer to the correct player, and also give the players their colors
			14) If end of file has not been reached, go back to step 5
			15) If end of file has been reached, close file
Reference: C++ documentation standard template library
********************************************************************* */
void Serialization::loadGame(Player** players, Player* &nextPlayer, Board &board) {

	getFiles();
	listFiles();

	// fileName holds the text file we want to read and parse
	std::string fileName;
	// blackPieces holds the current count of black pieces on the board, assigned to integer zero
	int blackPieces = 0;
	// whitePieces holds the current count of white pieces on the board, assigned to integer zero
	int whitePieces = 0;

	do {
		std::cout << "Please enter a valid save to load from this list: " << std::endl;
		// assigns user input for file they want to open to fileName
		std::cin >> fileName;

	} while (isUnique(fileName) == "true");

	// assigns the valid file name to itself appended with ".txt" for valid reading
	fileName = isUnique(fileName) + ".txt";
	std::ifstream inputFile(fileName);
	 
	// line holds the text inside a given line in the file being read
	std::string line;
	// tempBoard holds all pieces inside the game board
	std::array<std::array<Piece, 8>, 8> tempBoard;

	while (std::getline(inputFile, line)) {
		if (line == "Board:") {
			// Parse the board
			for (int i = 0; i < 8; ++i) {
				std::getline(inputFile, line);
				std::istringstream iss(line);
				// color holds a piece color at given coordinates on the board in text file
				char color;
				for (int j = 0; j < 8; ++j) {
					// assigns specific char piece color at a given line to color
					iss >> color;
					if (color == 'x') {
						// assigns empty piece to tempBoard array
						tempBoard[i][j] = Piece('.');
					}
					else {
						// assigns player piece to tempBoard array
						tempBoard[i][j] = Piece(toupper(color));

						if (toupper(color) == 'B' || color == 'b') {
							// assigns a new int discovered black piece (+1) to blackPieces
							blackPieces += 1;
						}
						else if (toupper(color) == 'W' || color == 'w') {
							// assigns a new int discovered white piece (+1) to whitePieces
							whitePieces += 1;
						}
					}
				}
			}
			// assigns tempBoard to the board reference
			board.setBoard(tempBoard);
		}
		// Parse human player
		else if (line == "Human:") {
			
			// Holds the text before the round won and score values
			std::string roundsWonKeyword, scoreKeyword;
			// Holds the number of rounds won by human and their score in a tournament
			int roundsWon, score;
			// Assigns the parsed values to their respective variables
			inputFile >> line >> roundsWonKeyword >> roundsWon >> scoreKeyword >> score;


			// Set human data
			(players[0])->setWins(roundsWon);
			(players[0])->setScore(score);
		}
		// Parse computer player
		else if (line == "Computer:") {
			// Holds the text before the round won and score values
			std::string roundsWonKeyword, scoreKeyword;
			// Holds the number of rounds won by computer and their score in a tournament
			int roundsWon, score;
			// Assigns the parsed values to their respective variables
			inputFile >> line >> roundsWonKeyword >> roundsWon >> scoreKeyword >> score;
	
			
			// Set computer data
			(players[1])->setWins(roundsWon);
			(players[1])->setScore(score);
		}
		// Extract player type and color information
		else if (line == "Next player: Human" || line == "Next player: Computer") {
			
			
			std::istringstream playerStream(line);
			// Holds the player type and the text leading up to it
			std::string keyword1, keyword2, playerType;
			// Assigns the parsed values to their respective variables
			playerStream >> keyword1 >> keyword2 >> playerType;

			// Read the next line for color information
			std::getline(inputFile, line);
			std::istringstream colorStream(line);
			// Holds the player color and the text leading up to it
			std::string colorPrefix, color;
			// Assigns the parsed values to their respective variables
			colorStream >> colorPrefix >> color; 

			// Set nextPlayer and its color
			if (playerType == "Human") {
				nextPlayer = players[0];
				if (color == "Black") {
					players[0]->setColor('B');
					players[1]->setColor('W');
				}
				else {
					players[1]->setColor('B');
					players[0]->setColor('W');
				}
			}
			else {
				nextPlayer = players[1];
				if (color == "Black") {
					players[1]->setColor('B');
					players[0]->setColor('W');
				}
				else {
					players[0]->setColor('B');
					players[1]->setColor('W');
				}
			}
		}
	}
	inputFile.close();
}

/* *********************************************************************
Function Name: getFiles
Purpose: To store the save text file names inside of a vector data structure
         for easy searching
Parameters: none
Return Value: none
Algorithm: none
Reference: C++ documentation standard template library
********************************************************************* */
void Serialization::getFiles() {
	// Get the path to the directory
	std::string currentDirectory = fs::current_path().string();

	// Construct the path to the project folder relative to the executable
	std::string projectFolderPath = currentDirectory;

	// Iterate over the files in the project folder
	for (const auto& entry : fs::directory_iterator(projectFolderPath)) {
		// Check if the file is a regular file and ends with ".txt"
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			// Add the file path to the vector
			textFiles.push_back(entry.path().stem().string());
		}
	}
}

/* *********************************************************************
Function Name: toLower
Purpose: To modify a string value to become all lower case to make sure
         file name comparisons are not case sensitive
Parameters:
			fileName, a string passed by reference. It holds the name of 
			a saved file in the project folder. 
Return Value: The name of the file passed in as a parameter, but lower case
              a string value
Algorithm: none
Reference: None
********************************************************************* */
std::string Serialization::toLower(const std::string& fileName) {
	std::string result = "";
	for (char c : fileName) {
		result += std::tolower(c);
	}

	return result;
}

/* *********************************************************************
Function Name: isUnique
Purpose: To check whether the name of a saved text file is unique and 
         not given to another file in the project's folder
Parameters:
			fileName, a string passed by value. It holds the input
			of a player when asked to fill out a name for a new save file
Return Value: The name of an existing file if the names are the same or,
              the value "true" if file name is unique, string value
Algorithm: none
Reference: C++ documentation standard template library
********************************************************************* */
std::string Serialization::isUnique(std::string fileName) {

	for (int i = 0; i < textFiles.size(); i++) {
		if (toLower(fileName).compare(toLower(textFiles[i])) == 0) {
			return textFiles[i];
		}
	}
	return "true";
}


/* *********************************************************************
Function Name: isAlphaNum
Purpose: To check whether the name of a saved text file is comprised of
         either letters or numbers, no special characters
Parameters:
			fileName, a string passed by value. It holds the input
			of a player when asked to fill out a name for a new save file 
Return Value: The truth value for whether the file name is alpha-numeric,
              a boolean
Algorithm: none
Reference: C++ documentation standard template library
********************************************************************* */
bool Serialization::isAlphaNum(std::string fileName) {
	for (const char& character : fileName) {

		if (!isalnum(character)) {
			return false;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: listFiles
Purpose: To obtain all of the saved game text files in the project's directory
Parameters: none
Return Value: none
Algorithm: none
Reference: C++ documentation standard template library 
********************************************************************* */
void Serialization::listFiles() {

	std::cout << "SAVED GAMES: \n";

	if (textFiles.size() == 0) {
		std::cout << "No files found, please restart game and create new tournament. \n";
		exit(0);
	}

	for (const auto& file : textFiles) {
		std::cout << file << std::endl;
	}
}