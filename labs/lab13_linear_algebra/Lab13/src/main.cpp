#include <iostream>

// Lab 13

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    FILE* input_file = fopen("input.txt", "r");
    if (input_file == nullptr) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    int M, N;
    fscanf(input_file, "%d %d", &M, &N);
    int **coeffitients = new int *[M];
    for (int i = 0; i < M; i++) {
        coeffitients[i] = new int[N];
        for (int j = 0; j < N; j++) {
            fscanf(input_file, "%d", &coeffitients[i][j]);
        }
    }
    print_matrix(coeffitients, M, N);
    fclose(input_file);
    return 0;
}
