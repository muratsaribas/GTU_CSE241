#include "Hex.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//////////////////////////////////////////////////

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

void Hex::Cell::setCellRow(int rowT){ this->row = rowT; }

void Hex::Cell::setCellCol(char colT){ this->col = colT; }

void Hex::Cell::setCellMark(char markT){ this->mark = markT; }

void Hex::Cell::setAll(int rowT, char colT, char markT)
{
	setCellRow(rowT);
	setCellCol(colT);
	setCellMark(markT);
}

//////////////////////////////////////////////////
const string Hex::colLetters = "ABCDEFGHIJKL";
int Hex::numOfLiveHexClass = 0;

Hex::Hex()	// Constructor
{
	setBoardSize(6);
	setGameType('t');
	numOfLiveHexClass++;
}

Hex::Hex(int boardSizeT) : Hex(boardSizeT, 't') // Constructor
{/*  Empty    */
}

Hex::Hex(int boardSizeT, char GameType) : Hex()	// Constructor
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
Hex::Hex(const Hex &other)	// Copy constructor
{
	setBoardSize(other.getBoardSize());
	setGameType(other.getGameType());

	numOfLiveHexClass++;
}

Hex& Hex::operator =(const Hex& rightSide)	// Copy assignment
{
	if (this == &rightSide)  // same object?
		return *this;

	createBoard();
	if (getBoardSize() != rightSide.getBoardSize())
	{
		delete[] hexCells;
		int tempSize = rightSide.getBoardSize();
		hexCells = new Cell*[tempSize];
		for (int i = 0; i<tempSize; i++)
			hexCells[i] = new Cell[tempSize];
	}

	setBoardSize(rightSide.getBoardSize());
	for (int i = 0; i < getBoardSize(); i++)
		for (int j = 0; j < getBoardSize(); j++)
			hexCells[i][j] = rightSide.hexCells[i][j];

	return *this;
}

Hex::~Hex()			// destructor
{
	delete[] hexCells;
	//numOfLiveHexClass--;
}

void Hex::setBoardSize(int boardSizeT){ this->boardSize = boardSizeT; }

void Hex::setGameType(char type){ this->gameType = type; }


void Hex::createBoard(){	// oyun tahtasýný mevcut deðiþkenler ile oluþturur
	int tempSize = getBoardSize();
	hexCells = new Cell*[tempSize];
	for (int i = 0; i<tempSize; i++)
		hexCells[i] = new Cell[tempSize];

	for (int i = 0; i < tempSize; i++)
		for (int j = 0; j < tempSize; j++){
			char colLet = colLetters[j];
			hexCells[i][j].setAll(i, colLet, '.');
		}
}

