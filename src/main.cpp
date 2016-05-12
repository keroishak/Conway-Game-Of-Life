#include <iostream>
#include <Infrastructure.hpp>
#include <ConwayGame.h>
#include<mpi.h>
#include<vector>
#include<omp.h>
using namespace std;

int main(int argc,char**argv){
	MPI_Init(&argc,&argv);
	double start=MPI_Wtime();
	//cout<<"Hello, World!"<<endl;

	//read Input .txt file
	std::shared_ptr<ConwayGameOfLife::ConwayGame>ConwayGame= std::make_shared<ConwayGameOfLife::ConwayGame>("Input.txt");
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		Break::Infrastructure::Engine* engine = Break::Services::getEngine();
		engine->setup(ConwayGame, Break::Infrastructure::API::OpenGL3_3);
		engine->join();
		engine->start();
	}
	else
		ConwayGame->input();
	double end=MPI_Wtime();
	printf("machine %d , time elapsed %f",rank,end-start);
	MPI_Finalize();
	return 0;
}
