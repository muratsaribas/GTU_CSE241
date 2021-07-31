#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include<fstream>
using namespace std;
struct position{ int row; int col; };

class Hex
{
public:
	Hex();
	Hex(int boardSizeT);
	Hex(int boardSizeT, char GameType); 
	Hex(const Hex &other); 
	void playGame();
	void setBoardSize(int boardSize); 
	char getCellMark(int &i, int &j) const;
	inline char getGameType() const{ return gameType; } 
	inline int getBoardSize() const{ return boardSize; } 
	inline int getWidth() const{ return getBoardSize(); } 
	inline int getHeight() const{ return getBoardSize(); } 
	void DrawBoard() const; 
	static int getnumOfLiveCells(){ return numOfLiveCells; } 
	inline bool isEndGame() const{ return winner; } 
	bool compare(const Hex &other); 
private:
	class Cell;
	vector<vector<Cell>> hexCells;
	static string colLetters;
	int boardSize;
	char gameType;
	static int numOfLiveCells;
	bool winner = 0;
	int turn = 1;        // 1 = user1orCOM, 2 = user2
	enum States { Empty = '.', X_is_here = 'x', O_is_here = 'o' };


	int boardsize() const; 
	string boardSizeVal() const; 
	void setBoard(); 
	void setGameType(char type); 
	char twoPlayerOrPC() const; 
	void play();
	bool play(position pos); 
	bool playO(position pos); 
	string getColumns(int boardSize) const; 
	position inputMove(int &user); 
	void couts(int user) const; 
	void resetPath(stack<position> stackPos, char passedPath[][12]) const; 
	void searchAlgorith(int user); 
	void pathFinder(char passedPath[][12], stack<position> stackPos, int row, int col, char mark); 
	bool checkPosition(int row, int col) const; 
	void saveGame(string filename, int &user) const; 
	void loadGame(string filename); 
	void createHeatmap(int heatmap[][12], int &row, int &col) const;

};

int main()
{
	cout << "||||||||| Welcome to the MyHex Game. |||||||||\n";
	cout << "where '.' represents the empty cells, \n"
		<< "'x' represents the computer(user1) cells \nand 'o' represents the user (user2) cells. \n";
	cout << "The 'x' player must create a connected path between the right and left sides to win.\n";
	cout << "The 'o' player must create a connected path between the up and down sides to win.\n\n\n";
	Hex hex1;
	Hex hex2(hex1);
	Hex hex3(6, 'c');
	Hex hex4(7);
	Hex hex5(8, 't');

	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex1 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex1.playGame();
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex2 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex2.playGame();
	cout << endl << hex1.compare(hex2) << endl;
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex3 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex3.playGame();
	cout << endl << hex1.compare(hex3) << endl;
	cout << endl << hex2.compare(hex3) << endl;
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex4 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex4.playGame();
	cout << endl << hex1.compare(hex4) << endl;
	cout << endl << hex2.compare(hex4) << endl;
	cout << endl << hex3.compare(hex4) << endl;
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex5 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex5.playGame();
	cout << endl << hex1.compare(hex5) << endl;
	cout << endl << hex2.compare(hex5) << endl;
	cout << endl << hex3.compare(hex5) << endl;
	cout << endl << hex4.compare(hex5) << endl;
	cout << endl << hex5.compare(hex5) << endl;
	
	cout << endl << Hex::getnumOfLiveCells() << endl;
	return 0;

}

//####################################
// 				Cell Class
class Hex::Cell
{
public:
	Cell();
	Cell(int row, char col, char mark);
	Cell(const Cell &other);
	void setCellRow(int rowT);
	void setCellCol(char colT);
	void setCellMark(char markT);
	void setAll(int rowT, char colT, char markT);
	inline int getCellRow() const{ return row; }
	inline char getCellCol() const{ return col; }
	inline char getCellMark() const{ return mark; }

private:
	int row;
	char col;
	char mark;

};

Hex::Cell::Cell()
{
	setCellRow(0);
	setCellCol('A');
	setCellMark('.');
}

Hex::Cell::Cell(int row, char col, char mark)
{
	setCellRow(row);
	setCellCol(col);
	setCellMark(mark);
}

