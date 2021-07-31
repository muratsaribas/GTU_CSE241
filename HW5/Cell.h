#ifndef CELL_H
#define CELL_H

#include "helper.h"

namespace SaribasCSE241{

	

	class Cell{
	public:
		Cell();
		Cell(int row, char col, State mark);
		Cell(const Cell &other);
		void setCellRow(int row);
		void setCellCol(char col);
		void setCellMark(State mark);
		void setAll(int row, char col, State mark);
		inline int getCellRow() const{ return this->row; }
		inline char getCellCol() const{ return this->col; }
		inline State getCellState() const{ return this->mark; }

	private:
		int row;
		char col;
		State mark;
	};
}





#endif