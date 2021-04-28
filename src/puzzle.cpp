#include <stdio.h>
#include <math.h>
#include "puzzle.h"

//*  Rules
//*  - Can't have 3 or more consecutive numbers
//*  - Final result must contain same amount of 0 as 1 in each row and column
//*  - No identical rows or columns

void *memcpy(void *dest, const void *src, size_t len)
{
	char *d = static_cast<char *>(dest);
	const char *s = (char *)src;
	while (len--)
		*d++ = *s++;
	return dest;
}

void Puzzle::load(int arr[10][10])
{
	memcpy(puzzle, arr, 10 * 10 * sizeof(int));
}

void Puzzle::clear()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			puzzle[i][j] = 2;
		}
	}
}

bool Puzzle::solve()
{
	// Solved the puzzle

	// Get the current count of unsolved spaces in the puzzle
	int currentCount = countUnsolved();
	int prevCount;

	// Bruteforce row method until this has no effect
	do
	{
		prevCount = currentCount;
		brute();
		currentCount = countUnsolved();
	} while (prevCount > currentCount);

	return true;
}

bool Puzzle::isSolved(int arr[10][10])
{
	// Return true if the puzzle is completely solved
	int copy[10][10];
	memcpy(copy, puzzle, 10 * 10 * sizeof(int));

	if (areRowsSolved(copy) && !identicalRows(copy))
	{
		transpose(arr, copy);
		if (areRowsSolved(copy) && !identicalRows(copy))
		{
			return true;
		}
	}

	return false;
}

bool Puzzle::identicalRows(int arr[10][10])
{
	// Return true if there are identical rows in the puzzle
	int rows[10];
	for (int i = 0; i < 10; i++)
	{
		rows[i] = base3(arr[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (rows[i] == rows[j] and i != j)
			{
				return true;
			}
		}
	}
	return false;
}

bool Puzzle::areRowsSolved(int arr[10][10])
{
	// Return true if all rows are solved
	for (int i = 0; i < 10; i++)
	{
		if (!isRowValid(arr[i], true))
		{
			return false;
		}
	}
	return true;
}

int Puzzle::countUnsolved()
{
	// Return the number of unsolved places
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (puzzle[i][j] == 2)
			{
				count++;
			}
		}
	}
	return count;
}

int Puzzle::base3(int arr[10])
{
	// Convert the row to base 3
	// This is done by multiplying this the x-th character by 3^x
	// Since the characters can only be 0, 1 and 2 this will return a unique int for a unique row
	unsigned int hash = 0;
	for (int i = 0; i < 10; i++)
	{
		int res = pow(3, i) * arr[i];
		hash += res;
	}
	return hash;
}

void Puzzle::base3ToArr(int num, int arr[10])
{
	// Convert base 3 back to a row and store it in the pointer passed in the arr argument
	for (int i = 0; i < 10; i++)
	{
		int x = pow(3, i);
		arr[i] = (num / x) % 3;
	}
}

void Puzzle::brute()
{
	// Perform the bruteforcerow method on all rows and columns

	// Rows
	rowBruteAll(puzzle);

	// Columns
	int copy[10][10];
	memcpy(copy, puzzle, 10 * 10 * sizeof(int));
	transpose(copy, puzzle);
	rowBruteAll(puzzle);

	// Transpose back
	memcpy(copy, puzzle, 10 * 10 * sizeof(int));
	transpose(copy, puzzle);
}

void Puzzle::rowBruteAll(int arr[10][10])
{
	//* Array to check for duplicate rows, elements are base 3
	int rows[10];
	for (int i = 0; i < 10; i++)
	{
		rows[i] = base3(arr[i]);
	}

	for (int rowIndex = 0; rowIndex < 10; rowIndex++)
	{
		// Remove the current row from the duplicate row checker
		int rowsCopy[10];
		memcpy(rowsCopy, rows, 10 * sizeof(int));
		rowsCopy[rowIndex] = -1;

		int solved[10];
		rowBrute(arr[rowIndex], solved, rowsCopy);

		for (int i = 0; i < 10; i++)
		{
			puzzle[rowIndex][i] = solved[i];
		}
	}
}