Hex::Cell::Cell(const Cell &other)
{
	setCellRow(other.getCellRow());
	setCellCol(other.getCellCol());
	setCellMark(other.getCellMark());
}

void Hex::Cell::setCellRow(int rowT){ row = rowT; }

void Hex::Cell::setCellCol(char colT){ col = colT; }

void Hex::Cell::setCellMark(char markT){ mark = markT; }

void Hex::Cell::setAll(int rowT, char colT, char markT)
{
	setCellRow(rowT);
	setCellCol(colT);
	setCellMark(markT);
}
//       		end Cell class
//###################################

// Hex Class
string Hex::colLetters = "ABCDEFGHIJKL";
int Hex::numOfLiveCells = 0;

Hex::Hex()
{
	setBoardSize(6);
	setGameType('t');
}
Hex::Hex(int boardSizeT) : Hex(boardSizeT, 't')
{/* Bilerek boþ býrakýlmýþtýr*/}
Hex::Hex(int boardSizeT, char GameType) : Hex()
{
	if (boardSizeT<13 && boardSizeT>5)
	{
		char temp = tolower(GameType);
		if (temp == 't' || temp == 'c')
		{
			setBoardSize(boardSizeT);
			setGameType(temp);
		}
		else
			cerr << "Invalid input. Hex is set by no parameter constructor.\n";
	}
	else
		cerr << "Invalid input. Hex is set by no parameter constructor.\n";
}
Hex::Hex(const Hex &other)
{
	setBoardSize(other.getBoardSize());
	setGameType(other.getGameType());
}

void Hex::setBoard()    // varsayýlan olarak 12x12 bir vektör oluþturur
{						// çünkü maksimum tahta boyutunu 12x12 olarak ayarladým
	vector<Cell> tempCell;
	Hex::Cell temp;

	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			char colLet = Hex::colLetters[j];
			temp.setAll(i, colLet, '.');
			tempCell.push_back(temp);
		}
		hexCells.push_back(tempCell);
	}
}
void Hex::setBoardSize(int boardSizeT){ boardSize = boardSizeT; }
void Hex::setGameType(char type){ gameType = type; }
int Hex::boardsize() const  // Klavyeden girilen string tahta boyutu deðeri ayrýþtýrarak
{  							// int deðer olarak döndür
	string inputSize = boardSizeVal();
	string split = inputSize.substr(0, inputSize.find("x"));
	int bsize = stoi(split);
	return bsize;
}
string Hex::boardSizeVal() const    // Girilen boyut deðeri doðru olana kadar devam et
{					   				// doðru deðer girilince string olarak döndür
	string BOARD_SIZE[] = { "6x6", "7x7", "8x8", "9x9", "10x10", "11x11", "12x12" };
	int lenght = sizeof(BOARD_SIZE) / sizeof(*BOARD_SIZE);
	string inputSize;
	bool flag = true;
	while (flag){
		cout << "What will be the board size?" << endl
			<< "The board size can be 6x6, 7x7, 8x8, 9x9, 10x10, 11x11, or 12x12."
			<< endl << "Please enter the board size: ";
		cin >> inputSize;
		for (int i = 0; i<lenght; i++){
			if (inputSize == BOARD_SIZE[i])
				flag = false;
		}
	}
	return inputSize;
}
char Hex::twoPlayerOrPC() const // oyun iki kiþilik mi oynanacak yoksa PC'ye karþý mý
{
	string input;
	char player;
	auto flag = true;
	while (flag){
		cout << endl << endl;
		cout << "Two Players(Press T) or Versus Computer(Press C)" << endl
			<< "Choose One:  ";
		cin >> input;
		if (input.length() != 1)
		{
			flag = true;
			cerr << "Wrong input" << endl;
		}
		else
		{
			player = input[0];
			player = tolower(player);
			if (player == 't' || player == 'c')
				flag = false;
			else
			{
				flag = true;
				cerr << "Wrong input" << endl;
			}
		}
	}
	return player;
}
void Hex::DrawBoard() const  // oyun tahtasýný ekrana yazdýr
{
	for (int i = 0; i<getBoardSize(); i++){
		cout << Hex::colLetters[i] << " ";
	}
	cout << endl;
	for (int i = 0; i<getBoardSize(); i++){
		for (int j = 0; j<getBoardSize(); j++){
			cout << hexCells[i][j].getCellMark() << " ";
		}
		cout << i + 1 << " " << endl;
		cout << string(i + 1, ' ');
	}
	cout << endl;
}
string Hex::getColumns(int boardSize) const
{
	string columns;
	for (int i = 0; i<boardSize; i++)
		columns = columns + Hex::colLetters[i];
	return columns;
}

