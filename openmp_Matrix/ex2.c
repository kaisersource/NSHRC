#include <stdio.h>
#include <omp.h>
#include <time.h>
#define threads 4
omp_lock_t lock;
int main()
{
        double start,stop;
        omp_init_lock(&lock);
        int x=0;
        printf("Insert the number to compute sum of squares \n");
        scanf("%d",&x);
        int n = 500, i;
        int sum=0.0;
        int lsum;
        omp_set_num_threads(threads);



start=omp_get_wtime();
//Reduction
#pragma omp parallel for reduction(+:sum)
  for (i=0; i<n; i++){
    sum+=x*x;
  }
stop=omp_get_wtime();
printf("Reduction - sum squares: %d. Time : %lf \n ",sum,stop-start);

sum=0;

//locks
start=omp_get_wtime();
#pragma omp parallel for
  for (i=0; i<n; i++){
    omp_set_lock(&lock);
    sum+=x*x;
    omp_unset_lock(&lock);
  }
stop=omp_get_wtime();
printf("Locks - sum squares: %d. Time : %lf \n",sum,stop-start);

sum=0;
//Critical
start=omp_get_wtime();
#pragma omp parallel private(i)
{
lsum=0;
#pragma omp for
  for (i=0; i<n; i++){
    lsum+=x*x;
  }
#pragma omp critical
sum+=lsum;
}
stop=omp_get_wtime();
printf("Critical - sum squares: %d. Time : %lf \n",sum,stop-start);

sum=0;
//Atomic
start=omp_get_wtime();
#pragma omp parallel for
  for (i=0; i<n; i++){
    #pragma omp atomic
    sum+=x*x;
  }
stop=omp_get_wtime();
printf("Atomic - sum squares: %d. Time : %lf \n",sum,stop-start);



        return 0;
}
