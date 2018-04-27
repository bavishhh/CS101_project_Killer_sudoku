#include <iostream>
using namespace std;

/* each cage will be assigned a unique id.
 * the cells array for each cage will contain the id of the cells belonging to the cage.
 * capacity of the cage = no of cells
 * cell id = row*10 + col (where row is the row number and col is the column number of the cell)
 * each cell will have a unique cell id.
 * each cage will have a unique id which equals the index of the cage in the array of cages.
 */
struct cage
{
	int sum, capacity;
	int cells[];
};

/* If a cell is not assigned any number, then value = 0.
 * each cell will have cage_id, i.e. the id of the cage to which the cell belongs
 */
struct cell {
	int value;
	int cage_id;
	
	//constructor
	cell() {
		value = 0;
	}
} Board[9][9];
 

bool solve_sudoku(cage[]);
void print_board();
bool isSafe(cage[], int, int, int);
bool isCageFilled(cage);
bool isCageSumSatisfied(cage);

int main() {

	//read input
	int no_of_cages;
	cin>>no_of_cages;
	cage Cage[no_of_cages];

	for (int cage_id = 0; cage_id<no_of_cages; cage_id++) {

		int cage_sum, no_of_cells;
		cin >> no_of_cells >> cage_sum;

		Cage[cage_id].sum = cage_sum;
		Cage[cage_id].capacity = no_of_cells;

		for (int j=0; j<no_of_cells; j++) {
			int row, col;
			cin >> row >> col;

			Cage[cage_id].cells[j] = row*10 + col;
			Board[row][col].cage_id = cage_id;

		}

	}

	if(solve_sudoku(Cage)) {
		print_board();
	}
	else {
		
	}
    
	return 0;
}

/* Searches the grid to find a cell that is still unassigned.
 * Sets the reference parameters row and col to the row and column of this cell
 * returns false if no such cell is found.
 */
bool FindEmptyCell(int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (Board[row][col].value == 0)
                return true;
    return false;
}

bool solve_sudoku(cage Cage[])
{
    int row, col;
    if(!FindEmptyCell(row, col)) return true;
    cage currentCage = Cage[Board[row][col].cage_id];
        
    for (int num=1; num<=9; num++) {
        if (isSafe(Cage, row, col, num)) {
            Board[row][col].value = num;
            
            if (isCageSumSatisfied(currentCage)){
                
                solve_sudoku(Cage);
            }
        }
        Board[row][col].value = 0;
    }
    return false;

}



/* Returns true if there is no conflict in the row while assigning a number
 * returns false if the number is already used.
 */
bool UsedInRow(int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (Board[row][col].value == num)
            return true;
    return false;
}


/* Returns true if there is no conflict in the column while assigning a number
 * returns false if the number is already used.
 */
bool UsedInCol(int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (Board[row][col].value == num)
            return true;
    return false;
}


/* Returns a boolean which indicates whether any assigned entry
 * within the specified 3x3 box matches the given number.
 */
bool UsedInBox(int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (Board[row+boxStartRow][col+boxStartCol].value == num)
                return true;
    return false;
}


/*Returns a true if the number is already present in the cage
   Else returns false
*/
bool UsedInCage(cage Cage, int num)
{
    int no_of_cells = Cage.capacity  ;
    for(int cell=0; cell < no_of_cells; cell++)
    {
         int row = Cage.cells[cell]/10 ;
         int col = Cage.cells[cell]%10 ;
            if(Board[row][col].value == num )
                return true ;
    }
    return false ;
}


/* Returns a boolean which indicates whether it will be legal to assign
 * num to the given row,col location.
 */
bool isSafe(cage Cage[], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    int cage_id = Board[row][col].cage_id;
    return !UsedInRow(row, num) &&
           !UsedInCol(col, num) &&
           !UsedInBox(row - row%3 , col - col%3, num) &&
           !UsedInCage(Cage[cage_id], num) ;
}


void print_board()
{
    for(int row=0 ; row<9 ; row++)
    {
        for(int col=0 ; col<9 ; col++)
            cout<<Board[row][col].value <<" " ;
        cout<<"\n" ;
    }
}


/* checks whether the sum of all the cells in a cage
 * equals the cage sum and returns true if it is.
 * Returns true if the cage is not yet filled.
 * else returns false
 */
bool isCageSumSatisfied(cage Cage) {
	if (!isCageFilled(Cage)) return true;
	int sum = 0, row, col;
	for (int cell=0; cell<Cage.capacity; cell++) {
		row = Cage.cells[cell]/10;
		col = Cage.cells[cell]%10;
		sum += Board[row][col].value;
	}
	if (sum == Cage.sum)
		return true;
	else
		return false;
}


/* Checks whether all the cells in a particular cage are filled.
 * returns true if they are filled
 * else returns false
 */
bool isCageFilled(cage Cage) {
	int row, col;
	for (int cell=0; cell<Cage.capacity; cell++) {
		row = Cage.cells[cell]/10;
		col = Cage.cells[cell]%10;
		if (Board[row][col].value == 0)
			return false;
	}
	return true;
}

