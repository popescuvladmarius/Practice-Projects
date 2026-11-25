#ChessOnConsole

Chess game on console that expects two players, built as a passion project to experiment with C++.
It is heavily experimental and will see a lot of additions and changes.
The project is under development.

##Structure

The current game structure involves interactions between the following classes:

GameManager
    |------Board              
    |------Controller
    |------PieceManager
                |------Team
                        |------Pawn : Piece
                               Knight : Piece
                               Rook : Piece        
                               Bishop : Piece        
                               Queen : Piece        
                               King : Piece
    |------Gamestate
    |------RuleManager

GameManager: owns all objects and directs the main loop of the game;
Board: offers a graphical representation of the board and pieces, along file and rank coordinates for input. The pieces are represented by initials, uppercase for whites and lowercase for blacks;
Controller: Reads input from player and validates it, converts it from file and rank notation to array coordinates;
Piece: abstract base class from which all pieces derive from. Implements the basic piece functionality that each piece employs and a few pure virtual functions;
Derived Pieces: each one implements its own movement rules and provides overrides for the inherited virtual functions;
Team: a class that owns all derived pieces of one team. It ensures a clear separation of pieces between two teams;
PieceManager: owns both Team objects, initializes all pieces and provides an interface to access them and their combined functionality;
Gamestate: manages the state of the game, a record of all moves performed during the game, as well as a subdivision of the turn into stages. Holds a pointer to the currently selected piece and a collection of the checking pieces;
RuleManager: currently it manages the castling logic for the king. It was built to handle the check and checkmate logic and the check state of the kings as well as all special moves like castling and promotion, but that task was divided into different responsabilities and distributed to different objects, like the kings themselves, PieceManager and GameManager. It resulted in being easier to implement this way and offered more granularity. It will be probably integrated into Gamestate with a different name as it is too specific to act as a standalone actor.

The game uses polymorphism to supply a common interface for each piece and provide easy access to each one by addressing a pointer to the base class.

##Game loop

At the start of the turn, the game allows the player to perform an indefinite number of inputs, by allowing to continuously select between pieces and different moves until a valid move has been performed, which then triggers a switch of the turn. 
This is done by dividing a loop iteration into three stages: denoted initial, pieceSelected and moveSelected; which occur in the specified order. As the input runs unbothered by any constraints, the game interprets it according to the current stage.
If we are in stage initial and the input falls upon a piece in the current team, the loop status is set to pieceSelected. If it then lands on a valid move position it performs the move and sets the state to moveSelected, which signals the end of the loop iteration and the turn is toggled. The validity of the input is checked according to the current stage, and if it fails the stage simply remains unchanged, making the condition in the loop evaluate as true and let the player reselect another input until it evaluates as false.

##How moves work

Eeach piece is responsible for the implementation of its own move rules and move validity, which accounts for collisions with team pieces and captures of enemy pieces.
Each piece stores a position and an end position. The position is the current position of the piece and the end position takes the input of the controller. If the piece selected has a point type of move (like knights and pawns), this end position is compared with pseudo positions returned by functions that calculate the position of one base move performed by the piece from the current position, and if they match, the move selected respects the piece's move rules and is further checked for collisions and captures (e.g. for a king a forward() function calculates the position it would assume if it moved forward, the end pos is checked against that position and if they match, the end position given by input did represent a forward move). If the piece selected covers a range (like rooks and bishops) a function that sweeps the range of squares between the current position and the selected position is used to check for collisions and captures. If the move passes all checks, it is validated and finally the position is updated with the value of the end position and written to board.

##Board representation and coordinates

The game has two boards, a graphical one managed by the Board class, and a logical one managed by PieceManager. The Board class just prints to console the board and piece's graphical representation. It implements no logic as it is merely a mirror of the logical one.
The logic board inside PieceManager, also called masterArray, holds pointers to all pieces in the board, from both teams, and is the main access point to each piece. 
The game employs a global coordinate system defined by the masterArray's coordinates (or indices) and uses a function that outputs -1 or 1 (depending on the team the piece belongs to) to calculate up and down (x coordinates) positions in a generalised way regardless of the direction the piece must follow.   

##Check handling

After a valid move has been performed, a scanning operation that searches if the enemy king is under check is fired. The scanning operation is fired for all pieces inside the current team, and silently sets the check flag of the enemy king during the current turn, if threatened by any piece. This process triggers all possible moves for each piece in the team and if one corresponds to the position of the enemy king, and the path is clear for range pieces, the check is signaled. 
At the start of each turn the current team's king is verified if under check, and if yes the checkmate evaluation is invoked. If it evaluates an escape for the king, the game loop is focused in enforcing moves that only make the king escape check. If the checkmate evaluation calculates no chances for the king, checkmate is signaled and the game is ended.
During the scanning operation, range pieces like rooks and bishops can lock enemy pieces in place for the next turn, if those stand between them and the king. This is done to prevent them from being moved next turn and expose the king to check.
If the selected piece for a move is a king, each move it performs is verified if it puts the king in danger, and undone if that move would trigger a check. In this situation a global scanning operation is performed instead of a local (team) one normally fired for any other piece. This one triggers all possible moves for all pieces in both teams, to cover both the situation in which the selected king might step in danger, and the situation in which a move of the current king might expose the enemy king to check.
The scanning operation works by signals that are thrown at each turn, it doesn't cache any positions.

##Checkmate evaluation

The purpose of this process is to find at least one move that lifts the check. The evaluation first takes into account the action type of the checking pieces, which is either point or range. For point ones it checks if there are available safe positions for the king or any other piece in the team can capture the checking one. For ranged checking pieces, it additionally checks if any other piece can block its range.
These verifications are done by firing all possible moves of each piece in the team and find at least one move that either captures the threatening piece or blocks its range, and for the king a move that puts it to safety. These checks will be optimized by supplying each piece wuth the position of the checking ones and fire only moves that are relevant, like firing only that one that stands in the direction of the checking piece or not firing anything if it is too far away.


##Future additions 

The game will be converted to a window application with 3D rendered pieces and table and a proper user interface. A save system will be built to save the current state of the match (or multiple matches with different slots);
It will be ported to online matchmaking;
The long term goal is to build a solver chess engine as AI player. It will be built as a separate component.
As ideas come, they will be written here. The project is open and anyone can contribute.

##Improvements

Reduce to a bare minimum the number of dynamic casts. 
If a broader role cannot be defined for the RuleManager class, it will be refactored inside Gamestate if further functionality cannot be added to it, as the class is currently very specifc and fits better as a component rather than a standalone actor.
Experiment with a dispatch communication class as a form of bilateral communication between certain classes that cannot talk directly like a piece and RuleManager.

