#ifndef PIECE_TEXTURES_H
#define PIECE_TEXTURES_H

#include <SFML/Graphics.hpp>
#include <string>

class PieceTextures {
public:
	static sf::Texture* blackKing;
	static sf::Texture* blackQueen;
	static sf::Texture* blackPawn;

	static sf::Texture* whiteKing;
	static sf::Texture* whiteQueen;
	static sf::Texture* whitePawn;

	static sf::Texture& loadTexture(std::string str, sf::Texture*& texture);
	static void cleanup();
};

#endif