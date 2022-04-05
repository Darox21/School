#include <stdio.h>
#include <stdlib.h>


// Por otra parte, podemos darle un alias a la estructura.
// por si no queremos escribir todo el nombre de la estructura.
typedef struct Persona{
    char *Nombre;
    int Edad;
    float Peso;
} Alguien; // <-- Alias de la estructura.

// Typedefs son aliases para estructuras, de una forma parecida a #define.
// Por ejemplo:
typedef unsigned long ulong;

void main(){
    Alguien Dario = {
        "Darío",
        34,
        53.5
    };

    printf(
        "\n%s tiene %d años y pesa %.2f kg\n", 
        Dario.Nombre, 
        Dario.Edad, 
        Dario.Peso
    );
}