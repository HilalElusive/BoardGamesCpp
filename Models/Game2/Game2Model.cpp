#include "Game2Model.h"
#include <iostream>

Game2Model::Game2Model() : board(), player1(1, "Player One"), player2(2, "Player Two") {
	turnInitialized = false;
	restart();
}

const std::vector<int>& Game2Model::getValidMoves() const { return validPotentialMove; }

const Board2Model & Game2Model::getBoardModel() const { return board; }

bool Game2Model::isTurnInitialized() const { return turnInitialized; }

bool Game2Model::isSelected() const { return selected; }

void Game2Model::setTurnInit(bool turn) { turnInitialized = turn; }

void Game2Model::restart() {
	// Reset game state
	selected = false;
	playerTurn = true; // Setting the first player as the one who starts the game
	selectedPiece = nullptr;

	player1.initializePieces(true); // true so that player1 get white colored pieces
	player2.initializePieces(false);  // false so that player2 get black colored pieces
}

void Game2Model::selectPiece(int pos) {
	Game2Player& currentPlayer = (playerTurn ? player1 : player2);
	selectedPiece = currentPlayer.findPieceAtPosition(pos);
	bool isCapturingPiece = std::find(capturingPieces.begin(), capturingPieces.end(), selectedPiece) != capturingPieces.end();

	if (selectedPiece != nullptr) {
		if (isCapturingPiece || capturingPieces.empty()) {
			selected = true;
			std::cout << "selected piece at : " << pos << std::endl;
			validPotentialMove = validPossibleMoves();
		}
	}
}

void Game2Model::moveSelected(int pos) {
	bool validMove{ false };
	// Check pos with the Piece's possibleMoves
	for (int validPosition : validPotentialMove) {
		if (pos == validPosition) {
			validMove = true;
			break;
		}
	}
	if (validMove) {
		if (!capturingPieces.empty()) capturing(pos);
		selectedPiece->setPosition(pos); // Moving the piece
		// If a pawn piece has been moved, check for possible promotion
		if (selectedPiece->getType() == 'P') pawnPromotion(selectedPiece);
		turnInitialized = false;

		playerTurn = !playerTurn;
		capturingPieces.clear();
	}
	selected = false;
}

void Game2Model::capturing(int endPosition) {
	// Find the capture sequence that ends at the specified position
	std::vector<std::vector<int>> captureSequences;
	if (selectedPiece->getType() == 'P') captureSequences = validPawnCaptures(selectedPiece).first;
	else if (selectedPiece->getType() == 'Q') captureSequences = validQueenCaptures(selectedPiece).first;
	
	std::vector<int> capturePath;
	for (const std::vector<int>& sequence : captureSequences) {
		if (sequence.back() == endPosition) {
			capturePath = sequence;
			break;
		}
	}
	int currentPos = selectedPiece->getPosition();
	for (int nextPos : capturePath) {
		// Calculate the direction of the move
		int rowDiff = (nextPos / 10) - (currentPos / 10);
		int colDiff = (nextPos % 10) - (currentPos % 10);
		int direction = (rowDiff > 0 ? 10 : -10) + (colDiff > 0 ? 1 : -1);
		// Step through the squares in the direction until the next position in the path
		for (int pos = currentPos + direction; pos != nextPos; pos += direction) {
			Piece2Model* pieceAtPos = findPieceAtPosition(pos);
			if (pieceAtPos && pieceAtPos->getPlayer() != selectedPiece->getPlayer()) {
				// This piece is captured
				pieceAtPos->setPosition(-1);
				break; // A queen captures only one piece per jump
			}
		}
		currentPos = nextPos; // Update the current position for the next segment of the path
	}
}

void Game2Model::validPieceMoves(std::vector<int>& moves) {
	std::vector<std::vector<int>::iterator> toRemove;
	for (auto it = moves.begin(); it != moves.end(); ++it) {
		int currentPos = selectedPiece->getPosition();
		// Calculate the direction of the move
		int rowDiff = (*it / 10) - (currentPos / 10);
		int colDiff = (*it % 10) - (currentPos % 10);
		int direction = (rowDiff > 0 ? 10 : -10) + (colDiff > 0 ? 1 : -1);
		for (int pos = currentPos + direction; pos != *it + direction; pos += direction) {
			const Piece2Model* pieceAtPos = findPieceAtPosition(pos);
			if (pieceAtPos) {
				if (pieceAtPos->getPosition() == selectedPiece->getPosition()) continue;
				toRemove.push_back(it);
				break; // Break out of the loop as we found an obstacle
			}
		}
	}
	for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) { moves.erase(*it); }
}

