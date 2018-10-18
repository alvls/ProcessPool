#include "process_pool.h"

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);

  TProcessPool processPool;
  TCommunicator* comm = processPool.GetFreeProcs(2);

  MPI_Finalize();
  return 0;
}