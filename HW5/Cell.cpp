#include "Cell.h"


namespace SaribasCSE241{

	Cell::Cell(){
		setCellRow(0);
		setCellCol('A');
		setCellMark(State::Empty);
	}

	Cell::Cell(int row, char col, State mark)
	{
		setCellRow(row);
		setCellCol(col);
		setCellMark(mark);
	}

	Cell::Cell(const Cell &other)
	{
		setCellRow(other.getCellRow());
		setCellCol(other.getCellCol());
		setCellMark(other.getCellState());
	}

	void Cell::setCellRow(int row){ this->row = row; }

	void Cell::setCellCol(char col){ this->col = col; }

	void Cell::setCellMark(State mark){ this->mark = mark; }

	void Cell::setAll(int row, char col, State mark)
	{
		setCellRow(row);
		setCellCol(col);
		setCellMark(mark);
	}



}

