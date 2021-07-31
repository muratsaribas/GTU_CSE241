#ifndef HEX_H
#define HEX_H
#include <string>
#include <stack>
using namespace std;
class Hex
{
public:
	class Cell;
	
	Hex();								
	explicit Hex(int boardSizeT);		// explicit conversion
	Hex(int boardSizeT, char GameType); 

	//Big three
	Hex(const Hex &other);
	Hex& operator =(const Hex& rightSide);
	~Hex();

	inline static int getnumOfLiveHexClass() { return numOfLiveHexClass; } // mevcut oynanabilen oyun sayýsý döndürür
	inline char getGameType() const{ return this->gameType; }			   // oyun tipi döndürür
	inline int getBoardSize() const{ return this->boardSize; }			   // tahta boyutunu döndürür	
	inline int getWidth() const{ return getBoardSize(); }
	inline int getHeight() const{ return getBoardSize(); }
	inline bool isEndGame() const{ return this->isWon; }				   // oyunu kazanan biri var mý?
	inline string getsaveFile() const{ return this->saveFile; }			   
	inline string getloadFile() const{ return this->loadFile; }
	inline bool getUndo() const{ return this->undo; }
	inline int getscoreX() const{ return this->scoreX; }
	inline int getscoreO() const{ return this->scoreO; }
	inline bool getearlyStop() const{ return this->earlyStop; }

	struct Position{ int row; int col; };

	void DrawBoard() const;	// tahtayý yazdýr			
	void StartGame(); 		// oyunu baþlat
	void PlayGame();		// 1 adým oyna(hangi oyuncunun oynayacaðýna fonksiyon içerisinde karar veriliyor)

	void couts(int &User) const;
	Position inputMove(int &user);

	char getCellMark(int &i, int &j) const;


	Hex & operator--();              // --prefix  (undo)
	Hex & operator--(int dummy);     // postfix-- (undo)
	friend ostream & operator<<(ostream &out, const Hex &hex); // save
	friend istream & operator>>(istream &in, Hex &hex);		   // load	
	friend bool operator==(Hex &hex1, Hex &hex2); // **overload operator== (compare)

private:
	Cell ** hexCells = nullptr;
	
	int boardSize;
	char gameType;
	
	bool isWon = false;
	
	static const string colLetters;
	static int numOfLiveHexClass;
	stack<int> allMoves; 		

	int scoreX = 0;
	int scoreO = 0;

	string saveFile = "";
	string loadFile = "";
	bool undo = false;
	bool earlyStop = false;

	int turn = 1;        // 1 = user1orCOM, 2 = user2
	int useR = 0;
	Position pos;
	enum States { Empty = '.', X_is_here = 'x', O_is_here = 'o' };


	void createBoard();				  //
	void setBoardSize(int boardSize); //
	int boardsize() const; 			  //
	string boardSizeVal() const;      //

	char twoPlayerOrPC() const;		  //
	void setGameType(char type);	  //
	string getColumns(int &boardSize) const;

	void play(); 				   // COM 1 adým oynar
	bool play(Position position);  // user 1 adým oynar
	bool playO(Position position); // user 1 adým oynar

	void resetPath(stack<Position> stackPos, char passedPath[][12]) const;
	bool checkPosition(int row, int col) const;
	void pathFinder(char passedPath[][12], stack<Position> stackPos, int row, int col, char mark);
	void searchAlgorith(int &user);

	void createHeatmap(int heatmap[][12], int &row, int &col) const;

};


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
	inline int getCellRow() const{ return this->row; }
	inline char getCellCol() const{ return this->col; }
	inline char getCellMark() const{ return this->mark; }

private:
	int row;
	char col;
	char mark;
};



#endif
