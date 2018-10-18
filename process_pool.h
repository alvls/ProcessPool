#pragma once

#include <list>
#include "communicator.h"

using std::list;
using PTCommunicator = shared_ptr<TCommunicator>;

class TProcessPool
{
  PTCommunicator pWorld;
  vector<PTCommunicator> comms;
  int worldSize;

  vector<int> busyProcRanks;
  list<int> freeProcRanks;
public:
  TProcessPool();
  ~TProcessPool();
  TCommunicator* GetFreeProcs(int count);
};

