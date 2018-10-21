#pragma once

#include <list>
#include "communicator.h"

using std::list;

class TProcessPool
{
  // worldSize - ������ ������������� MPI_COMM_WORLD
  int worldSize;

  vector<TCommunicator*> workComms; // ������� �������������

  // ����� ��������� ���������
  // ���� 0 ������ ����� - �� ��� �������� "��������" solver, �������� �������� ������
  list<int> freeProcRanks;
public:
  TProcessPool();
  ~TProcessPool();
  TCommunicator* GetFreeProcs(int count);
  void ReleaseProcs(TCommunicator* p�);
};

