// El programa del cubo de punteros 
// Para la asignatura de Introducción a la programación.
// Autor: Darío Quiñones Cruz (2022)

// Utiliza un modesto menú gráfico hecho en graphics.h
// para manejar cubos hechos a partir de nodos con punteros
// a cada dirección alrededor de él (6 nodos).



#include<graphics.h>
#include<conio.h>

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logic.h"
#include "main.h"

int main() {
	int MENU_SIZE = 5;
    bool lines = true;
    int win[2] = {
	(int)(WINDOW_OFFSET*2 + (NODE_OFFSET*MENU_SIZE*1.5)+NODE_SIZE/2),
	(int)(WINDOW_OFFSET*2 + NODE_OFFSET*MENU_SIZE)
	};
	int option;
	int cube_size, cube_type;
	struct Node *cube;

	initwindow(win[0],win[1], "Pointer Cubes");

	// Imprime el menú
	settextstyle(1,0,2);
	outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+0, "Bienvenido al cubo de punteros");
	outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+40,"Elige una opcion:");
	outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+120,"1: Nuevo cubo");
	outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+160,"2: Abrir un Cubo guardado");
	outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+200,"3: Salir");
	printf("1: Nuevo cubo\n2: Abrir un Cubo guardado\n3: Salir\n");

	// Selecciona una opción
	option = getchar();
	cleardevice();

	// Switch para las opciones
	switch(option) {
		case '1':
			// Crea un nuevo cubo de punteros
			// El \xF1 es hexadecimal para ñ
			outtextxy(WINDOW_OFFSET,WINDOW_OFFSET, "Ingresa el tama\xF1o del cubo: "); 
			printf("Tamano: ");
			scanf("%d", &cube_size);
			outtextxy(WINDOW_OFFSET,WINDOW_OFFSET+40, "Ingresa el tipo de cubo: ");
			outtextxy(WINDOW_OFFSET+30,WINDOW_OFFSET+70, "0: Ceros");
			outtextxy(WINDOW_OFFSET+30,WINDOW_OFFSET+100, "1: Secuencial");
			outtextxy(WINDOW_OFFSET+30,WINDOW_OFFSET+130, "2: Aleatorio");
			printf("Tipo: ");
			scanf("%d", &cube_type);
			cleardevice();

			cube = new_cube(cube_size, cube_type);
			printf("Cubo de (%d^3)\n\n", cube_size);
			
			// Dibuja el cubo
			draw_cube(cube, lines, (int)12/(cube_size*2));
			
			// Menu para el cubo
			cube_menu(cube);
			
			free_cube(cube);
			break;
		case '2':
			// WORK IN PROGRESS
			printf("Abrir un Cubo guardado\n\n");
			break;
		case '3':
			// Salir del programa
			exit(0);
			break;
	}
	
	return 0;
}

// Presenta el menú de opciones de cada cubo
//
// cube: Puntero a un cubo
void cube_menu(struct Node *cube) {
	int option, value, changed, exit;
	char confirm_exit;
	int coords[3] = {0,0,0};
	
	do { // Loop hasta Salir
	
		outtextxy(20,30,"1: Guardar   2: Editar    3: Salir");
		printf("1: Guardar\n2: Editar\n");
	
		scanf("%d", &option);
		
		switch(option){
			case 1:
				//printf("Guardar como texto? (y/n)");
				//scanf("%d", &option);
				//if (option == 'y'){
				//	save_cube(cube, 1);
				//} else {
				//	save_cube(cube, 0);
				//}
				save_cube(cube, 1);
				break;
			case 2:
				printf("Editar\n");
				outtextxy(20, 30, "Escoge una coordenada para editar:");
				printf("Coordenadas:\nx: ");
				scanf("%d", &coords[0]);
				printf("y: ");
				scanf("%d", &coords[1]);
				printf("z: ");
				scanf("%d", &coords[2]);
				
				outtextxy(20, 30, "Nuevo valor par a el nodo:        ");
				printf("valor: ");
				scanf("%d", &value);
				edit_coordinate(cube, coords[0], coords[1], coords[2], value);
				changed = true;
				draw_cube(cube, true, 0);
				
				break;
			default:
				if (changed == true) {
					printf("Fueron realizados cambios, est\xE1s seguro que quieres salir? \n(y/n): ");
					scanf("%c", confirm_exit);
					if (confirm_exit == 'y' || confirm_exit == 'Y' ) {
						exit = true;
					}
				} else {
					exit = true;
				}
				printf("Saliendo...\n");
				break;
		}
	} while (exit != true);
}

