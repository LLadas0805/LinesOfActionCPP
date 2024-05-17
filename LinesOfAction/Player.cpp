#include "Player.h" 

/* *********************************************************************
Function Name: Player
Purpose: Constructor meant to initialize and define private members of the 
         Player class when created as an object
Parameters: identity, a string passed by value meant to assign the Player
            object with either human or computer 

			color, a char passed by value used to define what color of 
			pieces the player can control 

			score, an int passed by value used to pass on the total score
			a player has throughout the tournament

			wins, an int passed by value used to pass on the total round
			wins the player has throughout the tournament
			
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
Player::Player(std::string identity, char color, int score, int wins) {

	 this->color = color;
	 this->score = score;
	 this->wins = wins;
	 this->identity = identity;
}

/* *********************************************************************
Function Name: play
Purpose: Default definition for Player object play function, temporary and 
         meant to be overridden by children classes
Parameters: board, a Board object reference meant to be have it's board grid
            modified when pieces are moved

			self, a Player object pointer, getting the memory address of the current
			player in a turn

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn 
Return Value: empty string
Algorithm: none
Reference: none
********************************************************************* */
std::string Player::play(Board& board, Player* self, Player* nextPlayer) {
	return "";
}

/* *********************************************************************
Function Name: getColor
Purpose: To obtain the current player's color/side
Parameters: none
Return Value: The color associated with the player object, a char value
Algorithm: none
Reference: none
********************************************************************* */
char Player::getColor() {
	return this->color;
}
/* *********************************************************************
Function Name: setColor
Purpose: modifies the current player's color
Parameters: color, a char passed by value used to be assigned to the color 
            in the Player class
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Player::setColor(char color) {
	this->color = color;
}

/* *********************************************************************
Function Name: getPieces
Purpose: To obtain the number of pieces associated with the player's color
Parameters:
			board, a 2D array of Piece class objects passed by value. 
			It holds all of the board grid information on pieces
Return Value: The total count of pieces on the board matching with the 
              player's color
Algorithm: none
Reference: none
********************************************************************* */
int Player::getPieces(std::array<std::array<Piece, 8>, 8> board) {

	int pieces = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getColor() == color) {
				pieces++;
			}
		}
	}
	return pieces;
}

/* *********************************************************************
Function Name: getScore
Purpose: To obtain the current player's score in the tournament
Parameters: none
Return Value: The integer value of the player's score
Algorithm: none
Reference: none
********************************************************************* */
int Player::getScore() {
	return score;
}
/* *********************************************************************
Function Name: setScore
Purpose: modifies the current player's score
Parameters: score, an int passed by value used to be assigned to the score
			in the Player class
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Player::setScore(int score) {
	this->score = score;
}
/* *********************************************************************
Function Name: getWins
Purpose: To obtain the current player's wins in the tournament
Parameters: none
Return Value: The integer value of the player's wins
Algorithm: none
Reference: none
********************************************************************* */
int Player::getWins() {
	return wins;
}
/* *********************************************************************
Function Name: setWins
Purpose: modifies the current player's wins in the tournament
Parameters: wins, an int passed by value used to be assigned to the wins
			in the Player class
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Player::setWins(int wins) {
	this->wins = wins;
}
/* *********************************************************************
Function Name: getIdentity
Purpose: To obtain the current player's identity in a tournament
Parameters: none
Return Value: The string value associated with a player's identity
Algorithm: none
Reference: none
********************************************************************* */
std::string Player::getIdentity() {
	return identity;
}

