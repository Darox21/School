// Este es el archivo de lógica del cubo de punteros.

// La parte gráfica del cubo de punteros se puede encontrar en
// el archivo principal en C/Pointer_Cube/main.cpp

#include <stdio.h>
#include <stdlib.h>

#include "logic.h"

int node_number = 0;

/********************* Function Definitions *********************/
/****************************************************************/

// Crea un nuevo nodo devuelve el puntero a este.
//
// n: valor para asignar a node.data
struct Node *new_node(int n){
	struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
	// struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->data = n;
	return node;
}

// Crea una nueva fila de nodos devuelve el puntero al principio de la fila.
//
// size: Tamaño de la fila
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

// Crea una cara del cubo de punteros devuelve el puntero al principio de la cara.
//
// size: Tamaño de la cara
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

// Crea un cubo de punteros devuelve el puntero al principio del cubo.
// y por principio me refiero a arriba-izquierda-atrás.
//
// size: Tamaño del cubo
// type: Tipo de dato para cada nodo
// 		0: Ceros
// 		1: Secuencial
// 		2: Aleatorio
struct Node *new_cube(int size, int type){

	// Puntero a la raíz y a cada capa
	struct Node *root, *frontface, *backface;
	// Punteros al principio de las filas actuales
	struct Node *frontrow, *backrow;
	// Punteros a los nodos actuales
	struct Node *frontnode, *backnode;
	int i;

	root = new_face(size);
	backface = root;

	// Crea el resto de las capas
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

	// Aplica una función opcional para los valores de cada nodo
	switch(type){
		case 0:
			printf("Cubo de ceros\n");
			break;
		case 1:
			printf("Cubo de de valores secuenciales\n");
			map_to_cube(root, &secuential_node);
			// El nodo secuencial usa una variable global
			// así que reseteamos esa variable.
			node_number = 0;
			break;
		case 2:
			printf("Cubo de valores aleatorios\n");
			map_to_cube(root, &random_node);
			break;
		default:
			printf("Tipo de cubo desconocido\n");
	}

	return root;
}

// Le da un valor secuencial a un nodo, tomando una variable global como referencia
//
// n: Nodo a modificar
void secuential_node(struct Node *n){
	n->data = node_number;
	node_number++;
}

// Le da un valor aleatorio a un nodo, del 0 al 999
//
// n: Nodo a modificar
void random_node(struct Node *n){
	n->data = rand() % 1000;
}

// Toma una función y la aplica a cada nodo
//
// cube: Puntero a la raíz del cubo
// *f: Puntero a una función que retorna void, y tiene como parámetro un &nodo
void map_to_cube(struct Node *cube, void(*f)(struct Node *)) {
	struct Node *current[3] = {cube, cube, cube};
	struct Node *next[3];

	// Primero guardamos un puntero al valor siguiente
	// (por si borramos el valor anterior)
	while (current[2] != NULL) {
		next[2] = current[2]->front;
		while (current[1] != NULL) {
			next[1] = current[1]->down;
			while (current[0] != NULL) {
				next[0] = current[0]->right;
				// Usamos la función
				(*f)(current[0]);
				current[0] = next[0];
			}
			// Continuar a la siguiente fila
			current[1] = next[1];
			current[0] = next[1];
		}
		// Continuar a la siguiente capa
		current[2] = next[2];
		current[1] = next[2];
		current[0] = next[2];
	}
}

// Retorna la longitud de una fila del cubo
// Útil para obtener  el tamaño del cubo, considerando que
// todos sus lados son iguales
//
// cube: Puntero a la raíz del cubo
int row_length(struct Node *cube) {
	struct Node *current = cube;
	int out = 0;
	while (current != NULL) {
		current = current->right;
		out++;
	}
	return out;
}

// Imprime el cubo en la consola
//
// cube: Puntero a la raíz del cubo
// size: Tamaño del cubo
void print_cube(struct Node *cube){
	struct Node *current[3] = {cube, cube, cube};

	while (current[2] != NULL) {
		while (current[1] != NULL) {
			while (current[0] != NULL) {
				// Imprimimos y avanzamos a la derecha
				printf("%d ", current[0]->data);
				current[0] = current[0]->right;
			}
			printf("\n");
			// Continuar a la siguiente fila
			current[1] = current[1]->down;;
			current[0] = current[1];
		}
		printf("\n");
		// Continuar a la siguiente capa
		current[2] = current[2]->front;
		current[1] = current[2];
		current[0] = current[2];
	}
}

