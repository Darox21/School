#include <stdio.h>
#include <stdlib.h>

// Si utilizamos en cambio una estructura para guardar los datos,
// podemos guardar los datos en una sola variable.

struct Persona{
    char *Nombre;
    int Edad;
    float Peso;
};

void main(){
    struct Persona Juan = {
        "Juan",
        21,
        52.5
    };

    struct Persona Karel = {
        "Karel",
        19,
        78.5
    };

    printf(
        "\n%s tiene %d años y pesa %.2f kg\n", 
        Juan.Nombre, 
        Juan.Edad, 
        Juan.Peso
    );

    printf(
        "%s tiene %d años y pesa %.2f kg\n\n", 
        Karel.Nombre, 
        Karel.Edad, 
        Karel.Peso
    );

}