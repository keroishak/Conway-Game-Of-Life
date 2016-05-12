#pragma once
#include <Application.hpp>
#include <Sprite.hpp>
#include <SpriteBatch.hpp>
#include "ConwayUniverse.h"
#include "IConwaySimulator.h"
#include <glm\glm.hpp>
using namespace std;
namespace ConwayGameOfLife{
	//this is a typical Break Application 
    class ConwayGame: public Break::Infrastructure::Application {
	public:
        ConwayGame(string);

        ~ConwayGame();
		void save();
        void init() override;

        void loadResources() override;

        void setupScene() override;

        void cleanUp() override;

        void input() override;

        void update(Break::Infrastructure::TimeStep time) override;

        void render() override;

	private:
		//number of conway game generations
		int generations;
		//size of the grid for drawing
		int m_pixelSize;
		int width;
		void LoadFile(std::string );
		//color of the grid
		Break::Infrastructure::Color m_gridColor, m_cellColor;
		//camera translation in cells
		glm::ivec2 m_translation;
		//sprite batch for drawing cells
		std::shared_ptr<Break::Graphics::SpriteBatch> m_spriteBatch;
		//conway simulator takes a universe and simulate a step through step function
		std::shared_ptr<IConwaySimulator> m_serialSimulator, m_parallelSimulator;
		//conway universe
		std::shared_ptr<ConwayUniverse> m_universe;
		//boolean for mouse continuous actions
		bool left_down, right_down;
    };
}
