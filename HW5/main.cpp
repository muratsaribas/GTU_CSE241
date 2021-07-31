#include "HexVector.h"
#include "HexArray1D.h"

using namespace SaribasCSE241;
using namespace std;


int main(){

	HexVector hex1;
	HexVector hex2(5);
	HexVector hex3(5,'c');
	HexArray1D hex4;
	HexArray1D hex5(5, 'c');

	AbstractHex * ptr[] = { &hex1, &hex2, &hex3, &hex4, &hex5 };
	

	cout << "|||||||| test - readFromFile ||||||||\n";
	hex4.readFromFile("7.TXT");
	hex4.print();

	cout << "|||||||| test - setSize ||||||||\n";
	hex4.setSize(6);
	hex4.print();

	cout << "|||||||| test - writeToFile ||||||||\n";
	hex4.writeToFile("test.TXT");

	cout << "|||||||| test - operator() ||||||||\n";
	hex4.readFromFile("7.TXT");
	hex4.print();
	
	try{
		cout << "Cell Content: " << hex4.operator()(1, 1) << endl;
	}
	catch (HexVector_Exception& e){
		cout << e.out_of_range() << endl;
	}
	
	for (AbstractHex * hex : ptr)
	{
		(*hex).print();
		do
		{
			try{
				(*hex).play();
				string pos = (*hex).inputMove();
				(*hex).play(pos);
				cout << "Last Move:" << (*hex).lastMove() << "----" << (*hex).numberOfMoves() << endl;
			}
			catch (exception ex){
				cout << ex.what();
			}
			
		} while (!(*hex).isEnd());
	}

	return 0;
}