/* *********************************************************************
Function Name: strategize
Purpose: For finding the best piece a player can move to in a given turn
Parameters: board, a Board class object passed by value 

			self, a Player object pointer, getting the memory address of the current
			player in a turn

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn
Return Value: A Piece class object of the best piece and their best strategy
Algorithm:
			1) Iterate through the board's grid and get the color of the piece at the given iterated coordinates
			2) Check if the current player's color matches with the color the iteration landed on 
			3) If true, we generate the best strategy the piece has and store it inside a vector
			4) If the player is a human, we output the piece's strategy
			5) Exit loop, enter new loop to iterate through strategy vector
			6) Sort the vector by ranking each piece and their strategy
			7) The first element of the vector is selected as the best piece to choose for returns
			8) Recommended strategy for this piece is output to player
Reference: C++ documentation Standard Template Library
********************************************************************* */
Piece Player::strategize(Board board, Player* self, Player* nextPlayer) {

	if (self->getIdentity() == "Human") {
		std::cout << std::endl << "Available Strategies:\n" << std::endl;
	}
	// playerPieces holds all of the pieces associated with current player
	std::vector<Piece> playerPieces;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// coordColor holds the current color of a piece in the current nested loop iteration of the board 
			char coordColor = board.getBoard()[i][j].getColor();
			if (coordColor == color && color != '.') {
				// coords holds the conversion of the iteration values into the formatted input for selecting pieces
				std::string coords = std::string(1, static_cast<char>(j + 65)) + std::to_string(8 - (i));
				// currPiece holds the given piece at this loop iterator's element and the best strategy ithas
				Piece currPiece = pieceStrategy(board, coords, self, nextPlayer);
				// only adds pieces with available strategies
				if (currPiece.getStrategy() != "") {
					// assigns where the piece was first found in the board
					currPiece.setOrigin(coords);
					// add the current piece to the playerPieces vector
					playerPieces.push_back(currPiece);
					
					std::cout << " - Move piece from " << coords << " to " << currPiece.getStratCoords() << " (" << currPiece.getStrategy() << ")\n";
					
				}
			}
		}
	}

	// sorts playerPieces from best strategy to worst strategy
	for (int i = 0; i < playerPieces.size(); ++i) {
		for (int j = 0; j < playerPieces.size() - i - 1; ++j) {
			if (!comparePiecesByStrategy(playerPieces[j], playerPieces[j + 1])) {
				// Swap pieces if they are not in the correct order
				std::swap(playerPieces[j], playerPieces[j + 1]);
			}
		}
	}

	// bestPiece holds the best possible piece and strategy to make out of all the player pieces
	// assign first element of sorted player Pieces to bestPiece
	Piece bestPiece = playerPieces[0];

	if (self->getIdentity() == "Human") {
		std::cout << std::endl << "Recommended Strategy:\n" << std::endl;
	}
	else {
		std::cout << std::endl << "Computer's Strategy:\n" << std::endl;
	}
	std::cout << " - Moves piece from " << bestPiece.getOrigin() << " to " << bestPiece.getStratCoords() << " (" << bestPiece.getStrategy() << ")\n";
	std::cout << std::endl;


	return bestPiece;
}

/* *********************************************************************
Function Name: comparePiecesByStrategy
Purpose: Comparing two pieces to rank which strategy is higher priority
Parameters: piece1, a Piece class object passed by reference, used for left hand comparison
			for strategy ranking, no modification

			piece2, a Piece class object passed by reference, used for right hand comparison
			for strategy ranking, no modification
Return Value: the truth value of if the first piece's strategy is worse than the second
Algorithm: none
Reference: none
********************************************************************* */
bool Player::comparePiecesByStrategy(Piece& piece1, Piece& piece2) {
	int rank1 = strategyToRank(piece1.getStrategy());
	int rank2 = strategyToRank(piece2.getStrategy());
	return rank1 < rank2;
}

