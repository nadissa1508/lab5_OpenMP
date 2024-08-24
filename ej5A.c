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
 * paralelizacion del archivo Ejercicio_5A
 * -------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#define N 131072
#define THRESHOLD 1024 

//Funcion de conteo de key con enfoque recursivo
long count_key_recursive(long start, long end, long *a, long key) {
    long count = 0;
    
    if (end - start <= THRESHOLD) {
        // Caso base
        #pragma omp parallel for reduction(+:count)
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
    } else {
        // Caso recursivo: dividimos en dos tareas
        long mitad = start + (end - start) / 2;
        long count1, count2;

        //Resolver la primera parte del array
        #pragma omp task shared(count1)
        count1 = count_key_recursive(start, mitad, a, key);

        //Resolver la segunda parte del array
        #pragma omp task shared(count2)
        count2 = count_key_recursive(mitad, end, a, key);

        //sumar los conteos iindividuales
        #pragma omp taskwait
        count = count1 + count2;
    }
    
    return count;
}

//Funcion de conteo de key secuencial
long count_key(long Nlen, long *a, long key) {
    long count = 0;
    for (int i = 0; i < Nlen; i++)
        if (a[i] == key) count++;
    return count;
}

int main() {
    long a[N], key = 42, nkey = 0, nkey_s = 0;
    //llenamos el array a de valores aleatorios
    for (long i = 0; i < N; i++){
        a[i] = rand() % N;
    } 
    //ubicar minimo 3 veces el valor key
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    nkey_s = count_key(N, a, key);  // cuenta key secuencialmente
    
    #pragma omp parallel
    {
        #pragma omp single
        nkey = count_key_recursive(0, N, a, key);  // cuenta key paralelamente
    }
    
    //comparamos que los resultados del conteo sean iguales
    printf("Numero de veces que 'key' aparece paralelamente: %ld\n", nkey);
    printf("Numero de veces que 'key' aparece secuencialmente: %ld\n", nkey_s);

    return 0;
}
