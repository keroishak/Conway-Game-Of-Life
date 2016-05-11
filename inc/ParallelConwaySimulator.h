#pragma once
#include "IConwaySimulator.h"
#include<mpi.h>
#include<omp.h>
#include<iostream>
#include<vector>
using namespace std;
namespace ConwayGameOfLife
{
	class ParallelConwaySimulator:public IConwaySimulator
	{
		int _Processes; //number of machines
		int _Master;	   //master machine
		void PrepareData(std::vector<int>&,int*,int*);
	public:
		ParallelConwaySimulator(std::shared_ptr<ConwayUniverse>);
		~ParallelConwaySimulator()override;
		void step() override;
	};
}
