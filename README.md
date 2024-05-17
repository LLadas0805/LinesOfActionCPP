Luke Ladas - C++ Lines of Action Manual
Bug Report:
- If there is white space after “Next Player: Human” or “Next Player: Computer” in a serialization text save file. The parsing that occurs in the Serialization.loadGame() function will not be able to parse the next player’s information. To fix this, make sure this line has no white space after the text.
- Serialization.loadGame() does not check if a file is empty and it will not check to see if a file has the proper layout/format of a typical save. 
- Potential integer overflow that could occur with values such as score and round wins for a player depending on how long a tournament goes on for. Realistically, the chances of a Tournament ever reaching this state are next to impossible but it is important to know this hasn’t been dealt with. 
- These are the main bugs I am aware of, like many programs, there are probably many unforeseen bugs that I could not locate.
Missing Feature Report:
- Data is not saved redundantly, no potential fidelity problems in data storage
- Changes to data always validated
- Code for repeated execution separated from code for single execution (e.g.,for round)
- Each function in charge of only one logical task 
- Selectors are const
- All literal constants are explained at each occurrence
- Symbolic constants are used whenever possible

Additional Feature Report:
- Additional strategies such as winning, moving/gravitate towards same colored pieces
Data Structures:
- Arrays were used pretty extensively inside my project, two of the most vital members of any of the classes in my program were using this data structure. I created a two dimensional array as a way to store pieces inside the simulated board and also used an array to store the roster of players that are inside a tournament. Without arrays I could have used vectors but I saved that data structure for specific use cases mentioned later. Arrays are fixed sizes which means I do not have to worry about someone manipulating my board grid or the amount of players in a game.
- Vectors were also used quite often inside my project as a way to store lists with dynamic sizes. I used them to store possible strategies for my move helper function in Player, and also used them to store the names of text files in my project’s directory. 
Classes:
Basic:
- Piece is a class that represents a space on the game board. The main member of a piece is the color, which is mainly used by the Player related classes, letting them know which color piece on the board they can move around, block, or capture. The three values are typically ‘B’ which is for black pieces, ‘W’ which is for white pieces, and ‘.’ which actually represents an empty space on the board. Piece also contains three more members, one for getting the best strategy associated with a piece, second being the location of the piece on the board, and the third being the location that the strategy is associated with. These three members are used in Player as well for outputting possible moves in the strategy helper function. Piece is used inside the Board class and is used for a data type in a 2D array. Piece does not reference any classes.
Composite:
- Tournament is a class that is essentially used for storing the group of players that will be playing in a match and handles the creation of rounds. If a round ends, the tournament prompts a user to either create a new round or end the tournament. Without the Tournament class, there would be no “round loop”, the game would just be single rounds rather than complete tournaments. Tournament references Player, Round, Human, and Computer classes.
- Round handles the actual turn based gameplay that makes up lines of action. It decides which player can go first in a game, and at the end of every move the players will swap places. The Round class also checks for a win condition; if a player has won, a round is over and the round declares who has won. Round references Player, BoardView and Board classes. 
- Player is a class that is used for holding vital information for a player in a tournament. Contains classifiers such as a Player’s color, which directly aligns with what pieces they can control or capture. Players also have an identifier for letting certain classes know if a player is a computer or human. Finally the last members of the Player are the amount of pieces they have in a round, the score they have in a tournament as well as their total wins. Player holds the functions for a strategy helper, which recommends a player with a best case scenario move. Depending on the state of a round, the player will be suggested different strategies and ultimately try to get wins and increase their score. Player has a play() function but it is empty, meant to be overridden by its children. Player is a parent class who passes down its members and functions onto the Human and Computer class. Player is a Player references Piece and Board
- Board stores a code representation of the game board. Its main member and code representation of the board is a 2D array of Piece class objects. Board can call this array to select, move and capture pieces on the board. It also handles validation of moves and selected pieces from a player. Board also is responsible for finding out if a player has won by checking if pieces are in one single group. Board references Piece. 
- BoardView is a class whose sole purpose is to display a visual representation of the game board to the players. It is used inside the Round class during initiate_round() before and after a move is made. The BoardView class references the Piece class, since the main parameter for BoardView, display_board() has an 8x8 2D array of Pieces that it iterates through to output the game board accurately.
- Serialization is how the game handles saving and loading files. Saved files need a unique name to not accidentally overwrite an existing file, and also need a name with no special characters to prevent errors. Loaded files are obtained by a user’s input matching an existing file displayed in the program output. The program parses the text file going through each line to try and find keywords matching the format of the project description’s format. This information is sent back to the Round class so that the game board, and player information are properly loaded in. Serialization references Player, Piece and Board classes.
Derived:
- Human is a class that has its functions and members inherited from the Player. It overrides the Player’s play() function where it is asked for an input for a piece to move, and if that piece was valid, it asks for a location to move that piece to. If the move was valid, the piece on the board will move, but if not a valid move, the user is prompted to enter this info again. Human references Player as it is a child of that class. 
- Computer is a class that has its functions and members inherited from Player. It overrides the Player’s play() where it will call the strategize function and move their piece to the best possible move/strategy from the best piece.This moves the specified piece on the board to its best location. It technically references Player as it is a child of that class. 
Project Log:
Jan 30 2024:
- Defined Piece class, which contains private char member color. Used for holding
  the type of piece that will be placed on the board.
