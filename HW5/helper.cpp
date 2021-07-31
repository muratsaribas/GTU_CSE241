#include "helper.h"

namespace SaribasCSE241{

	void couts(int user)
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

	string getColumns(int boardSize)
	{
		string columns = "";
		for (int i = 0; i<boardSize; i++)
			columns = columns + colLetters[i];
		return columns;
	}

	char StatetoChar(State temp){
		char st;
		switch (temp) {
		case Empty:
			st = '.';
			break;
		case X_player:
			st = 'x';
			break;
		case O_player:
			st = 'o';
			break;
		case upperO:
			st = 'O';
			break;
		case upperX:
			st = 'X';
			break;
		}
		return st;
	}

	void resetPath(stack<pair<int, int>> &stackPos, char passedPath[][10], int boardsize){
		while (!stackPos.empty())
			stackPos.pop();
		for (int i = 0; i < boardsize; i++)
		{
			for (int j = 0; j < boardsize; j++)
				passedPath[i][j] = '.';
		}
	}

	bool checkPosition(int row, int col, int boardsize) {
		if (row < 0 || row >= boardsize || col < 0 || col >= boardsize)
			return false;
		else
			return true;

	}

	

}