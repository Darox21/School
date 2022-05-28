// Este programa dibuja el famoso copo de nieve de Koch
// Autor: Darío Quiñones Cruz (2022)

#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define OFFSET 125 // Offset de la ventana
#define SIZE 400 // Tamaño del copo de nieve
#define PI 3.14159265 // Pi
#define LEVEL 4 // Nivel de recursividad

// Longitud de el sub-triangulo
float LENGTH = 1/3.3334;
// Proporción de la segmentación, 3 son tercios.
float PROPORTION = 3;

void draw_triangle(int n, int x1, int y1, int x2, int y2, int x3, int y3);
void draw_line(int n, int x1, int y1, int x5, int y5);

int main() {
   int gd = DETECT, gm;
   int i;
   float l;
   int p[3][2] ={ // Triángulo equilátero
      {OFFSET, OFFSET},
      {OFFSET+SIZE, OFFSET},
      {(int)OFFSET+SIZE/2, OFFSET+(int)(SIZE*sin(PI/3))}
   };

   initgraph(&gd, &gm, "C:\\TC\\BGI");


   setcolor(WHITE); // Color de la línea
   for (i = 0; i <= LEVEL+1; i++) {
      // Limpia la pantalla
      cleardevice();
      // Dibuja el triángulo
      draw_triangle(i, p[0][0], p[0][1], p[1][0], p[1][1], p[2][0], p[2][1]);
      floodfill(p[0][0]+2, p[0][1]+2, WHITE);
      // Espera un segundo
      sleep(1);
   }

   // Transición de el copo inverso al copo original
   i = 1;
   LENGTH-=0.05; // Cambiamos cada iteración la longitud del sub-triangulo
   for (l = LENGTH+0.05; LENGTH >= -l; LENGTH-=0.05) {
      setcolor(i);
      draw_triangle(LEVEL, p[0][0], p[0][1], p[1][0], p[1][1], p[2][0], p[2][1]);
      sleep(1);
      i++; // Cambia el color de la línea
   }

   // Dibujado final
   sleep(1);
   setcolor(WHITE);
   cleardevice();
   // Triangulo en el sentido del reloj
   draw_triangle(LEVEL+1, p[0][0], p[0][1], p[1][0], p[1][1], p[2][0], p[2][1]);
   sleep(2);
   cleardevice();
   // Triangulo en el sentido contra el reloj
   draw_triangle(LEVEL+1, p[1][0], p[1][1], p[0][0], p[0][1], p[2][0], p[2][1]);

   // Pausa y Cierra
   getch();
   closegraph();
   return 0;
}

// Dibuja un triangulo según los puntos dados, con el nivel de recursividad
// dado.
//
// n: Nivel de recursividad
// x1, y1: Coordenadas del primer punto
// x2, y2: Coordenadas del segundo punto
// x3, y3: Coordenadas del tercer punto
void draw_triangle(int n, int x1, int y1, int x2, int y2, int x3, int y3) {
   draw_line(n, x1, y1, x2, y2);
   draw_line(n, x2, y2, x3, y3);
   draw_line(n, x3, y3, x1, y1);
}


// Dibuja una linea, subdividiéndola recursivamente.
//
// n: Nivel de recursividad
// x1, y1: Coordenadas del primer punto
// x5, y5: Coordenadas del segundo punto
void draw_line(int n, int x1, int y1, int x5, int y5) {
   int midx, midy, x2, y2, x3, y3, x4, y4;
   float magnitude, m, ortho_m;
   // Caso base: Dibuja la linea
   if (n == 0) {
      line(x1, y1, x5, y5);
   } else { // Caso recursivo: Dibuja 4 lineas
      // Calcula la magnitud de la linea
      magnitude = sqrt(pow(x5 - x1, 2) + pow(y5 - y1, 2));
      // Pendiente de la linea
      m = (float)(y5 - y1) / (float)(x5 - x1);
      // Pendiente ortogonal a la linea
      ortho_m = atan(-1/m);// arcotangente de -1/m
      // Calcula el punto medio de la linea
      midx = (x1 + x5) / 2;
      midy = (y1 + y5) / 2;

      // Calcula el punto central del sub-triangulo.
      // Un punto sobre la recta perpendicular a la linea.
      if (y1>y5) {
         x3 = midx - (int)(magnitude*LENGTH * cos(ortho_m));
         y3 = midy - (int)(magnitude*LENGTH * sin(ortho_m));
      } else {
         x3 = midx + (int)(magnitude*LENGTH * cos(ortho_m));
         y3 = midy + (int)(magnitude*LENGTH * sin(ortho_m));
      }

      // Dividimos la linea original en una proporción dada.
      x2 = (x5-x1) / PROPORTION + x1;
      y2 = (y5-y1) / PROPORTION  + y1;
      x4 = -(x5-x1) / PROPORTION  + x5;
      y4 = -(y5-y1) / PROPORTION  + y5;


      // Dibuja los 4 sub-triangulos, recursivamente.
      draw_line(n-1, x1, y1, x2, y2);
      draw_line(n-1, x2, y2, x3, y3);
      draw_line(n-1, x3, y3, x4, y4);
      draw_line(n-1, x4, y4, x5, y5);
   }
}
