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
 * -------------------------------------------------------------
 * programa que tiene un ciclo for, donde se modifican dos variables
 * de forma paralela, usando las clausulas shared y private
 * -------------------------------------------------------------
 */
#include <stdio.h>
#include <omp.h>

int main()
{
    //x sera la variable privada, mientras y la variable compartida
    int x = 0, y = 0;

    #pragma omp parallel for private(x) shared(y)
    for(int i = 0; i < 5; i++){
        x += i;
        //colocamos atomic para evitar condiciones de carrera
        #pragma omp atomic
        y += i;
        printf("Hilo %d: x = %d, y = %d\n", omp_get_thread_num(), x, y);
    }
    //resultados finales de las variables
    printf("Fuera del ciclo for: y = %d x = %d\n", y, x);
    return 0;
}