void Hex::play()            // COM hareketi
{							
	int heatmap[12][12];
	for (int i = 0; i < getBoardSize(); i++)
		for (int j = 0; j < getBoardSize(); j++)
			heatmap[i][j] = 0;
	for (int i = 0; i < getBoardSize(); i++)     // 'o' iþareti olan hücrelere göre bir
		for (int j = 0; j < getBoardSize(); j++) // ýsý haritasý oluþtur
		{
			if (hexCells[i][j].getCellMark() == States::O_is_here)
			{
				createHeatmap(heatmap, i, j);
			}
		}
	for (int i = 0; i < getBoardSize(); i++)
		for (int j = 0; j < getBoardSize(); j++)
		{
			if (hexCells[i][j].getCellMark() == States::O_is_here || hexCells[i][j].getCellMark() == States::X_is_here)
			{
				heatmap[i][j] = 0;
			}
		}
	int max_i = 0;
	int max_j = 0;
	for (int i = 0; i < getBoardSize(); i++)
	{											 	 // ýsý haritasýndaki en büyük deðeri
		for (int j = 0; j < getBoardSize(); j++){	 // bilgisayar hareketi olarak gönder
			if (heatmap[max_i][max_j] < heatmap[i][j])
			{
				max_i = i;
				max_j = j;
			}
		}
	}
	hexCells[max_i][max_j].setCellMark('x');
	numOfLiveCells++;
	string columns = getColumns(getBoardSize());
	cout << endl << "=====COM PLAY: " << columns[max_j] << " " << max_i + 1 << "  =====\n\n";
}
bool Hex::play(position pos) // iki kiþilik oyunda
{							 // 'x' oyuncu hareketi
	auto flag = true;
	if (hexCells[pos.row][pos.col].getCellMark() == States::Empty)
	{
		hexCells[pos.row][pos.col].setCellMark('x');
		numOfLiveCells++;
		flag = false;
	}
	else
		cerr << "Wrong input\n";
	return flag;
}
bool Hex::playO(position pos) // 'o' oyuncu hareketi
{
	auto flag = true;
	if (hexCells[pos.row][pos.col].getCellMark() == States::Empty)
	{
		hexCells[pos.row][pos.col].setCellMark('o');
		flag = false;
		numOfLiveCells++;
	}
	else
		cerr << "Wrong input\n";
	return flag;
}
void Hex::saveGame(string filename, int &user) const
{
	ofstream file;
	file.open(filename);
	file << user << endl;      // oyun sýrasýnýn kimde olduðunu yaz
	file << getGameType() << endl;  // oyun türünü (vs user2 veya vs com) yaz
	file << getBoardSize() << endl; // tahta boyutunu yaz

	for (int i = 0; i<getBoardSize(); i++){   // tahtayý yazdýr
		for (int j = 0; j<getBoardSize(); j++)
			file << hexCells[i][j].getCellMark();
		file << endl;
	}
	file.close();
}
void Hex::loadGame(string filename)
{
	for (int i = 0; i<getBoardSize(); i++)				// eðer yeni bir oyun load edildiyse
		for (int j = 0; j<getBoardSize(); j++)          // bitmemiþ olan oyundaki bütün yaþayan
		{ 												// hücreleri numOfLiveCells deðiþkenden çýkart
			if (hexCells[i][j].getCellMark() != States::Empty)
				numOfLiveCells--;
		}
	ifstream file;
	file.close();
	file.open(filename);
	int turnLoad;
	char gametypeLoad;
	int boardsizeLoad;
	char ch;
	if (file.is_open())
	{
		file >> turnLoad;
		turn = turnLoad;
		file >> gametypeLoad;
		setGameType(gametypeLoad);
		file >> boardsizeLoad;
		setBoardSize(boardsizeLoad);

		for (int i = 0; i<getBoardSize(); i++)
		{
			for (int j = 0; j<getBoardSize(); j++)
			{
				file >> ch;
				hexCells[i][j].setCellMark(ch);  	
				if (ch != States::Empty)			// yüklenen oyundaki yaþayan hücreleri
					numOfLiveCells++;				//	numOfLiveCells deðiþkenine ekle
			}
		}
	}
	else
	{
		file.close();
		cerr << "File loading failed" << endl;
		exit(1);
	}
	file.close();	
}
position Hex::inputMove(int &user)
{
	string columns = getColumns(getBoardSize());
	auto flag = true;
	string input;
	position pos;
	pos.col = -1; // oyun save edildiyse döndürülecek 
	pos.row = -1; // varsayýlan deðer
	while (flag)
	{
		couts(user);
		getline(cin, input);
		string slPart = input.substr(0, input.find(" "));
		if (slPart == "SAVE") // oyunu kaydet
		{
			string fileName = input.substr(5);
			saveGame(fileName, user);
			cout << "GAME SAVED. \n";

		}
		else if (slPart == "LOAD") // oyunu yükle
		{
			string fileName = input.substr(5);
			loadGame(fileName);
			cout << "GAME LOADED. \n";
			DrawBoard();
			if (turn == 1)
			{
				pos.row = -2;  // oyun sýrasýnýn kimde olduðunu öðrenmek için
				pos.col = -2;
			}
			else
			{
				pos.row = -3;  // oyun sýrasýnýn kimde olduðunu öðrenmek için
				pos.col = -3;
			}
			return pos;
		}

		else if (input.length()>2 && input.length()<5)
		{
			// girilen deðerin doðruluðunu kontrol edip geri döndür
			string inputColumn = input.substr(0, input.find(" "));
			int inputRow = stoi(input.substr(2, 2));
			if (inputColumn != "" && columns.find(inputColumn) != -1 && inputRow > -1 && inputRow < columns.length() + 1)
			{
				pos.col = columns.find(inputColumn);
				pos.row = inputRow - 1;
				flag = false;
				return pos; // oyuncu hareketini döndür
			}
			else
				cerr << "Wrong input" << endl;
		}
		else
			cerr << "Wrong input" << endl;
	}
	return pos; 
}
void Hex::couts(int User) const  // görüntü kalabalýðý olmasýn diye
{
	cout << endl << "Make a move!\n";
	cout << "Use positions such as A 1, B 3, C 6, etc. \n";
	cout << "If you want to load a saved game, type 'LOAD FILENAME.TXT'\n";
	cout << "or for save the current game, type 'SAVE FILENAME.TXT'\n";
	if (User == 1)
		cout << endl << "User1 (X) Turn: ";
	else
		cout << endl << "User2 (O) Turn: ";
}
void Hex::resetPath(stack<position> stackPos, char passedPath[][12]) const
{  		// yolu sýfýrla
	while (!stackPos.empty())
		stackPos.pop();
	for (int i = 0; i<getBoardSize(); i++)
	{
		for (int j = 0; j<getBoardSize(); j++)
			passedPath[i][j] = '.';
	}
}
bool Hex::checkPosition(int row, int col) const // pozisyon deðerlerini kontrol et
{
	if (row < 0 || row >= getBoardSize() || col < 0 || col >= getBoardSize())
		return false;
	else
		return true;

}
void Hex::pathFinder(char passedPath[][12], stack<position> stackPos, int row, int col, char mark)
{   // Gönderilen iþarete göre yol aramasý yap
	auto flag = true;
	auto control = true;
	position pos;
	while (control){
		if (checkPosition(row, col + 1) && hexCells[row][col + 1].getCellMark() == mark && passedPath[row][col + 1] != 'p'){
			passedPath[row][col + 1] = 'p';
			col++;
			flag = true;
		}
		else if (checkPosition(row, col - 1) && hexCells[row][col - 1].getCellMark() == mark && passedPath[row][col - 1] != 'p'){
			passedPath[row][col - 1] = 'p';
			col--;
			flag = true;
		}
		else if (checkPosition(row + 1, col) && hexCells[row + 1][col].getCellMark() == mark && passedPath[row + 1][col] != 'p'){
			passedPath[row + 1][col] = 'p';
			row++;
			flag = true;
		}
		else if (checkPosition(row - 1, col) && hexCells[row - 1][col].getCellMark() == mark && passedPath[row - 1][col] != 'p'){
			passedPath[row - 1][col] = 'p';
			row--;
			flag = true;
		}
		else if (checkPosition(row - 1, col + 1) && hexCells[row - 1][col + 1].getCellMark() == mark && passedPath[row - 1][col + 1] != 'p'){
			passedPath[row - 1][col + 1] = 'p';
			row--;
			col++;
			flag = true;
		}
		else if (checkPosition(row + 1, col - 1) && hexCells[row + 1][col - 1].getCellMark() == mark && passedPath[row + 1][col - 1] != 'p'){
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
					pos = stackPos.top();
					row = pos.row;
					col = pos.col;
				}
			}
			else
				control = false;
			flag = false;
		}
		if (flag){
			pos.row = row;
			pos.col = col;
			stackPos.push(pos);
			if (row == getBoardSize() - 1 && mark == States::O_is_here) // Eðer yol en son satýra kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					pos = stackPos.top();
					row = pos.row;
					col = pos.col;
					hexCells[row][col].setCellMark(toupper(mark));
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard();
				cout << endl << "||||||  'O' PLAYER WON!!!   ||||||\n";
				winner = true; 
			}
			else if (col == getBoardSize() - 1 && mark == States::X_is_here) // Eðer yol en son sütuna kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					pos = stackPos.top();
					row = pos.row;
					col = pos.col;
					hexCells[row][col].setCellMark(toupper(mark));
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard();
				cout << endl << "||||||  'X' PLAYER WON!!!   ||||||\n";
				winner = true;
			}
		}
	}
}
void Hex::searchAlgorith(int user) //
{
	char passedPath[12][12];
	stack<position> stackPos;
	position pos;
	if (user == 1)     // 'x' oyuncusu için arama yap
	{
		for (int i = 0; i<getBoardSize(); i++)
		{
			if (hexCells[i][0].getCellMark() == States::X_is_here){    // ilk sütunda 'x' varsa aramayý baþlat
				resetPath(stackPos, passedPath);
				pos.row = i;
				pos.col = 0;
				passedPath[pos.row][pos.col] = 'p';
				stackPos.push(pos);
				pathFinder(passedPath, stackPos, i, 0, 'x');
			}
		}
	}
	else if (user == 2)   // 'o' oyuncusu için arama yap
	{
		for (int i = 0; i<getBoardSize(); i++)
		{
			if (hexCells[0][i].getCellMark() == States::O_is_here){  // ilk satýrda 'o' varsa aramayý baþlat
				resetPath(stackPos, passedPath);
				pos.row = 0;
				pos.col = i;
				passedPath[pos.row][pos.col] = 'p';
				stackPos.push(pos);
				pathFinder(passedPath, stackPos, 0, i, 'o');
			}
		}
	}
}
void Hex::createHeatmap(int heatmap[][12], int &row, int &col) const
{
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
bool Hex::compare(const Hex &other)
{
	int markedCells = 0;
	int markedCellsOther = 0;
	for (int i = 0; i<getBoardSize(); i++)
		for (int j = 0; j<getBoardSize(); j++)
		{
			if (hexCells[i][j].getCellMark() != States::Empty)
				markedCells++;
		}
	for (int i = 0; i<other.getBoardSize(); i++)
		for (int j = 0; j<other.getBoardSize(); j++)
		{
			if (other.getCellMark(i,j) != States::Empty)
				markedCellsOther++;
		}
	return markedCells > markedCellsOther;
}
char Hex::getCellMark(int &i, int &j) const
{
	return hexCells[i][j].getCellMark();
}
void Hex::playGame()
{
	cout << "Current Board Size: " << getWidth() << "x" << getHeight() << endl;
	cout << "Do you wanna change Board Size? : (y)" << endl;
	char input;
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		int bsize = boardsize();
		setBoardSize(bsize);
		cout << "Board size is updated to: " << getWidth() << "x" << getHeight() << endl;
	}
	setBoard();
	cout << "Current GameType: " << getGameType() << "    (t: two player, c: vs COM) \n";
	cout << "Do you wanna play default GameType? : (y)" << endl;
	char input2;
	cin >> input2;
	if (input2 == 'Y' || input2 == 'y')
	{
		setGameType(getGameType());
	}
	else
	{
		char type = twoPlayerOrPC();
		setGameType(type);
	}
	DrawBoard();
	int user;
	while (!isEndGame())
	{
		if (turn == 1 && getGameType() == 't')  // oyun sýrasý 'x' oyuncusunda ise
		{
			bool flag = true;
			bool flag2 = true;
			while (flag && getGameType() == 't')
			{
				user = 1;
				position pos = inputMove(user);
				if (pos.row == -3)
				{
					flag = false;
					flag2 = false;
					turn = 2;
				}
				else if (pos.row > -1)
					flag = play(pos);
			}
			if (flag2 && getGameType() == 't')
			{
				DrawBoard();
				searchAlgorith(user);
				cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
				if (!isEndGame())
				{
					bool flag = true;
					while (flag && getGameType() == 't')
					{
						user = 2;
						position pos = inputMove(user);
						if (pos.row == -3)
						{
							flag = false;
							flag2 = false;
							turn = 2;
						}
						else if (pos.row > -1)
							flag = playO(pos);
					}
					if (flag2 && getGameType() == 't')
					{
						DrawBoard();
						searchAlgorith(user);
						cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
					}
				}
			}
		}
		else if (turn == 2 && getGameType() == 't')// oyun sýrasý 'o' oyuncusunda ise
		{
			bool flag = true;
			bool flag2 = true;
			while (flag && getGameType() == 't')
			{
				user = 2;
				position pos = inputMove(user);
				if (pos.row == -2)
				{
					flag = false;
					flag2 = false;
					turn = 1;
				}
				else if (pos.row > -1)
					flag = playO(pos);
			}
			if (flag2 && getGameType() == 't')
			{
				DrawBoard();
				searchAlgorith(user);
				cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
				if (!isEndGame() && getGameType() == 't')
				{
					bool flag = true;
					while (flag && getGameType() == 't')
					{
						user = 1;
						position pos = inputMove(user);
						if (pos.row == -2)
						{
							flag = false;
							flag2 = false;
							turn = 1;
						}
						else if (pos.row > -1)
							flag = play(pos);
					}
					if (flag2 && getGameType() == 't')
					{
						DrawBoard();
						searchAlgorith(user);
						cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
					}
				}
			}
		}
		else if (turn == 1 && getGameType() == 'c')
		{
			user = 1;
			play(); // COM PLAY
			DrawBoard();
			searchAlgorith(user);
			cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
			if (!isEndGame())
			{
				bool flag2 = true;
				bool flag = true;
				while (flag && getGameType() == 'c')
				{
					user = 2;
					position pos = inputMove(user);
					if (pos.row == -3)
					{
						flag = false;
						flag2 = false;
						turn = 2;
					}
					else if (pos.row > -1)
						flag = playO(pos);
				}
				if (flag2 && getGameType() == 'c')
				{
					DrawBoard();
					searchAlgorith(user);
					cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
				}
			}
		}
		else if (turn == 2 && getGameType() == 'c')
		{
			bool flag = true;
			bool flag2 = true;
			while (flag && getGameType() == 'c')
			{
				user = 2;
				position pos = inputMove(user);
				if (pos.row == -2)
				{
					flag = false;
					flag2 = false;
					turn = 1;
				}
				else if (pos.row > -1)
					flag = playO(pos);
			}
			if (flag2 && getGameType() == 'c')
			{
				DrawBoard();
				searchAlgorith(user);
				cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
				if (!isEndGame() && getGameType() == 't')
				{
					user = 1;
					play(); // COM PLAY
					DrawBoard();
					searchAlgorith(user);
					cout << endl << "Number of Live Cells: " << Hex::getnumOfLiveCells() << endl;
				}
			}
		}
		else
		{
			cerr << "ERROR!!!";
			exit(1);
		}
	}
}

//end hex class
