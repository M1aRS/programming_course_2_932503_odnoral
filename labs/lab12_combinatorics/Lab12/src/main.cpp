#include <iostream>

// Lab 12
void v_lob_i_tupo(char **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '.') { 
                matrix[i][j] = 'X';   

                for (int k = 1; i + k < n; k++) {
                    matrix[i + k][j] = '~';
                    if (j + k < n) matrix[i + k][j + k] = '~';
                    if (j - k >= 0) matrix[i + k][j - k] = '~';
                }

                for (int l = j + 1; l < n; l++) {
                    matrix[i][l] = '~';
                }
                break; 
            }
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

    v_lob_i_tupo(matrix, N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){    
                printf("%2c ", matrix[i][j]);
            }
            printf("\n");
    }
    return 0;
}
