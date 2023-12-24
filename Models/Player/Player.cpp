#include "Player.h"

Player::Player(int id, const std::string& name) : playerId(id), playerName(name), score(0) {}

int Player::getId() const {
	return playerId;
}

std::string Player::getName() const {
	return playerName;
}

void Player::initializePieces(bool player) {} // Default implementation: Do nothing
