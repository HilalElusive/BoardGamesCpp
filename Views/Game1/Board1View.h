#ifndef BOARD1VIEW_H
#define BOARD1VIEW_H

#include "../../Models/Game1/Board1Model.h"
#include "../Board/BoardView.h"

class Board1View : public BoardView {

public:
	Board1View(const Board1Model& model);
};

#endif