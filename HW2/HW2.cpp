#include<iostream>
#include<string>
#include<stack>
#include<fstream>
using namespace std;

struct position
{
	int col;
	int row;
};

enum States { Empty = '.', X_is_here = 'x', O_is_here = 'o'};

int boardsize();
string boardSizeVal();
char twoPlayerOrPC();
string getColumnLetters(const int &boardSize);
void DrawBoard(const int &boardSize, string &columns, char board[][12]);
void couts(int user = 1);
position inputMove(char board[][12], const int &boardSize, string &columns, int user, const char &gameType);
void XplayerTurn(char board[][12], const int &boardSize, string &columns, const char &gameType);
void XplayerTurn(char board[][12], const int &boardSize, string &columns, position &pos);
void OplayerTurn(char board[][12], const int &boardSize, string &columns, const char &gameType);
void pathFinder(char board[][12], char passedPath[][12], const int &boardSize, stack<position> stackPos, int row = 0, int col = 0, char mark = 'x');
void resetPath(stack<position> stackPos, char passedPath[][12], const int &boardSize);
void searchAlgorith(char board[][12], const int &boardSize, int user = 1);
void saveGame(char board[][12], const int &boardSize, const char &gameType, int &user, string &fileName);
void loadGame(string &fileName);
bool checkPosition(int row, int col, const int &boardSize);
void createHeatmap(int heatmap[][12], int &row, int &col, const int &boardSize);
void computerMove(char board[][12], const int &boardSize);
void playGame(char board[][12], const int &boardSize, const char &gameType, int turn = 1);


int main()
{
	cout << "||||||||| Welcome to the MyHex Game. |||||||||\n";
	cout << "where '.' represents the empty cells, "
		<< "'x' represents the computer(user1) cells and 'o' represents the user (user2) cells. \n";
	cout << "The 'x' player must create a connected path between the right and left sides to win.\n";
	cout << "The 'o' player must create a connected path between the up and down sides to win.\n\n\n";
	char board[12][12];
	const int boardSize = boardsize();
	for (int i = 0; i<boardSize; i++)
	{
		for (int j = 0; j<boardSize; j++)
			board[i][j] = '.';
	}

	const char gameType = twoPlayerOrPC();
	playGame(board, boardSize, gameType);
}

int boardsize() // Klavyeden girilen string tahta boyutu deðeri ayrýþtýrarak
{  				// int deðer olarak döndür
	string inputSize = boardSizeVal();
	string split = inputSize.substr(0, inputSize.find("x"));
	int boardSize = stoi(split);
	return boardSize;
}

string boardSizeVal()  // Girilen boyut deðeri doðru olana kadar devam et
{					   // doðru deðer girilince string olarak döndür
	string BOARD_SIZE[] = { "6x6", "7x7", "8x8", "9x9", "10x10", "11x11", "12x12" };
	int lenght = sizeof(BOARD_SIZE) / sizeof(*BOARD_SIZE);
	string inputSize;
	bool flag = true;
	while (flag){
		cout << "What will be the board size?" << endl
			<< "The board size can be 6x6, 7x7, 8x8, 9x9, 10x10, 11x11, or 12x12."
			<< endl << "Pleas enter the board size: ";
		cin >> inputSize;
		for (int i = 0; i<lenght; i++){
			if (inputSize == BOARD_SIZE[i])
				flag = false;
		}
	}
	return inputSize;
}

