// Arreglos_n-dimensionales.c
// N-dimensional arrays using pointers on C
//
// Darío Quiñones Cruz - 2022
// For the class of Fundamentos de Programación

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************** Type definitions ***************************************/
/***********************************************************************************************/
#define MAX_SIZE 1000



/************************************* function prototypes *************************************/
/***********************************************************************************************/

// Create a new array of the given dimensions
int *new_array(int *dim, int size);

// // Dimensions to the total size of the array
// dim: array of dimensions
// dim_size: number of dimensions
int dim_to_size(int *dim, int dim_size);

// Fill the array with random values
void fill_array(int *arr, int *dim, int size, int rand_max);

// Prints a number of spaces
void print_indent(int indent);

// Prints the array in a recursive way for the given dimensions
// n: number of dimensions
// arr: array to print
// dim: values of the dimensions
// size: size of arr
// indent: number of spaces to print before the array
void print_array(int n, int *arr, int *dim, int size, int *counter, int indent);

// Returns the address of the element in the array
int *coord_to_index(int *index, int *dim, int dim_size, int *counters);

// Computes the average of the array
float average(int *arr, int size);

// int *element(int *arr, int dim[], int *index);

/************************************* function definitions ************************************/
/***********************************************************************************************/
void main() {
    int *arr;
    int size, counter;
    int dim[] = {14};
    // Examples of dimensions
    // int dim[] = {6, 9};
    // int dim[] = {5, 5, 5};
    // int dim[] = {2, 3, 4, 5};
    // int dim[] = {6, 5, 4, 3, 2};

    int dim_size = sizeof(dim)/sizeof(*dim);
    int rand_max = 100;


    system("clear");
    printf("Creating a new array of dimensions: [");
    for (int i = 0; i < dim_size; i++) {
        printf("%d,", dim[i]);
    }
    printf("]\n");
    size = dim_to_size(dim, dim_size);
    
    if (size > MAX_SIZE) {
        printf("The array is too big: %d (max %d)\n", size, MAX_SIZE);
        return;
    }
    arr = new_array(dim, size);

    printf("Filling array with random values... ");
    fill_array(arr, dim, size, rand_max);
    
    printf("The size of the array is: %d\n", size);
    printf("Dimensions: %d\n", dim_size);

    counter = 0;
    print_array(dim_size -1, arr, dim, size, &counter, 0);

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

int dim_to_size(int *dim, int dim_size) {
    int i = 0;
    int size = 1;

    printf("Multiplying dimensions... ");
    for (i = 0; i < dim_size; i++) {
        // printf("%d ", dim[i]);
        size *= dim[i];
    }
    
    return size;
}

void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
}

void print_array(int n, int *arr, int *dim, int size, int *counter, int indent) {
    int i, j;
    if (n > 0) {
        for (i = 0; i < dim[n]; i++) {
            if (n >= 2) {
                print_indent(indent);
                printf("[\n");
                print_array(n-1, arr, dim, size, counter, indent + 2);
                print_indent(indent);
                printf("],\n");
            }
            else {
                print_array(n-1, arr, dim, size, counter, indent);
            }
        }
    } else {
        print_indent(indent);
        printf("[");
        for (i = 0; i < dim[n]-1; i++) {
            
            
            printf("%d,", arr[*counter]);
            *counter += 1;
        }
        printf("%d],\n", arr[*counter]);
        *counter += 1;
    }
    
}

int *coord_to_index(int *index, int *dim, int dim_size, int *counters) {
    int i;
    int pos = 0;
    for (i = 0; i < dim_size; i++) {
        pos += dim[i] * counters[i];
        printf("%d ", pos);
    }
    return &index[pos];
}

void fill_array(int *arr, int *dim, int size, int rand_max) {
    int i = 0;
    int *counter = calloc(sizeof(dim), sizeof(int));
    printf("[");
    for (i = 0; i < size; i++) {
        arr[i] = rand() % rand_max;
        //Pretty formatting
        if (size > 10) {
            if (i < 3) {
                printf("%d, ", arr[i]);
            } else if (i == 3) {
                printf(" ...  ");            
            } else if (i >= size - 3) {
                printf("%d,", arr[i]);
            } 
        } else { // Usual formatting
            printf("%d, ", arr[i]);
        }

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