#include "get_next_line.h"  // Incluye el header donde está declarado get_next_line.
#include <fcntl.h>          // Biblioteca para manipulación de archivos (open, close).
#include <stdio.h>          // Biblioteca estándar para entrada/salida (printf).

int main() {
    // Abre el archivo "test.txt" en modo solo lectura (O_RDONLY)
    int fd = open("test.txt", O_RDONLY);
    
    // Verifica si la apertura del archivo fue exitosa
    if (fd < 0) 
    {
        perror("Error al abrir el archivo");
        return 1;  // Retorna un código de error si la apertura falla.
    }

    char *line;  // Puntero para almacenar lcada línea leída.

    // Bucle que llama repetidamente a get_next_line hasta que devuelve NULL (fin de archivo o error).
    while ((line = get_next_line(fd))) 
    {  
        printf("%s", line);  // Imprime la línea obtenida (ya contiene el '\n' si está en el archivo).
        free(line);  // Libera la memoria asignada para evitar fugas de memoria.
    }

    // Cierra el archivo después de leer todas las líneas.
    close(fd);

    return 0;  // Retorna 0 indicando que el programa terminó correctamente.
}

