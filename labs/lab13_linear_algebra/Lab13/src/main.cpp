#include <iostream>
#include <cstdio>
#include <cmath>

// Lab 13

void print_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.3lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void triangularize(double **matrix, int rows, int cols) {
    for (int k = 0; k < rows; k++) {
        int max_row = k;
        for (int i = k + 1; i < rows; i++) {
            if (std::abs(matrix[i][k]) > std::abs(matrix[max_row][k])) {
                max_row = i;
            }
        }

        double *temp = matrix[k];
        matrix[k] = matrix[max_row];
        matrix[max_row] = temp;

        if (std::abs(matrix[k][k]) < 1e-12) {
            continue; 
        }

        double element = matrix[k][k];
        for (int j = k; j < cols; j++) {
            matrix[k][j] /= element;
        }

        for (int i = k + 1; i < rows; i++) {
            double factor = matrix[i][k];
            for (int j = k; j < cols; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            matrix[i][k] = 0;
        }
    }
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    if (input_file == nullptr) {
        std::cout << "Error!" << std::endl;
        return 1;
    }
    int M, N;
    fscanf(input_file, "%d %d", &M, &N);
    double **coeffitients = new double *[M];
    N+=1;
    for (int i = 0; i < M; i++) {
        coeffitients[i] = new double[N];
        for (int j = 0; j < N; j++) {
            fscanf(input_file, "%lf", &coeffitients[i][j]);
        }
    }

    print_matrix(coeffitients, M, N);
    printf("----- \n");
    triangularize(coeffitients, M, N);
    print_matrix(coeffitients, M, N);
    fclose(input_file);
    return 0;
}
