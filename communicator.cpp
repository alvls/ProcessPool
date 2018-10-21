#include "communicator.h"

TCommunicator::TCommunicator(MPI_Comm c, vector<int> r) : comm(c), ranks(r)
{
}

TCommunicator::~TCommunicator()
{
}

void TCommunicator::Send(int data[], int count, int destRank, int tag)
{
}

void TCommunicator::Send(vector<int> data, int destRank, int tag)
{
}

void TCommunicator::Send(double data[], int count, int destRank, int tag)
{
}

void TCommunicator::Send(vector<double> data, int destRank, int tag)
{
}

void TCommunicator::Send(char rawData[], int count, int destRank, int tag)
{
}

vector<int> TCommunicator::GetWorldRanks()
{
  return ranks;
}
