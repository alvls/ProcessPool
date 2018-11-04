#pragma once

#include <list>
#include "communicator.h"
#include <iostream>
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
void PrintFreeProcRank()
  {
    std::cout <<"we have "<< freeProcRanks.size() << " free procs"<<std::endl;

  }
  void PrintWorkComms()
  {
      
      for (int i = 0; i < workComms.size();i++)
      {
          std::cout << "procs ranks in " << i << " comm: ";
          for (int j = 0; j < workComms[i]->GetWorldRanks().size(); j++)
          {
              std::cout << workComms[i]->GetWorldRanks()[j]<<";";
             
          }
          std::cout << std::endl;
      }
      
     
  }
};

