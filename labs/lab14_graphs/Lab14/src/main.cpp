#include <iostream>
#include <cstdio>

// Lab 14
void dfs(int u, int current_tree, int *S, int *L, int *D, int *visited) {
    visited[u] = current_tree;
    for (int k = S[u]; k < S[u] + L[u]; k++) {
        int v = D[k];
        if (visited[v] == 0) {
            dfs(v, current_tree, S, L, D, visited);
        }
    }

}
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
void read_index_neighbor_matrix_and_make_graphs(){
    FILE *fin = fopen("output2.txt", "r");
    FILE *fout = fopen("output3.txt", "w");
    if (!fin) {
        printf("Error: output2 file read error. \n");
        if (fout) fclose(fout);
        return;
    }

    int n, m_double;
    fscanf(fin, "%d %d", &n, &m_double);
    int *S = new int[n];
    int *L = new int[n];
    int *D = new int[m_double];

    for (int i = 0; i < n; i++) fscanf(fin, "%d", &S[i]);
    for (int i = 0; i < n; i++) fscanf(fin, "%d", &L[i]);
    for (int i = 0; i < m_double; i++) fscanf(fin, "%d", &D[i]);
    for (int i = 0; i < n; i++) {
        for (int k = S[i]; k < S[i] + L[i]; k++) {
            int j = D[k]; // смежная вершина
            
            if (i <= j) {
                fprintf(fout, "%d %d\n", i+1, j+1);
            }
        }
    }
    delete[] S; delete[] L; delete[] D;
    
    fclose(fin);
    fclose(fout);
}
void solve_genealogy(){
    FILE *fin = fopen("genealogy_input.txt", "r");
    if (!fin) {
        printf("Error: genealogy input file read error. \n");
        return;
    }
    
    int n, u, v;
    fscanf(fin, "%d", &n);

    int **matrix = new int*[n];
    int *present_citizens = new int[n];
    for (int i = 0; i < n; i++){
        present_citizens[i] = 0;
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }

    while (fscanf(fin, "%d %d", &u, &v) == 2) {
        if (u == -1 && v == -1) {
            break;
        }
        u--; v--;
        matrix[u][v] = 1;
        matrix[v][u] = 1;
        present_citizens[u] = 1;
        present_citizens[v] = 1;
    }
    fclose(fin);

    FILE *fout = fopen("genealogy_output.txt", "w");
    int *U = new int[n]; 
    int *S = new int[n]; 
    int *L = new int[n];
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

    int *visited = new int[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    int trees_count = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            trees_count++;
            dfs(i, trees_count, S, L, D, visited);
        }
    }

    if (!fout) {
        printf("Error: cannot create output_gen.txt file.\n");
    } else {
        fprintf(fout, "Families: %d\n\n", trees_count);
        
        for (int k = 1; k <= trees_count; k++) {
            for (int i = 0; i < n; i++) {
                if (visited[i] == k) {
                    fprintf(fout, "%d ", i+1);
                }
            }
            fprintf(fout, "\n");
        }
        fclose(fout);
        printf("Completed! \n");
    }

    // Очистка памяти
    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] U; delete[] S; delete[] L; delete[] D;
    delete[] present_citizens; delete[] visited;
}

int main() {
    /*read_input_and_make_matirx();
    read_matrix_and_make_index_neigbor_matrix();
    read_index_neighbor_matrix_and_make_graphs();*/
    solve_genealogy();
    return 0;
}
