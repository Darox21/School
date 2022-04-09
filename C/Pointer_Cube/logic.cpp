// Este es el archivo de lógica del cubo de punteros.
// Está anotado lo más posible para que sea fácil de leer.
// Si prefieren agregar otros comentarios o código,
// pueden hacer una pull request en GitHub.

// HECHO:
// - Una función para crear el cubo de punteros.
// - Una función para imprimir el cubo de punteros (en consola).

// QUEDA PENDIENTE:
// 1. Sumas de filas y columnas.
// 2. Convertir los punteros dentro de la creación de la matriz en un
// arreglo de punteros funciona por el momento, pero se vuelve poco legible
// 3. Función para liberar cada puntero dentro de la matriz.

// La parte gráfica del cubo de punteros se puede encontrar en
// el archivo principal de C/Pointer_Cube/main.cpp y sigue PENDIENTE.

#include <stdio.h>
#include <stdlib.h>

#include "logic.h"

int node_number = 0;

/***************************** Main *****************************/
/****************************************************************/

// Este es un main() temporal para probar el código.
// Pero como no estoy en un IDE, no iba a hacer un makefile manualmente.
int main(){
    // Crea un nuevo cubo de punteros
    struct Node *cube = new_cube(5);

    // Imprime el cubo en consola
    print_cube(cube, 5);

    // // Suma una fila al cubo
    // printf("Sum of the cube: %d\n", sum_of_cube(cube));

    // Libera el cubo
    // free_cube(cube);

    return 0;
}

/********************* Function Definitions *********************/
/****************************************************************/

struct Node *new_node(int data){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = node_number;
    node_number++;
    return node;
}

struct Node *new_row(int size){
    struct Node *root, *current, *next;
    int i;

    root = new_node(0); // Un puntero al principio de la lista
    current = root; // Un puntero al nodo actual

    for(i = 1; i < size; i++){ 
        // Comenzamos en 1 porque el nodo 0 es root

        next = new_node(0); 
        // Unimos los nodos entre sí
        current->right = next; 
        next->left = current; 
        // Actualizamos el nodo actual
        current = next; 
    }

    return root;
}

// Crea una cara del cubo de punteros
// de forma muy similar a la función para crear una lista.
struct Node *new_face(int size){
    struct Node *root, *aboverow, *belowrow, *above, *below;
    int i;

    root = new_row(size); // Un puntero al principio de la primera lista
    aboverow = root; // Y a la fila actual

    for(i = 1; i < size; i++){
        // Añadimos una nueva lista debajo de la actual
        belowrow = new_row(size);  // Creamos una nueva lista
        
        // E inicializamos los punteros para cada nodo
        above = aboverow;
        below = belowrow;

        while (above != NULL && below != NULL){
            above->down = below;
            below->up = above;
            // Nos movemos a la derecha
            above = above->right;
            below = below->right;
        }
        // Actualizamos el nodo actual
        aboverow = belowrow;
    }

    return root;
}

// Create a pointer cube of the given size.
struct Node *new_cube(int size){
    // Puntero a la raíz y a cada cara
    struct Node *root, *frontface, *backface;
    // Punteros al principio de las filas actuales
    struct Node *frontrow, *backrow;
    // Punteros a los nodos actuales
    struct Node *frontnode, *backnode;
    int i;

    root = new_face(size);
    backface = root;
    
    for(i = 1; i < size; i++){
        // Añadimos una nueva cara adelante de la actual
        frontface = new_face(size);

        // Tomamos la primera fila de ambas caras
        backrow = backface;
        frontrow = frontface;

        // Unimos cada fila de la cara actual con la cara anterior
        while (backrow != NULL && frontrow != NULL){
            // Inicializamos los punteros a los nodos actuales
            frontnode = frontrow;
            backnode = backrow;
            
            while (frontnode != NULL && backnode != NULL){
                // Unimos los nodos 
                frontnode->back = backnode;
                backnode->front = frontnode;
                // Continuamos a la derecha
                frontnode = frontnode->right;
                backnode = backnode->right;
            }

            // Nos movemos a la siguiente fila
            backrow = backrow->down;
            frontrow = frontrow->down;

        }
        
        // Actualizamos el puntero a la cara actual
        backface = frontface;
        // Y reiniciamos los otros punteros

    }

    return root;
}

// Imprime el cubo en consola
void print_cube(struct Node *cube, int size){
    struct Node *previous[3];
    int i, j, k;

    previous[0] = cube; // previa x
    previous[1] = cube; // previa y
    previous[2] = cube; // previa z

    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            for (k = 0; k < size; k++){
                // Imprime el valor del nodo
                printf("%d ", previous[0]->data);
                // Nos movemos al siguiente nodo
                previous[0] = previous[0]->right;
            }
            printf("\n");

            // Nos movemos a la siguiente fila
            previous[1] = previous[1]->down;
            // Reiniciamos el puntero al valor actual
            previous[0] = previous[1];
        }
        printf("\n");
        // Nos movemos a la siguiente cara
        previous[2] = previous[2]->front;
        // Reiniciamos el puntero a la fila actual y al valor actual
        previous[1] = previous[2];
        previous[0] = previous[2];
    }
}

// // Iterar sobre cada cara y liberar la memoria.
// void free_cube(struct Node *cube);

// // Suma los valores a lo largo del eje X de izquierda a derecha.
// int sum_of_row(struct Node *row);

// // Suma los valores a lo largo del eje Y de arriba a abajo.
// int sum_of_column(struct Node *column);

// // Suma los valores en de una cara.
// int sum_of_layer(struct Node *layer);

// // Suma los valores del cubo completo.
// int sum_of_cube(struct Node *cube);