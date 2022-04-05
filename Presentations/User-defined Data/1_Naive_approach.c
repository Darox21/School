#include <stdio.h>
#include <stdlib.h>

// Considerando un pensamiento directo.
// Si tenemos una serie de datos, lo claro es guardarlos cada
// uno en una variable.

void main(){
    char *Nombre = "Juan";
    int Edad = 21;
    float Peso = 52.5;
    system("clear");
    
    printf(
        "\n%s tiene %d años y pesa %.2f kg\n\n", 
        Nombre, 
        Edad, 
        Peso
    );

}