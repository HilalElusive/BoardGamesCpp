#include "Game3Model.h"

Game3Model::Game3Model() : board(), player1(1, "white", true), player2(2, "black", false) {
	turnInitialized = false;
	restart();

}

bool Game3Model::isSelected() { return selected; }

const BoardModel & Game3Model::getBoardModel() const { return board; }

void Game3Model::restart() {
	// Reset game state
	selected = false;
	playerTurn = player1.hasTurn(); // Setting the first player as the one who starts the game
	selectedPiece = nullptr;
	capturingPieces.clear();
	capturablePieces.clear();

	player1.initializePieces(true); // true so that player1 get white colored pieces
	player2.initializePieces(false);  // false so that player2 get black colored pieces
}

void Game3Model::selectPiece(int pos) {
	Player& currentPlayer = (playerTurn ? player1 : player2);
	selectedPiece = currentPlayer.findPieceAtPosition(pos);
	bool isCapturingPiece = std::find(capturingPieces.begin(), capturingPieces.end(), selectedPiece) != capturingPieces.end();

	if (selectedPiece != nullptr) {
		if (isCapturingPiece || capturingPieces.empty()) {
			selected = true;
			capturablePieces.clear();
			std::cout << "selected piece at : " << pos << std::endl;
			validPotentialMove = validPossibleMoves();
		}
	}
}

void Game3Model::moveSelected(int pos) {
	bool validMove{ false };
	// Check pos with the Piece's possibleMoves
	for (int validPosition : validPotentialMove) {
		if (pos == validPosition) {
			validMove = true;
			break;
		}
	}
	if (validMove) {
		// If we were jumping ahead of capturable piece we need to actually remove them
		if (!capturablePieces.empty()) capturing(pos);
		selectedPiece->setPosition(pos); // Moving the piece
		// If a pawn piece has been moved, check for possible promotion
		if (selectedPiece->getType() == 'P') pawnPromotion(selectedPiece);
		turnInitialized = false;

		playerTurn = !playerTurn;
		capturingPieces.clear();
		if (checkmate())
			std::cout << "CHECKMATE!!!" << std::endl;
	}
	selected = false;
}

void Game3Model::capturing(int endPosition) {
	// Calculate the path from the current position to the endPosition
	std::vector<int> capturePath = getIntermediatePositions(selectedPiece->getPosition(), endPosition, 2);
	// Iterate through capturablePieces to find and remove pieces on the capture path
	auto captureIt = capturablePieces.begin();
	while (captureIt != capturablePieces.end()) {
		Piece* piece = *captureIt;
		if (std::find(capturePath.begin(), capturePath.end(), piece->getPosition()) != capturePath.end()) {
			piece->setPosition(-1); // Remove the piece from the board
			captureIt = capturablePieces.erase(captureIt); // Erase and advance iterator
		}
		else ++captureIt;
	}
	// Remove the capturing piece from the list of pieces that need to capture
	capturingPieces.erase(std::remove(capturingPieces.begin(), capturingPieces.end(), selectedPiece), capturingPieces.end());
}

const std::vector<int>& Game3Model::getValidMoves() const {
	return validPotentialMove;
}

std::vector<int> Game3Model::validPossibleMoves() {
	validPotentialMove.clear();
	const std::vector<const Piece*>& allpieces = allPieces();
	// First check for queen captures movement, as they are prioritized
	if (selectedPiece->getType() == 'Q') {
		validPotentialMove = validQueenCaptures(selectedPiece, allpieces);
		if (!validPotentialMove.empty()) return validPotentialMove; // Prioritize queen captures
	}
	// If no queen captures or if the selected piece is not a queen, check for pawn captures movement
	if (selectedPiece->getType() == 'P') {
		validPotentialMove = validPawnCaptures(selectedPiece, allpieces);
		if (!validPotentialMove.empty()) return validPotentialMove; // Only allow captures if available
	}
	const std::vector<int>& possibleMoves = selectedPiece->getPossibleMoves();
	std::vector<int> validMoves = possibleMoves; // Make a local copy for modifications
	// Checking piece's type
	char pieceType = selectedPiece->getType();
	switch (pieceType) {
	case 'P':
	case 'Q':
		validRectangularPieceMoves(validMoves, allpieces);
		break;
	case 'K':
		validKingMoves(validMoves, allpieces);
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		break;
	}
	validPotentialMove = validMoves;
	return validPotentialMove;
}

