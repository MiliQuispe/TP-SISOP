#include "Personas.h"

void generarPersonaBancaria(t_persona* persona, int id) {
    char nombres[CANT][ESP] = {
        "Ana","Luis","Maria","Juan","Lucia","Pedro","Sofia","Diego","Valentina","Martin",
        "Camila","Javier","Carla","Fernando","Micaela","Andres","Julieta","Matias","Paula","Nicolas",
        "Agustina","Santiago","Rocio","Gonzalo","Victoria","Emiliano","Abril","Ramiro","Florencia","Franco",
        "Gabriela","Hernan","Esteban","Patricia","Cecilia","Alejandro","Liliana","Ivan","Marcos","Clara",
        "Elena","Daniel","Laura","Ezequiel","Silvia","Tomas","Noelia","Bruno","Alicia","Celeste",
        "Hugo","Cintia","Pablo","Lorena","Adrian","Marcela","Eduardo","Mariano","Pilar","Federico",
        "Graciela","Oscar","Leandro","Ariana","Miguel","Daniela","Damian","Raul","Teresa","Carolina",
        "Sebastian","Malena","Alfredo","Elsa","Cristian","Veronica","Manuel","Claudio","Pamela","Estela",
        "Rafael","Norma","Mario","Gloria","Guillermo","Josefina","Maximiliano","Irene","Ariel","Beatriz",
        "Fabian","Nora","Leonardo","Soledad","Agustin","Barbara","Julio","Natalia","Ricardo","Tamara"
    };
    
    char apellidos[CANT][ESP] = {
        "Garcia","Lopez","Martinez","Rodriguez","Fernandez","Gomez","Diaz","Sanchez","Romero","Alvarez",
        "Torres","Ruiz","Ramirez","Molina","Suarez","Ortega","Delgado","Castro","Ortiz","Vargas",
        "Silva","Morales","Herrera","Medina","Aguilar","Paredes","Rojas","Reyes","Mendez","Castillo",
        "Cabrera","Dominguez","Figueroa","Navarro","Campos","Pena","Cruz","Vega","Fuentes","Correa",
        "Ramos","Acosta","Bravo","Rivera","Roman","Esquivel","Nunez","Benitez","Palacios","Meza",
        "Godoy","Escobar","Bustos","Montoya","Maldonado","Varela","Peralta","Quiroga","Villalba","Luna",
        "Ponce","Ferrer","Bermudez","Roldan","Ojeda","Farias","Toledo","Vidal","Lozano","Zarate",
        "Arce","Paez","Ayala","Moreno","Caceres","Saavedra","Ledesma","Miranda","Cardozo","Cordoba",
        "Orozco","Camacho","Castano","Loyola","Herrero","Ibarra","Acuna","Mansilla","Bravo","Rico",
        "Olivera","Valdez","Chavez","Alonso","Salinas","Lemus","Ferreyra","Carrizo","Camposo","Villar"
    };


    persona->id = id;
    persona->nroCuenta = 1000 + id; 
    persona->dni = 10000000 + id;  
    strcpy(persona->nombre , nombres[rand() % 100]);
    strcpy(persona->apellido , apellidos[rand() % 100]);
    persona->fondo = (double)(rand() % 100000000); 
}

FILE* abrirPersonaCSV(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w+"); 

    if (archivo == NULL) {
            perror("Error al crear el archivo");
            return NULL;
        }
        fprintf(archivo, "id,nroCuenta,dni,nombre,apellido,fondo\n");
        fflush(archivo);

    return archivo;
}

int insertarPersonaCSV(FILE* archivo, t_persona* persona) {
    if (archivo == NULL || persona == NULL) return -1;

    fseek(archivo, 0, SEEK_END);


    fprintf(archivo, "%d,%d,%d,%s,%s,%.2lf\n",
            persona->id,
            persona->nroCuenta,
            persona->dni,
            persona->nombre,
            persona->apellido,
            persona->fondo);

    fflush(archivo); 
    return 0; 
}

int cerrarPersonaCSV(FILE* archivo) {
    if (archivo != NULL) {
        fclose(archivo);
        return 0; 
    }
    return -1; 
}

int obtenerUltimoID(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo){
        return 0; 
    }

    char linea[256];
    int ultimoID = 0;

   
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        int id;
        sscanf(linea, "%d,", &id); 
        ultimoID = id;
    }

    fclose(archivo);
    return ultimoID;
}