// Libera cada nodo del cubo
//
// cube: Puntero a la raíz del cubo
void free_cube(struct Node *cube){

	// Declaración de una función local
	// Ya que las funciones dentro de funciones no está en el estándar de C
	// Y las funciones anónimas (lamdas) fueron añadidas solo hasta C++ 11
	void free_node(struct Node *n);

	map_to_cube(cube, &free_node);
}

// Función para liberar un nodo individual
// Se usa localmente en free_cube()
void free_node(struct Node *n){
	free(n);
}

// Suma los valores a lo largo del eje X de izquierda a derecha.
//
// row: Puntero al principio de la fila
int sum_of_row(struct Node *row) {
	int sum = 0;
	struct Node *current = row;
	while (current != NULL) {
		sum += current->data;
		current = current->right;
	}
	return sum;
}

// Suma los valores a lo largo del eje Y de arriba a abajo.
//
// column: Puntero al principio de la columna
int sum_of_column(struct Node *column) {
	int sum = 0;
	struct Node *current = column;
	while (current != NULL) {
		sum += current->data;
		current = current->down;
	}
	return sum;
}

// Suma los valores en de una cara.
// Suma los valores normales a el axis especificado. (x, y, z)
// Es decir, si es en "z", suma los valores en el plano (x,y).
//
// layer: Puntero al principio de la capa
// axis: Eje normal al plano a sumar, 'x', 'y' o 'z'
int sum_of_layer(struct Node *layer, char axis) {
	int sum = 0;
	struct Node *currentrow = layer;
	switch (axis) {
		case 'x':
			while (currentrow != NULL) {
				sum += sum_of_column(currentrow);
				currentrow = currentrow->front;
			}
			break;
		case 'y':
			while (currentrow != NULL) {
				sum += sum_of_row(currentrow);
				currentrow = currentrow->front;
			}
			break;
		case 'z':
			while (currentrow != NULL) {
				sum += sum_of_row(currentrow);
				currentrow = currentrow->down;
			}
			break;
	}
	return sum;
}

// Suma los valores del cubo completo.
//
// cube: Puntero a la raíz del cubo
int sum_of_cube(struct Node *cube) {
	int sum = 0;
	struct Node *currentface = cube;
	while (currentface != NULL) {
		sum += sum_of_layer(currentface, 'z');
		currentface = currentface->front;
	}
	return sum;
}

// Retorna el cubo en forma de un arreglo tridimencional
// Pensado para la escritura de archivos
//
// cube: Puntero a la raíz del cubo
int *cube_values(struct Node *cube) {
	struct Node *current[3] = {cube, cube, cube};
	int size = row_length(cube);
	int *cube_data = (int*)malloc(size*size*size * sizeof(char));
	int *ptr = cube_data;

	while (current[2] != NULL) {
		while (current[1] != NULL) {
			while (current[0] != NULL) {
				// Copiamos el dato del nodo al arreglo
				*ptr = current[0]->data;
				// Avanzamos al siguiente valor
				ptr++;
				current[0] = current[0]->right;
			}
			// Continuar a la siguiente fila
			current[1] = current[1]->down;;
			current[0] = current[1];
		}
		// Continuar a la siguiente capa
		current[2] = current[2]->front;
		current[1] = current[2];
		current[0] = current[2];
	}
}

// Cambia el valor de un nodo en la coordenada especificada
// Retorna un int por la posibilidad en la que falle
//
// n: Puntero a la raíz del cubo
// x,y,z: Coordenada a partir de (0,0,0)
// value: Valor a otorgar para node.data
int edit_coordinate(struct Node *n, int x, int y, int z, int value){
	int i;
	int max = row_length(n) - 1;

	if (max < x || max < y || max < z){
		printf("Coordenada fuera de rango\n");
		return 1;
	}

	for (i=0; i<x; i++) {
		n = n->right;
	}
	for (i=0; i<y; i++) {
		n = n->down;
	}
	for (i=0; i<z; i++) {
		n = n->front;
	}
	n->data = value;
	return 0;
}



