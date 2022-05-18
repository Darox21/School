// Este es el encabezado de logic.cpp
// Contiene las funciones relacionadas a:
//             // Manejo de Nodos
//             // Operaciones del cubo
//             // Información de debug

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
//
// n: valor para asignar a node.data
struct Node *new_node(int n);

// Crea una nueva fila de nodos devuelve el puntero al principio de la fila.
//
// size: Tamaño de la fila
struct Node *new_row(int size);

// Crea una cara del cubo de punteros devuelve el puntero al principio de la cara.
//
// size: Tamaño de la cara
struct Node *new_face(int size);

// Crea un cubo de punteros devuelve el puntero al principio del cubo.
// y por principio me refiero a arriba-izquierda-atrás.
//
// size: Tamaño del cubo
// type: Tipo de dato para cada nodo
// 		0: Ceros
// 		1: Secuencial
// 		2: Aleatorio
struct Node *new_cube(int size, int type);

// Le da un valor secuencial a un nodo, tomando una variable global como referencia
//
// n: Nodo a modificar
void secuential_node(struct Node *n);

// Le da un valor aleatorio a un nodo, del 0 al 999
//
// n: Nodo a modificar
void random_node(struct Node *n);

// Toma una función y la aplica a cada nodo
//
// cube: Puntero a la raíz del cubo
// *f: Puntero a una función que retorna void, y tiene como parámetro un &nodo
void map_to_cube(struct Node *cube, void(*f)(struct Node *));

// Retorna la longitud de una fila del cubo
//
// cube: Puntero a la raíz del cubo
int row_length(struct Node *cube);

// Imprime el cubo en la consola
//
// cube: Puntero a la raíz del cubo
// size: Tamaño del cubo
void print_cube(struct Node *cube);

// Libera cada nodo del cubo
//
// cube: Puntero a la raíz del cubo
void free_cube(struct Node *cube);

// Suma los valores a lo largo del eje X de izquierda a derecha.
//
// row: Puntero al principio de la fila
int sum_of_row(struct Node *row);

// Suma los valores a lo largo del eje Y de arriba a abajo.
//
// column: Puntero al principio de la columna
int sum_of_column(struct Node *column);

// Suma los valores en de una cara.
// Suma los valores normales a el axis especificado. (x, y, z)
// Es decir, si es en "z", suma los valores en el plano (x,y).
//
// layer: Puntero al principio de la capa
// axis: Eje normal al plano a sumar, 'x', 'y' o 'z'
int sum_of_layer(struct Node *layer, char axis);

// Suma los valores del cubo completo.
//
// cube: Puntero a la raíz del cubo
int sum_of_cube(struct Node *cube);

// Retorna el cubo en forma de un arreglo tridimensional
// Pensado para la escritura de archivos
//
// cube: Puntero a la raíz del cubo
int *cube_values(struct Node *cube);

// Cambia el valor de un nodo en la coordenada especificada
// Retorna un int por la posibilidad en la que falle
//
// cube: Puntero a la raíz del cubo
// x,y,z: Coordenada a partir de (0,0,0)
// value: Valor a otorgar para node.data
int edit_coordinate(struct Node *cube, int x, int y, int z, int value);

#endif
