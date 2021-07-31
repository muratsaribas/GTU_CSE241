#include <iostream>
#include "Hex.h"
using namespace std;

int main()
{
	int scoreX = 0;
	int scoreO = 0;
	cout << "||||||||| Welcome to the MyHex Game. |||||||||\n";
	cout << "where '.' represents the empty cells, \n"
		<< "'x' represents the computer(user1) cells \nand 'o' represents the user (user2) cells. \n";
	cout << "The 'x' player must create a connected path between the right and left sides to win.\n";
	cout << "The 'o' player must create a connected path between the up and down sides to win.\n\n\n";
	Hex hex1;
	Hex hex2 = (Hex)7; //Explicit conversion
	Hex hex3(6, 'c');
	Hex hex4(hex1);
	Hex hex5(6, 't');

	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex1 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex1.StartGame();											
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex2 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex2.StartGame();
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex3 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex3.StartGame();
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex4 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex4.StartGame();
	cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
	cout << "||||||||| hex5 game started |||||||||\n";
	cout << "|||||||||||||||||||||||||||||||||||||\n\n";
	hex5.StartGame();

	cout << "numOfLiveHexClass: " << Hex::getnumOfLiveHexClass() << endl;

	while (Hex::getnumOfLiveHexClass()>0) 	// t�m oyunlar sonlanana kadar devam et
	{

		if (!hex1.isEndGame()) 		// hex1 oyunu bitmediyse ger�ekle�tir
		{
			cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
			cout << "||||||||| HEX1 GAME |||||||||||||||||\n";
			cout << "|||||||||||||||||||||||||||||||||||||\n\n";
			hex1.DrawBoard();									// tahtay� yazd�r
			hex1.PlayGame();
			if (hex1.getsaveFile() != "")						// saveFile de�i�keninin i�i bo� de�il ise SAVE komutu girilmi� demektir
				cout << hex1;									// operator<< ile save i�lemi ger�ekle�tirilir
			else if (hex1.getloadFile() != "")					// loadFile de�i�keninin i�i bo� de�il ise LOAD komutu girilmi� demektir
				cin >> hex1;									// operator>> ile load i�lemi ger�ekle�tirilir
			else if (hex1.getUndo()){							// getUndo() true d�nd�rm�� ise UNDO komutu girilmi� demektir
				hex1--;											// --prefix veya postfix-- operat�rleri ile undo i�lemi ger�ekle�tirilir
				cout << "<<<<< UNDO >>>>>" << endl;
			}
			else if (hex1.getearlyStop())						// getearlyStop() true d�nd�rm�� ise EARLYSTOP komutu girilmi� demektir
			{													
				scoreX = hex1.getscoreX(); 						// 'x' oyuncusu i�in hesaplanan skoru getirir
				scoreO = hex1.getscoreO();						// 'o' oyuncusu i�in
				cout << "scoreX: " << scoreX << "    scoreO: " << scoreO << endl;
				if (scoreX > scoreO)
				{
					cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
				}
				else if (scoreX < scoreO)
				{
					cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
				}
				else
				{ 			
					int random = rand() % 2;
					if (random == 0)
					{
						cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
					}
					else
					{
						cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
					}
				}
			}
			cout << "HEX1: " << hex1.isEndGame()      // oyunlar�n mevcut durumunu g�sterir
				<< ", HEX2: " << hex2.isEndGame()     // 1 ise oyun bitmi� demektir
				<< ", HEX3: " << hex3.isEndGame()     // 0 ise oyun hala devam ediyordur
				<< ", HEX4: " << hex4.isEndGame()
				<< ", HEX5: " << hex5.isEndGame() << endl;
		}
		if (!hex2.isEndGame())
		{
			cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
			cout << "||||||||| HEX2 GAME |||||||||||||||||\n";
			cout << "|||||||||||||||||||||||||||||||||||||\n\n";
			hex2.DrawBoard();
			hex2.PlayGame();
			if (hex2.getsaveFile() != "")
				cout << hex2;
			else if (hex2.getloadFile() != "")
				cin >> hex2;
			else if (hex2.getUndo()){
				hex2--;
				cout << "<<<<< UNDO >>>>>" << endl;
			}
			else if (hex2.getearlyStop())
			{
				scoreX = hex2.getscoreX();
				scoreO = hex2.getscoreO();
				cout << "scoreX: " << scoreX << "    scoreO: " << scoreO << endl;
				if (scoreX > scoreO)
				{
					cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
				}
				else if (scoreX < scoreO)
				{
					cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
				}
				else
				{
					int random = rand() % 2;
					if (random == 0)
					{
						cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
					}
					else
					{
						cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
					}
				}
			}
			cout << "HEX1: " << hex1.isEndGame()
				<< ", HEX2: " << hex2.isEndGame()
				<< ", HEX3: " << hex3.isEndGame()
				<< ", HEX4: " << hex4.isEndGame()
				<< ", HEX5: " << hex5.isEndGame() << endl;
			bool comp = (hex1 == hex2);
			cout << "hex1 == hex2: " << comp << endl;
		}
		if (!hex3.isEndGame())
		{
			cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
			cout << "||||||||| HEX3 GAME |||||||||||||||||\n";
			cout << "|||||||||||||||||||||||||||||||||||||\n\n";
			hex3.DrawBoard();
			hex3.PlayGame();
			if (hex3.getsaveFile() != "")
				cout << hex3;
			else if (hex3.getloadFile() != "")
				cin >> hex3;
			else if (hex3.getUndo()){
				--hex3;
				cout << "<<<<< UNDO >>>>>" << endl;
			}
			else if (hex3.getearlyStop())
			{
				scoreX = hex3.getscoreX();
				scoreO = hex3.getscoreO();
				cout << "scoreX: " << scoreX << "    scoreO: " << scoreO << endl;
				if (scoreX > scoreO)
				{
					cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
				}
				else if (scoreX < scoreO)
				{
					cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
				}
				else
				{
					int random = rand() % 2;
					if (random == 0)
					{
						cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
					}
					else
					{
						cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
					}
				}
			}
			cout << "HEX1: " << hex1.isEndGame()
				<< ", HEX2: " << hex2.isEndGame()
				<< ", HEX3: " << hex3.isEndGame()
				<< ", HEX4: " << hex4.isEndGame()
				<< ", HEX5: " << hex5.isEndGame() << endl;
			cout << "hex1 == hex3: " << (hex1 == hex3) << endl;
			cout << "hex2 == hex3: " << (hex2 == hex3) << endl;
		}
		if (!hex4.isEndGame())
		{
			cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
			cout << "||||||||| HEX4 GAME |||||||||||||||||\n";
			cout << "|||||||||||||||||||||||||||||||||||||\n\n";
			hex4.DrawBoard();
			hex4.PlayGame();
			if (hex4.getsaveFile() != "")
				cout << hex4;
			else if (hex4.getloadFile() != "")
				cin >> hex5;
			else if (hex4.getUndo()){
				--hex4;
				cout << "<<<<< UNDO >>>>>" << endl;
			}
			else if (hex4.getearlyStop())
			{
				scoreX = hex4.getscoreX();
				scoreO = hex4.getscoreO();
				cout << "scoreX: " << scoreX << "    scoreO: " << scoreO << endl;
				if (scoreX > scoreO)
				{
					cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
				}
				else if (scoreX < scoreO)
				{
					cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
				}
				else
				{
					int random = rand() % 2;
					if (random == 0)
					{
						cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
					}
					else
					{
						cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
					}
				}
			}
			cout << "HEX1: " << hex1.isEndGame()
				<< ", HEX2: " << hex2.isEndGame()
				<< ", HEX3: " << hex3.isEndGame()
				<< ", HEX4: " << hex4.isEndGame()
				<< ", HEX5: " << hex5.isEndGame() << endl;
			cout << "hex1 == hex4: " << (hex1 == hex3) << endl;
			cout << "hex2 == hex4: " << (hex2 == hex4) << endl;
			cout << "hex3 == hex4: " << (hex3 == hex4) << endl;
		}
		if (!hex5.isEndGame())
		{
			cout << endl << "|||||||||||||||||||||||||||||||||||||\n";
			cout << "||||||||| HEX5 GAME |||||||||||||||||\n";
			cout << "|||||||||||||||||||||||||||||||||||||\n\n";
			hex5.DrawBoard();
			hex5.PlayGame();
			if (hex5.getsaveFile() != "")
				cout << hex5;
			else if (hex5.getloadFile() != "")
				cin >> hex5;
			else if (hex5.getUndo()){
				hex5--;
				cout << "<<<<< UNDO >>>>>" << endl;
			}
			else if (hex5.getearlyStop())
			{
				scoreX = hex5.getscoreX();
				scoreO = hex5.getscoreO();
				cout << "scoreX: " << scoreX << "    scoreO: " << scoreO << endl;
				if (scoreX > scoreO)
				{
					cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
				}
				else if (scoreX < scoreO)
				{
					cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
				}
				else
				{
					int random = rand() % 2;
					if (random == 0)
					{
						cout << endl << "||||||  'X' PLAYER WON!!!  " << "scoreX: " << scoreX << "    |||||| \n";
					}
					else
					{
						cout << endl << "||||||  'O' PLAYER WON!!!  " << "scoreO: " << scoreO << "    |||||| \n";
					}
				}
			}
			cout << "HEX1: " << hex1.isEndGame()
				<< ", HEX2: " << hex2.isEndGame()
				<< ", HEX3: " << hex3.isEndGame()
				<< ", HEX4: " << hex4.isEndGame()
				<< ", HEX5: " << hex5.isEndGame() << endl;
			cout << "hex1 == hex5: " << (hex1 == hex5) << endl;
			cout << "hex2 == hex5: " << (hex2 == hex5) << endl;
			cout << "hex3 == hex5: " << (hex3 == hex5) << endl;
			cout << "hex4 == hex5: " << (hex4 == hex5) << endl;
		}
	}

}
