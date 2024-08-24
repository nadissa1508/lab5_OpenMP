/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3086 - Programacion de Microprocesadores
 * Ver.: 1.2 2024/21/08
 * Mod.: Angie Nadissa Vela López
 * Carnet: 23764
 *
 * References:
 * Chandra, . R. et al. Parallel Programming
 * in OpenMP
 * -------------------------------------------------------------
 * programa que calcula la suma de los primeros n numeros naturales
 * por medio de un for paralelo y utilizando la clausula reduction
 * para optimizar la suma
 * -------------------------------------------------------------
 */

#include <stdio.h>
#include <omp.h>

int main()
{
    const int N = 1000000;
    //se utiliza este tipo de dato para que se muestre el resultado de la suma correctamente
    long long int result = 0;
    double start_time, end_time;

    //capturamos el tiempo de ejecución antes de que comience el bloque paralelo
    start_time = omp_get_wtime();

    //usamos la directiva for y la cláusula reduction con el operador + por la suma
    //el for inicia en 1 y termina en N para sumar los primeros N numeros naturales 
    #pragma omp parallel for reduction(+ : result)
    for (int i = 1; i <= N; i++)
    {
        result += i;
    }
    //capturamos el tiempo de ejecución cuando termina el bloque paralelo
    end_time = omp_get_wtime();
    printf("La suma es: %lld tiempo de ejecucion: %f s\n", result, end_time - start_time);
    return 0;
}