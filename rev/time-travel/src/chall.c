#include <stdio.h>
#include <malloc.h>
#include "chall.h"

int64_t **allocate_matrix(int N) {
    int64_t **submatrix = malloc(N * sizeof(int64_t *));
    for (int i = 0; i < N; ++i) {
        submatrix[i] = malloc(sizeof(uint64_t) * (N));
    }
    return submatrix;
}

void print_matrix(int64_t **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%zd, ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int64_t **matrix, int N) {
    for (int i = 0; i < N; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int64_t **copy_submatrix(int64_t **matrix, int N, int64_t **submatrix, int skip_col) {
    int orig_j = 0;
    int orig_i = 1;
    int sub_i = 0;
    int sub_j = 0;
    while (orig_i < N) {
        while (orig_j < N) {
            if (orig_j == skip_col) {
                orig_j++;
                continue;
            }

            submatrix[sub_i][sub_j] = matrix[orig_i][orig_j];
//            printf("copied (%d, %d): %zd\n", orig_i, orig_j, matrix[orig_i][orig_j]);
            sub_j++;
            orig_j++;
        }
        sub_i++;
        orig_i++;

        orig_j = 0;
        sub_j = 0;
    }

    return submatrix;
}

// Compute determinant of submatrix of size N at offset,offset
int64_t determinant(int64_t **matrix, int N) {
    if (N == 1) {
        return matrix[0][0];
    }

//    print_matrix(matrix, N);

    int64_t accumulator = 0;
    int64_t sign = 1;
    // cofactor expansion
    for (int i = 0; i < N; ++i) {
        int64_t **submatrix = allocate_matrix(N - 1);

        copy_submatrix(matrix, N, submatrix, i);

        int64_t cofactor = matrix[0][i];

        accumulator += sign * cofactor * determinant(submatrix, N - 1);

        sign = -sign;

        free_matrix(submatrix, N - 1);
    }

    return accumulator;
}


char compute_chall(int64_t **input) {

}
