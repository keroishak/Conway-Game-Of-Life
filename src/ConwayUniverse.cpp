#include "ConwayUniverse.h"
using namespace ConwayGameOfLife;

ConwayUniverse::ConwayUniverse(){
}

ConwayUniverse::~ConwayUniverse(){
	m_aliveCells.clear();
}

void ConwayUniverse::turnOn(int x, int y){
	m_aliveCells.insert(std::make_tuple(x,y));
}

void ConwayUniverse::turnOff(int x, int y){
	auto cell_it = m_aliveCells.find(std::make_tuple(x,y));
	if(cell_it != m_aliveCells.end())
		m_aliveCells.erase(cell_it);
}

const std::set<std::tuple<int,int> >& ConwayUniverse::aliveCells(){
	return m_aliveCells;
}

int ConwayUniverse::countNeighbours(int x, int y) const{
	auto cell_n1 = m_aliveCells.find(std::make_tuple(x+1,y));
	auto cell_n2 = m_aliveCells.find(std::make_tuple(x-1,y));

	auto cell_n3 = m_aliveCells.find(std::make_tuple(x,y-1));
	auto cell_n4 = m_aliveCells.find(std::make_tuple(x,y+1));

	auto cell_n5 = m_aliveCells.find(std::make_tuple(x-1,y-1));
	auto cell_n6 = m_aliveCells.find(std::make_tuple(x+1,y-1));

	auto cell_n7 = m_aliveCells.find(std::make_tuple(x-1,y+1));
	auto cell_n8 = m_aliveCells.find(std::make_tuple(x+1,y+1));

	int result = 0;
	
	result += cell_n1 != m_aliveCells.end()? 1 : 0;
	result += cell_n2 != m_aliveCells.end()? 1 : 0;
	result += cell_n3 != m_aliveCells.end()? 1 : 0;
	result += cell_n4 != m_aliveCells.end()? 1 : 0;
	result += cell_n5 != m_aliveCells.end()? 1 : 0;
	result += cell_n6 != m_aliveCells.end()? 1 : 0;
	result += cell_n7 != m_aliveCells.end()? 1 : 0;
	result += cell_n8 != m_aliveCells.end()? 1 : 0;

	return result;
}

std::shared_ptr<ConwayUniverse> ConwayUniverse::clone(){
	auto result = std::make_shared<ConwayUniverse>();
	result->m_aliveCells = m_aliveCells;
	return result;
}

void ConwayUniverse::clear(){
	m_aliveCells.clear();
}