/* *********************************************************************
Function Name: pieceStrategy
Purpose: For finding the best strategy a piece can make in a given turn
Parameters: board, a Board class object passed by reference, allows for grid access and 
            piece modification
			
			origin, a string value holding the formatted current location of a piece

			self, a Player object pointer, getting the memory address of the current
			player in a turn

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn
Return Value: A Piece class object of the best piece and their best strategy
Algorithm:
			1) Get each direction for a piece and calculate how far it can move in that turn
			2) Format the coordinates so they can be passed in and compatible with the board
			3) Loop through each move coordinate and keep track of a best strategy variable
			4) If the move coordinate is a valid move, we can check all possible strategies
			5) First, a check is made for if the move will lead to a win
			6) Store the win strategy as part of current strategy
			5) Next, a check is made for if the move will lead to a thwart
			6) Store the thwart strategy as part of current strategy
			7) Then, a check is made for if the move will lead to a delay
			8) Store the delay strategy as part of current strategy
			9) Next, a check is made for if the move will lead to a capture
			10) Store the capture strategy as part of current strategy
			11) Then, a check is made for if the move will lead to a block
			12) Store the block strategy as part of current strategy
			13) Next, a check is made for if the move will lead to a group
			14) Store the group strategy as part of current strategy
			15) Then, a check is made for if the move will lead to a block
			16) Store the block strategy as part of current strategy
			17) If none of these strategies are valid, we can set current strategy to move
			18) At end of loop, if our current strategy is >= bestStrategy
			19) If true, we change our best strategy to current strategy
			20) We then modify the board class object array at original piece 
			    to set the best strategy and the strategy's destination
Reference: C++ documentation Standard Template Library
********************************************************************* */
Piece Player::pieceStrategy(Board& board, std::string origin, Player* self, Player* nextPlayer) {
	// row holds the specific row index value of the origin coordinates
	int row = 8 - static_cast<long long>(std::stoi(origin.substr(1, 1)));
	// col holds the specific column index value of the origin coordinates
	int col = static_cast<long long>(origin[0]) - 65;

	// boardGrid holds the 2D Piece array that is contained inside the board class reference
	std::array<std::array<Piece, 8>, 8> boardGrid = board.getBoard();
	// bestStrategy holds the integer value for the best strategy that can be made
	int bestStrategy = -1;
	// bestCoords holds the string coordinate value position associated with the best strategy
	std::string bestCoords;


	// Get each direction's possible distance
	// vertCount holds the distance a piece can move vertically
	int vertCount = board.calcPiecesVert(col);
	// horiCount holds the distance a piece can move horizontally
	int horiCount = board.calcPiecesHori(row);
	// diagPosCount holds the distance a piece can move diagonally with positive slope
	int diagPosCount = board.calcPiecesDiag(row, col, 1, -1);
	// diagNegCount holds the distance a piece can move diagonally with negative slope
	int diagNegCount = board.calcPiecesDiag(row, col, 1, 1);


	// destinations is a size 8 array of strings for
	// holding the formatted coordinates for each possible direction a player can move to
	std::string destinations[8] = {
		// upwards direction
		std::string(1, static_cast<char>(col + 65)) + std::to_string(8 - (row + (-1 * vertCount))),
		// downwards direction
		std::string(1, static_cast<char>(col + 65)) + std::to_string(8 - (row + vertCount)),
		// right direction
		std::string(1, static_cast<char>((col + horiCount) + 65)) + std::to_string(8 - (row)),
		// left direction
		std::string(1, static_cast<char>(((col)+(-1 * horiCount)) + 65)) + std::to_string(8 - (row)),
		// upright direction
		std::string(1, static_cast<char>((col + diagPosCount) + 65)) + std::to_string(8 - (row + (-1 * diagPosCount))),
		// downleft direction
		std::string(1, static_cast<char>((col + (diagPosCount * -1)) + 65)) + std::to_string(8 - (row + diagPosCount)),
		// downright direction
		std::string(1, static_cast<char>((col + (diagNegCount)) + 65)) + std::to_string(8 - (row + diagNegCount)),
		// upleft direction
		std::string(1, static_cast<char>((col + (diagNegCount * -1)) + 65)) + std::to_string(8 - (row + (-1 * diagNegCount)))
	};

	// check each piece direction for move strategies
	for (int i = 0; i < 8; i++) {

		// Go through each destination 
		std::string destination = destinations[i];

		// currStrategy holds which strategy a direction will select
		// assigned at -1 for now (not possible strategy)
		int currStrategy = -1;

		// Checks to see if the move direction is possible in the firstplace
		if (board.validate_moveset(origin, destination)) {


			if (canWin(board, origin, destination)) {

				if (isOccupied(boardGrid, destination)) {
					// assigns win & capture to currStrategy
					currStrategy = 7;
				}
				// assigns win to currStrategy
				currStrategy = 6;
			}
			else if (canThwart(board, destination, self, nextPlayer)) {
				// assigns thwart to currStrategy
				currStrategy = 5;
			}
			else if (canDelay(bestStrategy, boardGrid,  nextPlayer)) {
				// assigns delay to currStrategy
				currStrategy = 4;
			}
			else if (canCapture(boardGrid, destination, nextPlayer)) {
				// assigns capture to currStrategy
				currStrategy = 3;
			}
			else if (canGroup(board, origin, destination)) {
				// assigns group to currStrategy
				currStrategy = 2;
			}
			else if (canBlock(boardGrid, destination)) {
				// assigns block to currStrategy
				currStrategy = 1;
			}
			else {
				// assigns move to currStrategy
				currStrategy = 0;
			}

			// Compares strategies for finding best move
			if (currStrategy >= bestStrategy) {
				// assign current strategy that is better to bestStrategy
				bestStrategy = currStrategy;
				// assign the best strategy's destination to bestCoords
				bestCoords = destination;
			}
		}
	}

	// no strategy will be stored if somehow no possible moves could be made
	if (bestStrategy > -1) {
		// Piece at given coordinates has strategy and coordinates modified to the best strategy
		boardGrid[row][col].setStrategy(rankToStrategy(bestStrategy));
		boardGrid[row][col].setStratCoords(bestCoords);
	}

	return boardGrid[row][col];

}

