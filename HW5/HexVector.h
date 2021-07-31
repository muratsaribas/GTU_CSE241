#ifndef HEXVECTOR_H
#define HEXVECTOR_H

#include <string>
#include <iostream>
#include "AbstractHex.h"
#include <stack>

namespace SaribasCSE241{
	

	class HexVector_Exception : public exception{
	public:
		const char* out_of_range() const throw(){
			return "Hata! index degerleri boardSize degerinden kucuk ya da buyuk olamaz!!!";
		}
		const char* load_file() const throw(){
			return "Hata! Dosya okuma basarisiz!!!";
		}
		const char* invalidMove() const throw(){
			return "Hata! Gecersiz hareket!!!";
		}
	};

	class HexVector : public AbstractHex{
	public:
		HexVector();
		HexVector(int boardSize);
		HexVector(int boardSize, char gameType);

		void setSize(int boardSize);
		void print() const;
		void reset();
		void readFromFile(string fileName);
		void writeToFile(string fileName) const;
		void play();
		void play(string position);
		State getCell(int row, int col) const;
		string inputMove();

		char operator()(int index1, int index2) const;

	private:
		vector< vector<Cell> > hexCells;

		bool isValidMove(string pos) const;
		void searchAlgorith(int &player);
		void createHeatmap(int heatmap[][10], int row, int col) const;
		
	};


}

#endif