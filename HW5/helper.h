#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <utility>

namespace SaribasCSE241{

	using std::ostream;
	using std::exception;
	using std::cout;
	using std::endl;
	using std::string;
	using std::vector;
	using std::stack;
	using std::pair;

	enum State { Empty = '.', X_player = 'x', O_player = 'o', upperO = 'O', upperX = 'X'};

	const string colLetters = "ABCDEFGHIJ";

	void couts(int user);
	string getColumns(int boardSize);
	char StatetoChar(State temp);
	void resetPath(stack<pair<int, int>> &stackPos, char passedPath[][10], int boardsize);
	bool checkPosition(int row, int col, int boardsize);
}