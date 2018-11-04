#include "process_pool.h"


TProcessPool::TProcessPool()
{
    //����������� �� ��������� ������� ������ �� ��������� ��������� (�� �����)
    
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  for (int i = 1; i < worldSize; i++)
    freeProcRanks.push_back(i);
}

TProcessPool::~TProcessPool()
{

}

TCommunicator* TProcessPool::GetFreeProcs(int count)//������ �� count ���������
{
  TCommunicator* newComm = nullptr;
  if (count > freeProcRanks.size())//���� ������ �� ��������
    return newComm;//������ ������� ������������

  vector<int> ranks(count);//������� ������ ������ ���������(��� ������ � MPI)
  for (int i = 0; i < count; i++)//��������� ��� �� ��������� ���������
  {
    ranks[i] = freeProcRanks.front();
    freeProcRanks.pop_front();//������� ������� � ������ ������.
  }
  //������� ������� ������ ���������
  MPI_Comm comm;
  MPI_Group worldGroup, group;
  MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);//MPI_Comm_group(MPI_Comm comm, MPI_Group *worldGroup),

  //������� ������� ������ worldGroup ��� ��������� ���������, �������� � ������� ����� MPI_COMM_WORLD.

  MPI_Group_incl(worldGroup, count, ranks.data(), &group);//MPI_Group_incl(MPI_Group group, int n, int *ranks,MPI_Group *group)

  //ranks.data() ���������� ��������� �� ������ ������� � ������� ranks.

  //MPI_Group_incl ������� ����� ������ group, ������� ������� �� ��������� ������������ ������, ������������� � ������� ranks.
  //������� � ������� i � ����� ������ ���� ������� � ������� ranks[i] � ������������ ������. 
 //������ ������� � ������� ranks ������ ����� ���������� ����� � ������ worldGroup, � ����� ���� ��������� �� ������ ���� �����������.

  MPI_Comm_create(MPI_COMM_WORLD, group, &comm);//int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
 // ��� ������� ������� ������������ comm ��� ������ group.
  //��� ���������, ������� �� �������� ������� ������, ������������ �������� MPI_COMM_NULL.
  //������� ���������� ��� ������, ���� ������ group �� �������� ���������� ������������� �������������.

  //������ ������ MPI-������������ comm
  //����������� ��� � ���� �������� TCommunicator, ��������� �����������
  newComm = new TCommunicator(comm, ranks);//������� ��������� �� ����� ������������-��������
  workComms.push_back(newComm);//��������� ������ ��������� ��������� ��������������
 
  return newComm;//���������� ��������� �� ����� ����������� ������������
}

void TProcessPool::ReleaseProcs(TCommunicator* pc)
{
  // ������ ������ ��������� �� pc
  // ������� �������� � ������ ���������
  // ���������� MPI ������������

    int size = pc->ranks.size();
    for (int i = 0; i < size; i++)
    {
        freeProcRanks.push_back(pc->ranks.front());    
        pc->ranks.erase(pc->ranks.begin());
    
    }
    
    //MPI_Comm_free(&pc->comm);//��������� ������������ � pc 

    //������ �������:
    //������� ��� ��� MPI_COMM_WORLD
    MPI_Group worldGroup;
    MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
    MPI_Comm_create(MPI_COMM_WORLD, worldGroup, &pc->comm);


}
