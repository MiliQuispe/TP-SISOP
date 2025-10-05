#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>
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
void generarRegistros(t_persona* persona, int cantidad, int inicioID);
int insertarPersonaCSV(FILE* archivo, t_persona* persona);
FILE* abrirPersonaCSV(const char* nombreArchivo);   
int cerrarPersonaCSV(FILE* archivo);
int obtenerUltimoID(const char* nombreArchivo); // o mientras se inserta se guarda ese id como ultimo? lo hice por las dudas