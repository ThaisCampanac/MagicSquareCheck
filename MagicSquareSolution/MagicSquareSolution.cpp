/*
 * Author: Thais Campanac-Climent
 * Date: October 2  , 2019
 * Module Name: Magic Square
 * Module Purpose: Reads a txt file and checks the magic square of the input by checking the horizontal
 * vertical elements and diagonal sums of the square given
 * INPUT:
 * magic.txt file
 * OUTPUT:
 * magicNumber
 * magicSquare
 * magicSum
 * The results of the magic square tests
 * isMagicSquare
 * */

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

//need to make a class that will organize the code for determining a magic circle
class MagicSquareClass {
public:
	int getMagicSum() { return magicSum; }
	int getMagicNumber() { return magicNumber; }

	void readFile(ifstream&);
	void setMagicNumber(int number);
	bool isMagicSquare(int sum);
	void printSquare();
private:
	vector<vector<unsigned>> inputedSquare;
	int magicNumber;
	int magicSum;

	bool checkElementSquare();
	bool checkRowsAndCol(int sum);
	bool checkDiags(int sum);
	void clearVector();
};

//this is the main class of the program
int main()
{
	MagicSquareClass magicSquareObj;
	//first open the file and see if there is a file to open or not and call a error if there isn't a file
	ifstream file("magic.txt");

	try {
		if (!file)
			throw system_error(errno, system_category(), "Fail to open file");
	}
	catch (const system_error& e) {
		cout << (e.what()) << " (" << (e.code()) << ")" << endl;
		cerr << "Press any key to end" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	//then go through the file to determine if there is any magic squares or not
	int n;
	while (file >> n) {
		magicSquareObj.setMagicNumber(n);
		cout << "-------------------------------------" << endl;
		cout << "The magic number is " << n << endl;
		magicSquareObj.readFile(file);
		magicSquareObj.printSquare();
		magicSquareObj.isMagicSquare(magicSquareObj.getMagicSum());
		cout << "the end of the square" << endl;
		system("pause");
		cout << "-------------------------------------" << endl;

	}

	file.close();
	cout << "The end of the file" << endl;
	system("pause");
	return 0;
}

//this is to initailize the vector and determine the values of the matrixes
void MagicSquareClass::readFile(ifstream& file) {
	magicSum = (magicNumber*((magicNumber*magicNumber) + 1)) / 2;
	int value = 0;
	for (int row = 0; row < magicNumber; row++) {
		for (int col = 0; col < magicNumber; col++) {
			file >> value;
			inputedSquare[row][col] = value;
		}
	}
}

//this is to print the values of the matrix and then call for if the matrix is a magic square or not
// need to make sure all the sizes are the same
void MagicSquareClass::printSquare() {
	for (int row = 0; row < magicNumber; row++) {
		for (int col = 0; col < magicNumber; col++) {
			cout << setw(3) << setfill('0') << inputedSquare[row][col] << " ";
		}
		cout << endl;
	}
}

//this calls the critera in determining a magic square and sees if it is a magic square or not
bool MagicSquareClass::isMagicSquare(int sum) {
	if (checkElementSquare()) {
		if (checkRowsAndCol(sum)) {
			if (checkDiags(magicSum)) {
				cout << "This is a magic square of " << magicNumber << " with the magic sum of " << magicSum << endl;
				cout << "-------------------------------------" << endl;
				clearVector();
				return true;
			}
			else {
				cout << "This is not a magic square of " << magicNumber << endl;
				cout << "-------------------------------------" << endl;
				clearVector();
				return false;
			}
		}
		else {
			cout << "This is not a magic square of " << magicNumber << endl;
			cout << "-------------------------------------" << endl;
			clearVector();
			return false;
		}
	}
	else {
		cout << "This is not a magic square of " << magicNumber << endl;
		cout << "-------------------------------------" << endl;
		clearVector();
		return false;
	}
}

//these functions give bool values as a way to indicate it a vector is a magic square
bool MagicSquareClass::checkRowsAndCol(int sum) {
	for (int same = 0; same < magicNumber; same++) {
		int rowSum = 0;
		int colSum = 0;
		for (int diff = 0; diff < magicNumber; diff++) {
			rowSum += inputedSquare[same][diff];
			colSum += inputedSquare[diff][same];
		}
		if (rowSum != sum) {
			cout << "The " << same + 1 << " row does not equal to the MagicSum" << endl;
			return false;
		}
		else if (colSum != sum) {
			cout << "The " << same + 1 << " col does not equal to the MagicSum" << endl;
			return false;
		}
	}
	return true;
}

//this function checks the diagnals of the magic square
bool MagicSquareClass::checkDiags(int sum) {
	int dia1 = 0;
	int dia2 = 0;
	for (int pos = 0; pos < magicNumber; pos++) {
		dia1 += inputedSquare[pos][pos];
		dia2 += inputedSquare[pos][(magicNumber - pos) - 1];
	}
	if (dia1 != sum || dia2 != sum) {
		cout << "One of the diagonals does not equal to the magic sum" << endl;
		return false;
	}
	return true;
}

//this function gives a bool var depending if the elements of magic square
bool MagicSquareClass::checkElementSquare() {
	int problem = 0;
	int inputtedSize = magicNumber * magicNumber;
	vector<int> range;
	range.resize(inputtedSize, 0);

	//check
	for (int row = 0; row < magicNumber; row++) {
		for (int col = 0; col < magicNumber; col++) {
			if (inputedSquare[row][col] > (inputtedSize)) {
				cout << inputedSquare[row][col] << " is greater than the magic number squared which is " << inputtedSize << endl;
				problem++;
			}
			//checking if all elements from 1 to inputtedSize are in the square
			if (1 <= inputedSquare[row][col] && inputedSquare[row][col] <= inputtedSize) {
				int pos = inputedSquare[row][col] - 1;
				range[pos] = range[pos] + 1;
			}
		}
	}

	//make an vector and checking what numbers are in the vector and you need to order them
	for (int pos = 0; pos < range.size(); pos++) {
		//        if(range[pos]>1){
		if (range[pos] > 1) {
			cout << "The number " << (pos + 1) << " is not a unique number, repeated" << range[pos] << "times" << endl;
			problem++;
		}
		if (range[pos] < 1) {
			cout << "The number " << (pos + 1) << " is not a number in the magic square but should be" << endl;
			problem++;
		}
	}

	if (problem > 0) {
		return false;
	}
	return true;
}

//this function clears the capacity of the perivous vector once the square is cleared
void MagicSquareClass::clearVector() {
	inputedSquare.clear();
	vector<vector<unsigned>>(inputedSquare).swap(inputedSquare);
}

void MagicSquareClass::setMagicNumber(int number) {
	magicNumber = number;
	inputedSquare.resize(magicNumber, vector<unsigned>(magicNumber, 0));
}