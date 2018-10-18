#include "communicator.h"



TCommunicator::TCommunicator(MPI_Comm* c, vector<int> r) : comm(c), ranks(r)
{
  
}

TCommunicator::~TCommunicator()
{
}

vector<int> TCommunicator::GetRanks()
{
  return ranks;
}
