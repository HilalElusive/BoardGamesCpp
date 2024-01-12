#ifndef BOARD3VIEW_H
#define BOARD3VIEW_H

#include "../../Models/Game3/Board3Model.h"
#include "../Board/BoardView.h"

class Board3View : public BoardView {

public:
	Board3View(const Board3Model& model);
};

#endif