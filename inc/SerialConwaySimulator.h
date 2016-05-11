#pragma once

#include "IConwaySimulator.h"

namespace ConwayGameOfLife{

	class SerialConwaySimulator: public IConwaySimulator{
	public:
		SerialConwaySimulator(std::shared_ptr<ConwayUniverse> universe);
		~SerialConwaySimulator() override;

		void step() override;
	};
}