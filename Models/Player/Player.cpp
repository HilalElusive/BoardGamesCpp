#include "Player.h"

Player::Player(int id, const std::string& name, bool trn) : playerId(id), playerName(name), score(0), turn(trn) {}

int Player::getId() const {
	return playerId;
}

std::string Player::getName() const {
	return playerName;
}

bool Player::hasTurn() const {
	return turn;
}