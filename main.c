#include <stdio.h>
#include "Personas.h"

int main() {
    t_persona persona;

    for(int i = 0; i < 10; i++) {
        generarPersonaBancaria(&persona, i+1);
        printf("ID: %d, Nro Cuenta: %d, DNI: %d, Nombre: %s, Apellido: %s, Fondo: %.2f\n",
               persona.id, persona.nroCuenta, persona.dni, persona.nombre, persona.apellido, persona.fondo);
    }
    return 0;
}