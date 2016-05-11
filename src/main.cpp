#include <iostream>
#include <Infrastructure.hpp>
#include <ConwayGame.h>
#include<mpi.h>
#include<vector>
#include<omp.h>
using namespace std;

int main(int argc,char**argv){
	MPI_Init(&argc,&argv);
	cout<<"Hello, World!"<<endl;
	std::shared_ptr<ConwayGameOfLife::ConwayGame>ConwayGame= std::make_shared<ConwayGameOfLife::ConwayGame>();
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	/*vector<int> data;
	for(int i=0;i<20;++i)
		data.push_back(i);
	int counts[]={10,6,4};
	int dis[]={0,10,16};
	vector<int> rec;
	rec.resize(101);
	MPI_Scatterv(&data[0],counts,dis,MPI_INT,&rec[0],10,MPI_INT,0,MPI_COMM_WORLD);
	cout<<rank<<endl;
	cout<<dis[rank]<<endl;
	for(int i=0;i<counts[rank]+2;++i)
		cout<<rec[i]<<" ";
	cout<<endl;*/
	/*int arr[100]={0};
	int size=5;
	MPI_Bcast(arr,size, MPI_INT, 0,MPI_COMM_WORLD);
	for(int i=0;i<size;++i)
		std::cout<<arr[i]<<" ";
	std::cout<<std::endl;*/
	cout<<omp_get_thread_num()<<endl;
	if(rank==0)
	{
		Break::Infrastructure::Engine* engine = Break::Services::getEngine();
		engine->setup(ConwayGame, Break::Infrastructure::API::OpenGL3_3);
		engine->join();
		engine->start();
	}
	MPI_Finalize();
	return 0;
}
