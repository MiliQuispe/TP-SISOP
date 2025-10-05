# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lrt -lpthread

# Nombre del ejecutable
TARGET = main

# Archivos fuente y objetos
SOURCES = main-coordinador.c Personas.c
OBJECTS = $(SOURCES:.c=.o)

# Headers
HEADERS = Personas.h

# Regla principal
all: $(TARGET)

# Compilar también el programa de prueba
prueba: $(PRUEBA_OBJ) Personas.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar archivos objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Limpiar y recompilar
rebuild: clean all

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Reglas que no son archivos
.PHONY: all clean rebuild run