void Game3Model::validRectangularPieceMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces) {
	std::vector<std::vector<int>::iterator> toRemove;
	for (auto it = moves.begin(); it != moves.end(); ++it) {
		// Check if the move is to an already occupied position
		if (isPositionOccupied(*it, allPieces)) toRemove.push_back(it);
		else {
			// Check for obstacles only if the position is not already occupied
			std::vector<int> intermediatePositions = getIntermediatePositions(selectedPiece->getPosition(), *it);
			if (hasIntermediateObstacles(intermediatePositions, allPieces)) toRemove.push_back(it);
		}
	}
	for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) { moves.erase(*it); }
}

void Game3Model::validKingMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces) {
	std::vector<std::vector<int>::iterator> toRemove;

	//Finding the adversary king position
	int AdversaryKingPosition;
	for (const Piece* p : allPieces) {
		if (p->getPlayer() == !selectedPiece->getPlayer() && p->getType() == 'K') AdversaryKingPosition = p->getPosition();
	}
	for (auto it = moves.begin(); it != moves.end(); ++it) {
		// Check if the move is within the "Royal Distance"
		int moveDistance = std::abs(*it - AdversaryKingPosition);
		if (moveDistance == 30 || moveDistance == 28 || moveDistance == 32 || moveDistance == 2) toRemove.push_back(it);
		else {
			// Check for obstacles only if the position is not already occupied
			std::vector<int> intermediatePositions = getIntermediatePositions(selectedPiece->getPosition(), *it);
			if (hasIntermediateObstacles(intermediatePositions, allPieces)) toRemove.push_back(it);
		}
	}
	for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) { moves.erase(*it); }
}

std::vector<int> Game3Model::validPawnCaptures(const Piece* pawn, const std::vector<const Piece*>& allpieces) {
	std::vector<int> captures;
	int currentPosition = pawn->getPosition();
	if (currentPosition % 30 >= 15) return captures;

	int forwardDirection = pawn->getPlayer() ? -30 : 30;
	int obstacleDirection = pawn->getPlayer() ? -15 : 15;
	int lastEmptyPosition = -1; // Initialize to an invalid position

	while (true) {
		int opponentPosition = currentPosition + forwardDirection;
		int landingPosition = opponentPosition + forwardDirection;

		if (opponentPosition < 0 || opponentPosition >= 225 || landingPosition < 0 || landingPosition >= 225)
			break;

		if (isPositionOccupied(opponentPosition, allpieces) && !isPositionOccupied(landingPosition, allpieces)) {
			Piece* opponentPiece = findPieceAtPosition(opponentPosition);

			if (opponentPiece != nullptr && opponentPiece->getPlayer() != pawn->getPlayer()
				&& !isPositionOccupied(currentPosition + obstacleDirection, allpieces) && !isPositionOccupied(opponentPosition + obstacleDirection, allpieces)) {
				bool AlreadyCapturingPiece = std::find(capturingPieces.begin(), capturingPieces.end(), pawn) != capturingPieces.end();
				if (!AlreadyCapturingPiece) { capturingPieces.push_back(pawn); }
				capturablePieces.push_back(opponentPiece);
				lastEmptyPosition = landingPosition;
				currentPosition = landingPosition;
			}
			else { break; }
		}
		else { break; }
	}
	// If a capture is possible, add the final position to the captures vector
	if (lastEmptyPosition != -1) captures.push_back(lastEmptyPosition);
	return captures;
}

