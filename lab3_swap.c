#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, int N) {
    if (!matrix) return;
    for (int i = 0; i < N; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}


void swap_diagonals(int **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        if (i == N - 1 - i) continue;

        int tmp = matrix[i][i];
        matrix[i][i] = matrix[i][N - 1 - i];
        matrix[i][N - 1 - i] = tmp;
    }
}

void print_matrix(int **matrix, int N, FILE* fout) {
    fprintf(fout,"--- %dx%d ---\n", N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fprintf(fout,"%d ", matrix[i][j]);
        }
        fprintf(fout,"\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Input file open error");  
        return 1;
    }
    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        fclose(fin);
        perror("Output file open error"); 
        return 1;
    }
    int N;

    while (fscanf(fin, "%d", &N) == 1) {
        if (N <= 0) {
            continue;
        }
        int **matrix = malloc(N * sizeof(int *));
            if (!matrix) {
                fclose(fin);
                return 1;
            }


            for (int i = 0; i < N; ++i) {
                matrix[i] = malloc(N * sizeof(int));
                if (!matrix[i]) {
                    free_matrix(matrix, i);
                    fclose(fin);
                    return 1;
            }

            }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (fscanf(fin, "%d", &matrix[i][j]) != 1) {
                    break;
                }
            }
        }
        swap_diagonals(matrix, N);
        print_matrix(matrix, N, fout);
        free_matrix(matrix, N);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}