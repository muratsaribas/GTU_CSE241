#include "HexVector.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <utility>

using namespace std;

namespace SaribasCSE241{
	using std::ostream;
	using std::exception;
	using std::cout;
	using std::endl;
	using std::string;
	using std::vector;

	HexVector::HexVector() : AbstractHex()
	{
		hexCells.resize(getboardSize());
		for (int i = 0; i < getboardSize(); i++)
			hexCells[i].resize(getboardSize());

		for (int i = 0; i < getboardSize(); i++)
			for (int j = 0; j < getboardSize(); j++)
				hexCells[i][j].setCellMark(Empty);

	}

	HexVector::HexVector(int boardSize) : AbstractHex(boardSize)
	{
		hexCells.resize(getboardSize());
		for (int i = 0; i < getboardSize(); i++)
			hexCells[i].resize(getboardSize());

		for (int i = 0; i < getboardSize(); i++)
			for (int j = 0; j < getboardSize(); j++)
				hexCells[i][j].setCellMark(Empty);
	}

	HexVector::HexVector(int boardSize, char gameType) : AbstractHex(boardSize, gameType)
	{
		hexCells.resize(getboardSize());
		for (int i = 0; i < getboardSize(); i++)
			hexCells[i].resize(getboardSize());

		for (int i = 0; i < getboardSize(); i++)
			for (int j = 0; j < getboardSize(); j++)
				hexCells[i][j].setCellMark(Empty);

	}

	State HexVector::getCell(int row, int col) const{
		return hexCells[row][col].getCellState();
	}

	void HexVector::print() const{
		for (int i = 0; i<getboardSize(); i++){
			cout << colLetters[i] << " ";
		}
		cout << endl;
		for (int i = 0; i<getboardSize(); i++){
			for (int j = 0; j < getboardSize(); j++)
				cout << StatetoChar(hexCells[i][j].getCellState()) << " ";
			cout << i + 1 << " " << endl;
			cout << string(i + 1, ' ');
		}
		cout << endl;
	}

	void HexVector::reset(){
		for (int i = 0; i < getboardSize(); i++)
			for (int j = 0; j < getboardSize(); j++)
				hexCells[i][j].setCellMark(Empty);
	}

	void HexVector::setSize(int boardSize){
		this->_boardSize = boardSize;
		hexCells.resize(getboardSize());
		for (int i = 0; i < getboardSize(); i++)
			hexCells[i].resize(getboardSize());
		reset();
	}

	char HexVector::operator()(int index1, int index2) const{
			
		if (index1 <= 0 || index1 > getboardSize() || index2 <= 0 || index2 > getboardSize())
			throw HexVector_Exception();	
		else
			return StatetoChar(hexCells[index1-1][index2-1].getCellState());
		
	}

