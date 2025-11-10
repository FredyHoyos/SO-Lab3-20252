#include <stdio.h>   // Biblioteca estándar para funciones de entrada/salida (printf, etc.)
#include <math.h>    // Biblioteca matemática (necesaria para fabs y operaciones con double)
#include <stdlib.h>  // Biblioteca estándar general (no se usa mucho aquí, pero útil para futuras expansiones)
#include <sys/time.h> // Para medir el tiempo con gettimeofday()

// ------------------------------------------------------------
// Función f(x): representa la función matemática del integrando
// En este caso, f(x) = 4 / (1 + x^2)
// que corresponde a la función cuya integral definida entre 0 y 1
// es igual a π (pi).
// ------------------------------------------------------------
double f(double a)
{
    return (4.0 / (1.0 + a * a));
}

// ------------------------------------------------------------
// Función CalcPi: calcula una aproximación del número π
// usando el método de integración numérica (regla del punto medio).
//
// Parámetros:
//   n → número de intervalos (mayor n = mayor precisión)
//
// Procedimiento:
//   1. Divide el intervalo [0,1] en n subintervalos iguales.
//   2. Calcula el valor de f(x) en el punto medio de cada subintervalo.
//   3. Suma todas las áreas aproximadas de los rectángulos.
// ------------------------------------------------------------
double CalcPi(long long n)
{
    const double fH = 1.0 / (double)n;  // Ancho de cada subintervalo
    double fSum = 0.0;                  // Acumulador para la suma de áreas
    double fX;                          // Variable auxiliar para el punto medio

    // Bucle principal: recorre los n subintervalos
    for (long long i = 0; i < n; i++)
    {
        // Calcula el punto medio del subintervalo i
        fX = fH * ((double)i + 0.5);

        // Suma el valor de la función f(x) en el punto medio
        fSum += f(fX);
    }

    // Multiplica la suma por el ancho del subintervalo para obtener el área total
    return fH * fSum;
}

// ------------------------------------------------------------
// Función auxiliar para obtener el tiempo actual en segundos
// ------------------------------------------------------------
double GetTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

// ------------------------------------------------------------
// Función principal (main): punto de entrada del programa.
// Aquí se llama a CalcPi, se imprime el resultado y se calcula el error.
// ------------------------------------------------------------
int main()
{
    long long n = 2000000000; // Número de intervalos (cuantos más, más preciso pero más lento)
    const double realPi = 3.14159265358979323846; // Valor real de π para comparar

    double start = GetTime();
    double pi = CalcPi(n);                        // Llamada a la función que calcula π
    double end = GetTime();

    double elapsed = end - start;

    printf("\npi ≈ %.20f\nError = %.20f\n", pi, fabs(pi - realPi));
    printf("Tiempo de ejecución (T_s) = %.6f segundos\n", elapsed);

    return 0; // Fin del programa (código 0 = ejecución correcta)
}
