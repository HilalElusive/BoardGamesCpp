#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "../Game3/Piece3Model.h"

class Player {
private:
	int playerId; // Unique identifier for the player
	std::string playerName; // Player's name or identifier
	int score; // Player's score during a session
	bool turn; // Indicates if it's this player turn
	std::array<Piece3Model, 24> pieces; // Array to hold player's pieces

public:
	Player(int id, const std::string& name, bool turn);

	int getId() const;
	std::string getName() const;
	bool hasTurn() const;

	const std::array<Piece3Model,24>& getPieces() const;
	Piece3Model* findPieceAtPosition(int position);
	void initializePieces(bool player);
};

#endif