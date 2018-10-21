#pragma once

#include <list>
#include "communicator.h"

using std::list;

class TProcessPool
{
  // worldSize - размер коммуникатора MPI_COMM_WORLD
  int worldSize;

  vector<TCommunicator*> workComms; // рабочие коммуникаторы

  // ранги свободных процессов
  // ранг 0 всегда занят - на нем работает "корневой" solver, решающий исходную задачу
  list<int> freeProcRanks;
public:
  TProcessPool();
  ~TProcessPool();
  TCommunicator* GetFreeProcs(int count);
  void ReleaseProcs(TCommunicator* pс);
};

