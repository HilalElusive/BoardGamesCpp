#include "PieceTextures.h"
#include <iostream>

sf::Texture* PieceTextures::blackQueen2 = nullptr;
sf::Texture* PieceTextures::blackPawn2 = nullptr;

sf::Texture* PieceTextures::whiteQueen2 = nullptr;
sf::Texture* PieceTextures::whitePawn2 = nullptr;

sf::Texture* PieceTextures::blackKing3 = nullptr;
sf::Texture* PieceTextures::blackQueen3 = nullptr;
sf::Texture* PieceTextures::blackPawn3 = nullptr;

sf::Texture* PieceTextures::whiteKing3 = nullptr;
sf::Texture* PieceTextures::whiteQueen3 = nullptr;
sf::Texture* PieceTextures::whitePawn3 = nullptr;

sf::Texture& PieceTextures::loadTexture(std::string str, sf::Texture*& texture) {
	if (!texture) {
		texture = new sf::Texture();
		if (!texture->loadFromFile(str)) {
			std::cout << "Error loading file\n";
		}
	}
	return *texture;
}

void PieceTextures::cleanup() {
	delete blackQueen2; blackQueen2 = nullptr;
	delete blackPawn2; blackPawn2 = nullptr;

	delete whiteQueen2; whiteQueen2 = nullptr;
	delete whitePawn2; whitePawn2 = nullptr;

	delete blackKing3; blackKing3 = nullptr;
	delete blackQueen3; blackQueen3 = nullptr;
	delete blackPawn3; blackPawn3 = nullptr;

	delete whiteKing3; whiteKing3 = nullptr;
	delete whiteQueen3; whiteQueen3 = nullptr; 
	delete whitePawn3; whitePawn3 = nullptr;
}