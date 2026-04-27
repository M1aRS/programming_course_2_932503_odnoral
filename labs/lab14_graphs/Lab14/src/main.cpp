#include <iostream>
#include <cstdio>

// Lab 14

void read_input_and_make_matirx(){
    FILE *fin = fopen("input1.txt", "r");
    FILE *fout = fopen("output1.txt", "w");
    if (!fin) {
        printf("Error: input file read error. \n");
        if (fout) fclose(fout);
        return;
    }
    int n,m;
    fscanf(fin, "%d%d", &n, &m);
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }

    for (int k = 0; k < m; k++){
        int u, v;
        fscanf(fin, "%d%d", &u, &v);
        u--; v--;
        matrix[u][v] = 1; matrix[v][u] = 1;
    }

    fprintf(fout, "%d\n", n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fprintf(fout, "%d ", matrix[i][j]);
        }
        fprintf(fout, "\n");
    }
    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;

    fclose(fin);
    fclose(fout);
}
void read_matrix_and_make_index_neigbor_matrix(){
    FILE *fin = fopen("output1.txt", "r");
    FILE *fout = fopen("output2.txt", "w");
    if (!fin) {
        printf("Error: output1 file read error. \n");
        if (fout) fclose(fout);
        return;
    }
    int n;
    fscanf(fin,"%d",&n);
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int [n];
        for (int j = 0; j < n; j++){
            fscanf(fin, "%d", &matrix[i][j]);
        }
    }
    
    int *U = new int[n]; int *S = new int[n]; int *L = new int[n];
    int D_size = 0;

    for (int j = 0; j < n; j++) L[j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                L[i]++;
                D_size++;
            }
        }
    }

    S[0] = 0;
    for (int j = 1; j < n; j++) {
        S[j] = S[j-1] + L[j-1];
    }

    for (int j = 0; j < n; j++) U[j] = S[j];

    int *D = new int[D_size];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                D[U[i]] = j;
                U[i]++;
            }
        }
    }

    fprintf(fout, "%d %d\n", n, D_size);
    for (int i = 0; i < n; i++) fprintf(fout, "%d ", S[i]);
    fprintf(fout, "\n");
    
    for (int i = 0; i < n; i++) fprintf(fout, "%d ", L[i]);
    fprintf(fout, "\n");
    
    for (int i = 0; i < D_size; i++) fprintf(fout, "%d ", D[i]);
    fprintf(fout, "\n");

    // Очистка памяти
    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] L; delete[] S; delete[] U; delete[] D;

    fclose(fin);
    fclose(fout);
}
int main() {
    read_input_and_make_matirx();
    read_matrix_and_make_index_neigbor_matrix();
    return 0;
}
