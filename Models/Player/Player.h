#ifndef PLAYER_H
#define PLAYER_H

#include <array>

class Player {
protected:
	int playerId; // Unique identifier for the player
	std::string playerName; // Player's name or identifier
	int score; // Player's score during a session
	bool turn; // Indicates if it's this player turn

public:
	Player(int id, const std::string& name, bool turn);

	int getId() const;
	std::string getName() const;
	bool hasTurn() const;

	virtual void initializePieces(bool player) = 0;
};

#endif