#include "process_pool.h"


TProcessPool::TProcessPool()
{
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  for (int i = 1; i < worldSize; i++)
    freeProcRanks.push_back(i);
}

TProcessPool::~TProcessPool()
{

}

TCommunicator* TProcessPool::GetFreeProcs(int count)
{
  TCommunicator* newComm = nullptr;
  if (count > freeProcRanks.size())
    return newComm;

  vector<int> ranks(count);
  for (int i = 0; i < count; i++)
  {
    ranks[i] = freeProcRanks.front();
    freeProcRanks.pop_front();
  }
  MPI_Comm comm;
  MPI_Group worldGroup, group;
  MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
  MPI_Group_incl(worldGroup, count, ranks.data(), &group);
  MPI_Comm_create(MPI_COMM_WORLD, group, &comm);

  newComm = new TCommunicator(comm, ranks);
  workComms.push_back(newComm);

  return newComm;
}

void TProcessPool::ReleaseProcs(TCommunicator* pс)
{
  // узнать список процессов из pc
  // вернуть процессы в список свободных
  // освободить MPI коммуникатор
}