std::vector<int> Game3Model::validQueenCaptures(const Piece* queen, const std::vector<const Piece*>& allPieces) {
	std::vector<int> captures;
	int currentPosition = queen->getPosition();
	int rowStart, rowEnd;
	// Define movement directions based on the queen's orientation (horizontal/vertical)
	std::vector<int> moveDirections;
	(currentPosition % 30 < 15) ? moveDirections = { -30, 30 } : moveDirections = { -2, 2 }; //Move by -+30 (2rows) when the queen's orientation is horizontal else move my -+2 squares
	// Calculate the boundaries of the current row where the queen is located
	rowStart = currentPosition - currentPosition % 15;
	rowEnd = rowStart + 14;

	// Check captures in all directions
	for (int direction : moveDirections) {
		int scanPosition = currentPosition + direction;
		int lastCapturablePiecePosition = -1;
		bool inCaptureSequence = false;
		while (scanPosition >= 0 && scanPosition < 225) {
			// For vertical movement, ensure not to wrap around to the next row
			if ((direction == -2 || direction == 2) && (scanPosition < rowStart || scanPosition > rowEnd))
				break;
			if (isPositionOccupied(scanPosition, allPieces)) {
				// Checking if the selected existing piece is at the edges of the board
				if ((direction == -2 || direction == 2) && (scanPosition == rowStart || scanPosition == rowEnd)) { break; }
				else { if ((direction == -30 || direction == 30) && (scanPosition < 15 || scanPosition > 209)) { break; } }
				Piece* pieceAtPosition = findPieceAtPosition(scanPosition);
				if (pieceAtPosition->getPlayer() != queen->getPlayer() && !isPositionOccupied(scanPosition + direction, allPieces)
					&& !isPositionOccupied(scanPosition - (direction / 2), allPieces) && !isPositionOccupied(scanPosition + (direction / 2), allPieces)) {
					// Found a capturable opponent piece with a valid landing position and no king is in both ways
					if (std::find(capturablePieces.begin(), capturablePieces.end(), pieceAtPosition) == capturablePieces.end())
						capturablePieces.push_back(pieceAtPosition);
					lastCapturablePiecePosition = scanPosition;
					inCaptureSequence = true; // Start capture sequence
					scanPosition += direction; // Move to next position for subsequent captures
				}
				else { break; }// Stop scanning if we hit an ally rectangular piece or a king in the way
			}
			else { // If the space is empty
				if (!isPositionOccupied(scanPosition - (direction / 2), allPieces)) { // It's a valid landing position after a capture sequence
					if (inCaptureSequence) { captures.push_back(scanPosition); }
				}
				else { break; } // Stop scanning when hitting a king
				scanPosition += direction; // Continue scanning if not in a capture sequence
			}
		}
		if (lastCapturablePiecePosition != -1) { //Removing in-between opponent landing positions
			std::vector<int> invalidLandingPositions = getIntermediatePositions(currentPosition, lastCapturablePiecePosition, 2);
			for (auto landIt = invalidLandingPositions.begin(); landIt != invalidLandingPositions.end(); ++landIt) {
				auto captureIt = std::find(captures.begin(), captures.end(), *landIt);
				if (captureIt != captures.end()) { captures.erase(captureIt); }
			}
		}
	}
	// If captures were found, add the queen to the capturingPieces vector
	if (!captures.empty() && std::find(capturingPieces.begin(), capturingPieces.end(), queen) == capturingPieces.end())
		capturingPieces.push_back(queen);
	return captures;
}

std::vector<int> Game3Model::getIntermediatePositions(int from, int to, int s) {
	std::vector<int> intermediatePositions;
	int moveDistance = std::abs(to - from);
	if ((moveDistance == 14 && (from / 15 != to / 15)) || moveDistance == 16) return intermediatePositions;
	int stepSize = (moveDistance < 15) ? 1 * s : 15 * s;
	int step = (to > from) ? stepSize : -stepSize;

	for (int i = stepSize; i < moveDistance; i += stepSize) {
		intermediatePositions.push_back(from + (i / stepSize) * step);
	}
	return intermediatePositions;
}