char twoPlayerOrPC() // oyun iki kiþilik mi oynanacak yoksa PC'ye karþý mý
{
	string input;
	char player;
	auto flag = true;
	while (flag){              
		cout << endl << endl;
		cout << "Two Players(Press T) or Versus Computer(Press C)" << endl
			<< "Choose One:  ";
		cin >> input;
		if(input.length() != 1)
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

string getColumnLetters(const int &boardSize) // Sütundaki harfleri getir
{
	const char LETTERS[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };
	string columns;
	for (int i = 0; i<boardSize; i++)
		columns = columns + LETTERS[i];
	return columns;
}

void DrawBoard(const int &boardSize, string &columns, char board[][12]) 
{     // Oyun tahtasýný ekrana yazdýr          
	for (int i = 0; i<boardSize; i++){
		cout << columns[i] << " ";
	}
	cout << endl;
	for (int i = 0; i<boardSize; i++){
		for (int j = 0; j<boardSize; j++){
			cout << board[i][j] << " ";
		}
		cout << i + 1 << " " << endl;
		cout << string(i + 1, ' ');
	}
}

void couts(int user)  // 
{
	cout << endl << "Make a move!\n";
	cout << "Use positions such as A 1, B 3, C 6, etc. \n";
	cout << "If you want to load a saved game, type 'LOAD FILENAME.TXT'\n";
	cout << "or for save the current game, type 'SAVE FILENAME.TXT'\n";
	if (user == 1)
		cout << endl << "User1 (X) Turn: ";
	else
		cout << endl << "User2 (O) Turn: ";

}

position inputMove(char board[][12], const int &boardSize, string &columns, int user, const char &gameType)  
{	//Klavyeden girilen deðeri kontrol et
	auto flag = true;
	string input;
	while (flag)
	{
		couts(user);
		getline(cin, input);
		string slPart = input.substr(0, input.find(" "));
		if (slPart == "SAVE") // oyunu kaydet
		{
			string fileName = input.substr(5); 
			saveGame(board, boardSize, gameType, user, fileName);
			cout << "GAME SAVED. \n";
		}
		else if (slPart == "LOAD") // oyunu yükle
		{
			string fileName = input.substr(5);
			loadGame(fileName);
		}
		
		else if (input.length()>2 && input.length()<5)
		{
			// girilen deðerin doðruluðunu kontrol edip geri döndür
			string inputColumn = input.substr(0, input.find(" "));
			int inputRow = stoi(input.substr(2, 2));
			if (inputColumn != "" && columns.find(inputColumn) != -1 && inputRow > -1 && inputRow < columns.length() + 1)
			{
				position pos;
				pos.col = columns.find(inputColumn);
				pos.row = inputRow - 1;
				flag = false;
				return pos;
			}
			else
				cerr << "Wrong input" << endl;	
		}
		else
			cerr << "Wrong input" << endl;
	}
}

void XplayerTurn(char board[][12], const int &boardSize, string &columns, const char &gameType) 
{   //  'x' oyuncu sýrasý (vs user2)
	auto flag = true;
	while (flag)
	{
		position pos = inputMove(board, boardSize, columns, 1, gameType);
		if (board[pos.row][pos.col] == States::Empty)
		{
			board[pos.row][pos.col] = 'x';
			flag = false;
		}
	}
	DrawBoard(boardSize, columns, board);

	searchAlgorith(board, boardSize, 1);
}

void XplayerTurn(char board[][12], const int &boardSize, string &columns, position &pos) 
{  // 'x' oyuncu sýrasý (vs computer)
	
	board[pos.col][pos.row] = 'x';
	DrawBoard(boardSize, columns, board);
	searchAlgorith(board, boardSize, 1);
}

void OplayerTurn(char board[][12], const int &boardSize, string &columns, const char &gameType) 
{   // 'o' oyuncu sýrasý
	auto flag = true;
	while (flag)
	{
		position pos = inputMove(board, boardSize, columns, 2, gameType);
		if (board[pos.row][pos.col] == States::Empty)
		{
			board[pos.row][pos.col] = 'o';
			flag = false;
		}
	}
	DrawBoard(boardSize, columns, board);
	searchAlgorith(board, boardSize, 2);
}

void pathFinder(char board[][12], char passedPath[][12], const int &boardSize, stack<position> stackPos, int row, int col, char mark) 
{   // Gönderilen iþarete göre yol aramasý yap
	auto flag = true;
	auto control = true;
	position pos;
	string columns = getColumnLetters(boardSize);
	while (control){
		if (board[row][col + 1] == mark && passedPath[row][col + 1] != 'p'){
			passedPath[row][col + 1] = 'p';
			col++;
			flag = true;
		}
		else if (board[row][col - 1] == mark && passedPath[row][col - 1] != 'p'){
			passedPath[row][col - 1] = 'p';
			col--;
			flag = true;
		}
		else if (board[row + 1][col] == mark && passedPath[row + 1][col] != 'p'){
			passedPath[row + 1][col] = 'p';
			row++;
			flag = true;
		}
		else if (board[row - 1][col] == mark && passedPath[row - 1][col] != 'p'){
			passedPath[row - 1][col] = 'p';
			row--;
			flag = true;
		}
		else if (board[row - 1][col + 1] == mark && passedPath[row - 1][col + 1] != 'p'){
			passedPath[row - 1][col + 1] = 'p';
			row--;
			col++;
			flag = true;
		}
		else if (board[row + 1][col - 1] == mark && passedPath[row + 1][col - 1] != 'p'){
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
			if (row == boardSize - 1 && mark == States::O_is_here) // Eðer yol en son satýra kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					pos = stackPos.top();
					row = pos.row;
					col = pos.col;
					board[row][col] = toupper(mark);
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard(boardSize, columns, board);
				cout << endl << "||||||  'O' PLAYER WON!!!   ||||||\n";
				cin.get();
				exit(1);
			}
			else if (col == boardSize - 1 && mark == States::X_is_here) // Eðer yol en son sütuna kadar ulaþmýþsa
			{
				while (!stackPos.empty())
				{
					pos = stackPos.top();
					row = pos.row;
					col = pos.col;
					board[row][col] = toupper(mark);
					stackPos.pop();
				}
				cout << endl << endl << endl;
				DrawBoard(boardSize, columns, board);
				cout << endl << "||||||  'X' PLAYER WON!!!   ||||||\n";
				cin.get();
				exit(1);
			}

		}

	}
}

void resetPath(stack<position> stackPos, char passedPath[][12], const int &boardSize) 
{  // yolu sýfýrla
	while (!stackPos.empty())
		stackPos.pop();
	for (int i = 0; i<boardSize; i++)
	{
		for (int j = 0; j<boardSize; j++)
			passedPath[i][j] = '.';
	}
}

void searchAlgorith(char board[][12], const int &boardSize, int user) //
{
	auto flag = false;
	char passedPath[12][12];
	stack<position> stackPos;
	position pos;
	if (user == 1)     // 'x' oyuncusu için arama yap
	{
		for (int i = 0; i<boardSize; i++)
		{
			if (board[i][0] == States::X_is_here){    // ilk sütunda 'x' varsa aramayý baþlat
				resetPath(stackPos, passedPath, boardSize);
				pos.row = i;
				pos.col = 0;
				passedPath[pos.row][pos.col] = 'p';
				stackPos.push(pos);
				pathFinder(board, passedPath, boardSize, stackPos, i, 0, 'x');
			}
		}
	}
	else if (user == 2)   // 'o' oyuncusu için arama yap
	{
		for (int i = 0; i<boardSize; i++)
		{
			if (board[0][i] == States::O_is_here){  // ilk satýrda 'o' varsa aramayý baþlat
				resetPath(stackPos, passedPath, boardSize);
				pos.row = 0;
				pos.col = i;
				passedPath[pos.row][pos.col] = 'p';
				stackPos.push(pos);
				pathFinder(board, passedPath, boardSize, stackPos, 0, i, 'o');
			}
		}
	}
}

void saveGame(char board[][12], const int &boardSize, const char &gameType, int &user, string &fileName) 
{   // oyunu FILE.txt olarak kaydet
	ofstream file;
	file.open(fileName);
	file << user << endl;      // oyun sýrasýnýn kimde olduðunu yaz
	file << gameType << endl;  // oyun türünü (vs user2 veya vs com) yaz
	file << boardSize << endl; // tahta boyutunu yaz
	
	for (int i = 0; i<boardSize; i++){   // tahtayý yazdýr
		for (int j = 0; j<boardSize; j++)
			file << board[i][j];
		file << endl;
	}
	file.close();
	
}

void loadGame(string &fileName) //  oyunu FILE.txt dosyasýndan yükle
{
	ifstream file;
	file.open(fileName);
	int turn;
	char gametype;
	int boardsize;
	char boardd[12][12];
	char ch;
	if(file.is_open())
	{
		file >> turn;
		file >> gametype;
		file >> boardsize;

		for (int i = 0; i<boardsize; i++)
		{
			for (int j = 0; j<boardsize; j++)
			{
				file >> ch;
				boardd[i][j] = ch;
			}
		}
	}
	else
	{
		cerr << "File loading failed" << endl;
		exit(1);
	}
	file.close();
	const int boardSize = boardsize;
	const char gameType = gametype;
	playGame(boardd, boardsize, gametype, turn);
}

bool checkPosition(int row, int col, const int &boardSize) // pozisyon deðerlerini kontrol et
{
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize)
		return false;
	else
		return true;
	
}


