#include "Game1Model.h"
#include <iostream>
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

Game1Model::Game1Model() : board(), currentPlayerIndex(0) {
	turnInitialized = false;

	int nb; std::string name;
	std::cout << "Saisir le nombre des joueurs : ";
	std::cin >> nb;
	for (int i = 0; i < nb; i++) {
		std::cout << "Saisir le nom du joueur " << i+1 << ": ";
		std::cin >> name;
		players.emplace_back(i, name);
	}
	restart();
}

const std::vector<int>& Game1Model::getValidMoves() const { return validPotentialMove; }

bool Game1Model::isTurnInitialized() const { return turnInitialized; }

bool Game1Model::isRemovalPhase() const { return removalPhase; }

bool Game1Model::isSelected() const { return selected; }

const Board1Model & Game1Model::getBoardModel() const { return board; }

const std::vector<Game1Player>& Game1Model::getPlayers() const { return players; }

const std::array<Piece1Model, 64>& Game1Model::allPieces() const { return pieces; }

const Game1Player & Game1Model::getCurrentPlayer() const { return players[currentPlayerIndex]; }

Game1Player & Game1Model::getCurrentPlayer() { return players[currentPlayerIndex]; }

void Game1Model::setTurnInit(bool turn) { turnInitialized = turn; }

void Game1Model::nextTurn() { currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); }

void Game1Model::restart() {
	// Reset game state
	selected = false;
	removalPhase = true;
	selectedPiece = nullptr;

	// Create a vector with the correct number of each color
	std::vector<char> colors;
	colors.reserve(64); // Reserve space for 64 elements
	colors.insert(colors.end(), 34, 'J');
	colors.insert(colors.end(), 20, 'R');
	colors.insert(colors.end(), 10, 'N');

	// Shuffle the colors vector
	unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(colors.begin(), colors.end(), std::default_random_engine(seed));

	// Assign the shuffled colors to the pieces, keeping their positions
	for (int i = 0; i < 64; ++i)  pieces[i].setPiece(colors[i], i);
}

void Game1Model::selectPiece(int pos) {
	selectedPiece = findPieceAtPosition(pos);
	if (selectedPiece && selectedPiece->getColor() == 'J' && pos != -1) {
		if (removalPhase) {
			if (getCurrentPlayer().getId() == players.size() - 1)
				removalPhase = false;
			selectedPiece->setPosition(-1);
			nextTurn();
			return;
		}
		selected = true;

		validPotentialMove.clear();
		validCaptures(selectedPiece);
	}
}

void Game1Model::moveSelected(int pos) {
	bool validMove{ false };
	// Check pos with the Piece's possibleMoves
	for (int validPosition : validPotentialMove) {
		if (pos == validPosition) {
			validMove = true;
			break;
		}
	}
	if (validMove) {
		capturing(pos);
		selectedPiece->setPosition(pos); // Moving the piece
		turnInitialized = false;

		nextTurn();
	}
	selected = false;
}

void Game1Model::capturing(int endPosition) {
	// Find the capture sequence that ends at the specified position
    std::vector<std::vector<int>> captureSequences = validCaptures(selectedPiece);
    
	std::vector<int> capturePath;
	for (const std::vector<int>& sequence : captureSequences) {
		if (std::find(sequence.begin(), sequence.end(), endPosition) != sequence.end()) {
			capturePath = sequence;
			break; // Break after finding the first sequence that contains the endPosition
		}
	}

    int currentPos = selectedPiece->getPosition();
	for (int nextPos : capturePath) {
		// Calculate the jumped position (midpoint between currentPos and nextPos)
		int midPos = (currentPos + nextPos) / 2;
		Piece1Model* pieceAtPos = findPieceAtPosition(midPos);
		if (pieceAtPos) {
			// This piece is captured, remove it from the board
			pieceAtPos->setPosition(-1); // Set the position to an invalid state to indicate capture
			getCurrentPlayer().setScore(pieceAtPos->getValue());
		}
		currentPos = nextPos; // Update the current position for the next segment of the path
		// Stop capturing if the endPosition is reached
		if (currentPos == endPosition) break;
	}
}

std::vector<std::vector<int>> Game1Model::validCaptures(const Piece1Model * piece) {
	std::vector<std::vector<int>> allSequences;
	std::vector<int> currentSequence;
	capturablePieces.clear(); // Clear previous captured pieces
	exploreCaptures(piece, piece->getPosition(), currentSequence, allSequences);

	for (const auto& sequence : allSequences){
		for (const auto& elm : sequence) {
			if(std::find(validPotentialMove.begin(), validPotentialMove.end(), elm) == validPotentialMove.end())
				validPotentialMove.push_back(elm);
		}
	}
	return allSequences;
}

void Game1Model::exploreCaptures(const Piece1Model* piece, int currentPosition, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allSequences) {
	bool captureMade = false;
	// Directions for horizontal, vertical, and diagonal moves on an 8x8 board
	int moveDirections[] = { -9, -8, -7, -1, 1, 7, 8, 9 };

	for (int dir : moveDirections) {
		int jumpedPos = currentPosition + dir;
		int capturePos = currentPosition + 2 * dir;

		if (isValidMove(currentPosition, capturePos)) {
			const Piece1Model* jumpedPiece = findPieceAtPosition(jumpedPos);

			// Check if the landing position is empty and the jumped piece has not been captured before
			if (jumpedPiece && findPieceAtPosition(capturePos) == nullptr &&
				std::find(capturablePieces.begin(), capturablePieces.end(), jumpedPiece) == capturablePieces.end()) {

				capturablePieces.push_back(jumpedPiece); // Mark this piece as captured
				currentSequence.push_back(capturePos); // Add the landing position to the current sequence
				exploreCaptures(piece, capturePos, currentSequence, allSequences);
				currentSequence.pop_back(); // Backtrack
				capturablePieces.pop_back(); // Unmark this piece as captured
				captureMade = true;
			}
		}
	}

	if (!captureMade && !currentSequence.empty()) {
		allSequences.push_back(currentSequence); // Adding the complete sequence to all sequences
	}
}

Piece1Model* Game1Model::findPieceAtPosition(int position) {
	for (Piece1Model& p : pieces)
		if (p.getPosition() == position) return &p;
	return nullptr;
}

bool Game1Model::isValidMove(int fromPos, int toPos) {
	int fromRow = fromPos / 8;
	int fromCol = fromPos % 8;
	int toRow = toPos / 8;
	int toCol = toPos % 8;
	// Check bounds for the toPosition
	if (toPos < 0 || toPos >= 64) return false;
	// Check that the move is exactly two spaces away in any direction
	int rowDiff = abs(fromRow - toRow);
	int colDiff = abs(fromCol - toCol);
	return (rowDiff == 2 && colDiff == 0) || // Horizontal move
		(rowDiff == 0 && colDiff == 2) ||    // Vertical move
		(rowDiff == 2 && colDiff == 2);		 // Diagonal move
}