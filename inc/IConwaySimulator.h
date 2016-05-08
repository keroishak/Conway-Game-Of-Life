#pragma once

#include "ConwayUniverse.h"
#include <memory>

namespace ConwayGameOfLife{
	class IConwaySimulator{
	protected:
		std::shared_ptr<ConwayUniverse> m_universe;
	public:
		IConwaySimulator(std::shared_ptr<ConwayUniverse> universe):m_universe(universe){}
		virtual ~IConwaySimulator(){};

		virtual void step() = 0;
	};
}