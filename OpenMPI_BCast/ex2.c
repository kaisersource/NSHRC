#include<stdio.h>
#include<mpi.h>
#include<string.h>
typedef struct {
	char name[20];
    char surname[20];
	int age;
    char city[20];
    char tel[20];
} Data;


int main(int argc, char **argv)
{
	double t1,t2;
	double time;
	int rank, size, r;
	int src, dst, tag, i;	
	MPI_Status status;
	MPI_Datatype new_type;
	MPI_Datatype type[2] = { MPI_CHAR, MPI_INT };
	int blen[2] = { 20, 1 };
	MPI_Aint disp[5];
	MPI_Aint base, addr;
	Data tabrecord,tabrecieved;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0) 
		printf("MPI_Type_create_struct()\n");

	MPI_Get_address(&tabrecord, &base);
	MPI_Get_address(&(tabrecord.name), &addr);
	disp[0] = addr - base;
	MPI_Get_address(&(tabrecord.surname), &addr);
	disp[1] = addr - base;
    MPI_Get_address(&(tabrecord.age), &addr);
	disp[2] = addr - base;
    MPI_Get_address(&(tabrecord.city), &addr);
	disp[3] = addr - base;
    MPI_Get_address(&(tabrecord.tel), &addr);
	disp[4] = addr - base;
	
	MPI_Type_create_struct(2, blen, disp, type, &new_type);
	MPI_Type_commit(&new_type);

	if(rank != 0)
	{
		strcpy(tabrecieved.name, "Peter");
        strcpy(tabrecieved.surname, "Gomez");
        strcpy(tabrecieved.city, "Salt Lake City");
		tabrecieved.age = 55;
        strcpy(tabrecieved.tel, "0755440631");
        
		printf("In process %d I have received name: %s \n",rank,tabrecieved.name);
		printf("In process %d my surname is %s \n",rank,tabrecieved.surname);	
		MPI_Recv(&tabrecieved, 1, new_type, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("In process %d I have received city: %s\n",rank,tabrecieved.city);	
		printf("Age: %d\n",tabrecieved.age);
		printf("and telephone: %s\n",tabrecieved.tel);
	}
	else
	{
		
		strcpy(tabrecord.name, "John");
		strcpy(tabrecord.name, "Frusciante");
		tabrecord.age = 49;
		strcpy(tabrecieved.city, "Los Angeles");
		strcpy(tabrecieved.tel, "0755440635");
		t1 = MPI_Wtime();
		for (r=1; r<size; r++)
			MPI_Bsend(&tabrecord, 1, new_type, r, 0, MPI_COMM_WORLD);
		t2 = MPI_Wtime();
		time = t2-t1;
		printf("Time : %lf",time);

	}
	//MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
