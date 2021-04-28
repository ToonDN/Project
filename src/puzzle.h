#include <stdio.h>
#include <math.h>

class Puzzle
{	
public:
	void load(int arr[10][10]);
	void clear();
	bool solve();
	bool isSolved(int arr[10][10]);

private:
    int puzzle[10][10];

	bool identicalRows(int arr[10][10]);
	bool areRowsSolved(int arr[10][10]);
    int countUnsolved();

	int base3(int arr[10]);
	void base3ToArr(int num, int arr[10]);
	void brute();
	void rowBruteAll(int arr[10][10]);
	void rowBrute(int arr[10], int solved[10], int duplicateCheckArr[10]);
	void getCommonIndexes(int* arr, int numberOfRows, bool result[10]);
	bool isRowValid(int arr[10], bool solved=false);
	void transpose(int input[10][10], int transpose[10][10]);
	void print(bool clean=true, int arr[10][10] = NULL);
	void printRow(int index, bool column=false);


};