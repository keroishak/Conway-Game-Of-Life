#include <iostream>
#include <Infrastructure.hpp>
#include <ConwayGame.h>
#include<mpi.h>
#include<vector>
#include<omp.h>
using namespace std;

int main(int argc,char**argv){
	MPI_Init(&argc,&argv);
	//cout<<"Hello, World!"<<endl;
	std::shared_ptr<ConwayGameOfLife::ConwayGame>ConwayGame= std::make_shared<ConwayGameOfLife::ConwayGame>("Input.txt");
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//cout<<omp_get_thread_num()<<endl;
	if(rank==0)
	{
		Break::Infrastructure::Engine* engine = Break::Services::getEngine();
		engine->setup(ConwayGame, Break::Infrastructure::API::OpenGL3_3);
		engine->join();
		engine->start();
	}
	else
		ConwayGame->input();
	MPI_Finalize();
	return 0;
}
