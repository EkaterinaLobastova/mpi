#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//program run:
//mpicc main.cpp -o main
//mpirun -np 5 ./main


int main(int argc, char** argv) {
  int tmp,max=-1,rank_max=0;
  MPI_Status Status;
  MPI_Init(NULL, NULL);

  int thread_num;
  MPI_Comm_size(MPI_COMM_WORLD, &thread_num);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  srand((unsigned)time(NULL)+thread_num*rank);
  tmp=rand();

  if (rank==0){
      if (tmp>max){
          max=tmp;
      }
      printf("res=%d in %d\n", tmp, rank);
      for(int i=1;i<thread_num;i++){
          MPI_Recv(&tmp,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&Status);
          if (tmp>max) {
              max=tmp;
              rank_max=Status.MPI_SOURCE;
          }
      }
      printf("MAXIMUM=%d IN A PROCESS %d\n", max, rank_max);
  }
  else{
      printf("res=%d in %d\n", tmp, rank);
      MPI_Send(&tmp,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