// Guarda el cubo en un archivo ubicado en /saves/
// WORK IN PROGRESS
// 
// cube: Puntero al primer nodo del cubo
// mode: Tipo de guardado (Requerimento obligatorio)
//		0: Archivo binario
//		1: Archivo de texto
int save_cube(struct Node *cube, int mode){
	unsigned long timestamp = (unsigned long)time(NULL);
	FILE *fptr; // Puntero a un archivo
	char *savename = "saves/saves.txt";
	int size = row_length(cube);
	int total_length = size*size*size;
	// Alocamos un arreglo para los datos del cubo
	int *data = (int*)malloc(total_length * sizeof(int));
	// Un int puede tener un máximo de 5 dígitos en decimal (32,767)
	char *data_str = (char*)malloc(total_length * 5 * sizeof(char));
	
	data = cube_values(cube);
	
	// // Convertimos el arreglo en un string
	// // Puede ser su propia función arr_to_str()
	// for (int i=0; i<length; i++){
	// 		sprintf(&)
	// }
	
	// Escribimos al final del archivo los nuevos datos;
	fptr = fopen(savename,"a");
	
	if (fptr == NULL){
	  printf("Error al abrir \"%s\"", savename);   
	  exit(1);             
	}
	
	
	printf("Escoje un nombre para tu cubo \n");
	scanf("%s", savename);
	
	printf("Guardando...");
	// {
	// Nombre, fecha, tamaño,
	// [Datos]
	// }
	fprintf(fptr,"{\n%s,%ul,%d\n%s\n}",savename, timestamp, size, data_str);
	printf("   Guardado con éxito\n");
	return 0;
}

// Muestra un cubo guardado
// WORK IN PROGRESS
//
// n: Número del archivo
int retrieve_cube(int n){
	// Cada corchete es un cubo diferente,
	// Cada archivo guardado tiene 4 elementos, Nombre, fecha, tamaño y datos
	// A partir de su tamaño y de sus datos lo podemos reconstruir,
	// Y para los gráficos, el nombre está chido.
	// {
	// Nombre, fecha, tamaño,
	// [Datos]
	// }
	return 0;
}

// Dibuja un nodo con líneas dependiendo si existen sus vecinos
//
// n: nodo
// pos: su coordenada dentro del cubo
// lines: Si se dibujan líneas a nodos vecinos
// color: Color del nodo
int draw_node(struct Node *n, int pos[3], bool lines, int color) {
	int x, y, text_len;
	char text[32];
	x = pos[0]+(int)(pos[2]/2);
	y = pos[1]+(int)(pos[2]/3);
	
//	printf("Drawing Node\n");
	setcolor(color);
	setfillstyle(SOLID_FILL, color);
	
	bar(x, y, x+NODE_SIZE,y+NODE_SIZE);
	
	// Dibujar las líneas
	if (lines) {
		setcolor(WHITE);
		if (n->up!=NULL) {
			line(x+(NODE_SIZE/2)+4, y, x+(NODE_SIZE/2)+4, y-NODE_OFFSET+NODE_SIZE);
		}
		if (n->down!=NULL) {
			line(x+(NODE_SIZE/2)-4, y+NODE_SIZE, x+(NODE_SIZE/2)-4, y+NODE_OFFSET);
		}
		if (n->left!=NULL) {
			line(x, y+(NODE_SIZE/2)+4, x-NODE_OFFSET+NODE_SIZE, y+(NODE_SIZE/2)+4);
		}
		if (n->right!=NULL) {
			line(x+NODE_SIZE, y+(NODE_SIZE/2)-4, x+NODE_OFFSET, y+(NODE_SIZE/2)-4);
		}
	}
	
	// Texto dentro del nodo
	sprintf(text, "%d", n->data);
//	printf("text= %d, length %d\n", n->data, strlen(text));
	text_len = strlen(text);
	x += (NODE_SIZE/2) - (7 * text_len);
	y += (NODE_SIZE/2) - (8);
	outtextxy(x, y, text);
	
	return 0;
}

// Itera en el cubo dibujando cada nodo
//
// root: Puntero al primer nodo del cubo
// lines: Si se dibujan lineas a nodos vecinos
// slowness: Tiempo de espera entre nodo y nodo, en milisegundos
int draw_cube(struct Node *cube, bool lines, int slowness) {
	struct Node *previous[3];
    int i, j, k, color = 9;
    int pos[3] = {0,0,0};
    int size = row_length(cube);
    
    // Cierra todo lo demás
    closegraph();
    
    // Una ventana solo para el cubo
	initwindow((size*90)+50*2,(size*80)+50*2, "Cube");
	
	settextstyle(1,0,1);

    previous[0] = cube; // previo nodo x
    previous[1] = cube; // previa fila y
    previous[2] = cube; // previa cara z
    
    for (i = 0; i < size; i++){
    	pos[2]=i*NODE_OFFSET+ WINDOW_OFFSET;
        for (j = 0; j < size; j++){
        	pos[1]=j*NODE_OFFSET+ WINDOW_OFFSET;
            for (k = 0; k < size; k++){
            	pos[0]=k*NODE_OFFSET+ WINDOW_OFFSET;
				
				draw_node(previous[0], pos, lines, color);
				delay(slowness);
                // Nos movemos al siguiente nodo
                previous[0] = previous[0]->right;
            }

            // Nos movemos a la siguiente fila
            previous[1] = previous[1]->down;
            // Reiniciamos el puntero al valor actual
            previous[0] = previous[1];
        }
        color = (color%15)+1;
        // Nos movemos a la siguiente cara
        previous[2] = previous[2]->front;
        // Reiniciamos el puntero a la fila actual y al valor actual
        previous[1] = previous[2];
        previous[0] = previous[2];
    }
    
    return 0;
}
