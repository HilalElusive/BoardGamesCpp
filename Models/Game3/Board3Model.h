#ifndef BOARD3MODEL_H
#define BOARD3MODEL_H

#include <array>
#include "../Board/BoardModel.h"

class Board3Model : public BoardModel {
public:
	Board3Model();
	virtual ~Board3Model() = default;
	sf::Vector2f determineSquareSize(int position) const;

protected:
	void initializeSquares(int boardSize, const sf::Vector2f& uniformSize) override;

};

#endif