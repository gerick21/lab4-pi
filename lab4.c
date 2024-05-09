/*

Name:   pi_loop

Description:  This program computes numerically compute 
              the integral of

                 4/(1+x*x) 
				  
              from 0 to 1 to produce an estimate of pi
              This version of the program uses the loop
              level parallelism pattern.


History: Written by Tim Mattson, March 2023

*/

#include <stdio.h> 
#include <omp.h>
#include <iostream>
static long num_pasos = 0; 


int main ()
{
   double x, pi , paso , sum = 0.0; 
   int num_hilos;
   double tiempo_inicio, tiempo_total;
   
   std::cout << "Ingrese el número de pasos: ";
   std::cin >> num_pasos;

   paso = 1.0 / (double) num_pasos;
    
   tiempo_inicio = omp_get_wtime(); 


   #pragma omp parallel 
   {

       #pragma omp single
          num_hilos = omp_get_num_threads();

       #pragma omp for private(x) reduction(+:sum) 
           for (int i=0; i<num_pasos; i++){
               x = (i + 0.5) * paso;
               sum = sum + 4.0 / (1.0 + x*x);
           }
    }

    pi = paso * sum;
    tiempo_total = omp_get_wtime() - tiempo_inicio;
    printf("Valor de PI = %lf \n", pi);
    printf("Cantidad total de pasos: %ld \n", num_pasos);
    printf("Tiempo total de ejecución: %lf segundo(s) \n", tiempo_total);
}
