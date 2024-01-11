#include "PieceView.h"
#include "../../Models/Piece/PieceModel.h"

PieceView::PieceView(const PieceModel& model, sf::RenderWindow& win)
	: pieceModel(model), lastKnownPosition(-1) {}
