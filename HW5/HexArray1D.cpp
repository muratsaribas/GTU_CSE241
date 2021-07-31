#include "HexArray1D.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <utility>

using namespace std;

namespace SaribasCSE241{

	HexArray1D::HexArray1D() : AbstractHex()
	{
		hexCells = new Cell[getboardSize() * getboardSize()];

		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(Empty);
	}

	HexArray1D::HexArray1D(int boardSize) : AbstractHex(boardSize)
	{
		hexCells = new Cell[getboardSize() * getboardSize()];

		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(Empty);
	}

	HexArray1D::HexArray1D(int boardSize, char gameType) : AbstractHex(boardSize, gameType)
	{
		hexCells = new Cell[getboardSize() * getboardSize()];

		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(Empty);
	}

	HexArray1D::HexArray1D(const HexArray1D &other){
		this->_boardSize = other.getboardSize();
		this->_gameType = other._gameType;
		this->_isEnd = other.isEnd();
		this->_numberOfMoves = other.numberOfMoves();
		this->_lastMove = other.lastMove();
		this->_nextMove = other._nextMove;
	}

	HexArray1D& HexArray1D::operator=(const HexArray1D& rightSide){
		if (this == &rightSide)  // same object?
			return *this;
		if (getboardSize() != rightSide.getboardSize())
		{
			delete[] hexCells;
			int tempSize = rightSide.getboardSize();
			hexCells = new Cell[tempSize*tempSize];
		}
		this->_gameType = rightSide.getgameType();
		this->_isEnd = rightSide.isEnd();
		this->_numberOfMoves = rightSide.numberOfMoves();
		this->_lastMove = rightSide.lastMove();
		this->_nextMove = rightSide.getnextMove();

		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(rightSide.getCell(i));
		return *this;
	}

	HexArray1D::~HexArray1D(){
		delete[] hexCells;
	}
	
	State HexArray1D::getCell(int loc) const{
		return hexCells[loc].getCellState();
	}

	void HexArray1D::setSize(int boardSize){
		this->_boardSize = boardSize;
		delete[] hexCells;
		hexCells = new Cell[getboardSize() * getboardSize()];
		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(Empty);
	}
	void HexArray1D::print() const{
		for (int i = 0; i<getboardSize(); i++){
			cout << colLetters[i] << " ";
		}
		cout << endl;
		for (int i = 0; i<getboardSize(); i++){
			for (int j = 0; j < getboardSize(); j++)
				cout << StatetoChar(hexCells[i*getboardSize() + j].getCellState()) << " ";
			cout << i + 1 << " " << endl;
			cout << string(i + 1, ' ');
		}
		cout << endl;
	}
	void HexArray1D::reset(){
		for (int i = 0; i < getboardSize() * getboardSize(); i++)
			hexCells[i].setCellMark(Empty);
	}

	void HexArray1D::readFromFile(string fileName){
		ifstream file;
		file.open(fileName);

		int turnLoad;
		char gametypeLoad;
		int boardsizeLoad;
		char ch;

		try{
			if (file.is_open()){
				this->_numberOfMoves = 0;
				this->_lastMove = "";

				file >> turnLoad;
				this->_nextMove = turnLoad;
				file >> gametypeLoad;
				this->_gameType = gametypeLoad;
				file >> boardsizeLoad;

				setSize(boardsizeLoad);


				for (int i = 0; i<getboardSize(); i++)
					for (int j = 0; j<getboardSize(); j++)
					{
						file >> ch;
						State temp;
						if (ch == '.')
							temp = Empty;
						else if (ch == 'o')
							temp = O_player;
						else if (ch == 'x')
							temp = X_player;

						hexCells[i*getboardSize()+j].setCellMark(temp);
					}
			}
			else
				throw HexArray1D_Exception();
		}
		catch (HexArray1D_Exception& e){
			cout << e.load_file() << endl;
			exit(1);
		}

		file.close();
		cout << "\nGAME LOADED!\n";
	}

	void HexArray1D::writeToFile(string fileName) const{
		ofstream file;
		file.open(fileName);
		file << this->_nextMove << endl;      // oyun sýrasýnýn kimde olduðunu yaz
		file << this->_gameType << endl;  // oyun türünü (vs user2 veya vs com) yaz
		file << getboardSize() << endl; // tahta boyutunu yaz

		for (int i = 0; i<getboardSize(); i++){   // tahtayý yazdýr
			for (int j = 0; j<getboardSize(); j++)
				file << StatetoChar(hexCells[i*getboardSize() + j].getCellState());
			file << endl;
		}
		file.close();

		cout << "GAME SAVED!" << endl;
	}

