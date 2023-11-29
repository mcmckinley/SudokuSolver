
// easy sudoku 
var easy =   [5, 0, 0,  6, 7, 0,  9, 0, 0,
              0, 4, 0,  8, 0, 0,  0, 0, 0,
              8, 0, 0,  5, 0, 0,  6, 1, 3,
              
              0, 6, 2,  4, 0, 0,  0, 7, 0,
              1, 0, 0,  0, 0, 3,  0, 2, 0, 
              3, 7, 4,  9, 0, 8,  0, 0, 0,
              
              0, 9, 6,  1, 0, 7,  8, 0, 2, 
              2, 1, 8,  0, 0, 6,  0, 4, 5,
              0, 5, 0,  0, 8, 0,  0, 9, 0];

// hard sudoku
var hard =   [7, 4, 3,  5, 0, 0,  0, 6, 2,
              0, 5, 0,  1, 0, 0,  4, 0, 0,
              0, 0, 0,  0, 6, 4,  5, 0, 0,
                    
              9, 6, 0,  0, 7, 0,  0, 0, 5,
              0, 0, 0,  0, 4, 0,  0, 0, 0, 
              4, 0, 0,  0, 5, 0,  8, 0, 1,
            
              5, 0, 0,  0, 0, 0,  0, 0, 0, 
              3, 2, 0,  0, 0, 0,  6, 0, 0,
              0, 0, 9,  6, 8, 0,  0, 5, 0];


// a sudoku designed to be difficult for backtracking algos
var impossible = [0, 0, 0,  0, 0, 0,  0, 0, 0,
              0, 0, 0,  0, 0, 3,  0, 8, 5,
              0, 0, 1,  0, 2, 0,  0, 0, 0,

              0, 0, 0,  5, 0, 7,  0, 0, 0,
              0, 0, 4,  0, 0, 0,  1, 0, 0,
              0, 9, 0,  0, 0, 0,  0, 0, 0,

              5, 0, 0,  0, 0, 0,  0, 7, 3,
              0, 0, 2,  0, 1, 0,  0, 0, 0,
              0, 0, 0,  0, 4, 0,  0, 0, 9];


// Here, determine which difficulty you want it to run. // 

var sudoku = easy.slice();
//var sudoku = hard.slice();
//var sudoku = impossible.slice();



// display the sudoku to be solved
console.log("INITIAL SUDOKU:");
displaySudoku(sudoku);
const startDate = new Date();


// list that tells you which items are known and unknown
var givens = [];
for (var i=0; i<81; i++){
  if (sudoku[i] != 0){
    givens.push("given");
  } else {
    givens.push("unknown");
  }
}


// begin at the first unknown cell
var currentCell = -1;
findNextCell();

// initiate relevant cells
var relevantCells = returnAllRelevantCells(
      currentCell,
      findRowID(currentCell),
      findClmID(currentCell),
      findBoxID(currentCell)
    );

var numberOfIterations = 0;
var solved = false;

while (!solved) {
    numberOfIterations++;
    // identify all cells in the same row/clm/box as our target cell
    relevantCells = returnAllRelevantCells(
      currentCell, findRowID(currentCell), findClmID(currentCell), findBoxID(currentCell)
      ); 

  // increase value of cell until it creates no contradiction
  sudoku[currentCell]++;
  while ((contradicts(sudoku[currentCell])) ) {
    sudoku[currentCell]++;
  } 
  
  //once it's valid, move on to the next cell
  if (sudoku[currentCell] < 10){
    findNextCell();
    if (currentCell == 81) {
        break;
    }
  } else {
    // if no valid solution exists, clear the cell and backtrack
    sudoku[currentCell] = 0;
    findPreviousCell();
  }
}


console.log("FINAL SUDOKU:");
displaySudoku(sudoku);
const endDate = new Date;
console.log('number of iterations ' + numberOfIterations )
console.log("time elapsed: "+((endDate-startDate)/1000)+"s");
console.log(Math.floor(numberOfIterations/((endDate-startDate)/1000))+" iterations per second");


// FUNCTIONS
// find the next cell
function findNextCell() {
  currentCell++;
  while ((givens[currentCell] == "given")){
    currentCell++;
  }
}
function findPreviousCell() {
  currentCell--;
  while (givens[currentCell] == "given") {
    currentCell--;
  }
}

// returns the all cell IDs of a given row, column or box.
// cell - the cell to check
// row, clm. box - the IDs of the structures of the cell to check
function returnAllRelevantCells(cell, row, clm, box) {
  var cellList = [];
  for (var L=0; L<81; L++){
    if ((findRowID(L)== row ||
         findClmID(L) == clm ||
         findBoxID(L) == box)
         && (L != cell)){
      cellList.push(L);
    }
  }
  return cellList;
}

// TODO: Update the contradicts function with the same optimizations made
// in the C++ version.

// determine if the value contradicts
function contradicts(currentCellValue) {
  for (var k = 0; k<24; k++){
    if (currentCellValue == sudoku[(relevantCells[k])]){
          return true;
    }
  }
  return false;
}


// return ID of the structure in which a given cell resides
function findRowID(cell) {
  return (Math.floor(cell/9));
}
function findClmID(cell) {
  return cell%9;
}

// TODO: Give this the same optimizations found in the C++ version.
function findBoxID(cell) {
  var column = findClmID(cell);
  var row =    findRowID(cell);
  if (column < 3 && row < 3) {
    return 0;
  } else if (column < 6 && row < 3) {
    return 1;
  } else if (row < 3) {
    return 2;
  } else if (column < 3 && row < 6) {
    return 3;
  } else if (column < 6 && row < 6) {
    return 4;
  } else if (row < 6) {
    return 5;
  } else if (column < 3) {
    return 6;
  } else if (column < 6) {
    return 7;
  } else {
    return 8;
  }
}

// display a sudoku to the console
function displaySudoku(list) {
  for (var h = 0; h < 9; h++) {
    var row = [];
    for (var i = 0; i < 9; i++) {
      row.push(list[i + (h*9)]);
      if ((i+1)%3==0){
        row.push(" ");
      }
    }
    console.log(row.join(""));
    if ((h+1)%3 == 0){
      console.log(" ");
    }
  }
}