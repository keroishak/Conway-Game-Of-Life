#pragma once
#include <set>
#include <tuple>
#include <memory>
namespace ConwayGameOfLife{

	//the case of the sparse matrix is that we assume that initialy all values has a defined value which is 0 or off
	//then each interaction with the matrix and change in the state of the cell will be registered as on cell
	//so the registered cells are the on cells and every other cell is off
	class ConwayUniverse{
	public:
		ConwayUniverse();
		~ConwayUniverse();

		void turnOn(int x, int y);
		void turnOff(int x, int y);

		const std::set<std::tuple<int, int> >& aliveCells();

		int countNeighbours(int x, int y) const;

		std::shared_ptr<ConwayUniverse> clone();

		void clear();
	private:
		std::set<std::tuple<int, int> > m_aliveCells;
	};
}