void Hex::DrawBoard() const{	// oyun tahtasýný yazdýrýr

	for (int i = 0; i<getBoardSize(); i++){
		cout << colLetters[i] << " ";
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

void Hex::StartGame(){  // oyunun baþlangýç ayarlamalarý burada yapýlýr
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
	createBoard();
	DrawBoard();
}

void Hex::couts(int &User) const // görüntü kalabalýðý olmasýn diye
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

string Hex::getColumns(int &boardSize) const
{
	string columns;
	for (int i = 0; i<boardSize; i++)
		columns = columns + Hex::colLetters[i];
	return columns;
}

Hex::Position Hex::inputMove(int &user)
{
	int boardSize = getBoardSize();
	string columns = getColumns(boardSize);
	auto flag = true;
	string input;
	Hex::Position temp_Pos;
	while (flag)
	{
		couts(user);
		getline(cin, input);
		string slPart = input.substr(0, input.find(" "));
		if (slPart == "SAVE") // oyunu kaydet
		{
			saveFile = input.substr(5);
			temp_Pos.row = -4;
			temp_Pos.col = -4;
			return temp_Pos;

		}
		else if (slPart == "LOAD") // oyunu yükle
		{
			loadFile = input.substr(5);
			temp_Pos.row = -3;
			temp_Pos.col = -3;
			return temp_Pos;
		}
		else if (input == "UNDO")
		{
			temp_Pos.row = -2;
			temp_Pos.col = -2;
			return temp_Pos;
		}
		else if (input == "EARLYSTOP")
		{
			temp_Pos.row = -1;
			temp_Pos.col = -1;
			return temp_Pos;
		}

		else if (input.length()>2 && input.length()<5)
		{
			// girilen deðerin doðruluðunu kontrol edip geri döndür
			string inputColumn = input.substr(0, input.find(" "));
			int inputRow = stoi(input.substr(2, 2));
			if (inputColumn != "" && columns.find(inputColumn) != -1 && inputRow > -1 && inputRow < columns.length() + 1)
			{
				temp_Pos.col = columns.find(inputColumn);
				temp_Pos.row = inputRow - 1;
				flag = false;
				return temp_Pos; // oyuncu hareketini döndür
			}
			else
				cerr << "Wrong input" << endl;
		}
		else
			cerr << "Wrong input" << endl;
	}
	return temp_Pos;
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
	int tempSize = getBoardSize();
	string columns = getColumns(tempSize);
	cout << endl << "=====COM PLAY: " << columns[max_j] << " " << max_i + 1 << "  =====\n\n";
}

bool Hex::play(Position position)   // iki kiþilik oyunda
{							 		// 'x' oyuncu hareketi
	auto flag = true;
	if (hexCells[position.row][position.col].getCellMark() == States::Empty)
	{
		hexCells[position.row][position.col].setCellMark('x');
		flag = false;
	}
	else
		cerr << "Wrong input\n";
	return flag;
}

bool Hex::playO(Position position)	// iki kiþilik oyunda
{									// 'o' oyuncu hareketi
	auto flag = true;
	if (hexCells[position.row][position.col].getCellMark() == States::Empty)
	{
		hexCells[position.row][position.col].setCellMark('o');
		flag = false;
	}
	else
		cerr << "Wrong input\n";
	return flag;
}

void Hex::resetPath(stack<Position> stackPos, char passedPath[][12]) const
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

void Hex::pathFinder(char passedPath[][12], stack<Position> stackPos, int row, int col, char mark)
{   // Gönderilen iþarete göre yol aramasý yap
	auto flag = true;
	auto control = true;
	int score = 0;
	Hex::Position temp_Pos;
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
					temp_Pos = stackPos.top();
					row = temp_Pos.row;
					col = temp_Pos.col;
				}
			}
			else
				control = false;
			flag = false;
		}
		if (flag){
			score++;
			temp_Pos.row = row;
			temp_Pos.col = col;
			stackPos.push(temp_Pos);
			if (row == getBoardSize() - 1 && mark == States::O_is_here) // Eðer yol en son satýra kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					temp_Pos = stackPos.top();
					row = temp_Pos.row;
					col = temp_Pos.col;
					hexCells[row][col].setCellMark(toupper(mark));
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard();
				cout << endl << "||||||  'O' PLAYER WON!!!   ||||||\n";
				numOfLiveHexClass--;
				this->isWon = true;
			}
			else if (col == getBoardSize() - 1 && mark == States::X_is_here) // Eðer yol en son sütuna kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					temp_Pos = stackPos.top();
					row = temp_Pos.row;
					col = temp_Pos.col;
					hexCells[row][col].setCellMark(toupper(mark));
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard();
				cout << endl << "||||||  'X' PLAYER WON!!!   ||||||\n";
				numOfLiveHexClass--;
				this->isWon = true;
			}
		}
	}
	if (mark == 'x')
		this->scoreX = (this->scoreX > score) ? this->scoreX : score;
	else
		this->scoreO = (this->scoreO > score) ? this->scoreO : score;

}