/* *********************************************************************
Function Name: strategyToRank
Purpose: Converting a piece's strategy into their numerical ranking
Parameters: strategy, a string value passed by value, used for convering into rank
Return Value: the integer value of the rank associated with strategy
Algorithm: none
Reference: none
********************************************************************* */
int Player::strategyToRank(std::string strategy) {

	std::string strategies[8] = { "win & capture", "win", "thwart", "delay", "capture",  "group up with friendly pieces", "block", "move" };

	for (int i = 0; i < 8; i++) {

		if (strategy == strategies[i]) {
			return i;
		}
	}

	return 0;

}
/* *********************************************************************
Function Name: rankToStrategy
Purpose: Converting a piece's rank into their categorical strategy
Parameters: rank, an int value used for switch statement comparison
Return Value: the string value of the strategy associated with rank
Algorithm:
			1) Compare rank with each ranking and corresponding strategy in a switch 
			
Reference: none
********************************************************************* */
std::string Player::rankToStrategy(int rank) {

	// Compares parameter with all cases to return proper strategy
	switch (rank) {

	case 7:
		return "win & capture";
		break;
	case 6:
		return "win";
		break;
	case 5:
		return "thwart";
		break;
	case 4:
		return "delay";
		break;
	case 3:
		return "capture";
		break;
	case 2:
		return "group up with friendly pieces";
		break;
	case 1:
		return "block";
		break;
	case 0:
		return "move";
		break;
	default:
		return "";
	}
}

/* *********************************************************************
Function Name: scoreCheck
Purpose: Compares the two player's scores in a round 
Parameters: board, an 8x8 2D Piece array passed by value

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn 
Return Value: the truth value of if player's score in a round is <= opponent score
Algorithm: none
Reference: none
********************************************************************* */
bool Player::scoreCheck(std::array<std::array<Piece, 8>, 8> board, Player* nextPlayer) {
	int selfScore = getPieces(board) - nextPlayer->getPieces(board);
	int oppScore = nextPlayer->getPieces(board) - getPieces(board);
	return selfScore < oppScore;
}

/* *********************************************************************
Function Name: colorCheck
Purpose: Converting a piece's rank into their categorical strategy
Parameters: coordColor, a char passed by value used for comparing with
			own player's color
Return Value: the truth value if coordColor is not equal to player's color
              and if coordColor is not an empty piece
Algorithm: none
Reference: none
********************************************************************* */
bool Player::colorCheck(char coordColor) {
	return (coordColor != color && coordColor != '.');
}