std::vector<int> Game2Model::validPossibleMoves() {
	validPotentialMove.clear();

	if (selectedPiece->getType() == 'P') {
		for (const auto& sequence : validPawnCaptures(selectedPiece).first){
			if (!isPositionInSequence(sequence.back(), validPotentialMove))
				validPotentialMove.push_back(sequence.back());
		}
		if (!validPotentialMove.empty()) return validPotentialMove; // Only allow captures if available
	}
	if (selectedPiece->getType() == 'Q') {
		for (const auto& sequence : validQueenCaptures(selectedPiece).first){
			if (!isPositionInSequence(sequence.back(), validPotentialMove))
				validPotentialMove.push_back(sequence.back());
		}
		if (!validPotentialMove.empty()) return validPotentialMove; // Only allow captures if available
	}
	const std::vector<int>& possibleMoves = selectedPiece->getPossibleMoves();
	std::vector<int> validMoves = possibleMoves; // Make a local copy for modifications

	// Validating the piece's movement if it isn't a capturing situation
	validPieceMoves(validMoves);
	
	validPotentialMove = validMoves;
	return validPotentialMove;
}

std::pair<std::vector<std::vector<int>>, int> Game2Model::validPawnCaptures(const Piece2Model * piece) {
	std::vector<std::vector<int>> allLongestSequences;
	std::vector<int> currentSequence;
	explorePawnCaptures(piece, piece->getPosition(), currentSequence, allLongestSequences);

	int maxCapturablePieces = allLongestSequences.empty() ? 0 : static_cast<int>(allLongestSequences[0].size());
	return std::make_pair(allLongestSequences, maxCapturablePieces);
}

void Game2Model::explorePawnCaptures(const Piece2Model* piece, int currentPosition, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences) {
	bool captureMade = false;
	bool player = piece->getPlayer();
	int captureDirections[] = { -11, -9, 9, 11 };

	for (int dir : captureDirections) {
		int jumpedPos = currentPosition + dir;
		int capturePos = currentPosition + 2 * dir;

		if (isValidDiagonalMove(currentPosition, capturePos) && !isPositionInSequence(capturePos, currentSequence)) {
			const Piece2Model* jumpedPiece = findPieceAtPosition(jumpedPos);

			if (jumpedPiece && jumpedPiece->getPlayer() != player && findPieceAtPosition(capturePos) == nullptr) {
				currentSequence.push_back(capturePos);
				explorePawnCaptures(piece, capturePos, currentSequence, allLongestSequences);
				currentSequence.pop_back(); // Backtrack
				captureMade = true;
			}
		}
	}

	if (!captureMade) updateLongestSequences(currentSequence, allLongestSequences);
}

std::pair<std::vector<std::vector<int>>, int> Game2Model::validQueenCaptures(const Piece2Model* piece) {
	std::vector<std::vector<int>> allLongestSequences;
	std::vector<int> currentSequence;
	std::set<int> capturedPositions; // To keep track of captured pieces in a sequence
	exploreQueenCaptures(piece, piece->getPosition(), currentSequence, allLongestSequences, capturedPositions);

	int maxCapturablePieces = allLongestSequences.empty() ? 0 : static_cast<int>(allLongestSequences[0].size());
	return std::make_pair(allLongestSequences, maxCapturablePieces);
}

void Game2Model::exploreQueenCaptures(const Piece2Model* piece, int currentPosition, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences, std::set<int>& capturedPositions) {
	bool captureMade = false;
	bool player = piece->getPlayer();
	int captureDirections[] = { -11, -9, 9, 11 };

	for (int dir : captureDirections) {
		int nextPos = currentPosition + dir;
		bool continueSearch = true;

		// Move along the direction to find the first opponent piece
		while (continueSearch && isValidDiagonalMove(currentPosition, nextPos)) {
			if (const Piece2Model* nextPiece = findPieceAtPosition(nextPos)) {
				if (nextPiece->getPlayer() != player && capturedPositions.find(nextPos) == capturedPositions.end()) {
					// Check for valid landing positions after capturing this piece
					int landPos = nextPos + dir;
					while (isValidDiagonalMove(nextPos, landPos) && findPieceAtPosition(landPos) == nullptr) {
						currentSequence.push_back(landPos); // Add landing position to the sequence
						capturedPositions.insert(nextPos); // Mark this piece as captured

						exploreQueenCaptures(piece, landPos, currentSequence, allLongestSequences, capturedPositions);

						capturedPositions.erase(nextPos); // Unmark this piece, backtrack
						currentSequence.pop_back(); // Remove landing position, backtrack
						landPos += dir; // Move to the next landing position
						captureMade = true;
					}
				}
				continueSearch = false; // Found an opponent's piece, so stop looking in this direction
			}
			nextPos += dir; // Move to the next square in the direction
		}
	}

	if (!captureMade && !currentSequence.empty()) updateLongestSequences(currentSequence, allLongestSequences);
}

