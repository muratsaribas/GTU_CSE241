#include<iostream>
#include<string>
#include<stack>

using namespace std;
const string BOARD_SIZE[] = { "6x6", "7x7", "8x8", "9x9", "10x10", "11x11", "12x12" };
const char LETTERS[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };
char user1Mark = 'x';
char user2Mark = 'o';
stack<int> row;
stack<int> col;
char passedPath[12][12];
int start_row = 0;
int start_col = 0;

char board[12][12];
int heatmap[12][12] = { -1 };
int int_inputSize;
bool winner = false;

void DrawBoard();     // oyun tahtasýný yazdýr

void UpdateBoard();  // oyun tahtasýný güncelle ve yazdýr

bool inputSizeValidation(string inputSize);   // girilen boyut deðerini kontrol et

void ResetPath();

char PathFinder(char user_mark, char board[12][12], char passedPath[12][12]);

char Search(char user_mark);

char WhoisWon();

struct pos{
	int i;
	int j;
};

struct neighbour{
	int i[6] = { -1 };
	int j[6] = { -1 };
};

bool check_pos(pos d_pos, int d_size);

neighbour neighbours(pos pos1, int size);

neighbour bridge_ends(pos pos1, int size);

neighbour good_half_neighbour(pos pos1, int size);

pos SmartMove(char board[][12], pos pos1, int size);



int main(){
	bool control = true;
	string inputSize;
	char choosePlayer;
	char input[5];
	string move;
	string columns = "";
	string str_input;
	string inputColumn;
	string inputRow;
	int count = 0;
	bool valid1 = true;
	bool valid2 = true;
	int sat;
	int sut;
	char w;

	cout << "What will be the board size?" << endl
		<< "The board size can be 6x6, 7x7, 8x8, 9x9, 10x10, 11x11, or 12x12."
		<< endl << "Pleas enter the board size: ";
	cin >> inputSize;

	if (inputSizeValidation(inputSize)){
		while (control){             // oyuncu kontrolü  
			cout << endl << endl;
			cout << "Two Players(Press T) or Versus Computer(Press C)" << endl
				<< "Choose One:  ";
			cin >> choosePlayer;
			choosePlayer = tolower(choosePlayer);
			if (choosePlayer == 't' || choosePlayer == 'c')
				control = false;
			else
				control = true;
		}

		string Size = inputSize;
		string split = Size.substr(0, Size.find("x"));
		int_inputSize = stoi(split);
		for (int i = 0; i<int_inputSize; i++){
			columns = columns + LETTERS[i];
			for (int j = 0; j<int_inputSize; j++)
				heatmap[i][j] = 0;
		}
		DrawBoard();

		while (!winner){          // oyunculardan biri kazanana kadar devam et
			if (count % 2 == 0){  // birinci oyuncunun sýrasý
				valid1 = true;

				while (valid1){   // hareket doðru yapýlana kadar devam et
					cout << endl << "Make a move!" << endl;
					cout << "Use positions such as A 1, B 3, C 6, etc.";
					cout << endl << "User1 (X) Turn: ";
					getline(cin, str_input);
					if (str_input.length()>2 && str_input.length()<5){
						inputColumn = str_input.substr(0, str_input.find(" "));
						inputRow = str_input.substr(2, 2);

						if (inputColumn != "" && columns.find(inputColumn) != -1 && stoi(inputRow) > -1 && stoi(inputRow) < columns.length() + 1){
							sat = columns.find(inputColumn);
							sut = stoi(inputRow) - 1;
							if (board[sut][sat] == '.'){
								board[sut][sat] = user1Mark;
								count++;
								valid1 = false;
							}
							else
								cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;

							UpdateBoard();
							w = Search(user1Mark);
							if (w == 'x'){
								while (!row.empty() && !col.empty()){
									start_row = row.top();
									start_col = col.top();
									board[start_row][start_col] = toupper(user1Mark);
									row.pop();
									col.pop();
								}
								winner = true;
							}
						}
						else
							cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;
					}
					else
						cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;
				}
			}
			else{
				valid2 = true;
				if (choosePlayer == 'c'){  // vs Computer
					pos posX;
					posX.i = sut;
					posX.j = sat;
					pos position = SmartMove(board, posX, int_inputSize);
					board[position.i][position.j] = 'o';
					int aiMove_row = position.i + 1;
					char aiMove_col = LETTERS[position.j];
					cout << endl << "AI PLAY: " << aiMove_col << "   " << aiMove_row << endl;
					count++;
					UpdateBoard();
					w = Search(user2Mark);
					if (w == 'o'){
						while (!row.empty() && !col.empty()){
							start_row = row.top();
							start_col = col.top();
							board[start_row][start_col] = toupper(user2Mark);
							row.pop();
							col.pop();
						}
						winner = true;
					}

				}
				else{    // vs User2

					while (valid2){

						cout << endl << "Make a move!" << endl;
						cout << "Use positions such as A 1, B 3, C 6, etc.";
						cout << endl << "User2 (O) Turn: ";
						getline(cin, str_input);

						if (str_input.length()>2 && str_input.length()<5){
							inputColumn = str_input.substr(0, str_input.find(" "));
							inputRow = str_input.substr(2, 2);

							if (inputColumn != "" && columns.find(inputColumn) != -1 && stoi(inputRow)> -1 && stoi(inputRow)<columns.length() + 1){

								sat = columns.find(inputColumn);
								sut = stoi(inputRow) - 1;
								if (board[sut][sat] == '.'){
									board[sut][sat] = user2Mark;
									count++;
									valid2 = false;
								}
								else
									cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;

								UpdateBoard();
								w = Search(user2Mark);
								if (w == 'o'){
									while (!row.empty() && !col.empty()){
										start_row = row.top();
										start_col = col.top();
										board[start_row][start_col] = toupper(user2Mark);
										row.pop();
										col.pop();
									}
									winner = true;
								}
							}
							else
								cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;
						}
						else
							cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;
					}
				}

			}
		}
		if (winner){
			char won;
			cout << endl << endl << endl;
			UpdateBoard();
			won = WhoisWon();
			cout << endl << "<<<<<<  '" << won << "' PLAYER WON!!!! >>>>>" << endl;
		}
	}
	else
		cout << endl << "<<<<<<<< WRONG INPUT >>>>>>>" << endl;
	cin.get();
	return 0;
}

