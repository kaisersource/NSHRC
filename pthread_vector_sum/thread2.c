#include <stdio.h>
#include <stdlib.h>
#include "lib/tmeas.h"
#include <pthread.h>

#define SIZE 12
#define MAX_NUM_THREAD 4

/* define structure of thread's data */

int a[] = { 1, 2, 3,4,5, 6, 7, 8, 9, 10, 11,12};
int b[] = { 1, 2, 3,4,5, 6, 7, 8, 9, 10, 11,12};
int s[4] = { 0 };
int part = 0;
double t=0;
//int *vec1,*vec2,*vec3;
//vec.a=(int *)malloc(sizeof(int)*SIZE);
	//vec.b=(int *)malloc(sizeof(int)*SIZE);
	//vec.c=(int *)malloc(sizeof(int)*SIZE);




void* sum_array(void* arg)
{

    // 1/4 array
    int thread_part = part++;

    for (int i = thread_part * (SIZE / 4); i < (thread_part + 1) * (SIZE / 4); i++)
        s[thread_part] += a[i]+b[i];
}

int main()
{

    pthread_t threads[MAX_NUM_THREAD];
    tstart();
    // Creating 4 threads
    for (int i = 0; i < MAX_NUM_THREAD; i++)
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

    // joining and waiting threads
    for (int i = 0; i < MAX_NUM_THREAD; i++)
        pthread_join(threads[i], NULL);

    // adding sum of all 4 parts
    int total_sum = 0;
    for (int i = 0; i < MAX_NUM_THREAD; i++)
        total_sum += s[i];

    printf("sum is %d \n",total_sum);
    t=tstop();
    printf("time: %lf",t);
    return 0;
}
