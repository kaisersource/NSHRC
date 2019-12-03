#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 1000

int a[N][N];
int b[N][N];
int c[N][N];

int d[N][N];
int e[N][N];
int f[N][N];
int i, j, k;
double matMultiply(){
	double start,stop;
    start=omp_get_wtime();
    for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j) {
        for (k = 0; k < N; ++k) {
          c[i][j] += a[i][k] * b[k][j];
        }

      }
    }
    stop=omp_get_wtime();
    return stop-start;
}


int test(int Matrix1[N][N], int Matrix2[N][N], int Matrix3[N][N])
{
    int i,j,k,chk=0;
    double tmp,**Mtest;

    for (i = 0; i < N; i++)
    {
       for (j = 0; j < N; j++)
       {
	  tmp = 0;
	  for (k = 0; k < N; k++)
	  {
	     tmp += Matrix1[i][k] * Matrix2[k][j];
          }
	  if(Matrix3[i][j]!=tmp)
	  {
		printf("Error in element %d,%d!\n",i,j);
		chk=1;
          }
       }
    }
    return chk;
}



void openMpMultiply_for_outside(){
    double start,stop;
    //omp_set_num_threads(omp_get_num_procs());
		omp_set_num_threads(4);
    start=omp_get_wtime();
  #pragma omp parallel for schedule(dynamic) private(j, k) shared (d, e) reduction(+:f)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                f[i][j] += d[i][k] * e[k][j];
            }

        }
    }


    stop=omp_get_wtime();
  printf("first loop - Parallel matrix multiplication : %lf seconds\n", stop-start);
	/*
/////Second Loop Parallel
	start=omp_get_wtime();
	for (i = 0; i < N; ++i) {
			#pragma omp parallel for private(j, k) shared (d, e, f)
			for (j = 0; j < N; ++j) {
					for (k = 0; k < N; ++k) {
							f[i][j] += d[i][k] * e[k][j];
					}
			}
	}
	stop=omp_get_wtime();
	printf("second loop - Parallel matrix multiplication : %lf seconds\n", stop-start);

///Third loop

/////Second Loop Parallel
	start=omp_get_wtime();
	for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
					#pragma omp parallel for private(k) shared (d, e, f)
					for (k = 0; k < N; ++k) {
							f[i][j] += d[i][k] * e[k][j];
					}
			}
	}
	stop=omp_get_wtime();
	printf("third loop - Parallel matrix multiplication : %lf seconds\n", stop-start);

///reduction

/////Second Loop Reduction Parallel
	start=omp_get_wtime();
	for (i = 0; i < N; ++i) {
			#pragma omp parallel for schedule(dynamic) private(j, k) shared (d, e) reduction(+:f)
			for (j = 0; j < N; ++j) {

					for (k = 0; k < N; ++k) {
							f[i][j] += d[i][k] * e[k][j];
					}
			}
	}
	stop=omp_get_wtime();
	printf("Reduction inner loop - Parallel matrix multiplication : %lf seconds\n", stop-start);
*/

}


int main() {

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            a[i][j] = i;
            b[i][j] = j;
            d[i][j] = i;
            e[i][j] = j;
        }
    }


    double elapsed = matMultiply();

    printf("Sequential matrix multiplication : %lf seconds\n", elapsed);

    openMpMultiply_for_outside();

		    if(test(d,e,f)==1)
			printf("Program exited with errors\n");
    return 0;
}