void DrawBoard(){           // oyun tahtasýný yazdýr
	for (int i = 0; i<int_inputSize; i++){
		cout << LETTERS[i] << " ";
	}
	cout << endl;
	for (int i = 0; i<int_inputSize; i++){
		for (int j = 0; j<int_inputSize; j++){
			board[i][j] = '.';
			cout << board[i][j] << " ";
		}
		cout << i + 1 << " " << endl;
		cout << string(i + 1, ' ');
	}
}

void UpdateBoard(){  // oyun tahtasýný güncelle ve yazdýr
	cout << endl << endl;

	for (int i = 0; i<int_inputSize; i++)
		cout << LETTERS[i] << " ";
	cout << endl;
	for (int i = 0; i<int_inputSize; i++){
		for (int j = 0; j<int_inputSize; j++)
			cout << board[i][j] << " ";

		cout << i + 1 << " " << endl;
		cout << string(i + 1, ' ');
	}
}

bool inputSizeValidation(string inputSize){   // girilen boyut deðerini kontrol et

	string size = inputSize;
	int lenght = sizeof(BOARD_SIZE) / sizeof(*BOARD_SIZE);
	for (int i = 0; i<lenght; i++){
		if (size == BOARD_SIZE[i])
			return true;
	}
	return false;

}

void ResetPath(){
	while (!row.empty())
		row.pop();
	while (!col.empty())
		col.pop();
	for (int i = 0; i<int_inputSize; i++){
		for (int j = 0; j<int_inputSize; j++)
			passedPath[i][j] = '.';
	}
}

char PathFinder(char user_mark, char board[12][12], char passedPath[12][12]){
	bool flag = true;
	bool control = true;
	while (control){
		if (board[start_row][start_col + 1] == user_mark && passedPath[start_row][start_col + 1] != 'p'){
			passedPath[start_row][start_col + 1] = 'p';
			start_col++;
			flag = true;
		}
		else if (board[start_row][start_col - 1] == user_mark && passedPath[start_row][start_col - 1] != 'p'){
			passedPath[start_row][start_col - 1] = 'p';
			start_col--;
			flag = true;
		}
		else if (board[start_row + 1][start_col] == user_mark && passedPath[start_row + 1][start_col] != 'p'){
			passedPath[start_row + 1][start_col] = 'p';
			start_row++;
			flag = true;
		}
		else if (board[start_row - 1][start_col] == user_mark && passedPath[start_row - 1][start_col] != 'p'){
			passedPath[start_row - 1][start_col] = 'p';
			start_row--;
			flag = true;
		}
		else if (board[start_row - 1][start_col + 1] == user_mark && passedPath[start_row - 1][start_col + 1] != 'p'){
			passedPath[start_row - 1][start_col + 1] = 'p';
			start_row--;
			start_col++;
			flag = true;
		}
		else if (board[start_row + 1][start_col - 1] == user_mark && passedPath[start_row + 1][start_col - 1] != 'p'){
			passedPath[start_row + 1][start_col - 1] = 'p';
			start_row++;
			start_col--;
			flag = true;
		}
		else{
			if (!row.empty() && !col.empty())
			{
				row.pop();
				col.pop();
				if (!row.empty() && !col.empty())
				{
					start_row = row.top();
					start_col = col.top();
				}
			}
			else
				control = false;
			flag = false;

		}
		if (flag){
			row.push(start_row);
			col.push(start_col);
			if (start_row == int_inputSize - 1 && user_mark == user1Mark)
			{
				return 'x';
			}
			else if (start_col == int_inputSize - 1 && user_mark == user2Mark)
			{
				return 'o';
			}

		}

	}
	return '.';
}

