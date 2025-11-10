#include <stdio.h>      // Librería estándar para funciones de entrada/salida (printf, fprintf, etc.)
#include <stdlib.h>     // Librería estándar para gestión de memoria y conversión de datos (malloc, atoi, etc.)
#include <pthread.h>    // Librería para manejo de hilos POSIX (pthread_create, pthread_join, etc.)

// -------------------------------------------------------------
// Estructura para pasar múltiples argumentos al hilo trabajador
// -------------------------------------------------------------
typedef struct {
    int *arr;  // Puntero al arreglo compartido donde se guardará la secuencia
    int n;     // Número de elementos que debe generar la secuencia
} FibData;

// -------------------------------------------------------------
// Función que ejecutará el hilo trabajador
// Esta función calcula la secuencia de Fibonacci y la guarda en el arreglo
// -------------------------------------------------------------
void *generar_fibonacci(void *arg) {
    FibData *data = (FibData *)arg;  // Convertir el argumento genérico a un puntero de tipo FibData
    int *arr = data->arr;            // Obtener el puntero al arreglo
    int n = data->n;                 // Obtener el tamaño de la secuencia

    // Casos base: los dos primeros números de Fibonacci
    if (n > 0) arr[0] = 0;
    if (n > 1) arr[1] = 1;

    // Generar los siguientes términos de la secuencia
    for (int i = 2; i < n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    pthread_exit(NULL);  // Indica que el hilo ha terminado su ejecución correctamente
}

// -------------------------------------------------------------
// Función principal del programa
// -------------------------------------------------------------
int main(int argc, char *argv[]) {
    // Verificar que el usuario ingresó el número correcto de argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <N>\n", argv[0]);
        return 1; // Termina el programa con error
    }

    int N = atoi(argv[1]); // Convertir el argumento de texto a un número entero

    // Validar que el número de elementos sea mayor que cero
    if (N <= 0) {
        fprintf(stderr, "El número de elementos debe ser mayor que 0.\n");
        return 1;
    }

    // -------------------------------------------------------------
    // Asignar memoria dinámica para el arreglo que almacenará la secuencia
    // -------------------------------------------------------------
    int *fibonacci = (int *)malloc(N * sizeof(int));  // Se reserva memoria para N enteros
    if (fibonacci == NULL) {  // Verificar si la asignación falló
        perror("Error al asignar memoria");
        return 1;
    }

    // -------------------------------------------------------------
    // Preparar los datos que se pasarán al hilo trabajador
    // -------------------------------------------------------------
    FibData data;
    data.arr = fibonacci; // Asignar el puntero del arreglo
    data.n = N;           // Asignar la cantidad de números a generar

    pthread_t hilo;       // Declarar la variable para el identificador del hilo

    // -------------------------------------------------------------
    // Crear el hilo trabajador que generará la secuencia
    // -------------------------------------------------------------
    if (pthread_create(&hilo, NULL, generar_fibonacci, &data) != 0) {
        perror("Error al crear el hilo");
        free(fibonacci);  // Liberar la memoria si ocurre un error
        return 1;
    }

    // -------------------------------------------------------------
    // Esperar a que el hilo trabajador termine su ejecución
    // -------------------------------------------------------------
    pthread_join(hilo, NULL);

    // -------------------------------------------------------------
    // Imprimir la secuencia de Fibonacci almacenada en el arreglo
    // -------------------------------------------------------------
    printf("Secuencia de Fibonacci (%d elementos):\n", N);
    for (int i = 0; i < N; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    // -------------------------------------------------------------
    // Liberar la memoria asignada dinámicamente
    // -------------------------------------------------------------
    free(fibonacci);

    return 0;  // Fin del programa
}
