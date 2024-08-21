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
* programa que calcula la suma de los primeros n numeros naturales
* por medio de un for paralelo y utilizando la clausula reduction
* para optimizar la suma
* -------------------------------------------------------------
*/


#include <stdio.h>
#include <omp.h>

int main() {
    //  N debe ser 1000000
    const int N = 10;
    int result = 0;
    double end_time;

    #pragma omp parallel for reduction(+:result)
    for (int i=0; i<N; i++){
        end_time = omp_get_wtime();
        result += N;

    }

    printf("La suma es: %f\n", result);
    return 0;

}