#include <iostream>



namespace SaribasCSE241{


	const string colLetters = "ABCDEFGHIJKL";

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
		string columns;
		for (int i = 0; i<boardSize; i++)
			columns = columns + colLetters[i];
		return columns;
	}

}