#include "Board.h"


/* *********************************************************************
Function Name: initial_state
Purpose: Creates and formats a new board by placing pieces into default locations
Parameters: none
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Board::initial_state() {

	// Initially fills the entire board with empty pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = Piece('.');
		}
	}

	// Outputs black pieces at the top and bottom of the board
	for (int i = 0; i < 8; i += 7) {
		for (int j = 1; j < 7; j++) {
			board[i][j] = Piece('B');
		}
	}

	// Outputs white pieces at the left and right of the board
	for (int i = 1; i < 7; i++) {
		for (int j = 0; j < 8; j += 7) {
			board[i][j] = Piece('W');
		}
	}

}

/* *********************************************************************
Function Name: validate_range
Purpose: Checks to see if the input board coordinates are in the right
         syntax, format and range
Parameters: coordinates, a string value passed by value. Used for comparison 
            relative to the board's range and syntax

Return Value: The truth value for whether or not coordinates is the correct 
              format or if it is out of bounds, a boolean
Algorithm: none
Reference: none
********************************************************************* */
bool Board::validate_range(std::string coordinates) {

	if (coordinates.length() == 2) {
		// Checks to see if the row and column are either numbers and letters  respectively
		if (std::isalpha(coordinates[0]) && std::isdigit(coordinates[1])) {
			int rowRange = std::stoi(coordinates.substr(1, 1));
			char colRange = coordinates[0];
			// Compares the rows and range value to the boundaries of the board
			if ((rowRange > 0 && rowRange < 9) && (colRange >= 'A' && colRange <= 'H')) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: validate_piece
Purpose: Checks to see if the given piece at board coordinates are in range, and if 
         they match the color of the player
Parameters: color, a char variable passed by value. Used for determining what color
			the current player is

			coordinates, a string passed by value. Used for comparison
			relative to the board's range and syntax

Return Value: The truth value for whether or not coordinates is valid and 
              the piece's color matches the color of the player, boolean
Algorithm: none
Reference: none
********************************************************************* */
bool Board::validate_piece(char color, std::string coordinates) {

	if (validate_range(coordinates)) {
		Piece selected = board[8 - static_cast<long long>(std::stoi(coordinates.substr(1, 1)))][static_cast<long long>(coordinates[0]) - 65];
		if (color == selected.getColor()) {

			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: validate_moveset
Purpose: Handles which direction a piece should go and if it is a valid
         move to make
Parameters: origin, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			destination, a string passed by value. Used for obtaining
			the user's end coordinates for of a piece's move on the board

Return Value: The truth value for whether or not destination is valid and
			  if the move itself is available to perform
Algorithm: none
Reference: none
********************************************************************* */
bool Board::validate_moveset(std::string origin, std::string destination) {

	if (origin == destination) {
		return false;
	}

	if (validate_range(destination)) {
		// Piece is in the same vertical line as destination
		if (origin[0] == destination[0]) {
			return validate_vertical(origin, destination);
		}

		// Piece is in the same horizontal line as destination
		else if (origin[1] == destination[1]) {
			return validate_horizontal(origin, destination);
		}
		// Piece is in the same diagonal line as destination
		else if (origin[0] != destination[0] && origin[1] != destination[1]) {
			
			return validate_diagonal(origin, destination);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: calcPiecesHori
Purpose: Gets the number of pieces in a given row on the game board
Parameters: row, int passed by value. Used for finding which row in the board
            to count the pieces from
Return Value: The integer number of pieces that are inside the row
Algorithm: none
Reference: none
********************************************************************* */
int Board::calcPiecesHori(int row) {
	int pieceCount = 0;
	for (int i = 0; i < 8; i++) {
		if (board[row][i].getColor() == 'W' || board[row][i].getColor() == 'B') {
			pieceCount += 1;
		}
	}
	return pieceCount;
}

/* *********************************************************************
Function Name: calcPiecesVert
Purpose: Gets the number of pieces in a given column on the game board
Parameters: col, int passed by value. Used for finding which column in the board
			to count the pieces from
Return Value: The integer number of pieces that are inside the column
Algorithm: none
Reference: none
********************************************************************* */
int Board::calcPiecesVert(int col) {
	int pieceCount = 0;
	for (int i = 0; i < 8; i++) {
		if (board[i][col].getColor() == 'W' || board[i][col].getColor() == 'B') {
			pieceCount += 1;
		}
	}
	return pieceCount;
}

/* *********************************************************************
Function Name: calcPiecesDiag
Purpose: Gets the number of pieces in a given diagonal line on the game board
Parameters: row, int passed by value. Used for finding which row in the board
            to count the pieces from

			begCol, int passed by value. Used for finding which column in the board
			to count the pieces from

			slope_X, int passed by value. Used for finding which direction the line
			is heading for the rows

			slope_Y, int passed by value. Used for finding which direction the line
			is heading for the columns
Return Value: The integer number of pieces that are inside the diagonal line
Algorithm:
			1) Get right half of the diagonal line
			2) Iterate through right half to check if current position on the board is not empty	
			3) If board location is not empty, increment the piece count
			4) Get left half of the diagonal line
			5) Iterate through left half to check if current position on the board is not empty	
			6) If board location is not empty, incrememnt the piece count
Reference: none
********************************************************************* */
int Board::calcPiecesDiag(int begRow, int begCol, int slope_X, int slope_Y) {

	// pieceCount holds the number of pieces in a diagonal line, intially assigned as 0
	int pieceCount = 0;

	// Iterate over right side of the diagonal line
	for (int i = 0; i <= 8; i++) {
		
		// row holds the current row for searching line, assigned current row to variable
		int row = begRow + (i * slope_Y);
		// col holds the current column for searching line, assigned current column to variable
		int col = begCol + (i * slope_X);

		// Ensure row and column are within the bounds of the board
		if (row >= 0 && row < 8 && col >= 0 && col < 8) {
			if (board[row][col].getColor() == 'W' || board[row][col].getColor() == 'B') {
				// assigned pieceCount being incremented
				pieceCount += 1;
			}
		}
		else {
			break;
		}
	}
	// Iterate over left side of the diagonal line
	for (int i = 0; i <= 8; i++) {
		// row holds the current row for searching line, assigned current row to variable
		int row = begRow + (-1 * (i * slope_Y));
		// col holds the current column for searching line, assigned current column to variable
		int col = begCol + (-1 * (i * slope_X));

		// Ensure row and column are within the bounds of the board
		if (row >= 0 && row < 8 && col >= 0 && col < 8) {
			if (board[row][col].getColor() == 'W' || board[row][col].getColor() == 'B') {
				// assigned pieceCount being incremented
				pieceCount += 1;
			}
		}
		else {
			break;
		}
	}
	return pieceCount - 1;
}

/* *********************************************************************
Function Name: validate_vertical
Purpose: Handles if a vertical move given the two coordinates is possible,
		 checks for blocking pieces and if move distance was valid
Parameters: origin, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			destination, a string passed by value. Used for obtaining
			the user's end coordinates for of a piece's move on the board

Return Value: The truth value for whether or not moving vertically is valid
Algorithm:
			1) Get column that will be used to check for pieces
			2) Iterate through each row in the column searching for pieces
			3) If location is not empty, increment the piece count
			4) Calculate direction the column is heading 
			5) If the origin row is greater than the destination row,
			   the move is up
			6) If the origin row is less than the destination row,
			   the move is down
			7) Iterate through the column based on the direction, 
			   starting at the beginning row to the end row
			8) Check if a piece is found that is not the same color as the 
			   origin coordinate's piece
			9) If they are different colors and the location is not empty,
			   the truth value becomes false
			10) If they are the smame color or the location is empty, continue the loop
			11) Check if the distance between the two coordinates is equal to
			   the total piece count in the column
			12) If true, then the function after all the conditions is true
			13) If false, we return false

Reference: none
********************************************************************* */
bool Board::validate_vertical(std::string origin, std::string destination) {
	// line holds the column location in the board
	// assign column element of origin's coords, converted to integer, to line
	int line = static_cast<int>(origin[0]) - 65;
	// pieceCount holds the amount of pieces there are in the column
	// assign zero to line since no pieces found yet
	int pieceCount = 0;
	for (int i = 0; i < 8; i++) {
		if (board[i][line].getColor() == 'W' || board[i][line].getColor() == 'B') {
			// assign the total number of pieces in the column + 1 to pieceCount
			pieceCount += 1;
		}
	}

	// direction stores if the move is going up (-1) or down (1)
	// assign zero to direction for now
	long long direction = 0;
	// begRow stores the row index for where the start of the move occurs in the board
	long long begRow = 8 - static_cast<long long>(std::stoi(origin.substr(1, 1)));
	// begRow stores the row index for where the end of the move lands in the board
	long long endRow = 8 - static_cast<long long>(std::stoi(destination.substr(1, 1)));

	// Direction up
	if (begRow > endRow) {
		// assign up to direction
		direction = -1;
	}
	// Direction down
	else {
		// assign down to direction
		direction = 1;
	}

	// dist holds the distance in board space between two coordinates
	// assign the difference between the beginning row and end row value to dist
	int dist = (abs(begRow - endRow));

	// Checks for blocking pieces
	for (int row = 0; row < dist; row++) {
		// colorDiff holds the truth value for if the piece located on the row in the given column is a different color
		bool colorDiff = board[begRow + (direction * row)][line].getColor() != board[begRow][line].getColor();
		// emptyPos holds the truth value for if the row in the given column is empty space
		bool emptyPos = board[begRow + (direction * row)][line].getColor() != '.';

		if (colorDiff && emptyPos) {
			return false;
			break;
		}
	}

	// colorDiff holds the truth value for if the piece located on the ending row in the given column is a different color
	bool colorDiff = board[endRow][line].getColor() != board[begRow][line].getColor();
	// distCmp holds the truth value for if the distance between the two rows is the same as the total number of pieces in column
	bool distComp = (abs(begRow - endRow)) == pieceCount;

	// Final check for if the spot we are landing on is the same color as intial piece AND if its the right amount of space
	if (colorDiff && distComp) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: validate_horizontal
Purpose: Handles if a horizontal move given the two coordinates is possible,
		 checks for blocking pieces and if move distance was valid
Parameters: origin, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			destination, a string passed by value. Used for obtaining
			the user's end coordinates for of a piece's move on the board

Return Value: The truth value for whether or not moving horizontally is valid
Algorithm:
			1) Get row that will be used to check for pieces
			2) Iterate through each column in the row searching for pieces
			3) If location is not empty, increment the piece count
			4) Calculate direction the row is heading
			5) If the origin row is greater than the destination row,
			   the move is left
			6) If the origin row is less than the destination row,
			   the move is right
			7) Iterate through the row based on the direction,
			   starting at the beginning column to the end column
			8) Check if a piece is found that is not the same color as the
			   origin coordinate's piece
			9) If they are different colors and the location is not empty,
			   the truth value becomes false
			10) If they are the smame color or the location is empty, continue the loop
			11) Check if the distance between the two coordinates is equal to
			   the total piece count in the column
			12) If true, then the function after all the conditions is true
			13) If false, we return false
