#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {    
    MPI_Init(&argc, &argv);
    int world_rank,tag;
    int len = 20;
    char name[20];
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Get_processor_name(name,&len);

    int number;

  

    number= 3;
while(number>=0){
    if (world_rank != 0) 
    
    {
            MPI_Recv(&number, 1, MPI_INT, world_rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (number>0)
            printf("Process %d received number %d from i:%d on the machine %s \n",world_rank, number, world_rank-1,name);
       
    }
    else{  //at the start goes here
            
         printf("Insert a number\n");
        fflush(stdout);
        scanf("%d",&number);
        

    } 
  
    //continues here
    MPI_Send(&number, 1, MPI_INT, (world_rank+1)%world_size, tag, MPI_COMM_WORLD);
       


  if (world_rank == 0) {
        MPI_Recv(&number, 1, MPI_INT, world_rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}
    MPI_Finalize();
}