#include "PieceTextures.h"
#include <iostream>

sf::Texture& PieceTextures::loadTexture(std::string str, sf::Texture*& texture) {
	if (!texture) {
		texture = new sf::Texture();
		if (!texture->loadFromFile(str)) {
			std::cout << "Error loading file\n";
		}
	}
	return *texture;
}

sf::Texture* PieceTextures::blackKing = nullptr;
sf::Texture* PieceTextures::blackQueen = nullptr;
sf::Texture* PieceTextures::blackPawn = nullptr;

sf::Texture* PieceTextures::whiteKing = nullptr;
sf::Texture* PieceTextures::whiteQueen = nullptr;
sf::Texture* PieceTextures::whitePawn = nullptr;