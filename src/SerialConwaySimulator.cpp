#include "SerialConwaySimulator.h"
using namespace ConwayGameOfLife;

SerialConwaySimulator::SerialConwaySimulator(std::shared_ptr<ConwayUniverse> universe):IConwaySimulator(universe){
}

SerialConwaySimulator::~SerialConwaySimulator(){
	this->m_universe = nullptr;
}

void SerialConwaySimulator::step(){
	//go step
	if(!m_universe)
		return;

	auto prev = m_universe->clone();
	m_universe->clear();
	auto cells = prev->aliveCells();
	for (auto& cell : cells){
		int x = std::get<0>(cell), y = std::get<1>(cell);
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