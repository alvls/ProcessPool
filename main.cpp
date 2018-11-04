#include "process_pool.h"
#include <iostream>
int main(int argc, char* argv[])
{
   
  MPI_Init(&argc, &argv);
  int ProcRank;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

  TProcessPool processPool;
  TCommunicator* comm = processPool.GetFreeProcs(2);//�������� ������������� �� ������� 
  //���� ������� ���������, �� ����� ������ ������ ������������
  //���� �� ������� , �� ��������� comm ����� nullptr
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