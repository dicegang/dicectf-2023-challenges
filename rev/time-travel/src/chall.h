#include <stdint.h>

#define CHALL_SIZE 18

int64_t **allocate_matrix(int N);

void free_matrix(int64_t **matrix, int N);

void print_matrix(int64_t **matrix, int N);

int64_t determinant(int64_t **matrix, int N);

char compute_chall(int64_t **input);
