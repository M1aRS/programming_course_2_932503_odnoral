#include <iostream>
#include <cstdio>

// Lab 14
int count_dfs(int u, int target, int** matrix, int n){
    if (u == target) return 1;

    int count = 0;
    for (int v = 0; v < n; v++){
        if (matrix[u][v] == 1){
            count += count_dfs(v, target, matrix, n);
        }
    }
    return count;
}
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
void solve_travel(){
    FILE *fin = fopen("travel_input.txt", "r");
    if (!fin) {
        printf("Error: travel input file read error. \n");
        return;
    }
    int n, m, start, end;
    fscanf(fin, "%d%d%d%d", &n, &m, &start, &end);
    start--; end--;

    int **matrix = new int*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }

    for (int k = 0; k < m; k++){
        int u,v;
        fscanf(fin, "%d %d", &u, &v);
        u--; v--;
        matrix[u][v] = 1;
    }
    fclose(fin);

    int paths_count = count_dfs(start, end, matrix, n);
    FILE *fout = fopen("travel_output.txt", "w");
    if (!fout) {
        printf("Error: cannot create travel_output.txt file.\n");
    } else {
        fprintf(fout, "Number of paths from %d to %d: %d\n", start+1, end+1, paths_count);
        fclose(fout);
        printf("Completed! \n");
    }
    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
}
void solve_maze(){
    FILE *fin = fopen("maze_input.txt", "r");
    if (!fin) {
        printf("Error: maze input file read error. \n");
        return;
    }

    int R,C;
    if (fscanf(fin, "%d%d", &R, &C) != 2) {
        printf("Error: invalid maze input format.\n");
        fclose(fin);
        return;
    }

    char **maze = new char*[R];
    int **dist = new int*[R];

    for (int i = 0; i < R; i++) {
        maze[i] = new char[C];
        dist[i] = new int[C];
    }
    int start_r = -1, start_c = -1, end_r = -1, end_c = -1;

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            fscanf(fin, " %c", &maze[i][j]);
            dist[i][j] = -1;
            if (maze[i][j] == 's') { start_r = i; start_c = j; }
            if (maze[i][j] == 'f') { end_r = i; end_c = j; }
        }
    }
    fclose(fin);
    //вверх, вниз, влево, вправо, вверх-влево, вверх-вправо, вниз-влево, вниз-вправо
    int dr[8] = {-1,1,0,0,-1,-1,1,1};
    int dc[8] = {0,0,-1,1,-1,1,-1,1};

    int max_queue = R * C;
    int *Qr = new int [max_queue]; int *Qc = new int [max_queue];
    int head = 0, tail = 0;

    Qr[tail] = start_r; Qc[tail] = start_c; tail++;
    dist[start_r][start_c] = 0;
    bool found = false;

    while (head < tail) {
        int r = Qr[head]; int c = Qc[head]; head++;

        if (r == end_r && c == end_c) { found = true; break; }

        for (int d = 0; d < 8; d++){
            int nr = r + dr[d]; int nc = c + dc[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (maze[nr][nc] != '#' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    Qr[tail] = nr; Qc[tail] = nc; tail++;
                }
            }
        }
    }

    if (found){
        int curr_r = end_r; int curr_c = end_c;
        int curr_d = dist[end_r][end_c];

        while (curr_d > 1){
            for (int i = 0; i < 8; i++){
                int nr = curr_r + dr[i]; int nc = curr_c + dc[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C){
                    if (dist[nr][nc] == curr_d - 1){
                        curr_r = nr; curr_c = nc; curr_d--;
                        maze[curr_r][curr_c] = '*';
                        break;
                    }
                }
            }
        }
    }

    FILE *fout = fopen("maze_output.txt", "w");
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            fprintf(fout, "%c", maze[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
    for (int i = 0; i < R; i++) { delete[] maze[i]; delete[] dist[i]; }
    delete[] maze; delete[] dist; delete[] Qr; delete[] Qc;
}
int main() {
    /*read_input_and_make_matirx();
    read_matrix_and_make_index_neigbor_matrix();
    read_index_neighbor_matrix_and_make_graphs();
    solve_genealogy();
    solve_travel();*/
    solve_maze();
    return 0;
}
