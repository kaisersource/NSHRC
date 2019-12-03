

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {    
    MPI_Init(&argc, &argv);
    int world_rank,tag;
    int len = 20;
    const int root=0;
    char name[20];
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Get_processor_name(name,&len);

    int number;


    number= 3;

while(number>=0){
    
    if (world_rank == root) {
       printf("[%d]: Before Bcast, buf is %d\n", world_rank, number);
       printf("Insert a number\n");
           fflush(stdout);
        scanf("%d",&number);
    }
            
/* everyone calls bcast, data is taken from root and ends up in everyone's buf */
    else{
    
      if (number>0){
       
         printf("Process %d received number %d on the machine %s \n",world_rank, number, name);
        }  
         
    }
    MPI_Bcast(&number, 1, MPI_INT, root, MPI_COMM_WORLD);  
    
     
}
    
    MPI_Finalize();
    return 0;
}
