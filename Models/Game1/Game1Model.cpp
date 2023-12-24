#include "Game1Model.h"
#include <iostream>
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

Game1Model::Game1Model() : board(), currentPlayerIndex(0) {
	turnInitialized = false;
	removalPhase = true;

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

bool Game1Model::isTurnInitialized() const { return turnInitialized; }

bool Game1Model::isRemovalPhase() const { return removalPhase; }

bool Game1Model::isSelected() const { return selected; }

const Board1Model & Game1Model::getBoardModel() const { return board; }

const std::array<Piece1Model, 64>& Game1Model::allPieces() const { return pieces; }

Game1Player & Game1Model::getCurrentPlayer() { return players[currentPlayerIndex]; }

void Game1Model::setTurnInit(bool turn) { turnInitialized = turn; }

void Game1Model::nextTurn() {
	currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Game1Model::restart() {
	// Reset game state
	selected = false;
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
	if (selectedPiece && selectedPiece->getColor() == 'J') {
		if (removalPhase) {
			if (getCurrentPlayer().getId() == players.size() - 1)
				removalPhase = false;
			selectedPiece->setPosition(-1);
			nextTurn();
			return;
		}
		selected = true;
	}
}

void Game1Model::moveSelected(int pos) {
}

Piece1Model* Game1Model::findPieceAtPosition(int position) {
	for (Piece1Model& p : pieces) {
		if (p.getPosition() == position) return &p;
	}
	return nullptr;
}