void Hex::searchAlgorith(int &user) //
{
	char passedPath[12][12];
	stack<Position> stackPos;
	Hex::Position temp_Pos;
	if (user == 1)     // 'x' oyuncusu için arama yap
	{
		for (int i = 0; i<getBoardSize(); i++)
		{
			if (hexCells[i][0].getCellMark() == States::X_is_here){    // ilk sütunda 'x' varsa aramayý baþlat
				resetPath(stackPos, passedPath);
				temp_Pos.row = i;
				temp_Pos.col = 0;
				passedPath[temp_Pos.row][temp_Pos.col] = 'p';
				stackPos.push(temp_Pos);
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
				temp_Pos.row = 0;
				temp_Pos.col = i;
				passedPath[temp_Pos.row][temp_Pos.col] = 'p';
				stackPos.push(temp_Pos);
				pathFinder(passedPath, stackPos, 0, i, 'o');
			}
		}
	}
}

char Hex::getCellMark(int &i, int &j) const
{
	return hexCells[i][j].getCellMark();
}

bool operator== (Hex &hex1, Hex &hex2)	// iki farklý Hex objesini karþýlaþtýrýr
{										// her iki objenin de iþaretli hücre sayýsý hesaplanýr
	int markedCells = 0;				// ilk parametre olarak girilen objenin iþaretli hücre sayýsý 
	int markedCellsOther = 0;			// daha fazla ise true döndürür
	for (int i = 0; i<hex1.getBoardSize(); i++)
		for (int j = 0; j<hex1.getBoardSize(); j++)
		{
			if (hex1.getCellMark(i, j) != Hex::States::Empty)
				markedCells++;
		}
	for (int i = 0; i<hex2.getBoardSize(); i++)
		for (int j = 0; j<hex2.getBoardSize(); j++)
		{
			if (hex2.getCellMark(i, j) != Hex::States::Empty)
				markedCellsOther++;
		}
	return markedCells > markedCellsOther;
}

ostream & operator << (ostream &out, const Hex &hex) // save iþlemini gerçekleþtirir
{

	ofstream file;
	file.open(hex.saveFile);
	file << hex.useR << endl;      // oyun sýrasýnýn kimde olduðunu yaz
	file << hex.gameType << endl;  // oyun türünü (vs user2 veya vs com) yaz
	file << hex.boardSize << endl; // tahta boyutunu yaz

	for (int i = 0; i<hex.boardSize; i++){   // tahtayý yazdýr
		for (int j = 0; j<hex.boardSize; j++)
			file << hex.hexCells[i][j].getCellMark();
		file << endl;
	}
	file.close();

	out << "GAME SAVED!" << endl;
	return out;
}

istream & operator >> (istream &in, Hex &hex) // load iþlemini gerçekleþtirir
{
	ifstream file;
	file.open(hex.loadFile);
	int turnLoad;
	char gametypeLoad;
	int boardsizeLoad;
	char ch;

	if (file.is_open())
	{
		file >> turnLoad;
		hex.turn = turnLoad;
		file >> gametypeLoad;
		hex.gameType = gametypeLoad;
		file >> boardsizeLoad;
		hex.boardSize = boardsizeLoad;

		delete[] hex.hexCells;				// mevcut oyundaki hücreler silinir
											// çünkü yüklenen oyunun tahta boyutu farklý olabilir
		int tempSize = hex.boardSize;
		hex.createBoard();					// yüklenen oyuna göre tahta yeniden oluþturulur

		for (int i = 0; i<tempSize; i++)
			for (int j = 0; j<tempSize; j++)
			{
				file >> ch;
				hex.hexCells[i][j].setCellMark(ch); 
			}
	}
	else
	{
		file.close();
		cerr << "File loading failed" << endl;
		exit(1);
	}
	file.close();
	cout << "\nGAME LOADED!\n";
	return in;
}