- Defined Piece's constructor which passes in a char color argument with default
  value of '.' if no value is passed in.
- Defined Piece.getColor(), a selector which returns the char value of the private variable,
  color inside a Piece class object.
  (5 min for the above 3 items).

- Defined Board class, which contains the private 2D Piece object array board.
  Used for storing and representing the state and pieces of the game board.
- Defined void function Board.initial_state(), used inside
- Defined default constructor for board class in which it calls the initial_state function
- Defined selector function Board.getBoard()
  (30 min for the above 4).

- Defined BoardView class, which is used for display a visual representation of the
  2D piece board array that is used during a round.
- Defined void function BoardView.display_board, which will be used inside the Round class in the future,
  design planning.
  (15 min for the above 2).

- Inside the main function in LinesOfAction.cpp, tested the Board's initial state
  and used BoardView to test the output for displaying the board.
- Alignment issues in BoardView output, not matching perfectly with the format that
  is on the website. Modified display_board function to match the example output.
  (10 min for the above 2).

Total: 1 hour

Feb 1 2024:
- Defined Player class, for holding player state information in a tournament.
- Research C++ documentation on how to create virtual functions and research the concept of dynamic polymorphism so that future classes such as a Human or Computer, can be built off of the Player.
- Defined Player constructor, virtual function Player.play() which is empty, and all of the selectors and mutators for the current private members, id, color, score, wins and pieces
- Defined Human class, which is a child of the Player class, it holds all the same private members and functions. Player.play() is overridden but defined later on. 
- Defined Computer class, which is a child of the Player class, it holds all the same private members and functions. Player.play() is overridden but not defined yet. 
  (30 min for the above 5)

- Defined Round class, I decided to do this first over tournament because without the rounds, we have no tournament. Defined Round.initiate_round() which needs further expansion. For now, this function creates and initializes/displays a new board.
- Defined Tournament class, its constructor/destructor, selector for Players[], both being humans for now, and Tournament.initiate_tournament(). Tournament contains player information and passes that information along to rounds.
- Human.play() gets expanded where it returns a string of user input rather than being empty
- At this point, Round.starting_player() is defined to determine who should start a round, as well as Round.swap() to swap between players between each turn. Player.play() is also added into the Round.initiate_round() for whoever the current player is, but all this does is print the input. I need to work more on the Board class to add proper board manipulation.
  (1 hour for the above 4).

- Define the Board.validate_range(), Board.validate_piece(), Board.validate_moveset, and Board.validate_horizontal/vertical/diagonal, and finally Board.move_piece. This allows for player input to be formatted into proper coordinates, allowing for moves to be made in a round.
- Expand the Round.initiate_round() to check for a valid_piece() relative to player input, and if that is valid, the player selects a destination and that will be verified with the Board.validate_moveset()
- At this point, I test my movement and round logic
(5 hours for the above 2).

Total: 6.5 hours 

Feb 3 2024:
- Expanded/ Debugged Round.initiate_round() as there was no proper way a game would end, if all the pieces on one player’s side was grouped together or were somehow all removed, the game would still go on but that opponent would have no moves. I created a check to see if the opponent’s piece count was == to zero to end the game. This is more of a temporary fix for now. Also added at the end of a round, it displays the winner.
- Expanded Tournament.initiate_tournament to display end of round info such as score for both players and how many wins they have. Also asks user to quit or keep playing if a round has ended. This is the main game loop somewhat complete for Human vs Human.
(30 minutes for the above two).

- Research c++ documentation for file writing in the standard template library
- Defined the Serialization class, a way to save game progress and load it into a match. For today, I will focus on saving a game and implement loading another day. Defined Serialization.saveGame()
(2.5 hours).

- Implement serialization object into Round.initiate_round() where every turn asks the player to either save or keep playing
- Tested round/tournament state being saved as a text file
(1 hour for the above two).

Total: 4 hours

