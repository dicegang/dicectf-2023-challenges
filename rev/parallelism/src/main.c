#include <mpi/mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int size, rank;
static char flag_buffer[9];

bool distribute_flag() {
    char input[64 + 2] = {0};
    if (rank == 0) {
#if GEN_EXPECTED_FLAG
        FILE *flag_file = fopen("./flag.txt", "r");
        if (!flag_file) {
            printf("Expected ./flag.txt to exist.\n");
            exit(1);
        }
        fgets(input, sizeof(input), flag_file);
        fclose(flag_file);
#else
        printf("Enter the flag: ");
        fgets(input, sizeof(input), stdin);
#endif
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) != 64)
            return false;

        int swaps[] = {26, 32, 14, 11, 3, 1, 32, 24, 13, 17, 3, 17, 2, 13, 19, 6, 12, 22, 3, 30, 10, 6, 8, 26, 6, 22,
                       13, 1, 19, 1, 1, 29};
        for (int i = 0; i < 32; ++i) {
            char tmp = input[i];
            input[i] = input[swaps[i] + 31];
            input[swaps[i] + 31] = tmp;
        }
    }

    MPI_Scatter(input, 8, MPI_CHAR, flag_buffer, 8, MPI_CHAR, 0, MPI_COMM_WORLD);

    return true;
}

bool process() {
    for (int iteration = 0; iteration < 10000; ++iteration) {
        int slot = iteration % 8;

        MPI_Request send_request;
        MPI_Request recv_request;

        int destination = ((rank - iteration) % size + size) % size;
        MPI_Isend(&flag_buffer[slot], 1, MPI_CHAR, destination, destination, MPI_COMM_WORLD, &send_request);

        char tmp;
        int source = ((rank + iteration) % size + size) % size;
        MPI_Irecv(&tmp, 1, MPI_CHAR, source, rank, MPI_COMM_WORLD, &recv_request);

        MPI_Wait(&send_request, MPI_STATUS_IGNORE);
        MPI_Wait(&recv_request, MPI_STATUS_IGNORE);

        flag_buffer[slot] = tmp;

        MPI_Barrier(MPI_COMM_WORLD);
    }

    return true;
}

bool verify() {
    char processed[65] = {0};
    MPI_Gather(flag_buffer, 8, MPI_CHAR, processed, 8, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
#ifdef GEN_EXPECTED_FLAG
        FILE* processed_file = fopen("processed.txt", "w");
        fwrite(processed, 64, 1, processed_file);
        fclose(processed_file);
        printf("%s", processed);
#else
        return memcmp("m_ERpmfrNkekU4_4asI_Tra1e_4l_c4_GCDlryidS3{Ptsu9i}13Es4V73M4_ans", processed, 64) == 0;
#endif
    }

    return true;
}


int main(int argc, char **argv) {
    setbuf(stdout, NULL);

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 8) {
        printf("Must be run with 8 processes\n");
        goto cleanup;
    }

    if (!distribute_flag())
        goto invalid;

    if (!process())
        goto invalid;

    if (!verify())
        goto invalid;

    if (rank == 0) {
        printf("Correct!\n");
        goto cleanup;

        invalid:
        printf("Invalid flag!\n");
    }

    cleanup:
    MPI_Finalize();
    return 0;
}
