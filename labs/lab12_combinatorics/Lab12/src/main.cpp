#include <iostream>
#include <ctime>

// Lab 12
int solution_count = 0;

int *rowsUsed, *mainDiagonalsUsed, *antiDiagonalsUsed, *queenPositions, boardSize;

void findQueens(int col){
    for (int row = 0; row < boardSize; row++){
        int mainDiagInd = col - row + (boardSize - 1);
        int antiDiagInd = col + row;

        if (rowsUsed[row] == 0 && mainDiagonalsUsed[mainDiagInd] == 0 && antiDiagonalsUsed[antiDiagInd] == 0){
            rowsUsed[row] = 1;
            mainDiagonalsUsed[mainDiagInd] = 1; 
            antiDiagonalsUsed[antiDiagInd] = 1;
            queenPositions[col] = row;
            
            if (col == boardSize - 1){
                solution_count++;
                /*for (int row_i = 0; row_i < boardSize; row_i++){
                    for (int col_i = 0; col_i < boardSize; col_i++){
                        if (queenPositions[col_i] == row_i) { std::cout << "Q "; }
                        else { std::cout << ". "; }
                    }
                    printf("\n");
                }   
                printf("\n");*/
            } else { findQueens(col + 1); }

            rowsUsed[row] = 0;
            mainDiagonalsUsed[mainDiagInd] = 0;
            antiDiagonalsUsed[antiDiagInd] = 0;
        }
    }
}

void v_lob_i_tupo(char **matrix, int n, int row) {
    if (row == n){
        solution_count++;
        /*printf("Solutions: %d \n", solution_count);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                printf("%c ", matrix[i][j]);
            }
            printf("\n");
        }*/
    }

    for (int col = 0; col < n; col++) {
        bool is_safe_for_queen = true;

        for (int i = 1; i <= row; i++) {
            if (matrix[row - i][col] == 'Q') { is_safe_for_queen = false; break; }
            if (col - i >= 0 && matrix[row - i][col - i] == 'Q'){ is_safe_for_queen = false; break; }
            if (col + i < n && matrix[row - i][col + i] == 'Q'){ is_safe_for_queen = false; break; }
        }

        if (is_safe_for_queen) {
            matrix[row][col] = 'Q';
            v_lob_i_tupo(matrix, n, row + 1);
            matrix[row][col] = '.';
        }
    }
}

int main() {
    if (!(std::cin >> boardSize)){
        printf("Error! \n");
        return 1;
    }
    char **matrix;
    int diagSize = 2*boardSize - 1;
    rowsUsed = new int[boardSize]; queenPositions = new int[boardSize];
    mainDiagonalsUsed = new int[diagSize]; antiDiagonalsUsed = new int[diagSize];
    for (int i = 0; i < boardSize; i++){ rowsUsed[i] = 0; queenPositions[i] = 0; }
    for (int i = 0; i < diagSize; i++){ mainDiagonalsUsed[i] = 0; antiDiagonalsUsed[i] = 0; }

    matrix = new char*[boardSize];
    for (int i = 0; i < boardSize; i++){
        matrix[i] = new char[boardSize];
    }
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            matrix[i][j] = '.';
        }
    }
    clock_t t1 = clock();
    findQueens(0);
    clock_t t2 = clock();
    double dur1 = double(t2 - t1) / CLOCKS_PER_SEC;
    printf("findQueens time: %.6f s\n", dur1);
    printf("Solutions for N=%d: %d\n", boardSize, solution_count);
    printf("|-------------------------------------------------| \n");

    solution_count = 0;
    clock_t t3 = clock();
    v_lob_i_tupo(matrix, boardSize, 0);
    clock_t t4 = clock();
    double dur2 = double(t4 - t3) / CLOCKS_PER_SEC;
    printf("v_lob_i_tupo time: %.6f s\n", dur2);
    printf("\nSolutions for N=%d: %d\n", boardSize, solution_count);
    if (dur2 > 0.0) {
        printf("Ratio (findQueens / v_lob_i_tupo): %.6f\n", dur1 / dur2);
    } else {
        printf("Ratio (findQueens / v_lob_i_tupo): INF (second duration is zero)\n");
    }
    
    for (int i = 0; i < boardSize; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] rowsUsed; delete[] queenPositions;
    delete[] mainDiagonalsUsed; delete[]antiDiagonalsUsed;
    return 0;
}