Hex & Hex::operator--() 	// --prefix
{							// undo iþlemini gerçekleþtirir
	if (!allMoves.empty())	// oynanan son hareketi stack'ten alýr
	{						// ve yerine '.' yerleþtirir
		int srow;
		int scol;
		int sturn;
		sturn = allMoves.top();
		turn = sturn;
		allMoves.pop();
		scol = allMoves.top();
		allMoves.pop();
		srow = allMoves.top();
		allMoves.pop();
		hexCells[srow][scol].setCellMark('.');
	}
	else
		return *this;

	return *this;

}
Hex & Hex::operator--(int dummy)     // postfix--
{									 // diðerinin aynýsý
	if (allMoves.empty())
	{
		int srow;
		int scol;
		int sturn;
		srow = allMoves.top();
		allMoves.pop();
		scol = allMoves.top();
		allMoves.pop();
		sturn = allMoves.top();
		turn = sturn;
		allMoves.pop();
		hexCells[srow][scol].setCellMark('.');
	}
	else
		return *this;

	return *this;
}
void Hex::PlayGame()
{

	this->saveFile = "";
	this->loadFile = "";
	this->undo = false;
	this->earlyStop = false;

	if (turn == 1 && getGameType() == 't' && !isEndGame())  // oyun sýrasý 'x' oyuncusunda ise
	{
		bool flag = true;
		while (flag){
			useR = 1;
			pos = inputMove(useR);
			if (pos.row == -4){  // save
				turn = 2;
				return;
			}
			else if (pos.row == -3) // load
			{
				turn = 2;
				return;
			}
			else if (pos.row == -2) // undo
			{
				undo = true;
				return;
			}
			else if (pos.row == -1) // earlystop
			{
				earlyStop = true;
				this->isWon = true;
				numOfLiveHexClass--;
				return;
			}
			else if (pos.row > -1)
			{
				flag = play(pos);
				allMoves.push(pos.row);
				allMoves.push(pos.col);
				allMoves.push(turn);
			}
		}
		DrawBoard();
		searchAlgorith(useR);
		turn = 2;
		return;

	}
	else if (turn == 2 && getGameType() == 't' && !isEndGame())// oyun sýrasý 'o' oyuncusunda ise
	{
		bool flag = true;
		while (flag)
		{
			useR = 2;
			pos = inputMove(useR);
			if (pos.row == -4)
			{
				turn = 1;
				return;
			}
			else if (pos.row == -3)
			{
				turn = 1;
				return;
			}
			else if (pos.row == -2) // undo
			{
				undo = true;
				return;
			}
			else if (pos.row == -1) // earlystop
			{
				earlyStop = true;
				this->isWon = true;
				numOfLiveHexClass--;
				return;
			}
			else if (pos.row > -1)
			{
				flag = playO(pos);
				allMoves.push(pos.row);
				allMoves.push(pos.col);
				allMoves.push(turn);
			}
		}
		DrawBoard();
		searchAlgorith(useR);
		turn = 1;
		return;

	}
	else if (turn == 1 && getGameType() == 'c' && !isEndGame())
	{
		useR = 1;
		play(); // COM PLAY
		DrawBoard();
		searchAlgorith(useR);
		turn = 2;
		return;
	}
	else if (turn == 2 && getGameType() == 'c' && !isEndGame())
	{
		bool flag = true;
		while (flag)
		{
			useR = 2;
			pos = inputMove(useR);
			if (pos.row == -4)
			{
				turn = 1;
				return;
			}
			else if (pos.row == -3)
			{
				turn = 1;
				return;
			}
			else if (pos.row == -2) // undo
			{
				undo = true;
				return;
			}
			else if (pos.row == -1) // earlystop
			{
				earlyStop = true;
				this->isWon = true;
				numOfLiveHexClass--;
				return;
			}
			else if (pos.row > -1)
			{
				flag = playO(pos);
				allMoves.push(pos.row);
				allMoves.push(pos.col);
				allMoves.push(turn);
			}
		}
		DrawBoard();
		searchAlgorith(useR);
		turn = 1;
		return;
	}
	else
	{
		cerr << "ERROR!!!";
		exit(1);
	}

}