Reference: none
********************************************************************* */
bool Board::validate_horizontal(std::string origin, std::string destination) {
	// line holds the row location in the board
	// assign row element of origin's coords, converted to integer, to line
	int line = 8 - std::stoi(origin.substr(1, 1));
	// pieceCount holds the amount of pieces there are in the row
	// assign zero to line since no pieces found yet
	int pieceCount = 0;
	for (int i = 0; i < 8; i++) {
		if (board[line][i].getColor() == 'W' || board[line][i].getColor() == 'B') {
			// assign the total number of pieces in the row + 1 to pieceCount
			pieceCount += 1;
		}
	}

	// direction stores if the move is going left (-1) or right (1)
	// assign zero to direction for now
	long long direction = 0;
	// begCol stores the column index for where the start of the move occurs in the board
	int begCol = static_cast<long long>(origin[0]) - 65;
	// endCol stores the column index for where the end of the move occurs in the board
	int endCol = static_cast<long long>(destination[0]) - 65;


	
	if (begCol < endCol) {
		// assign right to direction
		direction = 1;
	}
	else {
		// assign down to direction
		direction = -1;
	}

	// dist holds the distance in board space between two coordinates
	// assign the difference between the beginning row and end row value to dist
	int dist = (abs(begCol - endCol));

	// Checks for blocking pieces
	for (int col = 0; col < dist; col++) {
		// colorDiff holds the truth value for if the piece located on the column in the given row is a different color
		bool colorDiff = board[line][begCol + (direction * col)].getColor() != board[line][begCol].getColor();
		// emptyPos holds the truth value for if the column in the given row is empty space
		bool emptyPos = board[line][begCol + (direction * col)].getColor() != '.';

		if (colorDiff && emptyPos) {
			
			return false;
			break;
		}
	}
	// colorDiff holds the truth value for if the piece located on the final column in the given row is a different color
	bool colorDiff = board[line][endCol].getColor() != board[line][begCol].getColor();
	// distCmp holds the truth value for if the distance between the two columns is the same as the total number of pieces in row
	bool distComp = (abs(begCol - endCol)) == pieceCount;

	// Final check for if  spot we are landing on is the same color as intial piece AND if its the right amount of space
	if (colorDiff && distComp) {
		return true;
	}
	else {
		return false;
	}

}