void createHeatmap(int heatmap[][12], int &row, int &col, const int &boardSize) 
{   // Bilgisayar hareketi için bir ýsý haritasý oluþtur
	if(checkPosition(row - 1, col, boardSize))
		heatmap[row-1][col] = heatmap[row-1][col] + 2;
	if(checkPosition(row - 1, col + 1, boardSize))
		heatmap[row-1][col+1] = heatmap[row-1][col+1] + 2;
	if(checkPosition(row, col-1, boardSize))					//
		heatmap[row][col-1] = heatmap[row][col-1] + 1;			// komþuluk durumlarýna göre 
	if(checkPosition(row, col+1, boardSize))					//
		heatmap[row][col+1] = heatmap[row][col+1] + 2;
	if(checkPosition(row + 1, col-1, boardSize))
		heatmap[row+1][col-1] = heatmap[row+1][col-1] + 1;
	if(checkPosition(row + 1, col, boardSize))
		heatmap[row+1][col] = heatmap[row+1][col] + 2;
	
	if(checkPosition(row + 2, col-1, boardSize))
		heatmap[row + 2][col-1] = heatmap[row + 2][col-1] + 3;
	if(checkPosition(row + 1, col-2, boardSize))
		heatmap[row + 1][col-2] = heatmap[row + 1][col-2] + 3;
	if(checkPosition(row + 1, col+1, boardSize))				//
		heatmap[row + 1][col+1] = heatmap[row + 1][col+1] + 3;	// köprü oluþturabilecek yerler
	if(checkPosition(row - 1, col-1, boardSize))				//
		heatmap[row - 1][col-1] = heatmap[row - 1][col-1] + 3;
	if(checkPosition(row - 1, col+2, boardSize))
		heatmap[row - 1][col+2] = heatmap[row - 1][col+2] + 3;
	if(checkPosition(row - 2, col+1, boardSize))
		heatmap[row - 2][col+1] = heatmap[row - 2][col+1] + 3;
			
}