	void HexVector::readFromFile(string fileName){
		
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

						hexCells[i][j].setCellMark(temp);
					}
			}
			else
				throw HexVector_Exception();
		}
		catch (HexVector_Exception& e){
			cout << e.load_file() << endl;
			exit(1);
		}

		file.close();
		cout << "\nGAME LOADED!\n";
		this->print();
	}

	void HexVector::writeToFile(string fileName) const{
		ofstream file;
		file.open(fileName);
		file << this->_nextMove << endl;      // oyun sýrasýnýn kimde olduðunu yaz
		file << this->_gameType << endl;  // oyun türünü (vs user2 veya vs com) yaz
		file << getboardSize() << endl; // tahta boyutunu yaz

		for (int i = 0; i<getboardSize(); i++){   // tahtayý yazdýr
			for (int j = 0; j<getboardSize(); j++)
				file << StatetoChar(hexCells[i][j].getCellState());
			file << endl;
		}
		file.close();

		cout << "GAME SAVED!" << endl;
	}

	

	bool HexVector::isValidMove(string pos) const{
		int pos1 = stoi(pos);
		int row = pos1 % 10;
		int col = (pos1 - row) / 10;

		if (hexCells[row][col].getCellState() == Empty)
			return true;
		else
			return false;
	}

	string HexVector::inputMove()
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
							throw HexVector_Exception();
					}
					catch (HexVector_Exception& e){
						cout << e.invalidMove() << endl;
					}
				}
				else
					throw HexVector_Exception();
			}
			catch (HexVector_Exception& e){
				cout << e.invalidMove() << endl;
			}
		}
		return move;
	}

	void HexVector::createHeatmap(int heatmap[][10], int row, int col) const{
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

	void HexVector::play(){
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
						if (hexCells[i][j].getCellState() == O_player)
						{
							createHeatmap(heatmap, i, j);
						}
					}
				for (int i = 0; i < getboardSize(); i++)
					for (int j = 0; j < getboardSize(); j++)
					{
						if (hexCells[i][j].getCellState() == O_player || hexCells[i][j].getCellState() == X_player)
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
				hexCells[max_i][max_j].setCellMark(X_player);
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

	

	void HexVector::searchAlgorith(int &player){
		char passedPath[10][10];
		stack<pair<int, int>> stackPos;
		pair<int, int> temp_Pos;
		int boardsize = getboardSize();

		if (player == 1)
		{
			for (int i = 0; i < boardsize; i++)
			{
				if (hexCells[i][0].getCellState() == X_player)
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
						if (checkPosition(row, col + 1) && hexCells[row][col + 1].getCellState() == mark && passedPath[row][col + 1] != 'p'){
							passedPath[row][col + 1] = 'p';
							col++;
							flag = true;
						}
						else if (checkPosition(row, col - 1) && hexCells[row][col - 1].getCellState() == mark && passedPath[row][col - 1] != 'p'){
							passedPath[row][col - 1] = 'p';
							col--;
							flag = true;
						}
						else if (checkPosition(row + 1, col) && hexCells[row + 1][col].getCellState() == mark && passedPath[row + 1][col] != 'p'){
							passedPath[row + 1][col] = 'p';
							row++;
							flag = true;
						}
						else if (checkPosition(row - 1, col) && hexCells[row - 1][col].getCellState() == mark && passedPath[row - 1][col] != 'p'){
							passedPath[row - 1][col] = 'p';
							row--;
							flag = true;
						}
						else if (checkPosition(row - 1, col + 1) && hexCells[row - 1][col + 1].getCellState() == mark && passedPath[row - 1][col + 1] != 'p'){
							passedPath[row - 1][col + 1] = 'p';
							row--;
							col++;
							flag = true;
						}
						else if (checkPosition(row + 1, col - 1) && hexCells[row + 1][col - 1].getCellState() == mark && passedPath[row + 1][col - 1] != 'p'){
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
									hexCells[row][col].setCellMark(upperX);
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
				if (hexCells[0][i].getCellState() == O_player)
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
						if (checkPosition(row, col + 1) && hexCells[row][col + 1].getCellState() == mark && passedPath[row][col + 1] != 'p'){
							passedPath[row][col + 1] = 'p';
							col++;
							flag = true;
						}
						else if (checkPosition(row, col - 1) && hexCells[row][col - 1].getCellState() == mark && passedPath[row][col - 1] != 'p'){
							passedPath[row][col - 1] = 'p';
							col--;
							flag = true;
						}
						else if (checkPosition(row + 1, col) && hexCells[row + 1][col].getCellState() == mark && passedPath[row + 1][col] != 'p'){
							passedPath[row + 1][col] = 'p';
							row++;
							flag = true;
						}
						else if (checkPosition(row - 1, col) && hexCells[row - 1][col].getCellState() == mark && passedPath[row - 1][col] != 'p'){
							passedPath[row - 1][col] = 'p';
							row--;
							flag = true;
						}
						else if (checkPosition(row - 1, col + 1) && hexCells[row - 1][col + 1].getCellState() == mark && passedPath[row - 1][col + 1] != 'p'){
							passedPath[row - 1][col + 1] = 'p';
							row--;
							col++;
							flag = true;
						}
						else if (checkPosition(row + 1, col - 1) && hexCells[row + 1][col - 1].getCellState() == mark && passedPath[row + 1][col - 1] != 'p'){
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
									hexCells[row][col].setCellMark(upperO);
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

	void HexVector::play(string position){
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
				hexCells[row][col].setCellMark(X_player);
				searchAlgorith(this->_nextMove);
				_nextMove = 2;
				this->print();
			}
			else if (this->_nextMove == 2 && this->_gameType == 't' || this->_nextMove == 2 && this->_gameType == 'c')
			{
				this->_numberOfMoves++;
				hexCells[row][col].setCellMark(O_player);
				searchAlgorith(this->_nextMove);
				_nextMove = 1;
				this->print();
			}
		}
	}

	

	


	
	
}