	bool HexArray1D::isValidMove(string pos) const{
		int pos1 = stoi(pos);
		int row = pos1 % 10;
		int col = (pos1 - row) / 10;

		if (hexCells[row*getboardSize() + col].getCellState() == Empty)
			return true;
		else
			return false;
	}

	string HexArray1D::inputMove()
	{
		string columns = getColumns(getboardSize());
		auto flag = true;
		string input;
		string move = "";
		while (flag)
		{
			couts(this->_nextMove);
			getline(cin, input);
			string slPart = input.substr(0, input.find(" "));
			try{
				if (slPart == "SAVE") // oyunu kaydet
				{
					string saveFile = input.substr(5);
					writeToFile(saveFile);
					return "S";

				}
				else if (slPart == "LOAD") // oyunu yükle
				{
					string loadFile = input.substr(5);
					readFromFile(loadFile);
					return "L";
				}

				else if (input.length()>2 && input.length()<5)
				{
					// girilen deðerin doðruluðunu kontrol edip geri döndür
					string inputColumn = input.substr(0, input.find(" "));
					int inputRow = stoi(input.substr(2, 2));
					try{

						if (inputColumn != "" && columns.find(inputColumn) != -1 && inputRow > -1 && inputRow < columns.length() + 1)
						{
							move = to_string(columns.find(inputColumn));
							move = move + to_string(inputRow - 1);
							if (isValidMove(move)){
								this->_lastMove = inputColumn + " " + to_string(inputRow);
								flag = false;
								return move; // oyuncu hareketini döndür
							}
							else
							{
								cout << "Invalid Move....\n";
							}

						}
						else
							throw HexArray1D_Exception();
					}
					catch (HexArray1D_Exception& e){
						cout << e.invalidMove() << endl;
					}
				}
				else
					throw HexArray1D_Exception();
			}
			catch (HexArray1D_Exception& e){
				cout << e.invalidMove() << endl;
			}
		}
		return move;
	}

	void HexArray1D::play(){
		if (this->_gameType == 'c' || this->_gameType == 'C')
		{
			if (this->_nextMove == 1)
			{
				this->_numberOfMoves++;
				int heatmap[10][10];
				for (int i = 0; i < getboardSize(); i++)
					for (int j = 0; j < getboardSize(); j++)
						heatmap[i][j] = 0;
				for (int i = 0; i < getboardSize(); i++)     // 'o' iþareti olan hücrelere göre bir
					for (int j = 0; j < getboardSize(); j++) // ýsý haritasý oluþtur
					{
						if (hexCells[i*getboardSize() + j].getCellState() == O_player)
						{
							createHeatmap(heatmap, i, j);
						}
					}
				for (int i = 0; i < getboardSize(); i++)
					for (int j = 0; j < getboardSize(); j++)
					{
						if (hexCells[i*getboardSize() + j].getCellState() == O_player || hexCells[i*getboardSize() + j].getCellState() == X_player)
						{
							heatmap[i][j] = 0;
						}
					}
				int max_i = 0;
				int max_j = 0;
				for (int i = 0; i < getboardSize(); i++)
				{											 	 // ýsý haritasýndaki en büyük deðeri
					for (int j = 0; j < getboardSize(); j++){	 // bilgisayar hareketi olarak gönder
						if (heatmap[max_i][max_j] < heatmap[i][j])
						{
							max_i = i;
							max_j = j;
						}
					}
				}
				hexCells[max_i*getboardSize() + max_j].setCellMark(X_player);
				int tempSize = getboardSize();
				string columns = getColumns(tempSize);
				cout << endl << "=====COM PLAY: " << columns[max_j] << " " << max_i + 1 << "  =====\n\n";
				searchAlgorith(this->_nextMove);
				_nextMove = 2;
				this->print();
			}
			else
				return;
		}

	}

	void HexArray1D::play(string position){
		if (position == "S")
			return;
		else if (position == "L")
			return;
		else{
			int pos = stoi(position);
			int row = pos % 10;
			int col = (pos - row) / 10;

			if (this->_nextMove == 1 && this->_gameType == 't'){
				this->_numberOfMoves++;
				hexCells[row*getboardSize() + col].setCellMark(X_player);
				searchAlgorith(this->_nextMove);
				_nextMove = 2;
				this->print();
			}
			else if (this->_nextMove == 2 && this->_gameType == 't' || this->_nextMove == 2 && this->_gameType == 'c')
			{
				this->_numberOfMoves++;
				hexCells[row*getboardSize() + col].setCellMark(O_player);
				searchAlgorith(this->_nextMove);
				_nextMove = 1;
				this->print();
			}
		}
	}

