#ifndef PIECE_TEXTURES_H
#define PIECE_TEXTURES_H

#include <SFML/Graphics.hpp>
#include <string>

class PieceTextures {
public:
	//Game 2
	static sf::Texture* blackQueen2;
	static sf::Texture* blackPawn2;

	static sf::Texture* whiteQueen2;
	static sf::Texture* whitePawn2;
	//Game 3
	static sf::Texture* blackKing3;
	static sf::Texture* blackQueen3;
	static sf::Texture* blackPawn3;

	static sf::Texture* whiteKing3;
	static sf::Texture* whiteQueen3;
	static sf::Texture* whitePawn3;

	static sf::Texture& loadTexture(std::string str, sf::Texture*& texture);
	static void cleanup();
};

#endif