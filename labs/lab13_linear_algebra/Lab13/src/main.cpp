#include <iostream>
#include <cstdio>
#include <cmath>

// Lab 13

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

int triangularize(double **matrix, int rows, int cols, double *X, int *L, int &r) {
    for (int i = 0; i < cols; i++) L[i] = i;

    if (cols < rows) { r = cols; }
    else { r = rows; } // ?? r =  (cols < rows) ? cols : rows

    int i = 0; 

    while (i < r) {
        int v = i, u = i;
        double max_val = 0;

        for (int j = i; j < rows; j++){
            for (int k = i; k < cols; k++){
                if (std::abs(matrix[j][k]) > max_val){
                    max_val = std::abs(matrix[j][k]);
                    v = j; u = k; // столбец и строка максимума
                }
            }
        }

        if (max_val < 1e-12){
            r = i; 
            break;
        }

        if (v != i){
            for (int k = i; k < cols; k++){
                double temp = matrix[i][k];
                matrix[i][k] = matrix[v][k];
                matrix[v][k] = temp;
            }
        }

        if (u != i){
            for (int k = 0; k < rows; k++){
                double temp = matrix[k][i];
                matrix[k][i] = matrix[k][u];
                matrix[k][u] = temp;
            }
            int tempL = L[i];
            L[i] = L[u];
            L[u] = tempL;
        }

        double c = matrix[i][i];
        for (int j = i; j <= cols; j++){
            matrix[i][j] /= c;
        }

        for (int k = 0; k < rows; k++){
            if (k != i){
                double factor = matrix[k][i];
                for (int j = i; j <= cols; j++) matrix[k][j] -= factor * matrix[i][j];
            }
        }
        i++;
    }

    int check_i = r;
    while (check_i < rows && std::abs(matrix[check_i][rows]) < 1e-12) check_i++;
    if (check_i < rows) return 0; //система не совместима

    if (r == cols) { // в этом случае решение одно-единственное
        for (int j = 0; j < cols; j++) X[L[j]] = matrix[j][cols];
        return 1;
    } else {
        for (int k = r; k < cols; k++) X[L[k]] = L[k];

        for (int j = 0; j < r; j++){
            X[L[j]] = matrix[j][cols];
            for (int k = r; k < cols; k++) X[L[j]] -= matrix[j][k] * X[L[k]];
        }
    }
}

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

    double *X = new double[N];
    int *L = new int[N];
    int r = 0;

    int status = triangularize(coeffitients, M, N, X, L, r);
    
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
