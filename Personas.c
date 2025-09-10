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
