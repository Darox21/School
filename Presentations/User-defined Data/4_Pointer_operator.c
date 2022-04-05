#include <stdio.h>
#include <stdlib.h>


typedef struct Persona{
    char *Nombre;
    int Edad;
    float Peso;
    char *RFC;
} Persona;

// Podemos pasar como parámetro una estructura.
void facturarCafe(Persona *persona, int costo){
    printf("\nCliente: %s\n", persona->Nombre);
    printf("RFC: %s\n", persona->RFC); // persona->RFC es equivalente a (*persona).RFC
    printf("Domicilio [...]:\n");

    printf("\n%s ha pagado %d pesos por un café\n", persona->Nombre, costo);
}

void main(){
    Persona Juan = {
        "Juan",
        21,
        52.5,
        "1234567890"
    };

    facturarCafe(&Juan, 25);
}