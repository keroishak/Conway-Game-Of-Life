#include "ParallelConwaySimulator.h"
using namespace ConwayGameOfLife;

ParallelConwaySimulator::ParallelConwaySimulator(std::shared_ptr<ConwayUniverse> universe) :IConwaySimulator(universe)
{

	_Master=0;
	MPI_Comm_size(MPI_COMM_WORLD,&_Processes);
	//_Processes=4;
}
ParallelConwaySimulator::~ParallelConwaySimulator()
{
	this->m_universe = nullptr;
}
void ParallelConwaySimulator::PrepareData(std::vector<int>&arr,int*sizes,int*displ)
{
	std::set<std::tuple<int, int> > LiveCellsRef= m_universe->aliveCells();
	if(!LiveCellsRef.size())
		return;
	int i=1;
	int chunk=LiveCellsRef.size()/_Processes;
	int Sizesiterator=0, sum=0;
	set<tuple<int,int>>temp;
	for(std::set<std::tuple<int, int> >::iterator it=LiveCellsRef.begin() ;it!=LiveCellsRef.end();++it, i++)
	{
		arr.push_back(std::get<0>(*it));
		arr.push_back(std::get<1>(*it));
		if(chunk==i)
		{


			/*sizes[Sizesiterator]=chunk;
			displ[Sizesiterator]=sum;
			if(LiveCellsRef.find(std::make_pair(std::get<0>(*it),std::get<1>(*it)+1))!=LiveCellsRef.end())
			{
			arr.push_back(std::get<0>(*it));
			arr.push_back(std::get<1>(*it)+1);
			++sizes[Sizesiterator];
			}
			for(int j=-1;j<=1;++j)
			if(LiveCellsRef.find(std::make_pair(std::get<0>(*it)+1,std::get<1>(*it)+j))!=LiveCellsRef.end())
			{
			arr.push_back(std::get<0>(*it)+1);
			arr.push_back(std::get<1>(*it)+j);
			++sizes[Sizesiterator];
			}
			arr.push_back(INT32_MIN);
			arr.push_back(chunk);
			sizes[Sizesiterator]*=2;
			sizes[Sizesiterator]+=2;
			sum+=sizes[Sizesiterator];
			++Sizesiterator;
			i=0;*/
		}
	}
	if(sizes[Sizesiterator]==0)
	{
		arr.push_back(INT32_MIN);
		displ[Sizesiterator]=sum;
		sizes[Sizesiterator]=LiveCellsRef.size()-((_Processes-1)*chunk);
		arr.push_back(sizes[Sizesiterator]);
		sizes[Sizesiterator]*=2;
		sizes[Sizesiterator]+=2;

	}
	cout<<"points :"<<LiveCellsRef.size()<<endl;
}
void ParallelConwaySimulator::step()
{
	int rank;
	vector<int> data(10000);
	int *ProcessesSizes=new int[_Processes*2];	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int size=10000;
	if(rank==_Master)	//if current running machine is master machine then do the following
	{
		size=0;
		auto LiveCellsRef= m_universe->aliveCells();
		int chunk=LiveCellsRef.size()/_Processes;
		for(int i=0;i<_Processes*2;i+=2)
		{
			ProcessesSizes[i]=chunk*2;
			ProcessesSizes[i+1]=chunk*2;
		}
		ProcessesSizes[(_Processes*2)-2]=(LiveCellsRef.size()-((_Processes-1)*chunk))*2;
		ProcessesSizes[(_Processes*2)-1]=chunk*2;
		for(std::set<std::tuple<int, int> >::iterator it=LiveCellsRef.begin() ;it!=LiveCellsRef.end();++it,++size)
		{
			data[size]=get<0>(*it);
			data[++size]=get<1>(*it);
		}
		data[size++]=INT32_MIN; //just an indicator
	}
	int *counts=new int[_Processes*2];

	MPI_Bcast(&data[0],size,MPI_INT,_Master,MPI_COMM_WORLD);
	MPI_Scatter(ProcessesSizes,2,MPI_INT,counts,2,MPI_INT,_Master,MPI_COMM_WORLD);
	auto aliveCells=m_universe->aliveCells();
	if(rank!=_Master)
	{
		for(int j=0;;j+=2)
		{
			if(data[j]==INT32_MIN)
				break;

			aliveCells.insert(make_tuple(data[j],data[j+1]));
		}
	}
	int start=rank*counts[1],end=start+counts[0];
	auto prev = m_universe->clone();
	m_universe->clear();
	auto cells = prev->aliveCells();
	int ChunkPerThread=2;
	int i;
#pragma omp parallel private(i)
	{
#pragma omp for schedule(dynamic,ChunkPerThread)
		for (i=start;i<end;i+=2)
		{
			cout<<"machine "<<rank<<" thread "<<omp_get_thread_num()<<endl;
			int x =data[i] , y = data[i+1];
			int n = prev->countNeighbours(x, y);

			int n1 = prev->countNeighbours(x-1,y-1);
			int n2 = prev->countNeighbours(x,y-1);
			int n3 = prev->countNeighbours(x+1,y-1);
			int n4 = prev->countNeighbours(x-1,y);
			int n5 = prev->countNeighbours(x+1,y);
			int n6 = prev->countNeighbours(x-1,y+1);
			int n7 = prev->countNeighbours(x,y+1);
			int n8 = prev->countNeighbours(x+1,y+1);


			//neighbours before cell
			if(n1 == 3)
				m_universe->turnOn(x-1, y-1);

			if(n2 == 3)
				m_universe->turnOn(x, y-1);

			if(n3 == 3)
				m_universe->turnOn(x+1, y-1);

			if(n4 == 3)
				m_universe->turnOn(x-1, y);

			//cell itself
			if(n==2 || n == 3)
				m_universe->turnOn(x, y);

			//neighbours after cell
			if(n5 == 3)
				m_universe->turnOn(x+1, y);

			if(n6 == 3)
				m_universe->turnOn(x-1, y+1);

			if(n7 == 3)
				m_universe->turnOn(x, y+1);

			if(n8 == 3)
				m_universe->turnOn(x+1, y+1);
		}
	}
	auto chengedUniverse=m_universe->aliveCells();

	if(rank==_Master)
	{
		for(int i=1;i<_Processes;++i)
		{
			MPI_Recv(&data[0],data.size(),MPI_INT,i,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
			for(int j=0;;j+=2)
			{
				if(data[j]==INT_MIN)
				{
					break;
				}
				chengedUniverse.insert(make_tuple(data[j],data[j+1]));
			}
		}
	}
	else
	{
		int i=0;	
		MPI_Request req;
		int*SendData=new int[m_universe->aliveCells().size()*2];
		for(std::set<std::tuple<int, int> >::iterator it=chengedUniverse.begin() ;it!=chengedUniverse.end();++it,++i)
		{
			SendData[i]=get<0>(*it);
			SendData[++i]=get<1>(*it);
		}
		SendData[i++]=INT_MIN;  //just an indicator
		MPI_Isend(SendData,i,MPI_INT,_Master,0,MPI_COMM_WORLD,&req);
	}
}
/*
int*displacment= new int[_Processes]
PrepareData(arr,ProcessesSizes,displacment);
/*cout<<"chunk sizes : ";
for(int i=0;i<_Processes;++i)
cout<<ProcessesSizes[i]<<" ";
cout<<endl;
vector<int>RecivData;
RecivData.resize(1000);
MPI_Scatterv(&arr[0],ProcessesSizes,displacment,MPI_INT,&RecivData[0],1000,MPI_INT,_Master,MPI_COMM_WORLD);
*/