#include <stdio.h>
#include <omp.h>

#include "inc/tmeas.h"

#define size 1500000
#define chunk 3
#define threads 4
int main()
{
        srand(time(NULL));
        int a=1,i;
        double t=0;
        omp_set_num_threads(threads);
        printf("Static with chunk = %d\n",chunk);

    tstart();
  #pragma omp parallel for schedule(static, chunk)
        for(i=0; i<size; i++) {
                a*=0.5;
                //printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
        t=tstop();
        printf("Time Static with 3 chunks: %lf\n",t);


        printf("Static with default chunk size\n");
        a=1;
        tstart();
  #pragma omp parallel for schedule(static)
        for(i=0; i<size; i++) {
                a*=0.5;
                //printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
          t=tstop();
          printf("Time Static with default chunks: %lf\n",t);

        printf("Dynamic with chunk size = %d\n",chunk);
        tstart();
        a=1;
        #pragma omp parallel for schedule(dynamic,chunk)
        for(i=0; i<size; i++) {
                a*=0.5;
              //  printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
        t=tstop();
        printf("Time Dynamic with 3 chunks: %lf\n",t);

        printf("Dynamic with default chunk size\n");
        a=1;
          tstart();
              #pragma omp parallel for schedule(dynamic)
        for(i=0; i<size; i++) {
                a*=0.5;
              //  printf("\tThread:  %d  Index: %d\n",omp_get_thread_num(),i);
        }
        t=tstop();
        printf("Time Dynamic with default chunks: %lf\n",t);

}