/* *********************************************************************
Function Name: isOccupied
Purpose: Checks to see if piece at coordinates in the board is from the opponent
Parameters: board, an 8x8 2D Piece array passed by value

			coordinates, a string passed by value used for finding if color 
			at given point in board is different than the player color
Return Value: the truth value of coordColor being different than player color and not empty
Algorithm: none
Reference: none
********************************************************************* */
bool Player::isOccupied(std::array<std::array<Piece, 8>, 8> board, std::string coordinates) {
	int row = 8 - static_cast<long long>(std::stoi(coordinates.substr(1, 1)));
	int col = static_cast<long long>(coordinates[0]) - 65;

	char coordColor = board[row][col].getColor();


	return colorCheck(coordColor);
}

/* *********************************************************************
Function Name: canCapture
Purpose: Checks to see if player's piece should capture an opponent's piece
Parameters: board, an 8x8 2D Piece array passed by value

			coordinates, a string passed by value used for finding if color
			at given point in board is different than the player color

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn
Return Value: the truth value of the coordinates being occupied and if the player score
              is less than or equal to the opponent score in a round
Algorithm: none
Reference: none
********************************************************************* */
bool Player::canCapture(std::array<std::array<Piece, 8>, 8> board, std::string coordinates, Player* nextPlayer) {

	return (isOccupied(board, coordinates) && scoreCheck(board, nextPlayer));
}

/* *********************************************************************
Function Name: canWin
Purpose: Checking if the piece, when moved will be grouped up with all other pieces of the 
         player's color
Parameters: board, an 8x8 2D Piece array passed by value

			origin, a string passed by value used for getting the formatted starting
			coordinates of the current piece

			destination, a string passed by value used for getting the formatted ending
			coordinates of the current piece


Return Value: the truth value of if the moved piece will meet the win conditions stated in the Board class
Algorithm: none
Reference: none
********************************************************************* */
bool Player::canWin(Board board, std::string origin, std::string destination) {

	board.move_piece(origin, destination);
	return board.winCondition(color, destination, getPieces(board.getBoard()));


}

/* *********************************************************************
Function Name: canDelay
Purpose: Converting a piece's rank into their categorical strategy
Parameters: strategy, an int value used for getting best strategy at the current iteration 
		    
			board, an 8x8 2D Piece array passed by value


			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn
Return Value: the truth value of if the piece has a low enough score and if the best strategy is winning
Algorithm: none
Reference: none
********************************************************************* */
bool Player::canDelay(int strategy, std::array<std::array<Piece, 8>, 8> board,  Player* nextPlayer) {

	return (scoreCheck(board, nextPlayer) && strategy == 6);
}

