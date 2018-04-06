// MatrixSimplexCalculator.cpp : Defines the entry point for the console application.

#include <iostream>
#include <math.h>

using namespace std;

void enterMatrix(double**, int, int);
void appendIdentity(double**, int, int, int);
void enterConstraintSolutions(double**, int, int, int);

int findMinimumColumn(double**, int, int, int);
int findMinimumRow(double**, int, int, int, int);

void scaleMatrixRow(double**, int, int, int);
void addRowMultiple(double**, int, int, int, int, int);

int main()
{
	int row, column, equation;	//enter rows and columns
	bool isEquationValid = false;
	while (!isEquationValid)
	{
		cout << "Enter the number of variables: ";
		cin >> equation;
		if (equation >= 2)
			isEquationValid = true;
		else
			cout << "Error, you must have at least two variables." << endl;
	}

	//make room for extra rows and variables according to the simplex
	row = equation + 1;
	column = equation + row + 1;


	double **tableux = new double*[row];
	for (int i = 0; i < row; i++)
	{
		tableux[i] = new double[column];
	}
	// set matrix to 0 matrix.
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			//tableux[i][j] = 0;
			tableux[i][j] = -i*j;
		}
	}

	//enterMatrix(tableux, row, equation);

	//appendIdentity(tableux, equation, row, column);

	//enterConstraintSolutions(tableux, equation, row, column);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << tableux[i][j] << "\t";
		}
		cout << endl;
	}



	int minCol, minRow;
	while (findMinimumColumn(tableux, equation, row, column) < 0)
	{
		minCol = findMinimumColumn(tableux, equation, row, column);
		minRow = findMinimumRow(tableux, equation, row, column, minCol);
		scaleMatrixRow(tableux, minRow, minCol, column);

		for (int i = 0; i < row; i++)
		{
			if (i == minRow)
				continue;
			else
				addRowMultiple(tableux, minRow, minCol, row, column, i);
		}
		//write pivot matrix formulas
	}
	//write extraction and return functions.

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << tableux[i][j] << "\t";
		}
		cout << endl;
	}


	for (int i = 0; i < row; i++)
	{
		delete[] tableux[i];
	}
	delete[] tableux;
	system("pause");
	return 0;
}

void enterMatrix(double** a, int row, int rawColumns)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rawColumns; j++)
		{
			cout << "Enter element " << j + 1 << " of row " << i + 1 << " : ";
			cin >> a[i][j];
		}
	}
}

void appendIdentity(double** a, int rawColumns, int rows, int columns)
{
	int counter = 0;
	while (counter < rows)
	{
		a[counter][rawColumns] = 1;
		rawColumns++;
		counter++;
	}
}

void enterConstraintSolutions(double** a, int rawColumns, int rows, int columns)
{
	int solutionColumn = columns - 1;	//you want the last column in your matrix.
	for (int i = 0; i < rows - 1; i++)
	{
		cout << "Enter the solution for equation " << i + 1 << " : ";
		cin >> a[i][solutionColumn];
	}
}

int findMinimumColumn(double** a, int equation, int rows, int columns)
{
	int solutionRow = --rows;
	int minColumn = 0;
	double minVal = a[solutionRow][minColumn];

	for (int i = 0; i < equation; i++)
	{
		if (a[solutionRow][i] < minVal)
		{
			minColumn = i;
			minVal = a[solutionRow][i];
			cout << "\nMinVal is : " << minVal << "\nminCol is " << minColumn << endl;
		}
	}
	return minColumn;
}

int findMinimumRow(double** a, int equation, int rows, int columns, int minCol)
{
	int minRow;
	double minVal = numeric_limits<int>::max();
	int lastColumn = --columns;
		for (int i = 0; i < rows; i++)
		{
			if (abs(a[i][minCol] / a[i][lastColumn]) < minVal)
			{
				minRow = i;
				minVal = abs(a[i][minCol] / a[i][lastColumn]);
			}
		}
	return minRow;
}

void scaleMatrixRow(double** a, int minRow, int minCol, int numCols)
{
	double scalingFactor = a[minRow][minCol];

	for (int i = 0; i < numCols; i++)
	{
		a[minRow][i] /= scalingFactor;
	}
}

void addRowMultiple(double** a, int minRow, int minCol, int numRows, int numCols, int currentRow)
{
	double scaleFactor = a[currentRow][minCol];

	double *tempRow = new double[numCols];
	for (int i = 0; i < numCols; i++)
	{
		tempRow[i] = a[minRow][i];
		tempRow[i] *= scaleFactor;
	}
	for (int i = 0; i < numCols; i++)
	{
		a[currentRow][i] -= tempRow[i];
	}
}