void computerMove(char board[][12], const int &boardSize)
{   // bilgisayar için bir hareket oluþtur
	int heatmap[12][12];
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			heatmap[i][j] = 0;
	
	
	for (int i = 0; i < boardSize; i++)     // 'o' iþareti olan hücrelere göre bir
		for (int j = 0; j < boardSize; j++) // ýsý haritasý oluþtur
		{
			if(board[i][j]==States::O_is_here)
			{
				createHeatmap(heatmap, i, j, boardSize);
			}
		}
		
	for (int i = 0; i < boardSize; i++) 
		for (int j = 0; j < boardSize; j++)
		{
			if(board[i][j]==States::O_is_here || board[i][j]==States::X_is_here)
			{
				heatmap[i][j] = 0;
			}
		}

	int max_i = 0;
	decltype(max_i) max_j = 0 + max_i;
	for (int i = 0; i < boardSize; i++) {        // ýsý haritasýndaki en büyük deðeri
		for (int j = 0; j < boardSize; j++){	 // bilgisayar hareketi olarak gönder
			if (heatmap[max_i][max_j] < heatmap[i][j])
			{
				max_i = i;
				max_j = j;
			}
		}
	}
	
	position pos = {max_i, max_j};
	decltype(getColumnLetters(boardSize)) columns = getColumnLetters(boardSize);
	cout << endl << "=====AI PLAY: " << columns[max_j] << " " << max_i + 1 << "  ====="<< endl;
	XplayerTurn(board, boardSize, columns, pos);	
}


void playGame(char board[][12], const int &boardSize, const char &gameType, int turn)
{
	string columns = getColumnLetters(boardSize);
	DrawBoard(boardSize, columns, board);
	if (gameType == 't')   // vs user2
	{
		while (1)
		{
			if(turn == 1)  // oyun sýrasý 'x' oyuncusunda ise
			{
				XplayerTurn(board, boardSize, columns, gameType);  
				OplayerTurn(board, boardSize, columns, gameType);	
			}
			else // oyun sýrasý 'o' oyuncusunda ise
			{
				OplayerTurn(board, boardSize, columns, gameType);
				XplayerTurn(board, boardSize, columns, gameType);
			}

		}
	}
	else  // vs computer
	{
		while (1)
		{
			if(turn == 1)
			{
				computerMove(board, boardSize);
				OplayerTurn(board, boardSize, columns, gameType);
				
			}
			else
			{
				OplayerTurn(board, boardSize, columns, gameType);
				computerMove(board, boardSize);
			}

		}
	}
}




