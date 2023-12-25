#ifndef PLAYER_H
#define PLAYER_H

#include <array>

class Player {
protected:
	int playerId; // Unique identifier for the player
	std::string playerName; // Player's name or identifier
	int score; // Player's score during a session

public:
	Player(int id, const std::string& name);

	int getId() const;
	std::string getName() const;
	int getScore() const;
	void setScore(int scr);

	virtual void initializePieces(bool player);
};

#endif