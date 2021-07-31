#ifndef HEXARRAY1D_H
#define HEXARRAY1D_H

#include <string>
#include <iostream>
#include "AbstractHex.h"
#include <stack>

namespace SaribasCSE241{

	class HexArray1D_Exception : public exception{
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

	class HexArray1D : public AbstractHex{
	public:
		HexArray1D();
		HexArray1D(int boardSize);
		HexArray1D(int boardSize, char gameType);

		HexArray1D(const HexArray1D &other);
		HexArray1D& operator =(const HexArray1D& rightSide);

		void setSize(int boardSize);
		void print() const;
		void reset();
		void readFromFile(string fileName);
		void writeToFile(string fileName) const;
		void play();
		void play(string position);
		State getCell(int loc) const;
		string inputMove();


		char operator()(int index1, int index2) const;

		~HexArray1D();

	private:
		Cell * hexCells = nullptr;

		bool isValidMove(string pos) const;
		void searchAlgorith(int &player);
		void createHeatmap(int heatmap[][10], int row, int col) const;

	};

}

#endif