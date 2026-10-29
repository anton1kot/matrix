#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, int p) {
    if (!matrix) return;
    for (int i = 0; i < p; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void spiral(int **matrix, int p) {
    printf("--- %dx%d ---\n", p, p);

    int top = 0;
    int bottom = p - 1;
    int left = 0;
    int right = p - 1;

    while (top <= bottom && left <= right) {
        // Вправо по верхней строке
        for (int j = left; j <= right; ++j) {
            printf("%d ", matrix[top][j]);
        }
        top++;

        // Вниз по правому столбцу
        for (int i = top; i <= bottom; ++i) {
            printf("%d ", matrix[i][right]);
        }
        right--;

        // Влево по нижней строке (если ещё есть строки)
        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                printf("%d ", matrix[bottom][j]);
            }
            bottom--;
        }

        // Вверх по левому столбцу (если ещё есть столбцы)
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                printf("%d ", matrix[i][left]);
            }
            left++;
        }
    }
    printf("\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("File open error");  // напишет причину: нет файла, нет прав и т.п.
        return 1;
    }

    int p;

    while (fscanf(fin, "%d", &p) == 1) {
        if (p <= 0) {
            continue;
        }
        int **matrix = malloc(p * sizeof(int *));
            if (!matrix) {
                fclose(fin);
                return 1;
            }


            for (int i = 0; i < p; ++i) {
                matrix[i] = malloc(p * sizeof(int));
                if (!matrix[i]) {
                    free_matrix(matrix, i);
                    fclose(fin);
                    return 1;
            }

            }
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < p; ++j) {
                if (fscanf(fin, "%d", &matrix[i][j]) != 1) {
                    break;
                }
            }
        }

        spiral(matrix, p);
        free_matrix(matrix, p);
    }

    fclose(fin);
    return 0;
}