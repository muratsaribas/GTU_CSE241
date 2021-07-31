#ifndef ABSTRACTHEX_H
#define ABSTRACTHEX_H

#include "Cell.h"


namespace SaribasCSE241{


	class AbstractHex_Exception : public exception{
	public:
		const char* errorboardSize() const throw(){
			return "Hata! boardSize degeri araliginda olmalidir: 4<x<10";
		}
		const char* errorgameType() const throw(){
			return "Hata! gameType ancak degerlerini alabilir: t, T, c, C";
		}
		const char* errorlastMove() const throw(){
			return "Hata! Son hareket bulunamadý.";
		}

	};



	class AbstractHex{
	public:
		AbstractHex();
		AbstractHex(int boardSize);
		AbstractHex(int boardSize, char gameType);


		int getboardSize() const;
		int getnextMove() const;
		char getgameType() const;
		bool isEnd() const;
		string lastMove() const;
		int numberOfMoves() const;
		bool checkPosition(int row, int col) const;

		virtual void setSize(int boardSize) = 0;
		virtual void print() const = 0;
		virtual void reset() = 0;
		virtual void readFromFile(string fileName) = 0;
		virtual void writeToFile(string fileName) const = 0;
		virtual void play() = 0;
		virtual void play(string position) = 0;

		virtual string inputMove() = 0;

		friend bool operator ==(const AbstractHex& hex1, const AbstractHex& hex2);
		virtual char operator()(int index1, int index2) const = 0;


		virtual ~AbstractHex();

	protected:
		int _boardSize;
		char _gameType;
		bool _isEnd = false;
		int _numberOfMoves = 0;
		string _lastMove = "";
		int _nextMove = 1;
	};
}





#endif