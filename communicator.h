#pragma once
#include "mpi.h"
#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;

class TCommunicator
{
private:
  shared_ptr<MPI_Comm> comm;
  vector<int> ranks; // коммуникатор хранит ранги процессов из MPI_COMM_WORLD
public:
  TCommunicator(MPI_Comm* c, vector<int> r);
  ~TCommunicator();
  vector<int> GetRanks();
};

