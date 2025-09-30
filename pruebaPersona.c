#include "Personas.h"

int main() {
    t_persona persona;

    // for(int i = 0; i < 10; i++) {
    //     generarPersonaBancaria(&persona, i+1);
    //     printf("ID: %d, Nro Cuenta: %d, DNI: %d, Nombre: %s, Apellido: %s, Fondo: %.2f\n",
    //            persona.id, persona.nroCuenta, persona.dni, persona.nombre, persona.apellido, persona.fondo);
    // }

    FILE* archivo = abrirPersonaCSV("personas.csv");
    if (archivo == NULL) {
        return -1; // Error al abrir o crear el archivo
    }   
    for(int i = 0; i < 10; i++) {
        generarPersonaBancaria(&persona, i);
        if (insertarPersonaCSV(archivo, &persona) != 0) {
            cerrarPersonaCSV(archivo);
            return -1; 
        }
    }
    for(int i = 11; i < 20; i++) {
        generarPersonaBancaria(&persona, i);
        if (insertarPersonaCSV(archivo, &persona) != 0) {
            cerrarPersonaCSV(archivo);
            return -1; 
        }
    }

    printf("Ultimo ID: %d\n", obtenerUltimoID("personas.csv"));

    cerrarPersonaCSV(archivo);

    return 0;
}