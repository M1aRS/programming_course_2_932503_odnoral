#include <iostream>
#include <cstdio>
#include <cmath>

// Lab 13

/*void print_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.3lf ", matrix[i][j]);
        }
        printf("\n");
    }
}*/

void print_matrix_to_file(FILE* out, double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(out, "%.3lf ", matrix[i][j]);
            printf("%.3lf ", matrix[i][j]);
        }
        fprintf(out, "\n");
        printf("\n");
    }
    fprintf(out, "--------------------------\n");
    printf("----- \n");
}

int triangularize(double **matrix, int rows, int cols) {
    for (int i = 0; i < cols-1; i++) {
        int v = i;
        for (int j = i + 1; j < rows; j++) {
            if (std::abs(matrix[j][i]) > std::abs(matrix[v][i])) {
                v = j;
            }
        }

        if (std::abs(matrix[v][i]) < 1e-12) {
            return -1; //матрица вырождена
        }

        if (v != i){
            for (int k = i; k < cols; k++){
                double temp = matrix[i][k];
                matrix[i][k] = matrix[v][k];
                matrix[v][k] = temp;
            }
        }

        for (int k = i + 1; k < rows; k++) {
            double factor = matrix[k][i]/matrix[i][i];
            for (int j = i; j < cols; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    } //ttestasdfc

    for (int i = cols; i < rows; i++){
        if (std::abs(matrix[i][cols-1]) > 1e-12) {
            return 0; //матрица несовместна
        }
    }

    return 1; //матрица невырождена и совместна
}

/*void solve_and_print(double **matrix, int rows, int cols) {
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
}*/

void solve_and_write_roots(FILE* out, double **matrix, int rows, int cols) {
    int n = rows; 
    double *x = new double[n];
    fprintf(out, "Roots:\n");
    for (int i = n - 1; i >= 0; i--) {
        x[i] = matrix[i][cols - 1];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
        x[i] /= matrix[i][i]; 
    }

    for (int i = 0; i < n; i++) {
        fprintf(out, "x%d = %.2lf", i + 1, x[i]);
        printf("x%d = %.2lf\n", i + 1, x[i]);
        if (i < n - 1) fprintf(out, "  "); 
    }
    fprintf(out, "\n");

    delete[] x;
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == nullptr) {
        printf("Error! \n");
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

    
    int status = triangularize(coeffitients, M, N);
    fprintf(output_file, "Triangular Matrix:\n");
    print_matrix_to_file(output_file, coeffitients, M, N);

    if (status == 1){
        solve_and_write_roots(output_file, coeffitients, M, N);
    }
    else if (status == 0){
        printf("Inconsistent system \n");
        fprintf(output_file, "Inconsistent system \n");
    }
    else if (status == -1){

    }
    
    for (int i = 0; i < M; i++) delete[] coeffitients[i];
    delete[] coeffitients;

    fclose(input_file);
    fclose(output_file);
    return 0;
}
