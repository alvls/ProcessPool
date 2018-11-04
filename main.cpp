#include "process_pool.h"
#include <iostream>
int main(int argc, char* argv[])
{
   
  MPI_Init(&argc, &argv);
  int ProcRank;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  TProcessPool processPool;
  TCommunicator* comm = processPool.GetFreeProcs(2);//создание коммуникатора по запросу 
  //если хватает процессов, то будет создан нужный коммуникатор
  //если не хватает , то указатель comm будет nullptr
  if (ProcRank == 0)
  {
      processPool.PrintFreeProcRank();
      processPool.PrintWorkComms();
  }

  processPool.ReleaseProcs(comm);

  if (ProcRank == 0)
  {
    
      processPool.PrintFreeProcRank();
      processPool.PrintWorkComms();
  }
  comm = processPool.GetFreeProcs(3);
  if (ProcRank == 0)
  {

      processPool.PrintFreeProcRank();
      processPool.PrintWorkComms();
  }
  MPI_Finalize();


  
  return 0;
}