/* *********************************************************************
Function Name: canBlock
Purpose: Checks if current player piece's move coordinates will land on the second and
         penultimate rows and columns. Also checks if piece will block at least one direction
         of movement for the opponent piece located at the first and last rows and columns in the board
Parameters: board, an 8x8 2D Piece array passed by value

			coordinates, a string passed by value used for getting location of
			piece on the board grid

Return Value: Returns the truth value of if the piece location of the current player is
              at the penultimate row and column or second row and columns. AND
			  if the piece will block a opponent piece in the first and last rows and columns
Algorithm:
			1) Check if row is the 2nd from the top of the board
			2) If true, iterate through all directions possible, top left, top center, top right
			3) At one of these directions, if current piece is blocking an opponent, true
			4) Check if row is the 2nd from the bottom of the board
			5) If true, iterate through all directions possible, bottom left, bottom center, bottom right
			6) At one of these directions, if current piece is blocking an opponent, true
			7) Check if column is the 2nd from the left most of the board
			8) If true, iterate through all directions possible, left up, top center, left bottom
			9) At one of these directions, if current piece is blocking an opponent, true
			10) Check if column is the 2nd from the right most of the board
			11) If true, iterate through all directions possible, right up, right center, right bottom
			12) At one of these directions, if current piece is blocking an opponent, true
			13) if row or column is equal to none of these values, return false
Reference: none
********************************************************************* */
bool Player::canBlock(std::array<std::array<Piece, 8>, 8> board, std::string coordinates) {

	// row holds the index value associated with the array's rows
	int row = 8 - static_cast<long long>(std::stoi(coordinates.substr(1, 1)));
	// col holds the index value associated with the array's columns
	int col = static_cast<long long>(coordinates[0]) - 65;

	// Check for top row blocking
	if (row == 1) {
		for (int i = -1; i < 2; i++) {
			if (col + i < 8 && col + i >= 0) {
				if (colorCheck(board[0][col + i].getColor()) == true) {
					return true;
				}
			}
		}
		return false;
	}
	// check for bottom row blocking
	else if (row == 6) {
		for (int i = -1; i < 2; i++) {
			if (col + i < 8 && col + i >= 0) {
				if (colorCheck(board[7][col + i].getColor()) == true) {
					return true;
				}
			}

		}
		return false;
	}
	// Check for first column blocking
	else if (col == 1) {
		for (int i = -1; i < 2; i++) {
			if (row + i < 8 && row + i >= 0) {
				if (colorCheck(board[row + i][0].getColor()) == true) {
					return true;
				}
			}
		}
		return false;
	}
	// Check for last column blocking
	else if (col == 6) {
		for (int i = -1; i < 2; i++) {
			if (row + i < 8 && row + i >= 0) {
				if (colorCheck(board[row + i][7].getColor()) == true) {
					return true;
				}
			}
		}
		return false;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: canGroup
Purpose: Checking if player will join a new group when moving to location
Parameters: board, a Board class object used to call board information and 
			get the pieces grid 

			origin, a string passed by value used for getting the formatted starting
			coordinates of the current piece

			destination, a string passed by value used for getting the formatted ending
			coordinates of the current piece
Return Value: the truth value for if when the piece moves, it leaves the original group and
              joins a new group
Algorithm: none
Reference: none
********************************************************************* */
bool Player::canGroup(Board board, std::string origin, std::string destination) {

	// Gets both groups and compares same occuring pieces 
	std::vector<std::string> firstGroup = board.getGroupPieces(origin, color);
	board.move_piece(origin, destination);
	std::vector<std::string> secondGroup = board.getGroupPieces(destination, color);

	for (int i = 0; i < firstGroup.size(); i++) {
		for (int j = 0; j < secondGroup.size(); j++) {


			if (firstGroup[i] == secondGroup[j] || secondGroup.size() <= 1) {
				return false;
			}
		}
	}

	return true;
}

/* *********************************************************************
Function Name: imminentWin
Purpose: Checking if each direction of a player can cause a win 
Parameters: board, a Board class object used to call board information and
			get the pieces grid

			winningCoords, a string vector passed by reference
			modifies the elements inside the vector
Return Value: the truth value for a win occuring at a certain direction 
Algorithm:
			1) Loop through board grid to find 
			2) Find color at board coordinates and compare it with player color
			3) If color matches, proceed with following steps at 5
			4) If color does not match, repeat steps above
			5) Get each direction for a piece and calculate how far it can move in that turn
			6) Format the coordinates so they can be passed in and compatible with the board
			7) Loop through each move coordinate and keep track of a best strategy variable
			8) If the move coordinate is a valid move, we can check all possible strategies
			9) First, a check is made for if the move will lead to a win
			10) push to vector if a win is found
			11) repeat from step 2
			12) After loop ended, check if vector is not empty
			13) If not empty, returen true
			14) If empty return false
Reference: none
********************************************************************* */
bool Player::imminentWin(Board board, std::vector<std::string> &winningCoords ) {

	// loop through entire board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// coordColor holds the piece color at the given indices in board grid
			char coordColor = board.getBoard()[i][j].getColor();
			if (coordColor == color) {
				// coords holds the formatted coordinates for board actions, assigned to iterators 
				// converted to string
				std::string coords = std::string(1, static_cast<char>(j + 65)) + std::to_string(8 - (i));

				// row holds the index value associated with the array's rows
				int row = 8 - static_cast<long long>(std::stoi(coords.substr(1, 1)));
				// col holds the index value associated with the array's columns
				int col = static_cast<long long>(coords[0]) - 65;

				// Get each direction's possible distance
				// vertCount holds the distance a piece can move vertically
				int vertCount = board.calcPiecesVert(col);
				// horiCount holds the distance a piece can move horizontally
				int horiCount = board.calcPiecesHori(row);
				// diagPosCount holds the distance a piece can move diagonally with positive slope
				int diagPosCount = board.calcPiecesDiag(row, col, 1, -1);
				// diagNegCount holds the distance a piece can move diagonally with negative slope
				int diagNegCount = board.calcPiecesDiag(row, col, 1, 1);

				// destinations is a size 8 array of strings for
				// holding the formatted coordinates for each possible direction a player can move to
				std::vector<std::string> destinations = {
					// upwards direction
					std::string(1, static_cast<char>(col + 65)) + std::to_string(8 - (row + (-1 * vertCount))),
					// downwards direction
					std::string(1, static_cast<char>(col + 65)) + std::to_string(8 - (row + vertCount)),
					// right direction
					std::string(1, static_cast<char>((col + horiCount) + 65)) + std::to_string(8 - (row)),
					// left direction
					std::string(1, static_cast<char>(((col)+(-1 * horiCount)) + 65)) + std::to_string(8 - (row)),
					// upright direction
					std::string(1, static_cast<char>((col + diagPosCount) + 65)) + std::to_string(8 - (row + (-1 * diagPosCount))),
					// downleft direction
					std::string(1, static_cast<char>((col + (diagPosCount * -1)) + 65)) + std::to_string(8 - (row + diagPosCount)),
					// downright direction
					std::string(1, static_cast<char>((col + (diagNegCount)) + 65)) + std::to_string(8 - (row + diagNegCount)),
					// upleft direction
					std::string(1, static_cast<char>((col + (diagNegCount * -1)) + 65)) + std::to_string(8 - (row + (-1 * diagNegCount)))
				};

				// check each piece direction for move strategies
				for (int i = 0; i < 8; i++) {
					// destination holds current destination being iterated through
					std::string destination = destinations[i];
					if (board.validate_moveset(coords, destination)) {
						// Is win going to happen in this future move
						if (canWin(board, coords, destination)) {
							winningCoords.push_back(destination);
						}
					}
				}
				
			}
		}
	}

	if (winningCoords.size() > 0) {
		return true;
	}
	else {
		return false;
	}

	
}

