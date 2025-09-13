#include "Personas.h"

typedef struct {
    int id;
    int dni;
    int nroCuenta;
    char nombre[30];
    char apellido[30];
    float fondos
} t_persona;


int main(){

    int procesos, registros, listos;
    int  i = 0;
    FILE *reg;

    printf("Ingresar la cantidad de procesos generadors: ");
    scanf("%d", &procesos);

    printf("Ingresar la cantidad total de registros a generar: ");
    scanf("%d", &registros);

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

    ftruncate(idMemoria, sizeof(t_persona));

    t_persona *persona = (t_persona*) mmap(NULL,
                                            sizeof(t_persona),
                                            PROT_READ | PROT_WRITE,
                                            MAP_SHARED,
                                            idMemoria,
                                            0);

    close(idMemoria);
    

    // Crear semaforo
    /*
    semaforos = controlTotal, registro 
    sem_t *semaforo = ...
    */

    sem_t *buffer = sem_open("buffer",
                            O_CREAT,
                            0600,
                            1);

    sem_t *control = sem_open("control",
                            O_CREAT,
                            0600,
                            1);
    

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
            exit(0);
        }
        else
            if (pid == 0){
                // Es el hijo
            }
            else // es el padre
                pids[i] = pid;
    }

    listos = 0;

    // Abro / Creo el archivo CSV

    if(pid != 0){

        // P(controlTotal) Para que no entre si ya llegamos al limite
        sem_wait(control);
        while (listos < registros)
        {
            // NOTA: deberia enviar un puntero a la variable t_persona como parametreo a la funcion generadora
            // De momento deberia recibir 2 parametros, el puntero a la variable y la cantidad (10 o menos) REVISAR

            if((registros - listos) >= 10){
            listos = listos + 10;
            sem_post(control);
            // Lo pongo abajo para darle algo de paralelismo
            //funcion generar registro(10)
            }
            else{
            listos = listos + (registros - listos);
            sem_post(control);
            //funcion generar registro(listos - registros)
            }

            // Escribo en el archivo CSV

            fwrite(persona, sizeof(t_persona), 1, reg);

            sem_post(buffer);

            sem_wait(control);
            //REVISAR si es bien la logica del semaforo registro, que actuaria como el del buffer
        }
        
    }

    // Cerrar el archivo CSV
    fclose(reg);

    // Esperar a los procesos hijos o esperar que terminen, ver eso

    
    // Liberar recursos
    /*
    munmap....

    sem_close...

    sem_unlink...

    munmap...
    
    shm_unlink...
    */

    sem_close(buffer);
    sem_close(control);

    sem_unlink("buffer");
    sem_unlink("control");

    munmap(persona, sizeof(t_persona));
    shm_unlink(NombreMemoria);

    return(0);

    // DEFINIR variables globales para los errores, constantes, etc...

}