char Search(char user_mark){
	if (user_mark == user1Mark){
		for (int i = 0; i<int_inputSize; i++){
			if (board[0][i] == user_mark){
				ResetPath();
				start_row = 0;
				start_col = i;
				passedPath[start_row][start_col] = 'p';
				row.push(start_row);
				col.push(start_col);
				return PathFinder(user_mark, board, passedPath);
			}
		}

	}
	else
	{
		for (int i = 0; i<int_inputSize; i++){
			if (board[i][0] == user_mark){
				ResetPath();
				start_row = i;
				start_col = 0;
				passedPath[start_row][start_col] = 'p';
				row.push(start_row);
				col.push(start_col);
				return PathFinder(user_mark, board, passedPath);
			}
		}
	}
	return '.';
}

char WhoisWon(){
	char won;
	for (int i = 0; i<int_inputSize; i++){
		for (int j = 0; j<int_inputSize; j++){
			if (board[i][j] == 'X'){
				won = 'X';
				break;
			}
			else if (board[i][j] == 'O'){
				won = 'O';
				break;
			}
		}
	}
	return won;
}

bool check_pos(pos d_pos, int d_size){
	try{
		int pi = d_pos.i;
		int pj = d_pos.j;
		if (pi < 0 || pi >= d_size || pj < 0 || pj >= d_size)
			return false;
		else
			return true;
	}
	catch (string s){}
	return false;
}

neighbour neighbours(pos pos1, int size){
	int i = pos1.i;
	int j = pos1.j;
	pos p1;
	neighbour n1;
	int pi[6] = { i - 1, i - 1, i, i, i + 1, i + 1 };
	int pj[6] = { j, j + 1, j - 1, j + 1, j - 1, j };
	for (int i = 0; i < 6; i++){
		p1.i = pi[i];
		p1.j = pj[i];
		if (check_pos(p1, size)){
			n1.i[i] = pi[i];
			n1.j[i] = pj[i];
		}
	}
	return n1;
}

neighbour bridge_ends(pos pos1, int size){
	int i = pos1.i;
	int j = pos1.j;
	pos p1;
	neighbour n1;
	int bei[6] = { i + 2, i + 1, i + 1, i - 1, i - 1, i - 2 };
	int bej[6] = { j - 1, j - 2, j + 1, j - 1, j + 2, j + 1 };
	for (int i = 0; i < 6; i++){
		p1.i = bei[i];
		p1.j = bej[i];
		if (check_pos(p1, size)){
			n1.i[i] = bei[i];
			n1.j[i] = bej[i];
		}
	}
	return n1;
}

neighbour good_half_neighbour(pos pos1, int size){
	int i = pos1.i;
	int j = pos1.j;
	pos p1;
	neighbour n1;
	int bei[3] = { i + 1, i + 1, i };
	int bej[3] = { j - 1, j + 1, j + 1 };

	for (int i = 0; i < 3; i++){
		p1.i = bei[i];
		p1.j = bej[i];
		if (check_pos(p1, size)){
			n1.i[i] = bei[i];
			n1.j[i] = bej[i];
		}
	}
	return n1;
}

pos SmartMove(char board[][12], pos pos1, int size){
	neighbour n1 = neighbours(pos1, size);
	for (int i = 0; i<6; i++){
		if (n1.i[i] != -1 && n1.j[i] != -1)
			heatmap[n1.i[i]][n1.j[i]] = heatmap[n1.i[i]][n1.j[i]] + 5;
	}
	neighbour n2 = bridge_ends(pos1, size);
	for (int i = 0; i<6; i++){
		if (n2.i[i] != -1 && n2.j[i] != -1)
			heatmap[n2.i[i]][n2.j[i]] = heatmap[n2.i[i]][n2.j[i]] + 10;
	}
	neighbour n3 = good_half_neighbour(pos1, size);
	for (int i = 0; i<6; i++){
		if (n3.i[i] != -1 && n3.j[i] != -1)
			heatmap[n3.i[i]][n3.j[i]] = heatmap[n3.i[i]][n3.j[i]] + 7;
	}
	for (int i = 0; i<size; i++){
		for (int j = 0; j<size; j++){
			if (board[i][j] == 'x' || board[i][j] == 'o')
				heatmap[i][j] = 0;
		}
	}
	int max_i = 0;
	int max_j = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++){
			if (heatmap[max_i][max_j] < heatmap[i][j]){
				max_i = i;
				max_j = j;
			}
		}
	}
	pos p1;
	p1.i = max_i;
	p1.j = max_j;
	return p1;
	if (heatmap[max_i][max_j]<5){
		pos p2;
		bool randf = true;
		while (randf){
			int rand_i = rand() % size;
			int rand_j = rand() % size;
			if (board[rand_i][rand_j] == '.'){
				p2.i = rand_i;
				p2.j = rand_j;
				randf = false;
			}
		}
		return p2;

	}


}