	char HexArray1D::operator()(int index1, int index2) const{
		if (index1 <= 0 || index1 > getboardSize() || index2 <= 0 || index2 > getboardSize())
			throw HexArray1D_Exception();
		else
			return StatetoChar(hexCells[(index1 - 1)*getboardSize() + (index2 - 1)].getCellState());
	}

	void HexArray1D::createHeatmap(int heatmap[][10], int row, int col) const{
		// Bilgisayar hareketi için bir ýsý haritasý oluþtur
		if (checkPosition(row - 1, col))
			heatmap[row - 1][col] = heatmap[row - 1][col] + 1;
		if (checkPosition(row - 1, col + 1))
			heatmap[row - 1][col + 1] = heatmap[row - 1][col + 1] + 1;
		if (checkPosition(row, col - 1))								//
			heatmap[row][col - 1] = heatmap[row][col - 1] + 1;			// komþuluk durumlarýna göre 
		if (checkPosition(row, col + 1))								//
			heatmap[row][col + 1] = heatmap[row][col + 1] + 2;
		if (checkPosition(row + 1, col - 1))
			heatmap[row + 1][col - 1] = heatmap[row + 1][col - 1] + 1;
		if (checkPosition(row + 1, col))
			heatmap[row + 1][col] = heatmap[row + 1][col] + 1;

		if (checkPosition(row + 2, col - 1))
			heatmap[row + 2][col - 1] = heatmap[row + 2][col - 1] + 2;
		if (checkPosition(row + 1, col - 2))
			heatmap[row + 1][col - 2] = heatmap[row + 1][col - 2] + 2;
		if (checkPosition(row + 1, col + 1))							//
			heatmap[row + 1][col + 1] = heatmap[row + 1][col + 1] + 2;	// köprü oluþturabilecek yerler
		if (checkPosition(row - 1, col - 1))							//
			heatmap[row - 1][col - 1] = heatmap[row - 1][col - 1] + 2;
		if (checkPosition(row - 1, col + 2))
			heatmap[row - 1][col + 2] = heatmap[row - 1][col + 2] + 2;
		if (checkPosition(row - 2, col + 1))
			heatmap[row - 2][col + 1] = heatmap[row - 2][col + 1] + 2;
	}

