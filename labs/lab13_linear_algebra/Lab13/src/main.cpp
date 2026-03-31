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

void print_matrix_to_file(FILE* out, double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(out, "%.3lf ", matrix[i][j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "--------------------------\n");
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

void solve_and_print(double **matrix, int rows, int cols) {
    int n = cols - 1;
    double *x = new double[n];

    for (int i = n - 1; i >= 0; i--) {
        x[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }
    printf("Result:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2lf\n", i + 1, x[i]);
    }

    delete[] x; 
}

void solve_and_write_roots(FILE* out, double **matrix, int rows, int cols) {
    int n = rows; 
    double *x = new double[n];

    for (int i = n - 1; i >= 0; i--) {
        x[i] = matrix[i][cols - 1];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }

    for (int i = 0; i < n; i++) {
        fprintf(out, "x%d = %.2lf", i + 1, x[i]);
        if (i < n - 1) fprintf(out, "  "); 
    }
    fprintf(out, "\n");

    delete[] x;
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

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
    fprintf(output_file, "Triangular Matrix:\n");
    print_matrix_to_file(output_file, coeffitients, M, N);

    print_matrix(coeffitients, M, N);
    solve_and_print(coeffitients, M, N);

    fprintf(output_file, "Roots:\n");
    solve_and_write_roots(output_file, coeffitients, M, N);
    
    for (int i = 0; i < M; i++) delete[] coeffitients[i];
    delete[] coeffitients;

    fclose(input_file);
    fclose(output_file);
    return 0;
}