/* *********************************************************************
Function Name: boundsCheck
Purpose: Checks if row and column being searched through are out of bounds
         relative to the 8x8 board  
Parameters: row, an int value used for checking row coordinate for board

			col, an int value used for checking col coordinate for board
Return Value: the truth value if row and column are less than 8 and greater than
              or equal to 0 (board bounds)
Algorithm: none
Reference: none
********************************************************************* */
bool Player::boundsCheck(int row, int col) {
	return ((row < 8 && row >= 0) && (col < 8 && col >= 0));
}

/* *********************************************************************
Function Name: canThwart
Purpose: Converting a piece's rank into their categorical strategy
Parameters: board, a Board class object used to call board information and 
			get the pieces grid 

			coordinates, a string passed by value used for getting location of
			piece on the board grid

			self, a Player object pointer, getting the memory address of the current
			player in a turn

			nextPlayer, a player object pointer, getting the memory address of the player
			who goes next turn
Return Value: the truth value for if an opponent win is imminent and if 
              the current player piece can block an opponent piece
Algorithm: none
Reference: none
********************************************************************* */
bool Player::canThwart(Board board, std::string coordinates, Player* self, Player* nextPlayer) {
	// Gets all winning strategies from the opponent and stores them in vector
	std::vector<std::string> winningCoords;
	bool isWin = nextPlayer->imminentWin(board, winningCoords);
	
	// Loops through winning coordinates to compare them with destination
	for (std::string winningPos : winningCoords) {
		if (winningPos == coordinates) {
			
			return true;
		}
	}

	return false;
}