bool Game3Model::isPositionOccupied(int position, const std::vector<const Piece*>& allPieces) const {
	for (const Piece* p : allPieces) {
		if (p->getPosition() == position) return true;
	}
	return false;
}

bool Game3Model::hasIntermediateObstacles(std::vector<int>& intermediatePositions, const std::vector<const Piece*>& allPieces) const {
	for (int pos : intermediatePositions) {
		for (const Piece* p : allPieces) {
			if (p->getPosition() == pos) return true;
		}
	}
	return false;
}

Piece* Game3Model::findPieceAtPosition(int position) {
	if (player1.findPieceAtPosition(position) != nullptr) return player1.findPieceAtPosition(position);
	if (player2.findPieceAtPosition(position) != nullptr) return player2.findPieceAtPosition(position);
	return nullptr; // Return nullptr if no piece is found at the position
}

std::vector<const Piece*> Game3Model::allPieces() const {
	std::vector<const Piece*> combinedPieces;

	// Add pieces from player1
	for (const Piece& piece : player1.getPieces()){
		if(piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}

	// Add pieces from player2
	for (const Piece& piece : player2.getPieces()) {
		if (piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}

	return combinedPieces;
}

void Game3Model::findCapturingScenarios() {
	Player& currentPlayer = (playerTurn ? player1 : player2);
	const std::array<Piece, 24>& playerPieces = currentPlayer.getPieces();

	const std::vector<const Piece*>& allpieces = allPieces();

	for (const Piece& p : playerPieces) {
		if (p.getPosition() != -1 && p.getType() == 'Q') validQueenCaptures(&p, allpieces);
	}

	if (capturingPieces.empty()) { // Only check for pawns if no queen captures are found
		for (const Piece& p : playerPieces) {
			// Check for horizontal pawn captures
			if (p.getType() == 'P' && p.getPosition() % 30 < 15) validPawnCaptures(&p, allpieces);
		}
	}
	if (!capturingPieces.empty()) {
		std::cout << "  +++++++++++++++++++++++++++++++++++++" << std::endl;
		for (auto i : capturingPieces) {
			std::cout << "||\tcapturing piece at : " << i->getPosition() << i->getType() << "\t||" << std::endl;
		}
		std::cout << "  +++++++++++++++++++++++++++++++++++++\n" << std::endl;
	}
	if (!capturablePieces.empty()) {
		std::cout << "  =====================================" << std::endl;
		for (auto i : capturablePieces) {
			std::cout << "||\tcapturable piece at : " << i->getPosition() << i->getType() << "\t||" << std::endl;
		}
		std::cout << "  =====================================\n" << std::endl;
	}
}

void Game3Model::pawnPromotion(Piece * pawn) {
	if (pawn->getPlayer() && pawn->getPosition() < 15) {
		pawn->setType('Q');
	}
	else {
		if (!pawn->getPlayer() && pawn->getPosition() > 209)
			pawn->setType('Q');
	}
}

bool Game3Model::checkmate() {
	// Check if one of kings is checkmated
	if (isKingCheckmated(player1.getPieces()[0]) || isKingCheckmated(player2.getPieces()[0]))
		return true;
	return false;
}

bool Game3Model::isKingCheckmated(const Piece& king) {
	const std::vector<const Piece*>& allpieces = allPieces();

	bool allyPiece = false; // Indicate if an ally is encircling the king
	int piecesBesideKing = 0; // Indicate the number of pieces encircling the king

	for (const Piece* p : allpieces) {
		if (p->getPosition() - 1 == king.getPosition() || p->getPosition() + 1 == king.getPosition()
			|| p->getPosition() - 15 == king.getPosition() || p->getPosition() + 15 == king.getPosition()) {
			if (p->getPlayer() == !king.getPlayer()) allyPiece = true;
			piecesBesideKing += 1;
		}
	}
	if (piecesBesideKing == 4 && allyPiece) return true;
	else return false;
}