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
            for (int k = i; k <= cols; k++){
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
    while (check_i < rows && std::abs(matrix[check_i][cols]) < 1e-12) check_i++;
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
        return -1;
    }
}

void solve_and_write_roots(FILE* out, int rows, int cols, int status, int r, int *L, double *X) {
    if (status == -1) {
            bool first = true;
            for (int v = 0; v < cols; v++) {
                // Ищем, является ли переменная v свободной
                bool is_free = false;
                for (int k = r; k < cols; k++) {
                    if (L[k] == v) {
                        is_free = true;
                        break;
                    }
                }
                
                if (is_free) {
                    if (!first) {
                        printf(", ");
                        fprintf(out, ", ");
                    }
                    printf("x%d", v + 1);
                    fprintf(out, "x%d", v + 1);
                    first = false;
                }
            }
            printf(" are free\n");
            fprintf(out, " are free\n");
        }

    for (int i = 0; i < cols; i++) {
        double val = std::round(X[i] * 1000.0) / 1000.0;
        if (val == -0.0) val = 0.0;
            
        printf("x%d = %g", i + 1, val);
        fprintf(out, "x%d = %g", i + 1, val);
            
        if (i < cols - 1) {
            printf("; ");
            fprintf(out, "; ");
        }
    }
    printf("\n");
    fprintf(out, "\n");
}

void write_temp_and_launch(double A1, double B1, double C1,
                           double A2, double B2, double C2,
                           int status, double *X)
{
    FILE* temp = fopen("temp_data.txt", "w");
    if (!temp) { printf("Cannot create temp_data.txt\n"); return; }

    fprintf(temp, "%.6f %.6f %.6f\n", A1, B1, C1);
    fprintf(temp, "%.6f %.6f %.6f\n", A2, B2, C2);

    if (status == 1) {
        fprintf(temp, "1\n");
        fprintf(temp, "%.6f %.6f\n", X[0], X[1]);
    } else if (status == -1) {
        fprintf(temp, "0\n");
        fprintf(temp, "0.0 0.0\n");
    } else {
        // Параллельные (нет решений)
        fprintf(temp, "-1\n");
        fprintf(temp, "0.0 0.0\n");
    }

    fclose(temp);
    system("graph\\project1.exe");
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == nullptr) {
        printf("Error! \n");
        return 1;
    }
    int M, N;
    if (fscanf(input_file, "%d %d", &M, &N) == 2) {
        double **coeffitients = new double *[M];
        for (int i = 0; i < M; i++) {
            coeffitients[i] = new double[N+1];
            for (int j = 0; j < N; j++) {
                fscanf(input_file, "%lf", &coeffitients[i][j]);
            }
            fscanf(input_file, "%lf", &coeffitients[i][N]);
        }
    
        double *X = new double[N];
        int *L = new int[N];
        int r = 0;

        print_matrix_to_file(output_file, coeffitients, M, N+1);
        int status = triangularize(coeffitients, M, N, X, L, r);

        fprintf(output_file, "Triangular Matrix:\n");
        print_matrix_to_file(output_file, coeffitients, M, N+1);

        if (status == 0){
            printf("Inconsistent system \n");
            fprintf(output_file, "Inconsistent system \n");
        }
        else {
            solve_and_write_roots(output_file, M, N, status, r, L, X);
        }
        
        for (int i = 0; i < M; i++) delete[] coeffitients[i];
        delete[] coeffitients;
        delete[] X;
        delete[] L;
    } else {
        rewind(input_file); // fscanf уже сдвинул указатель, возвращаемся в начало
        
        double A1, B1, C1, A2, B2, C2;
        if (fscanf(input_file, "%lfx %lfy = %lf\n", &A1, &B1, &C1) != 3 ||
            fscanf(input_file, "%lfx %lfy = %lf", &A2, &B2, &C2) != 3) {
            printf("Parse error\n");
            return 1;
        }

        double origA1=A1, origB1=B1, origC1=C1;
        double origA2=A2, origB2=B2, origC2=C2;

        double **coefficients = new double*[2];
        for (int i = 0; i < 2; i++)
            coefficients[i] = new double[3];

        coefficients[0][0]=A1; coefficients[0][1]=B1; coefficients[0][2]=C1;
        coefficients[1][0]=A2; coefficients[1][1]=B2; coefficients[1][2]=C2;

        double *X = new double[2];
        int *L = new int[2];
        int r = 0;

        fprintf(output_file, "Line 1: %.3fx + %.3fy = %.3f\n", origA1, origB1, origC1);
        fprintf(output_file, "Line 2: %.3fx + %.3fy = %.3f\n", origA2, origB2, origC2);
        fprintf(output_file, "Matrix:\n");
        print_matrix_to_file(output_file, coefficients, 2, 3);

        int status = triangularize(coefficients, 2, 2, X, L, r);

        fprintf(output_file, "Triangular Matrix:\n");
        print_matrix_to_file(output_file, coefficients, 2, 3);

        if (status == 0) {
            printf("Lines are parallel\n");
            fprintf(output_file, "Lines are parallel\n");
        } else {
            solve_and_write_roots(output_file, 2, 2, status, r, L, X);
        }

        write_temp_and_launch(origA1, origB1, origC1, origA2, origB2, origC2, status, X);

        delete[] coefficients[0]; delete[] coefficients[1];
        delete[] coefficients;
        delete[] X;
        delete[] L;
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
