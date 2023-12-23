#include<iostream>
#include<vector>
using namespace std;

void Display_Board(int array[9][9])
{
	cout << "--------------------------------" << endl;
	cout << "             SUDOKU             " << endl;
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;

	}
	cout << "--------------------------------" << endl;

}
//Whether we can put a number or not using same row,same col and same 3X3 subgrid rule
bool Placeyn(int array[9][9], int row, int col, int num)
{
	if (array[row][col] != 0)
	{
		return (false);
	}
	bool check = true;
	//no. of cell in 3X3 grid
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;

	for (int i = 0; i < 9; i++)
	{
		if(array[row][i]==num)
		{
			check = false;
			break;
		}
		if (array[i][col] == num)
		{
			check = false;
			break;
		}
		if (array[gridy + i / 3][gridx + 1 % 3] == num)
		{
			check = false;
			break;
		}
	}
	return check;

}
//to find possible numbers that can be placed in a specific cell based on then current state

vector<int> find(int array[9][9], int row, int col)
{
	vector<int> pyn = {};
	for (int i = 1; i <= 9; i++)
	{
		if (Placeyn(array, row, col, i))
		{
			pyn.push_back(i);
		}
	}
	return pyn;
}
//Copying the array
void Copyarr(int array[9][9], int arrayCPY[9][9])
{
	for (int s = 0; s < 9; s++)
	{
		for (int r = 0; r < 9; r++)
		{
			arrayCPY[s][r] = array[s][r];
		}

	}
}
// check for the next empty cell
void nextdimension(int array[9][9], int row, int col, int &rownxt, int &colnxt)
{
	int index = 9 * 9;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++)
	{
		if (array[i / 9][i % 9] == 0)
		{
			index = i;
			break;
		}
	}
	rownxt = index / 9;
	colnxt = index % 9;
}

//Recursive function
bool Solve(int array[9][9], int rows, int cols)
{
	if (rows > 8)
	{
		return true;
	}
	if (array[rows][cols] != 0)
	{
		int rownxt, colnxt;
		nextdimension(array, rows, cols, rownxt, colnxt);
		return ( Solve(array, rownxt, colnxt));


	}
	vector<int> allowed = find(array, rows, cols);
	if (allowed.size() == 0)
	{
		return false;
	}
	bool check = false;
	//Backtracking
	//allowed denotes the possible numbers to place in a cell
	for (int i = 0; i < allowed.size(); i++)
	{
		int num = allowed[i];
		int arrayCPY[9][9];
		Copyarr(array, arrayCPY);
		arrayCPY[rows][cols] = num;
		int rownxt, colnxt;
		nextdimension(arrayCPY, rows, cols, rownxt, colnxt);


		if (Solve(arrayCPY, rownxt, colnxt))
		{
			Copyarr(arrayCPY, array);
			check = true;
			break;
		}
		
	}


	return check;
}

int main()
{

	int board[9][9] = { { 5,3,0,0,7,0,0,0,0},
	                    { 6,0,0,1,9,5,0,0,0},
						{ 0,9,8,0,0,0,0,6,0},
						{ 8,0,0,0,6,0,0,0,3},
						{ 4,0,0,8,0,3,0,0,1},

						{ 7,0,0,0,2,0,0,0,6},
						{ 0,6,0,0,0,0,2,8,0},
						{ 0,0,0,4,1,9,0,0,5},
						{ 0,0,0,0,8,0,0,7,9}};

	Display_Board(board);
	Solve(board, 0, 0);
	Display_Board(board);




	return 0;
}