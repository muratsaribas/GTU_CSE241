#include "AbstractHex.h"
#include <string>

namespace SaribasCSE241{

	AbstractHex::AbstractHex() : _boardSize(5), _gameType('t')
	{/* empty */
	}

	AbstractHex::AbstractHex(int boardSize)
	{
		this->_gameType = 't';

		try{
			if (boardSize < 5 || boardSize > 9)
				throw AbstractHex_Exception();
			else
				this->_boardSize = boardSize;
		}
		catch (AbstractHex_Exception& e){
			cout << e.errorboardSize() << endl;
			_boardSize = 5;
			cout << "boardSize = 5 olarak ayarland�." << endl;
		}
	}

	AbstractHex::AbstractHex(int boardSize, char gameType)
	{
		try{
			if (boardSize < 5 || boardSize > 9)
				throw AbstractHex_Exception();
			else
				this->_boardSize = boardSize;
		}
		catch (AbstractHex_Exception& e){
			cout << e.errorboardSize() << endl;
			this->_boardSize = 5;
			cout << "boardSize varsay�lan olarak ayarland�: 5" << endl;
		}

		try{
			if (gameType == 't' || gameType == 'c' || gameType == 'T' || gameType == 'C')
				this->_gameType = tolower(gameType);
			else
				throw AbstractHex_Exception();
		}
		catch (AbstractHex_Exception& e){
			cout << e.errorgameType() << endl;
			this->_gameType = 't';
			cout << "gameType varsay�lan olarak ayarland�: t" << endl;
		}
	}

	int AbstractHex::getboardSize() const{
		return this->_boardSize;
	}

	int AbstractHex::getnextMove() const{
		return this->_nextMove;
	}

	char AbstractHex::getgameType() const{
		return this->_gameType;
	}

	bool AbstractHex::isEnd() const{
		return this->_isEnd;
	}

	string AbstractHex::lastMove() const{
		if (this->_lastMove == "")
		{
			throw AbstractHex_Exception();
		}
		return this->_lastMove;
	}

	int AbstractHex::numberOfMoves() const{
		return this->_numberOfMoves;
	}

	bool AbstractHex::checkPosition(int row, int col) const{
		if (row < 0 || row >= getboardSize() || col < 0 || col >= getboardSize())
			return false;
		else
			return true;
	}

	bool operator ==(const AbstractHex& hex1, const AbstractHex& hex2){
		return hex1.getboardSize() == hex2.getboardSize();
	}

	

	AbstractHex::~AbstractHex()
	{/* empty*/
	}

}
