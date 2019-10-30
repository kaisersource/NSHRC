
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define N 5     /* number of threads */
#define SIZE 3  /*shopping carts*/
#define SHPTMS 2 /*shopping time*/

pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex[SIZE];
char condition = 0;
int arr=0;
typedef struct {
	int *cart;
	int *cnt;
} cart_s;

cart_s carts;


void* thread(void* num) {
	int t_num = ((int)num);
        printf("Customer %d is ready\n", (int)t_num);
        while (carts.cnt[(int)t_num]<SHPTMS) {
		for(int i=0;i<SIZE;i++){
			if(carts.cnt[(int)t_num]<SHPTMS && carts.cart[i]==0){
					shop((int)t_num,i);

			}
		}
	}
	return NULL;
}

void shop(int t_num,int i){
	pthread_mutex_lock( &mutex[i]);
	carts.cnt[(int)t_num]++;
	carts.cart[i]==1;
	arr = rand() % 3;
	sleep(arr);
	printf("Customer %d took cart %d, shops for %d seconds \n",(int)t_num,i+1,arr);

	printf("Customer %d had shopping for %d seconds and releases cart %d \n",(int)t_num,arr,i+1);
	pthread_mutex_unlock( &mutex[i]);
	sleep(arr);
}


int main() {

	for (int i = 0; i < SIZE; i++)
        pthread_mutex_init(&mutex[i], NULL);

	carts.cart=(int *)malloc(sizeof(int)*SIZE);
	carts.cnt=(int *)malloc(sizeof(int)*N);
	int x,y;
	for(x=0;x<SIZE;x++)
		carts.cart[x]=0;
	for(y=0;y<N;y++)
		carts.cnt[y]=0;

        pthread_t id[N];
        int i;

        puts("Beginning of the program");

        for (i=0; i < N; i++) {
                errno = pthread_create(&id[i], NULL, thread, (void*)(i+1));
                if (errno) {
                        perror("pthread_create");
                        return EXIT_FAILURE;
                }
        }

        for( i = 0; i < N; i++ )
		pthread_join(id[i], NULL);
        puts("End of program");
        return EXIT_SUCCESS;
}