/* *********************************************************************
Function Name: validate_diagonal
Purpose: Handles if a diagonal move given the two coordinates is possible,
		 checks for blocking pieces and if move distance was valid
Parameters: origin, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			destination, a string passed by value. Used for obtaining
			the user's end coordinates for of a piece's move on the board

Return Value: The truth value for whether or not moving diagonally is valid
Algorithm:
			1) Get row that will be used to check for pieces
			2) Iterate through each column in the row searching for pieces
			3) If location is not empty, increment the piece count
			4) Calculate direction the row is heading
			5) If the origin row is greater than the destination row,
			   the move is left
			6) If the origin row is less than the destination row,
			   the move is right
			7) Iterate through the row based on the direction,
			   starting at the beginning column to the end column
			8) Check if a piece is found that is not the same color as the
			   origin coordinate's piece
			9) If they are different colors and the location is not empty,
			   the truth value becomes false
			10) If they are the smame color or the location is empty, continue the loop
			11) Check if the distance between the two coordinates is equal to
			   the total piece count in the column
			12) If true, then the function after all the conditions is true
			13) If false, we return false
Reference: none
********************************************************************* */
bool Board::validate_diagonal(std::string origin, std::string destination) {

	
	// begRow stores the row index for where the start of the move occurs in the board
	int begRow = 8 - static_cast<long long>(std::stoi(origin.substr(1, 1)));
	// begRow stores the row index for where the end of the move lands in the board
	int endRow = 8 - static_cast<long long>(std::stoi(destination.substr(1, 1)));
	// begCol stores the column index for where the start of the move occurs in the board
	int begCol = static_cast<long long>(origin[0]) - 65;
	// endCol stores the column index for where the end of the move occurs in the board
	int endCol = static_cast<long long>(destination[0]) - 65;

	// pieceCount holds the amount of pieces there are in the row
	// assign zero to line since no pieces found yet
	int pieceCount = 0;

	// slope_X holds the direction for the row will go in the diagonal line (-1) up or (1) down
	long long slope_X = 0;
	// slope_Y holds the direction for the column will go in the diagonal line (-1) left or (1) right
	long long slope_Y = 0;
	
	// The line goes up and to the right 
	if ((begRow > endRow && begCol < endCol)) {
		// assign up to slope_X
		slope_X = -1;
		// assign right to slope_Y
		slope_Y = 1;
	}
	// The line goes down to the left
	else if ((begRow < endRow && begCol > endCol)) {
		// assign down to slope_X
		slope_X = 1;
		// assign left to slope_Y
		slope_Y = -1;
	}
	// The line goes down and to the right
	else if ((begRow < endRow && begCol < endCol) ) {
		// assign down to slope_X
		slope_X = 1;
		// assign right to slope_Y
		slope_Y = 1;
	}
	// The line goes up and to the left
	else if ((begRow > endRow && begCol > endCol)) {
		// assign up to slope_X
		slope_X = -1;
		// assign left to slope_Y
		slope_Y = -1;
	}

	// maxDistanceToEnd holds the max distance for iteration from beginning to end
	int maxDistanceToEnd = std::max(8 - begCol, 8 - endCol);
	// maxDistanceToStart holds the max distance for iteration from row to column
	int maxDistanceToStart = std::max(begRow + 1, begCol + 1);
	// maxDistance holds the max distance between the start and end distance
	int maxDistance = std::max(maxDistanceToEnd, maxDistanceToStart);
	
	// Iterate over the entire diagonal line
	for (int i = -maxDistance; i <= maxDistance; i++) {
		int row = begRow + (i * slope_Y);
		int col = begCol + (i * slope_X);
		// Ensure row and column are within the bounds of the board
		if (row >= 0 && row < 8 && col >= 0 && col < 8) {
			if (board[row][col].getColor() == 'W' || board[row][col].getColor() == 'B') {
				pieceCount += 1;
			}
		}
	}
	// dist holds the distance in board space between two coordinates
	// assign the difference between the beginning row and end row value to dist
	int dist = (abs(begRow - endRow));
	// Checks for blocking pieces
	for (int diagIter = 0; diagIter < dist; diagIter++) {
		// colorDiff holds the truth value for if the piece located on the column and row is a different color
		bool colorDiff = board[begRow + (slope_X * diagIter)][begCol + (slope_Y * diagIter)].getColor() != board[begRow][begCol].getColor();
		// emptyPos holds the truth value for if the column and row is empty space
		bool emptyPos = board[begRow + (slope_X * diagIter)][begCol + (slope_Y * diagIter)].getColor() != '.';
	
		if (colorDiff && emptyPos) {
			return false;
		}
	}
	// colorDiff holds the truth value for if the piece located on the final column and row is a different color
	bool colorDiff = board[endRow][endCol].getColor() != board[begRow][begCol].getColor();
	// distCmp holds the truth value for if the distance between the two columns and rows is the same as the total number of pieces in row
	bool distComp = (abs(begRow - endRow) == pieceCount) && (abs(begCol - endCol) == pieceCount);
	// Final check for if the spot we are landing on has the same color as the initial piece AND if it's the right amount of space
	
	if (colorDiff && distComp) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: move_piece
Purpose: Handles the movement of a piece on the board, taking into account
         captures as well
Parameters: origin, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			destination, a string passed by value. Used for obtaining
			the user's end coordinates for of a piece's move on the board

Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Board::move_piece(std::string origin, std::string destination) {

	int begCol = static_cast<int>(origin[0]) - 65;
	int endCol = static_cast<int>(destination[0]) - 65;
	int begRow = 8 - std::stoi(origin.substr(1, 1));
	int endRow = 8 - std::stoi(destination.substr(1, 1));

	Piece selected = board[begRow][begCol];
	board[begRow][begCol] = Piece('.');
	board[endRow][endCol] = selected;
}

/* *********************************************************************
Function Name: getGroupPieces
Purpose: Stores all of the piece coordinates in a single group
Parameters: coordinates, a string passed by value. Used for obtaining
			the start of a piece's move on the board

			color, a char passed by value. Used for determining which color
			a piece should have to be grouped together

Return Value: a vector of strings, storing each piece coordinate in a group
Algorithm: none
Reference: none
********************************************************************* */
std::vector<std::string> Board::getGroupPieces(std::string coordinates, char color) {

	std::array<std::array<bool, 8>, 8> visited = {};
	std::vector<std::string> pieces;

	int row = 8 - std::stoi(coordinates.substr(1, 1));
	int col = static_cast<int>(coordinates[0]) - 65;
	
	int count = isGrouped(row, col, color, visited, pieces);

	return pieces;

}

/* *********************************************************************
Function Name: isGrouped
Purpose: Keeps count of how many pieces of the same color are inside a 
         single group
Parameters: row, an integer passed by value. Used for determining what 
			row to look at for checking if a piece is in the group

			col, an passed by value. Used for determining which column
			to look at for checking if a piece is in thegroup

			color, a char passed by value. Used for determining which color
			a piece should have to be grouped together

			visited, a 2D 8x8 array of booleans passed by reference, containing
			the truth values for if a piece on the board has been visited by the group.
			Modifies the truth values inside the elements of the array

			pieces, a vector of strings passed by reference, containing the coordinates
			of each element in a group, reference modifies the string values for elements
Return Value: the amount of pieces in a group, an integer value
Algorithm:
			1) Check if current row and column coordinates are out of bounds
			2) If true, return zero
			3) Check if the given row and column coordinates have been visited already
			4) If true, return zero
			5) Check if the piece current row and column coordinates' color 
			   is equal to the given color
			6) If not equal, return zero
			7) If all conditions are true, the given coordinates in the visited
			   2D array are true now
			8) Store the coordinates in the pieces vector
			9) Count is equal to 1
			9) Count becomes the sum of count and the isGrouped function in 
			   all eight possible directions
Reference: none
********************************************************************* */
int Board::isGrouped(int row, int col, char color, std::array<std::array<bool, 8>, 8> & visited, std::vector<std::string>& pieces) {
	// Check if the current position is within the board boundaries
	if (row < 0 || row >= 8 || col < 0 || col >= 8) {
		return 0;
	}

	// Check if the current position has already been visited
	if (visited[row][col]) {
		return 0;
	}

	// Check if the piece at the current position has the same color
	if (board[row][col].getColor() != color) {
		return 0;
	}

	// Mark the current position as visited
	visited[row][col] = true;
	// coords converts the row and column parameters into properly formatted coordinates
	// assign ascii value of column + row as string to coords
	std::string coords = std::string(1, static_cast<char>(col + 65)) + std::to_string(row + 1);
	pieces.push_back(coords);

	// count holds the total amount of pieces in a group, assign 1 to variable
	int count = 1;
	// assign down direction for isGrouped to count
	count += isGrouped(row + 1, col, color, visited, pieces); 
	// assign up direction for isGrouped to count
	count += isGrouped(row - 1, col, color, visited, pieces); 
	// assign right direction for isGrouped to count
	count += isGrouped(row, col + 1, color, visited, pieces);
	// assign left direction for isGrouped to count
	count += isGrouped(row, col - 1, color, visited, pieces);
	// assign diagonal down right for isGrouped to count
	count += isGrouped(row + 1, col + 1, color, visited, pieces); 
	// assign diagonal up right for isGrouped to count
	count += isGrouped(row - 1, col + 1, color, visited, pieces); 
	// assign diagonal down left for isGrouped to count
	count += isGrouped(row + 1, col - 1, color, visited, pieces);
	// assign diagonal up left for isGrouped to count
	count += isGrouped(row - 1, col - 1, color, visited, pieces);

	return count;

}

/* *********************************************************************
Function Name: winCondition
Purpose: Handles if a diagonal move given the two coordinates is possible,
		 checks for blocking pieces and if move distance was valid
Parameters: color, a char passed by value. Used for determining which color
			a piece should have to be grouped together

			coordinates, a string passed by value. Used for obtaining
			the start of a piece's move on the board
			
			pieceCount, an integer passed by value. Used for obtaining the total
			number of pieces associated with a player
Return Value: The truth value for whether or not the group that was found has 
              the same integer value as the total amount of pieces for a player
			  on the board
Algorithm: none
Reference: none
********************************************************************* */
bool Board::winCondition(char color, std::string coordinates, int pieceCount) {
	std::array<std::array<bool, 8>, 8> visited = {};
	int col = static_cast<int>(coordinates[0]) - 65;
	int row = 8 - std::stoi(coordinates.substr(1, 1));
		
	std::vector<std::string> pieces;
	int groupSize = isGrouped(row, col, color, visited, pieces);
	bool oneGroup = groupSize == pieceCount;

	// If only one group of pieces of the specified color is found, return true
	if (oneGroup) {
		return true;
	}
	else {
		return false;
	}
	
}

/* *********************************************************************
Function Name: getBoard
Purpose: To obtain all of the piece's information in a board
Parameters: none
Return Value: an 8x8 2D array of Piece objects
Algorithm: none
Reference: none
********************************************************************* */
std::array<std::array<Piece, 8>, 8> Board::getBoard() {
	return board;
}

/* *********************************************************************
Function Name: setRoundWon
Purpose: To assign a truth value to the roundWon private member boolean
Parameters:
			board, an 8x8 2D array passed by value. It holds the 
			list of pieces to call information from
Return Value: none
Algorithm: none
Reference: none
********************************************************************* */
void Board::setBoard(std::array<std::array<Piece, 8>, 8> board) {
	this->board = board;
}
