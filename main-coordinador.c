#include "Personas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>

// --- CONSTANTES ---
#define SHM_NAME "/shm_personas"
#define SEM_BUFFER_NAME "/sem_buffer"
#define SEM_MUTEX_NAME "/sem_mutex_id"
#define FILENAME "personas.csv"
#define BLOCK_SIZE 10 // Tamaño del bloque de IDs a solicitar

typedef struct {
    int id;
    int dni;
    int nroCuenta;
    char nombre[30];
    char apellido[30];
    double fondos
} t_persona;


int main(){

    int procesos, registros;
    int  i = 0;
    FILE *reg;

    // Entrada de Datos
    if (scanf("%d", &procesos) != 1 || procesos <= 0) {
        fprintf(stderr, "Error: Cantidad de procesos generadores no válida.\n");
        return 1;
    }

    printf("Ingresar la cantidad total de registros a generar: ");
    if (scanf("%d", &registros) != 1 || registros <= 0) {
        fprintf(stderr, "Error: Cantidad total de registros no válida.\n");
        return 1;
    }

    srand(time(NULL));

    // Crear memoria compartida, solo un t_persona y no un array
    /*
    idMemoria = shm_open...

    ftruncate...

    t_persona *persona = ...

    close(idMemoria)
    */

    int idMemoria = shm_open(NombreMemoria,
                            O_CREAT | O_RDWR,
                            0600);
    if (idMemoria == -1) {
        perror("shm_open(SHM_PERSONA)");
        return 1;
    }  

    if (ftruncate(idMemoria, sizeof(t_persona)) == -1) {
        perror("ftruncate(SHM_PERSONA)");
        shm_unlink(NombreMemoria); // Limpieza
        return 1;
    }

    t_persona *persona = (t_persona*) mmap(NULL,
                                            sizeof(t_persona),
                                            PROT_READ | PROT_WRITE,
                                            MAP_SHARED,
                                            idMemoria,
                                            0);
    if (persona == MAP_FAILED) {
        perror("mmap(SHM_PERSONA)");
        shm_unlink(NombreMemoria); // Limpieza
        return 1;
    }

    close(idMemoria);

    // 1. Crear/Abrir SHM para el ID Counter
    int idMemoriaID = shm_open(nombreId, O_CREAT | O_RDWR, 0600);
    
    if (idMemoriaID == -1) {
        perror("shm_open(SHM_ID)");
        munmap(persona, sizeof(t_persona)); 
        shm_unlink(NombreMemoria);
        return 1;
    }


    // 2. Dimensionar la SHM para un entero (int)
    if (ftruncate(idMemoriaID, sizeof(int)) == -1) {
        perror("ftruncate(SHM_ID)");
        shm_unlink(nombreId); 
        munmap(persona, sizeof(t_persona));
        shm_unlink(NombreMemoria);
        return 1;
    }


    // 3. Mapear la SHM
    int *listos = (int*) mmap(NULL, sizeof(int), 
                                    PROT_READ | PROT_WRITE, MAP_SHARED, 
                                    idMemoriaID, 0);
    

    if (listos == MAP_FAILED) {
        perror("mmap(SHM_ID)");
        shm_unlink(nombreId); 
        munmap(persona, sizeof(t_persona));
        shm_unlink(NombreMemoria);
        
        return 1;
    }

    close(idMemoriaID); // Cerrar el descriptor
    
    *listos = 0; // Inicializar el contador de IDs generados

    // Crear semaforo
    /*
    semaforos = controlTotal, registro 
    sem_t *semaforo = ...
    */

    // espacio del buffer 1
    sem_t *buffer = sem_open("buffer",
                            O_CREAT,
                            0600,
                            1);
        if (buffer == SEM_FAILED) {
            perror("sem_open(buffer)");

            munmap(persona, sizeof(t_persona));
            munmap(listos, sizeof(int)); 
            shm_unlink(NombreMemoria);
            shm_unlink(nombreId); 
            return 1; 
        }

    // espacio que hay en el buffer ocupado 0
    sem_t *ocupado = sem_open("ocupado",
                            O_CREAT,
                            0600,
                            0);
    if (ocupado == SEM_FAILED) {
        perror("sem_open(ocupado)");
        munmap(persona, sizeof(t_persona));
        munmap(listos, sizeof(int)); 
        shm_unlink(NombreMemoria);
        shm_unlink(nombreId); 
        sem_close(buffer);
        sem_unlink("buffer");
        return 1;
    }

    sem_t *control = sem_open("control",
                            O_CREAT,
                            0600,
                            1);
    if (control == SEM_FAILED) {
        perror("sem_open(control)");
        munmap(persona, sizeof(t_persona));
        munmap(listos, sizeof(int)); 
        shm_unlink(NombreMemoria);
        shm_unlink(nombreId); 
        sem_close(buffer);
        sem_unlink("buffer");
        sem_close(ocupado);
        sem_unlink("ocupado");
        return 1;
    }

    sem_t *semId= sem_open("semId",
                            O_CREAT,
                            0600,
                            1);
    if (semId == SEM_FAILED) {
        perror("sem_open(semId)");
        munmap(persona, sizeof(t_persona));
        munmap(listos, sizeof(int)); 
        shm_unlink(NombreMemoria);
        shm_unlink(nombreId); 
        sem_close(buffer);
        sem_unlink("buffer");
        sem_close(ocupado);
        sem_unlink("ocupado");
        sem_close(control);
        sem_unlink("control");
        return 1;
    }
    

    // un pid para cada proceso
    pid_t pids[procesos];


    // Tomo como proceso coordinador al proceso padre (Revisar esto)
    // Creo los procesos generadores y guardo si pid en en el array pids[]

    pid_t pid;

   

    for(i ; i < procesos; i++)
    {
        pid = fork();

        if(pid == -1){
            printf("Error en el fork");
            exit(1);
        }
        else
            if (pid == 0){
                // Es el hijo
                // y realiza la produccion

                if((registros - *listos) >= 10){

                    sem_wait(semId);
                    *listos= *listos + 10;
                    sem_post(semId);
                    // Lo pongo abajo para darle algo de paralelismo
                    //funcion generar registro(10)

                    for(int j = 0; j < 10; j++){

                        sem_wait(buffer);
                        sem_wait(control);
                        generarPersonaBancaria(persona, *listos - 10 + j + 1);
                        sem_post(control);
                        sem_post(ocupado);

                        // insertarPersonaCSV(reg, persona); // No deberia escribir aca
                    }
                }
                
                else if ((registros - *listos) < 10 && (registros - *listos) > 0){

                    sem_wait(semId);
                    //idMemoria= listos + (registros - listos);
                    *listos = *listos + (registros - *listos);
                    sem_post(semId);

                    //funcion generar registro(listos - registros)

                    for(int j = 0; j < (registros - *listos); j++){
                        sem_wait(buffer);
                        sem_wait(control);
                        generarPersonaBancaria(persona, *listos - (registros - *listos) + j + 1);
                        sem_post(control);
                        sem_post(ocupado);
                        
                        
                        // insertarPersonaCSV(reg, persona); // No deberia escribir aca

                    }

                }

                exit(0); // El hijo termina
            }
            else{
                // es el padre
                pids[i] = pid;
                // consume desde aca la memoria compartida
                // y escribe en el archivo CSV
            } 
    }

    

    // Abro / Creo el archivo CSV
    reg = abrirPersonaCSV(FILENAME);
        if (reg == NULL) {
            return -1; // Error al abrir o crear el archivo
        }

    if(pid != 0){

        // P(controlTotal) Para que no entre si ya llegamos al limite
        while (listos < registros)
        {
            // NOTA: deberia enviar un puntero a la variable t_persona como parametreo a la funcion generadora
            // De momento deberia recibir 2 parametros, el puntero a la variable y la cantidad (10 o menos) REVISAR

            sem_wait(ocupado);
            sem_wait(control);
            // Escribo en el archivo CSV

            insertarPersonaCSV(reg, persona);
            
            // fwrite(persona, sizeof(t_persona), 1, reg);

            sem_post(buffer);

            sem_post(control);
            //REVISAR si es bien la logica del semaforo registro, que actuaria como el del buffer
        }
        
    }

    for (int k = 0; k < procesos; k++) {
        wait(NULL); 
    }

    // Cerrar el archivo CSV

    if(cerrarPersonaCSV(reg) != 0){
        printf("Error al cerrar el archivo\n");
        return -1;
    }

    // Esperar a los procesos hijos o esperar que terminen, ver eso

    
    // Liberar recursos
    /*
    munmap....

    sem_close...

    sem_unlink...

    munmap...
    
    shm_unlink...
    */

    // Liberar recursos
    sem_close(buffer);
    sem_close(ocupado);    // <--- AGREGADO
    sem_close(control);
    sem_close(semId);      // <--- AGREGADO

    sem_unlink("buffer");
    sem_unlink("ocupado"); // <--- AGREGADO (Usando el nombre que abriste)
    sem_unlink("control");
    sem_unlink("semId");   // <--- AGREGADO (Usando el nombre que abriste)

    munmap(persona, sizeof(t_persona));
    munmap(listos, sizeof(int)); // <--- AGREGADO para el SHM del ID
    shm_unlink(NombreMemoria);
    shm_unlink(nombreId); // <--- AGREGADO para el SHM del ID

    return(0);

    // DEFINIR variables globales para los errores, constantes, etc...

}
