// Arreglos_n-dimensionales.c
// N-dimensional arrays using pointers on C
//
// Darío Quiñones Cruz - 2022
// For the class of Fundamentos de Programación

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type definitions
#define MAX_SIZE 1000



// function prototypes

// Create a new array of the given dimensions
int *new_array(int *dim, int size);

// // Dimensions to the total size of the array
int dim_to_size(int *dim);

// Fill the array with random values
void fill_array(int *arr, int *dim, int size);

// Prints the array for a maximum of 3 dimensions (for now)
// n: level of recursion
// arr: array to print
// dim: dimensions of the array
// size: size of the array
// counters: current position in the array
void print_array(int n, int *arr, int *dim, int size, int *counters);

float average(int *arr, int size);

// int *element(int *arr, int dim[], int *index);

// function definitions
void main() {
    int *arr;
    int size;
    int dim[] = {3,2,1};
    

    printf("Creating a new array of dimensions: [");
    for (int i = 0; i < sizeof(dim)/sizeof(dim[0]); i++) {
        printf("%d,", dim[i]);
    }
    printf("]\n");
    size = dim_to_size(dim);
    printf("The size of the array is: %d\n", size);
    if (size > MAX_SIZE) {
        printf("The array is too big.\n");
        return;
    }
    arr = new_array(dim, size);

    printf("Filling array with random values... ");
    fill_array(arr, dim, size);
    printf("\nPrinting array...\n");
    print_array(0, arr, dim, size, calloc(sizeof(dim), sizeof(int)));

    printf("\nFinding average of array...\n");
    printf("Average: %f\n", average(arr, size));

    free(arr);
}

int *new_array(int *dim, int size) {
    int i = 0;
    // int size= dim_to_size(dim);
    int *arr = calloc(size, sizeof(int));

    for (i = 0; i < dim[0]; i++) {
        arr[i] = i;
    }
    return arr;
}

int dim_to_size(int *dim) {
    int i = 0;
    int size = 1;
    int len = sizeof(dim) / sizeof(dim[0]);
    printf("Multiplying dimensions...\n");
    for (i = 0; i <= len; i++) {
        // printf("%d ", dim[i]);
        size *= dim[i];
    }
    
    return size;
}

void print_array(int n, int *arr, int *dim, int size, int *counters) {
    int i, j, k;
    int pos;
    // Prints 2d slices of the array, separated by a new line
    // I have not yet figured out how to dynamically print the array
    for (i = 0; i < dim[n]; i++) {
        printf("[\n");
        for (j = 0; j < dim[1]; j++) {
            printf("  [");
            for (k = 0; k < dim[2]; k++) {
                printf("%d ", arr[i * dim[1] * dim[2] + j * dim[2] + k]);
            }
            printf("]\n");
        }
        printf("]\n");
    }
}

void fill_array(int *arr, int *dim, int size) {
    int i = 0;
    int *counter = calloc(sizeof(dim), sizeof(int));
    printf("[");
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 10;
        printf("%d,", arr[i]);
    }
    printf("]\n");
}

float average(int *arr, int size) {
    int i = 0;
    float sum = 0.0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}