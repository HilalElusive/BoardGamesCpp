#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "PieceTextures.h"

class Piece : public sf::Drawable {

public:

	Piece() {}

	void setPiece(char type, bool player, int pos);

	void setType(char ch) { m_type = ch; setTexture(); }
	char getType() const { return m_type; }

	void setPlayer(bool bl) { m_player = bl; }
	bool getPlayer() const { return m_player; }

	void setPosition(int pos);
	int getPosition() const { return m_position; }

	void setMoved(bool moved) { m_moved = moved; }
	bool isMoved() const { return m_moved; }

	const std::vector<int>& getPossibleMoves(); //Depending on the type it return the possible moves

private:
	sf::Sprite m_sprite;
	std::vector<int> possibleMoves;

	char m_type; //'K'=King , 'Q' = Queen , 'P' = Pawn
	bool m_player; // true == White , false == Black  // To Future Me : Do it in a Class !!!!!!
	int m_position; // 0-224 board, -1 dead
	bool m_moved;
	
	void setTexture();
	void move(); //aligning the sprite to Board

	void PossibleKingMoves();
	void PossibleQueenMoves();
	void PossiblePawnMoves();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite);
	}
};

#endif
