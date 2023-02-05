#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "chall.h"

struct __attribute__((packed)) input_char {
    int64_t vals[CHALL_SIZE * CHALL_SIZE];
    int64_t offset;
};

struct __attribute__((packed))  input {
    int N;
    struct input_char chars[64];
};

struct input *read_input(char *filename) {
    FILE *file;

    struct input *input = malloc(sizeof(*input));
    if (!(file = fopen(filename, "r")) || fread(input, sizeof(*input), 1, file) != 1) {
        printf("Failed.\n");
        return NULL;
    }

    fclose(file);
    return input;
}

int main(int argc, char **argv) {
    struct input *input = read_input(argv[1]);

    for (int chr = 0; chr < 64; ++chr) {
        int64_t **matrix = allocate_matrix(input->N);
        for (int i = 0; i < input->N; ++i) {
            memcpy(matrix[i], input->chars[chr].vals + CHALL_SIZE * i, CHALL_SIZE * sizeof(int64_t));
        }

        int64_t det = determinant(matrix, input->N);
        printf("%c", (char) (input->chars[chr].offset - det) + chr);
        fflush(stdout);
    }
    printf("\n");
}
