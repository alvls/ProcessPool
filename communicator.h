#pragma once
#include "mpi.h"
#include <memory>
#include <vector>

using std::vector;

class TProcessPool;

class TCommunicator
{
  friend TProcessPool;
private:
  MPI_Comm comm;
  // класс Коммуникатор хранит ранги выделенных ему процессов из MPI_COMM_WORLD
  vector<int> ranks; 

  vector<int> GetWorldRanks();
public:
  TCommunicator(MPI_Comm c, vector<int> r);
  ~TCommunicator();
  void Send(int data[], int count, int destRank, int tag);
  void Send(vector<int> data, int destRank, int tag);
  void Send(double data[], int count, int destRank, int tag);
  void Send(vector<double> data, int destRank, int tag);
  void Send(char rawData[], int count, int destRank, int tag);
};

