#include "process_pool.h"


TProcessPool::TProcessPool()
{
    //конструктор по умолчанию создаст список из свободных процессов (их ранги)
    
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  for (int i = 1; i < worldSize; i++)
    freeProcRanks.push_back(i);
}

TProcessPool::~TProcessPool()
{

}

TCommunicator* TProcessPool::GetFreeProcs(int count)//запрос на count процессов
{
  TCommunicator* newComm = nullptr;
  if (count > freeProcRanks.size())//если запрос не выполним
    return newComm;//вернем нулевой коммуникатор

  vector<int> ranks(count);//создаем вектор рангов процессов(для работы с MPI)
  for (int i = 0; i < count; i++)//заполняем его из имеющихся свободных
  {
    ranks[i] = freeProcRanks.front();
    freeProcRanks.pop_front();//Удаляет элемент в начале списка.
  }
  //создаем рабочую группу процессов
  MPI_Comm comm;
  MPI_Group worldGroup, group;
  MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);//MPI_Comm_group(MPI_Comm comm, MPI_Group *worldGroup),

  //Функция создает группу worldGroup для множества процессов, входящих в область связи MPI_COMM_WORLD.

  MPI_Group_incl(worldGroup, count, ranks.data(), &group);//MPI_Group_incl(MPI_Group group, int n, int *ranks,MPI_Group *group)

  //ranks.data() возвращает указатель на первый элемент в векторе ranks.

  //MPI_Group_incl создает новую группу group, которая состоит из процессов существующей группы, перечисленных в массиве ranks.
  //Процесс с номером i в новой группе есть процесс с номером ranks[i] в существующей группе. 
 //Каждый элемент в массиве ranks должен иметь корректный номер в группе worldGroup, и среди этих элементов не должно быть совпадающих.

  MPI_Comm_create(MPI_COMM_WORLD, group, &comm);//int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
 // Эта функция создает коммуникатор comm для группы group.
  //Для процессов, которые не являются членами группы, возвращается значение MPI_COMM_NULL.
  //Функция возвращает код ошибки, если группа group не является подгруппой родительского коммуникатора.

  //теперь создан MPI-коммуникатор comm
  //оборачиваем его в нашу оболочку TCommunicator, используя конструктор
  newComm = new TCommunicator(comm, ranks);//создаем указатель на новый коммуникатор-оболочка
  workComms.push_back(newComm);//пополняем список созданных локальных коммуникаторов
 
  return newComm;//возвращаем указатель на новый построенный коммуникатор
}

void TProcessPool::ReleaseProcs(TCommunicator* pc)
{
  // узнать список процессов из pc
  // вернуть процессы в список свободных
  // освободить MPI коммуникатор

    int size = pc->ranks.size();
    for (int i = 0; i < size; i++)
    {
        freeProcRanks.push_back(pc->ranks.front());    
        pc->ranks.erase(pc->ranks.begin());
    
    }
    
    //MPI_Comm_free(&pc->comm);//уничтожаю коммуникатор в pc 

    //другой вариант:
    //сделать его для MPI_COMM_WORLD
    MPI_Group worldGroup;
    MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
    MPI_Comm_create(MPI_COMM_WORLD, worldGroup, &pc->comm);


}
