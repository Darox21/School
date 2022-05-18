// Encabezado de main.cpp
// Contiene las funciones relacionadas a:
// 			// Gráficos
// 			// Manejo de archivos

/*************************** GLOBALS ****************************/
/****************************************************************/
#define NODE_SIZE 40
#define NODE_OFFSET 60
#define WINDOW_OFFSET 50


/********************** Function Prototypes *********************/
/****************************************************************/

// Presenta el menú de opciones de cada cubo
//
// cube: Puntero a un cubo
void cube_menu(struct Node *cube);

// Guarda el cubo en un archivo ubicado en /saves/
// WORK IN PROGRESS
//
// cube: Puntero al primer nodo del cubo
// mode: Tipo de guardado (Requerimento obligatorio)
//		0: Archivo binario
//		1: Archivo de texto
int save_cube(struct Node *cube, int mode);

// Muestra un cubo guardado
// WORK IN PROGRESS
//
// n: Número del archivo
int retrieve_cube(int n);

// Dibuja un nodo con líneas dependiendo si existen sus vecinos
//
// n: nodo
// pos: su coordenada dentro del cubo
// lines: Si se dibujan líneas a nodos vecinos
// color: Color del nodo
int draw_node(struct Node *n, int pos[3], bool lines, int color);

// Itera en el cubo dibujando cada nodo
//
// root: Puntero al primer nodo del cubo
// lines: Si se dibujan lineas a nodos vecinos
// slowness: Tiempo de espera entre nodo y nodo, en milisegundos
int draw_cube(struct Node *root, bool lines, int slowness);


