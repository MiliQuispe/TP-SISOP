#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CANT 100
#define ESP 30

typedef struct {
    int id;
    int nroCuenta;
    int dni;
    char nombre[30];
    char apellido[30];
    double fondo;

} t_persona;



void generarPersonaBancaria(t_persona* persona, int id);