void Game2Model::updateLongestSequences(const std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences) {
	if (currentSequence.size() > (allLongestSequences.empty() ? 0 : allLongestSequences[0].size())) {
		// Found a longer sequence, so clear the previous sequences and add this one
		allLongestSequences.clear();
		allLongestSequences.push_back(currentSequence);
	}
	else if (!currentSequence.empty() && currentSequence.size() == allLongestSequences[0].size()) {
		// Found a sequence of equal length, so add it to the list
		allLongestSequences.push_back(currentSequence);
	}
}

bool Game2Model::isPositionInSequence(int position, const std::vector<int>& sequence) {
	return std::find(sequence.begin(), sequence.end(), position) != sequence.end();
}

bool Game2Model::isValidDiagonalMove(int fromPos, int toPos) {
	int fromRow = fromPos / 10;
	int fromCol = fromPos % 10;
	int toRow = toPos / 10;
	int toCol = toPos % 10;

	return (toPos >= 0 && toPos < 100) && abs(fromRow - toRow) == abs(fromCol - toCol);
}

std::vector<const Piece2Model*> Game2Model::allPieces() const {
	std::vector<const Piece2Model*> combinedPieces;

	// Add pieces from player1
	for (const Piece2Model& piece : player1.getPieces()) {
		if (piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}
	// Add pieces from player2
	for (const Piece2Model& piece : player2.getPieces()) {
		if (piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}

	return combinedPieces;
}

Piece2Model* Game2Model::findPieceAtPosition(int position) {
	if (player1.findPieceAtPosition(position) != nullptr) return player1.findPieceAtPosition(position);
	if (player2.findPieceAtPosition(position) != nullptr) return player2.findPieceAtPosition(position);
	return nullptr; // Return nullptr if no piece is found at the position
}

void Game2Model::pawnPromotion(Piece2Model * pawn) {
	if (pawn->getPlayer() && pawn->getPosition() < 10) {
		pawn->setType('Q');
	}
	else {
		if (!pawn->getPlayer() && pawn->getPosition() > 89)
			pawn->setType('Q');
	}
}

void Game2Model::findCapturingScenarios() {
	Game2Player& currentPlayer = (playerTurn ? player1 : player2);
	const std::array<Piece2Model, 20>& playerPieces = currentPlayer.getPieces();

	int pieceCaptures = 0, maxCaptures = 0;
	std::vector<const Piece2Model*> piecesWithMaxCaptures;

	for (const Piece2Model& piece : playerPieces) {
		if (piece.getPosition() != -1) {
			if (piece.getType() == 'P')
				pieceCaptures = validPawnCaptures(&piece).second;
			else if (piece.getType() == 'Q')
				pieceCaptures = validQueenCaptures(&piece).second;

			if (pieceCaptures > maxCaptures) {
				maxCaptures = pieceCaptures;
				piecesWithMaxCaptures.clear();
				piecesWithMaxCaptures.push_back(&piece);
			}
			else if (pieceCaptures == maxCaptures && maxCaptures != 0) {
				piecesWithMaxCaptures.push_back(&piece);
			}
		}
	}
	capturingPieces.clear();
	for (const Piece2Model* maxCapturePiece : piecesWithMaxCaptures)
		capturingPieces.push_back(maxCapturePiece);

	if (!capturingPieces.empty()) {
		std::cout << "  +++++++++++++++++++++++++++++++++++++" << std::endl;
		for (auto i : capturingPieces) {
			std::cout << "||\tcapturing piece at : " << i->getPosition() << i->getType() << "\t||" << std::endl;
		}
		std::cout << "  +++++++++++++++++++++++++++++++++++++\n" << std::endl;
	}
}