#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MATRIX_SIZE 1000


int MatrixA[MATRIX_SIZE][MATRIX_SIZE];
int MatrixB[MATRIX_SIZE][MATRIX_SIZE];
int ResultMatrix[MATRIX_SIZE][MATRIX_SIZE];


typedef struct {
    int thread_id;
    int num_threads;
} ThreadData;


void* MultiplyMatrices(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start = data->thread_id * (MATRIX_SIZE / data->num_threads);
    int end = start + (MATRIX_SIZE / data->num_threads);
    for (int i = start; i < end; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ResultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                ResultMatrix[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	
    int num_threads = atoi(argv[1]);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            MatrixA[i][j] = rand() % 10;
            MatrixB[i][j] = rand() % 10;
        }
    }


    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // Multiply the matrices using pthreads
    pthread_t threads[num_threads];
    ThreadData threadArgs[num_threads];
    for (int i = 0; i < num_threads; i++) {
        threadArgs[i].thread_id = i;
        threadArgs[i].num_threads = num_threads;
        pthread_create(&threads[i], NULL, MultiplyMatrices, &threadArgs[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }


    gettimeofday(&endTime, NULL);
    double executionTime = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    printf("Execution time using %d threads: %f seconds\n", num_threads, executionTime);

    return 0;
}
