/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3086 - Programacion de Microprocesadores
 * Ver.: 1.1 2024/21/08
 * Mod.: Angie Nadissa Vela López
 * Carnet: 23764
 *
 * References:
 * Chandra, . R. et al. Parallel Programming
 * in OpenMP
 *
 * GeeksforGeeks. (2024). Factorial program in C. GeeksforGeeks.
 * https://www.geeksforgeeks.org/c-program-for-factorial-of-a-number/
 *
 * GeeksforGeeks. (2024). Nth Fibonacci number. GeeksforGeeks.
 * https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
 *
 * W3Schools.com. (s.f.). https://www.w3schools.com/c/c_arrays.php
 * -------------------------------------------------------------
 * Programa que calcula 3 operaciones matemáticas complejas paralelamente.
 * Dichas funciones serán independientes, para prácticar la aplicación de
 * la directiva sections
 * -------------------------------------------------------------
 */

#include <stdio.h>
#include <omp.h>

// Calculo de factorial por medio de un for
unsigned int factorial(unsigned int N){
    int fact = 1;
    // Hacemos un ciclo desde 1 hasta N para calcular el factorial
    #pragma omp parallel for reduction(*:fact)
    for (int i = 1; i <= N; i++){
        fact *= i;
    }
    return fact;
}

// Calculo de fibonacci usando recursividad
int fib(int n){
    if (n <= 1)
        return n; // condicion de salida
    return fib(n - 1) + fib(n - 2);
}

// Encuentra el numero mayor de un array
int findMax(int *listNumbers, int length){
    int max = listNumbers[0];

    #pragma omp parallel for reduction(max:max)
    for (int i = 1; i < length; i++){
        if (listNumbers[i] > max){
            max = listNumbers[i];
        }
    }
    return max;
}

int main()
{
    int num = 10, n = 9, length = 0, nMax = 0;
    int listNumbers[] = {5, 2, 30, 15, 40, 96, 78, 102, 3, 27, 13, 14, 25, 78, 215, 86, 41, 12, 36, 95, 1, 30, 28};
    length = sizeof(listNumbers) / sizeof(listNumbers[0]);
    nMax = findMax(listNumbers, length);

    double start_time, end_time;

    //capturamos el tiempo de ejecución antes de que comience el bloque paralelo
    start_time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
		{ 
            printf("\nEl factorial de %d es %d", num, factorial(num));
        }

        #pragma omp section
		{ 
            printf("\nEl fibonacci de %d es %d", n, fib(n));
        }

        #pragma omp section
		{ 
            printf("\nEl numero mayor del arreglo es %d", nMax);
        }
    }

    //capturamos el tiempo de ejecución cuando termina el bloque paralelo
    end_time = omp_get_wtime();

    printf("\nTiempo de ejecucion: %f s\n", end_time - start_time);
    
    return 0;
}