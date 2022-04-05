#include <stdio.h>
#include <stdlib.h>

void con_arreglos();

// Pero este acercamiento se vuelve impráctico 
// con múltiples personas.

void main(){
    char *Nombre = "Juan";
    int Edad = 21;
    float Peso = 52.5;
    // system("clear");
    
    printf(
        "\n%s tiene %d años y pesa %.2f kg\n", 
        Nombre, 
        Edad, 
        Peso
    );

    char *Nombre2 = "Karel";
    int Edad2 = 19;
    float Peso2 = 78.5;

    printf(
        "%s tiene %d años y pesa %.2f kg\n\n", 
        Nombre2, 
        Edad2, 
        Peso2
    );

    // Por otra parte, lo podemos intentar hacer con arreglos.
    
    // con_arreglos();
}

// Funciona, pero en realidad los nombres y las edades no están relacionados,
// Son arreglos completamente independientes.

void con_arreglos(){
    char Nombres[2][10] = {
        "César",
        "Ángel"
    };

    int Edades[2] = {
        19,
        19
    };

    float Pesos[2] = {
        70.5,
        72.5
    };

    // system("clear");

    for(int i = 0; i < 2; i++){
        printf(
            "%s tiene %d años y pesa %.2f kg\n", 
            Nombres[i], 
            Edades[i], 
            Pesos[i]
        );
    }
}