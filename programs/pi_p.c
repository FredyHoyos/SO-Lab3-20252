#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para atoi, exit
#include <math.h>       // Para fabs
#include <pthread.h>    // Para pthread_create, pthread_join, etc.
#include <sys/time.h>   // Para medir el tiempo con gettimeofday

// ------------------------------------------------------------
// Estructura que almacena los datos de cada hilo
// ------------------------------------------------------------
typedef struct {
    int n;              // Total de intervalos
    int start;          // Índice inicial del hilo
    int end;            // Índice final del hilo
    double partialSum;  // Resultado parcial que calcula el hilo
} ThreadData;

// ------------------------------------------------------------
// Función para obtener el tiempo actual en segundos
// ------------------------------------------------------------
double GetTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

// ------------------------------------------------------------
// Función que ejecuta cada hilo
// ------------------------------------------------------------
void* threadCalc(void* arg)
{
    ThreadData* data = (ThreadData*)arg;
    double fH = 1.0 / (double)data->n;
    double sum = 0.0;
    double fX;

    for (int i = data->start; i < data->end; i++) {
        fX = fH * ((double)i + 0.5);
        sum += 4.0 / (1.0 + fX * fX);
    }

    data->partialSum = sum;
    pthread_exit(NULL);
}

// ------------------------------------------------------------
// Programa principal
// Uso: ./pi_p <n> <num_hilos>
// ------------------------------------------------------------
int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Uso: %s <n> <num_hilos>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    pthread_t threads[numThreads];
    ThreadData data[numThreads];

    int chunk = n / numThreads;

    // Inicia medición de tiempo
    double startTime = GetTime();

    // Crear los hilos
    for (int i = 0; i < numThreads; i++) {
        data[i].n = n;
        data[i].start = i * chunk;
        data[i].end = (i == numThreads - 1) ? n : (i + 1) * chunk;
        data[i].partialSum = 0.0;
        pthread_create(&threads[i], NULL, threadCalc, &data[i]);
    }

    // Esperar a que todos terminen
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combinar resultados parciales
    double totalSum = 0.0;
    for (int i = 0; i < numThreads; i++) {
        totalSum += data[i].partialSum;
    }

    // Finaliza medición de tiempo
    double endTime = GetTime();
    double elapsed = endTime - startTime;

    // Resultado final
    double pi = (1.0 / (double)n) * totalSum;
    const double realPi = 3.14159265358979323846;

    printf("\npi ≈ %.20f\nError = %.20f\n", pi, fabs(pi - realPi));
    printf("Tiempo de ejecución: %.6f segundos\n", elapsed);

    return 0;
}