void Puzzle::rowBrute(int arr[10], int solved[10], int duplicateCheckArr[10])
{
	memcpy(solved, arr, 10 * sizeof(int));

	int emptyAmount = 0;
	int emptyIndexes[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	for (int columnIndex = 0; columnIndex < 10; columnIndex++)

	//* Get empty indexes and amount of empties
	{

		if (arr[columnIndex] == 2)
		{
			emptyIndexes[emptyAmount] = columnIndex;
			emptyAmount++;
		}
	}

	//* Iterate over all possible combinations and add to array if row is valid

	int numberOfPermutations = pow(2, emptyAmount);

	int *validRows = new int[numberOfPermutations];
	int numberOfValidRows = 0;

	for (int i = 0; i < numberOfPermutations; i++)
	{
		// Convert decimal number to array of binaries
		int decimalValue = i;
		int rowCopy[10];
		memcpy(rowCopy, arr, 10 * sizeof(int));

		int values[emptyAmount];
		for (int j = 0; j < emptyAmount; j++)
		{
			values[j] = decimalValue % 2;
			decimalValue = decimalValue / 2;
		}

		// The array of binaries can be used to fill in the empties
		// Ex.	if there are 3 empties
		//		101 will fill the first empty with 1, second with 0, third with 1
		// This ensures all possible permutations are checked
		for (int valueIndex = 0; valueIndex < emptyAmount; valueIndex++)
		{
			int value = values[valueIndex];
			int index = emptyIndexes[valueIndex];
			rowCopy[index] = value;
		}

		// Check if the row is valid, meaning it contains no 3 consecutive characters
		// and contains no more than 3 consecutive 0's or 1's
		if (isRowValid(rowCopy))
		{
			int encoded = base3(rowCopy);
			bool duplicate = false;

			// Check if the row is a duplicate of an already existing row using the duplicateCheckArr
			for (int duplicateIndex = 0; duplicateIndex < 10; duplicateIndex++)
			{
				if (duplicateCheckArr[duplicateIndex] == encoded)
				{
					duplicate = true;
					break;
				}
			}

			// Add the row to the validRows array if it is not considered a duplicate
			if (!duplicate)
			{
				validRows[numberOfValidRows] = encoded;
				numberOfValidRows++;
			}
		}
	}

	// Get common values for each index, if all validRows contain the same value at a
	// specific index for all the rows in validRows, this is guaranteed to be the correct value
	bool commonIndexes[10];
	getCommonIndexes(validRows, numberOfValidRows, commonIndexes);

	// Fill in the characters that are guaranteed te be correct
	int validRow[10];
	base3ToArr(validRows[0], validRow);
	for (int i = 0; i < 10; i++)
	{
		if (commonIndexes[i])
		{
			solved[i] = validRow[i];
		}
		else
		{
			solved[i] = 2;
		}
	}
}

void Puzzle::getCommonIndexes(int *arr, int numberOfRows, bool result[10])
{
	// Input arr is an array ith base 3 encoded rows

	// Return an an array of booleans, true if all the rows in arr contains the same
	// value at a specific index

	if (sizeof(arr) == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			result[i] = false;
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			result[i] = true;
			int x = pow(3, i);
			int previous = (arr[0] / x) % 3;
			for (int rowIndex = 1; rowIndex < numberOfRows; rowIndex++)
			{
				int current = (arr[rowIndex] / x) % 3;
				if (current != previous)
				{
					result[i] = false;
					break;
				}
				else
				{
					previous = current;
				}
			}
		}
	}
}

bool Puzzle::isRowValid(int arr[10], bool solved = false)
{
	// Check if row contains 5 or more 0's or 1's or
	// contains 3 or more consecutive 0's or 1's

	// If solved is true it will only return true if the row
	// contains exactly 5 0's and 1's

	int nums[3] = {0, 0, 0};
	for (int i = 0; i < 10; i++)
	{
		nums[arr[i]]++;
	}

	// Check for 5 or more 0's or 1's
	if (solved)
	{
		if (nums[0] != 5 or nums[1] != 5)
		{
			return false;
		}
	}
	else
	{
		if (nums[0] > 5 or nums[1] > 5)
		{
			return false;
		}
	}

	// Check if more than 3 of same type are consecutive
	for (int i = 1; i < 9; i++)
	{
		if (arr[i] != 2 && arr[i - 1] == arr[i] && arr[i + 1] == arr[i])
		{
			return false;
		}
	}

	return true;
}

void Puzzle::transpose(int input[10][10], int transpose[10][10])
{
	// Transpose the input matrix and store in in the transpose argument

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			transpose[j][i] = input[i][j];
		}
	}
}

void Puzzle::print(bool clean = true, int arr[10][10] = NULL)
{
	// Print the puzzle, replace 0's by _ if clean is true
	// Another puzzle can also be passed in, by default it will print
	// the array stored in the class variable puzzle

	if (arr == NULL)
	{
		arr = puzzle;
	}

	for (int i = 0; i < 10; i++)
	{
		char string[20];
		for (int j = 0; j < 10; j++)
		{
			if (arr[i][j] == 2 && clean)
			{
				printf("_");
			}
			else
			{

				printf("%i", arr[i][j]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

void Puzzle::printRow(int index, bool column = false)
{
	// Print row or column at specific index

	if (column)
	{
		printf("Column %i|  ", index);
		for (int i = 0; i < 10; i++)
		{
			if (puzzle[i][index] == 2)
			{
				printf("_ ");
			}
			else
			{
				printf("%i ", puzzle[i][index]);
			}
		}
	}
	else
	{
		printf("Row %i: ", index);
		for (int i = 0; i < 10; i++)
		{
			if (puzzle[index][i] == 2)
			{
				printf("_ ");
			}
			else
			{
				printf("%i ", puzzle[index][i]);
			}
		}
	}
	printf("\n");
}