	void HexArray1D::searchAlgorith(int &player){
		char passedPath[10][10];
		stack<pair<int, int>> stackPos;
		pair<int, int> temp_Pos;
		int boardsize = getboardSize();

		if (player == 1)
		{
			for (int i = 0; i < boardsize; i++)
			{
				if (hexCells[i*boardsize].getCellState() == X_player)
				{
					resetPath(stackPos, passedPath, boardsize);
					temp_Pos.first = i;
					temp_Pos.second = 0;
					passedPath[temp_Pos.first][temp_Pos.second] = 'p';
					stackPos.push(temp_Pos);
					auto flag = true;
					auto control = true;
					int row = i;
					int col = 0;
					State mark = X_player;
					while (control){
						if (checkPosition(row, col + 1) && hexCells[row*boardsize +col + 1].getCellState() == mark && passedPath[row][col + 1] != 'p'){
							passedPath[row][col + 1] = 'p';
							col++;
							flag = true;
						}
						else if (checkPosition(row, col - 1) && hexCells[row*boardsize + col - 1].getCellState() == mark && passedPath[row][col - 1] != 'p'){
							passedPath[row][col - 1] = 'p';
							col--;
							flag = true;
						}
						else if (checkPosition(row + 1, col) && hexCells[(row + 1) * boardsize + col].getCellState() == mark && passedPath[row + 1][col] != 'p'){
							passedPath[row + 1][col] = 'p';
							row++;
							flag = true;
						}
						else if (checkPosition(row - 1, col) && hexCells[(row - 1)*boardsize + col].getCellState() == mark && passedPath[row - 1][col] != 'p'){
							passedPath[row - 1][col] = 'p';
							row--;
							flag = true;
						}
						else if (checkPosition(row - 1, col + 1) && hexCells[(row - 1)*boardsize + col + 1].getCellState() == mark && passedPath[row - 1][col + 1] != 'p'){
							passedPath[row - 1][col + 1] = 'p';
							row--;
							col++;
							flag = true;
						}
						else if (checkPosition(row + 1, col - 1) && hexCells[(row + 1)*boardsize + col - 1].getCellState() == mark && passedPath[row + 1][col - 1] != 'p'){
							passedPath[row + 1][col - 1] = 'p';
							row++;
							col--;
							flag = true;
						}
						else{
							if (!stackPos.empty())
							{
								stackPos.pop();
								if (!stackPos.empty())
								{
									temp_Pos = stackPos.top();
									row = temp_Pos.first;
									col = temp_Pos.second;
								}
							}
							else
								control = false;
							flag = false;
						}
						if (flag){
							temp_Pos.first = row;
							temp_Pos.second = col;
							stackPos.push(temp_Pos);
							if (col == boardsize - 1 && mark == X_player) // Eðer yol en son sütuna kadar ulaþmýþsa
							{
								while (!stackPos.empty())
								{
									temp_Pos = stackPos.top();
									row = temp_Pos.first;
									col = temp_Pos.second;
									hexCells[row*boardsize + col].setCellMark(upperX);
									stackPos.pop();
								}
								cout << endl << endl << endl;
								cout << endl << "||||||  'X' PLAYER WON!!!   ||||||\n";
								this->_isEnd = true;
								return;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < boardsize; i++)
			{
				if (hexCells[0 * boardsize + i].getCellState() == O_player)
				{
					resetPath(stackPos, passedPath, boardsize);
					temp_Pos.first = 0;
					temp_Pos.second = i;
					passedPath[temp_Pos.first][temp_Pos.second] = 'p';
					stackPos.push(temp_Pos);
					auto flag = true;
					auto control = true;
					int row = 0;
					int col = i;
					State mark = O_player;
					while (control){
						if (checkPosition(row, col + 1) && hexCells[row*boardsize + col + 1].getCellState() == mark && passedPath[row][col + 1] != 'p'){
							passedPath[row][col + 1] = 'p';
							col++;
							flag = true;
						}
						else if (checkPosition(row, col - 1) && hexCells[row*boardsize + col - 1].getCellState() == mark && passedPath[row][col - 1] != 'p'){
							passedPath[row][col - 1] = 'p';
							col--;
							flag = true;
						}
						else if (checkPosition(row + 1, col) && hexCells[(row + 1) * boardsize + col].getCellState() == mark && passedPath[row + 1][col] != 'p'){
							passedPath[row + 1][col] = 'p';
							row++;
							flag = true;
						}
						else if (checkPosition(row - 1, col) && hexCells[(row - 1) * boardsize + col].getCellState() == mark && passedPath[row - 1][col] != 'p'){
							passedPath[row - 1][col] = 'p';
							row--;
							flag = true;
						}
						else if (checkPosition(row - 1, col + 1) && hexCells[(row - 1) * boardsize + col + 1].getCellState() == mark && passedPath[row - 1][col + 1] != 'p'){
							passedPath[row - 1][col + 1] = 'p';
							row--;
							col++;
							flag = true;
						}
						else if (checkPosition(row + 1, col - 1) && hexCells[(row + 1)*boardsize + col - 1].getCellState() == mark && passedPath[row + 1][col - 1] != 'p'){
							passedPath[row + 1][col - 1] = 'p';
							row++;
							col--;
							flag = true;
						}
						else{
							if (!stackPos.empty())
							{
								stackPos.pop();
								if (!stackPos.empty())
								{
									temp_Pos = stackPos.top();
									row = temp_Pos.first;
									col = temp_Pos.second;
								}
							}
							else
								control = false;
							flag = false;
						}
						if (flag){
							temp_Pos.first = row;
							temp_Pos.second = col;
							stackPos.push(temp_Pos);
							if (row == boardsize - 1 && mark == O_player) // Eðer yol en son satýra kadar ulaþmýþsa
							{
								while (!stackPos.empty())
								{
									temp_Pos = stackPos.top();
									row = temp_Pos.first;
									col = temp_Pos.second;
									hexCells[row*boardsize + col].setCellMark(upperO);
									stackPos.pop();
								}
								cout << endl << endl << endl;
								cout << endl << "||||||  'O' PLAYER WON!!!   ||||||\n";
								this->_isEnd = true;
								return;
							}
						}
					}
				}
			}
		}
	}
}