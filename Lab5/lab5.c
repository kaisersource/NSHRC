#include <stdio.h>
#include <omp.h>

#include "inc/tmeas.h"
#define size 15
#define chunk 3
#define threads 4
int main()
{
        srand(time(NULL));
        int a=1,i;

        omp_set_num_threads(threads);
        printf("Static with chunk = %d\n",chunk);

  #pragma omp parallel for schedule(static, chunk)
        for(i=0; i<size; i++) {
                a*=0.5;
                printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }


        printf("Static with default chunk size\n");
        a=1;
  #pragma omp parallel for schedule(static)
        for(i=0; i<size; i++) {
                a*=0.5;
                printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
        printf("Dynamic with chunk size = %d\n",chunk);
        a=1;
        #pragma omp parallel for schedule(dynamic,chunk)
        for(i=0; i<size; i++) {
                a*=0.5;
                printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
        printf("Dynamic with default chunk size\n");
        a=1;
              #pragma omp parallel for schedule(dynamic)
        for(i=0; i<size; i++) {
                a*=0.5;
                printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }

}