Feb 5 2024:
- Research c++ documentation for file reading and parsing in the standard template library
- Defined the Serialization.loadGame() function, marking the completion of my serialization logic
- Modify the Round.initiate_round() and Tournament.initiate_tournament() to allow for a file to be read but also for that info to be parsed and stored in these classes
- Testing the load game functionality with save game files, there are no files available on the website at this time so I am manually making cases
- Debugging load game parsing as an issue with my parsing came up, specifically text wasn’t being placed in the right stream values. Another issue was Next player information being ignored because it would try to check the whole line being equal to “Next Player:” when in reality the text will be Next Player: Human or Computer.
(4.5 hours for the above 4)

Total: 4.5 hours

Feb 8 2024:
- Modified Computer class, defining the overridden play function from Player class.
  Temporarily gets random coordinates in the bounds of the game board to send back to
  player and returns the string value.
-  Modified the Tournament class to hold a Computer Player as the second element inside the Players array instead of having two humans. Initial implementation of Human vs Computer gameplay.
(30 minutes for above two)
- Testing possible inputs a player can make on the board for moves. Manual input by   myself as well as using the random input from the computer for faster testing times.
- Debugging for Board.validate_horizontal, Board.validate_vertical, and Board.validate_diagonal. Certain inputs would produce a subscript array out of range error. Certain inputs would produce the wrong piece counts. Depending on what move a player may want to take, the direction was being miscalculated and the loop to check for the amount of pieces in a line, or for checking for blocking pieces may go the opposite direction. 
(3.5 hours for above two)

Total: 4 hours

Feb 9 2024:
- Defined Board.isGrouped() and Board.winCondition(), design wise, this means my round can finally have a proper winning state. Board.isGrouped() is used to return a truth value where pieces of the same color are chained together. It also modifies an integer as a parameter to store the count, this was a flawed design choice and will be changed later.
 (1 hour)
- Modified the win/break loop condition inside of the Round.intiate_round() class. Initially, we had a check to see if the opponent's piece count was equal to zero. We now want to check if the opponent’s pieces count was >= zero as technically one piece remaining would be a win as it is a single group of all the pieces remaining. We also want to add an OR condition to this win condition alongside the piece count check which calls Board.winCondition() and checks if it is true. 
- Researching lines of action wikipedia to find out common movements and strategies to win to allow for easy tests
 (30 minutes)
- Testing win condition by playing multiple tournaments
  (1 hour)

Total: 2.5 hours

Feb 13 2024:
- Begin designing player strategies, start thinking about logic by watching lines of action youtube videos and looking at the wikipedia page once again. How will I translate these strategies into the helper function for the Computer and Human?
(1 hour)
- Defining Player.strategize() which will be the helper function to suggest the best piece and their action to perform in a turn. I also need to define a Player.pieceStrategy() function which picks the best move a piece of the current player can take. I started defining and ranking some but not all strategy functions
- Define Player.canWin(), Player.canCapture(), Player.canBlock() and Player.canMove()
- Testing the current strategies 
(5 hours for above two)
Total: 6 hours

Feb 15 2024:
- Define Player.canThwart(), Player.canDelay(), Player.canGroup(), imminentWin(), and other strategies to complete the hierarchy/priority of strategies
- Debugging build errors such as memory overflow, fixed by not storing so many vectors and arrays as local variables
Total: 4 hours

Feb 17 2024:
- Remove the logic for move validation and movement logic in the Round.initiate_round() function
- Modify the Human.play() function to contain all of the board validation and movement logic that was originally in Round
- Add logic to Human.play() to call the strategize function if HELP was input by the user
- Modify the Computer.play() function to return the best piece on the board based on the move and strategy when calling strategize
- Testing all features of my program now in preparation for demonstration

Total: 3 hours

Feb 18 2024:
- Once again, testing features such as strategy, user inputs and overall game logic before demonstration. 

Total: 1 hour
Feb 19 2024:
- Tested all serialization file examples now that they are available on the website
(1.5 hours)

- Debugging Serialization.loadGame(), player information not stored properly in case 4 of the serialization examples. The reason I found out after a while was there was extra white space in that file making the comparison for Next Player: never equal
(1 hour)

Total: 2.5 hours

Feb 21 2024:
- Modified the Player.canThwart() strategy to make it more accurate to the game design in real life. Initially I thought thwart was a last ditch effort to block any opponent’s movement in a single direction in hopes that it would block the winning move for them. After the demonstration I changed it so that the condition for thwart was based on if any of the current player’s pieces can land on the opponent’s winning position, as a means of interception. 
- Modified helper function strategy explanation to make it clear what types of moves are being suggested

Total: 1 hour

How to Run Program:
Running the main function inside the LinesOfAction.cpp file in my directory will cause the game to start, asking the player to either load a session or create a new tournament. The main function in LinesOfAction.cpp is calling a Tournament class object’s initiate_tournament() function which sets up the game.
