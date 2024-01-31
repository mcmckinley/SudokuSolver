#include<iostream>

bool solved = false;
bool indexKnown[81] = {true};
int currentCell = -1;


int sudoku[81] = {5, 0, 0,  6, 7, 0,  9, 0, 0,
                  0, 4, 0,  8, 0, 0,  0, 0, 0,
                  8, 0, 0,  5, 0, 0,  6, 1, 3,
              
                  0, 6, 2,  4, 0, 0,  0, 7, 0,
                  1, 0, 0,  0, 0, 3,  0, 2, 0, 
                  3, 7, 4,  9, 0, 8,  0, 0, 0,
              
                  0, 9, 6,  1, 0, 7,  8, 0, 2, 
                  2, 1, 8,  0, 0, 6,  0, 4, 5,
                  0, 5, 0,  0, 8, 0,  0, 9, 0};



// This sudoku is designed to beat backtracking algorithms
/*
int sudoku[81] = 
   {0, 0, 0,  0, 0, 0,  0, 0, 0,
    0, 0, 0,  0, 0, 3,  0, 8, 5,
    0, 0, 1,  0, 2, 0,  0, 0, 0,

    0, 0, 0,  5, 0, 7,  0, 0, 0,
    0, 0, 4,  0, 0, 0,  1, 0, 0,
    0, 9, 0,  0, 0, 0,  0, 0, 0,

    5, 0, 0,  0, 0, 0,  0, 7, 3,
    0, 0, 2,  0, 1, 0,  0, 0, 0,
    0, 0, 0,  0, 4, 0,  0, 0, 9};
*/

void displaySudoku(int sudoku[81]){
    for (int h = 0; h < 9; h++) {
        for (int i = 0; i < 9; i++) {
            std::cout << sudoku[i + h*9];
            if (i%3 ==2) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
        if (h%3 == 2){
            std::cout << "\n";
        }
    }
}

void findNextCell() {
    currentCell++;
    if (currentCell==81){
        solved = true;
        return;
    }
    while(indexKnown[currentCell]){
        currentCell++;
    }
}
void findPreviousCell() {
    currentCell--;
    while(indexKnown[currentCell]){
        currentCell--;
    }
}

int findRowID(int cell){
    return floor(cell/9);
}
int findClmID(int cell){
    return cell%9;
}
int findBoxID(int cell){
    int column = findClmID(cell);
    int row = findRowID(cell);
    // Tricky mathematical operation that returns a box number, given a column and row
    return (floor(row/3)*3)+floor(column/3);
}

// determine if the value at the current cell contradicts with its neighbors.
// int cell - the ID of the cell to be checking; this param gets modified
bool contradicts (int cell){
    //cout << "checking if "<<sudoku[currentCell]<< " in " << currentCell;
    //cout << " contradicts\n";
    if (sudoku[cell]==10){
        return false;
    }
    
    int originalCell = cell;
    // 1 - search for contradiction in the current row
    for (int i=0; i<8; i++){
        cell--;
        if ((cell+1)%9==0){
            cell+=9;
        }
        //cout << "comparing " << cell << " and " << currentCell;
        //cout << " avoiding " << originalCell << endl;
        if (sudoku[cell] == sudoku[currentCell]){
            return true;
        }
    }

    // 2 - search for contradiction in the current column
    cell = originalCell;
    for (int i=0; i<8; i++){
        cell+=9;
        if (cell>80){
            cell-=81;
        }
        if (sudoku[cell] == sudoku[currentCell]){
            return true;
        }
    }

    // 3 - search for contradictions in the current box
    int boxToAvoid = originalCell;
    // starts at the top left corner:
    cell = ((floor(findBoxID(cell)/3))*27) + (findBoxID(cell)%3)*3;
    for (int i=0; i<3; i++){ 
        for (int j=0; j<3; j++){
            if (sudoku[cell] == sudoku[currentCell] && cell != boxToAvoid){
                return true;
            }
            cell++;
        }
        cell+=6;
    }
    return false;
}

int main() {
    // Create an array of bools that indicate whether any given index 
    // is already known.
    for (int i=0; i<81; i++){
        indexKnown[i] = !(sudoku[i]==0);
    }

    // Begin the program at the first unknown index
    findNextCell();
    while (!solved){
        // Increment the value until it doesn't contradict with its neighbors
        do {
            sudoku[currentCell]++;
        } while (contradicts(currentCell));

        // If the value at the current index is valid, continue.
        // If all possible options have been exhuasted, clear the cell and backtrack
        if (sudoku[currentCell] < 10) {
            findNextCell();
        } else {
            sudoku[currentCell] = 0;
            findPreviousCell();
        }
    }
    std::cout << "FINAL SUDOKU:" << std::endl;
    displaySudoku(sudoku);
    return 0;
}