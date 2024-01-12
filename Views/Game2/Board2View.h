#ifndef BOARD2VIEW_H
#define BOARD2VIEW_H

#include "../../Models/Game2/Board2Model.h"
#include "../Board/BoardView.h"

class Board2View : public BoardView {

public:
	Board2View(const Board2Model& model);
};

#endif