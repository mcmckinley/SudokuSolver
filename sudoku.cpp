#include<iostream>
#include<vector>
#include<cmath>
#include<array>
using namespace std;

bool solved = false;
int numberOfIterations = 0;
int sudoku[81] = {5, 0, 0,  6, 7, 0,  9, 0, 0,
                  0, 4, 0,  8, 0, 0,  0, 0, 0,
                  8, 0, 0,  5, 0, 0,  6, 1, 3,
              
                  0, 6, 2,  4, 0, 0,  0, 7, 0,
                  1, 0, 0,  0, 0, 3,  0, 2, 0, 
                  3, 7, 4,  9, 0, 8,  0, 0, 0,
              
                  0, 9, 6,  1, 0, 7,  8, 0, 2, 
                  2, 1, 8,  0, 0, 6,  0, 4, 5,
                  0, 5, 0,  0, 8, 0,  0, 9, 0};

//int sudoku[81] = 
  // {0, 0, 0, 0, 0, 0, 0, 0, 0,
   // 0, 0, 0, 0, 0, 3, 0, 8, 5,
   // 0, 0, 1, 0, 2, 0, 0, 0, 0,
   // 0, 0, 0, 5, 0, 7, 0, 0, 0,
   // 0, 0, 4, 0, 0, 0, 1, 0, 0,
   // 0, 9, 0, 0, 0, 0, 0, 0, 0,
   // 5, 0, 0, 0, 0, 0, 0, 7, 3,
   // 0, 0, 2, 0, 1, 0, 0, 0, 0,
   // 0, 0, 0, 0, 4, 0, 0, 0, 9};


bool indexKnown[81] = {true};
int currentCell = -1;

void displaySudoku(int sudoku[81]){
    for (int h = 0; h < 9; h++) {
        for (int i = 0; i < 9; i++) {
            cout << sudoku[i + h*9];
            if (i%3 ==2) {
                cout << " ";
            }
        }
        cout << "\n";
        if (h%3 == 2){
            cout << "\n";
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
    return (floor(row/3)*3)+floor(column/3);
}
// determine if the current cell in its current
// state has any contradictions.
// int cell - the ID of the cell to be checking
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
    cell = originalCell;
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
    for (int i=0; i<81; i++){
        indexKnown[i] = !(sudoku[i]==0);
    }
    findNextCell();
    while (!solved){
        sudoku[currentCell]++;

        while (contradicts(currentCell)) {
            sudoku[currentCell]++;
        } 
        //cout << "passing thru line 199\n";
        if (sudoku[currentCell] < 10) {
            findNextCell();
        } else {
            // if no valid solution exists, clear the cell and backtrack
            sudoku[currentCell] = 0;
            findPreviousCell();
        }
    }
    cout << "FINAL SUDOKU:" << endl;
    displaySudoku(sudoku);
    return 0;
}