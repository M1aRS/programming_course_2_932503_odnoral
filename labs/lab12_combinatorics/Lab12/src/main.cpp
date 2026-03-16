#include <iostream>

// Lab 12
int solution_count = 0;

void v_lob_i_tupo(char **matrix, int n, int row) {
    if (row == n){
        solution_count++;
        printf("Solutions: %d \n", solution_count);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                printf("%c ", matrix[i][j]);
            }
            printf("\n");
        }
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
    int N;
    if (!(std::cin >> N)){
        printf("Error! \n");
        return 1;
    }
    char **matrix;
    matrix = new char*[N];
    for (int i = 0; i < N; i++){
        matrix[i] = new char[N];
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrix[i][j] = '.';
        }
    }

    v_lob_i_tupo(matrix, N, 0);
    printf("\nSolutions for N=%d: %d\n", N, solution_count);
    for (int i = 0; i < N; i++) delete[] matrix[i];
    delete[] matrix;
    
    return 0;
}
