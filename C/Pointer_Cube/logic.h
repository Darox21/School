// Este es el encabezado de logic.cpp

// Evitar que se incluya dos veces
#ifndef LOGIC_H 
#define LOGIC_H

/*********************** Type Definitions ***********************/
/****************************************************************/

// Un nodo de un cubo de punteros
struct Node
{
    int data;
    struct Node *left; // Eje X
    struct Node *right;
    struct Node *up; // Eje Y
    struct Node *down;
    struct Node *front; // Eje Z
    struct Node *back;
};

/********************** Function Prototypes *********************/
/****************************************************************/

// Crea un nuevo nodo devuelve el puntero a este.
struct Node *new_node(int data);

// Crea una nueva fila de nodos devuelve el puntero al principio de la fila.
struct Node *new_row(int size);

// Crea una cara del cubo de punteros devuelve el puntero al principio de la cara.
struct Node *new_face(int size);

// Crea un cubo de punteros devuelve el puntero al principio del cubo.
// y por principio me refiero a arriba-izquierda-atrás.
struct Node *new_cube(int size);

// Imprime los valores de cada cara en la consola.
void print_cube(struct Node *cube, int size);

// // Iterar sobre cada cara y liberar la memoria.
// void free_cube(struct Node *cube);

// Suma los valores a lo largo del eje X de izquierda a derecha.
int sum_of_row(struct Node *row);

// Suma los valores a lo largo del eje Y de arriba a abajo.
int sum_of_column(struct Node *column);

// Suma los valores en de una cara.
int sum_of_layer(struct Node *layer, char axis);

// Suma los valores del cubo completo.
int sum_of_cube(struct Node *cube);

#endif