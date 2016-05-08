#include "ConwayGame.h"
#include <TimeStep.hpp>
#include <Pixel.hpp>
#include "SerialConwaySimulator.h"
#include <Keyboard.hpp>
#include <Mouse.hpp>
#include <time.h>
using namespace ConwayGameOfLife;
using namespace Break;
using namespace Break::Infrastructure;

ConwayGame::ConwayGame()
{
	this->window = std::make_shared<Window>(500,500, "Conway Game Of Life");
	m_pixelSize = 10;
	m_translation = glm::ivec2(0);
	m_universe = std::make_shared<ConwayUniverse>();
	m_serialSimulator = std::make_shared<SerialConwaySimulator>(m_universe);
	left_down = right_down = false;
}

ConwayGame::~ConwayGame()
{

}

void ConwayGame::init()
{
	//setup map
	m_spriteBatch = std::make_shared<Break::Graphics::SpriteBatch>();
	m_gridColor = Color(200,200,200,50);
	m_cellColor = Color(255,255,255,255);

	/*
	srand(time(0));
	for(int i=0;i<50;i++){
		m_universe->turnOn(rand()%(window->getWidth()/m_pixelSize),rand()%(window->getHeight()/m_pixelSize));
	}
	*/
}

void ConwayGame::loadResources()
{

}

void ConwayGame::setupScene()
{

}

void ConwayGame::cleanUp()
{

}

void ConwayGame::input()
{
	if(Keyboard::getKey(Keyboard::Down) == Keyboard::State_Down)
		m_translation.y -= 1;

	if(Keyboard::getKey(Keyboard::Up) == Keyboard::State_Down)
		m_translation.y += 1;

	if(Keyboard::getKey(Keyboard::Right) == Keyboard::State_Down)
		m_translation.x -= 1;

	if(Keyboard::getKey(Keyboard::Left) == Keyboard::State_Down)
		m_translation.x += 1;

	if(Keyboard::getKey(Keyboard::Space) == Keyboard::State_Down)
		m_translation = glm::ivec2(0);

	if(Keyboard::getKey(Keyboard::S) == Keyboard::State_Down)
		m_serialSimulator->step();

	if(Mouse::getButton(Mouse::Left_Button) == Mouse::State_Down){
		left_down = true;
	}

	if(left_down){
		int x = Mouse::getPosition().x / m_pixelSize;
		int y = Mouse::getPosition().y / m_pixelSize;

		m_universe->turnOn(x+(-m_translation.x), y+(-m_translation.y));
	}

	if(Mouse::getButton(Mouse::Left_Button) == Mouse::State_Up){
		left_down = false;
	}

	if(Mouse::getButton(Mouse::Right_Button) == Mouse::State_Down){
		right_down = true;
	}

	if(right_down){
		int x = Mouse::getPosition().x / m_pixelSize;
		int y = Mouse::getPosition().y / m_pixelSize;

		m_universe->turnOff(x+(-m_translation.x), y+(-m_translation.y));
	}

	if(Mouse::getButton(Mouse::Right_Button) == Mouse::State_Up){
		right_down = false;
	}

	if(Keyboard::getKey(Keyboard::Q) == Keyboard::State_Down && m_pixelSize < window->getWidth())
		m_pixelSize += 1;

	if(Keyboard::getKey(Keyboard::A) == Keyboard::State_Down && m_pixelSize > 1)
		m_pixelSize -= 1;
}

void ConwayGame::update(TimeStep time)
{

}

void ConwayGame::render()
{
	m_spriteBatch->begin();

	auto aliveCells = m_universe->aliveCells();
	for(auto& live_cell : aliveCells){
		m_spriteBatch->draw(nullptr, //texture
			(std::get<0>(live_cell)+m_translation.x)*m_pixelSize, //position x
			(std::get<1>(live_cell)+m_translation.y)*m_pixelSize, //position y
			m_pixelSize, //width
			m_pixelSize, //height
			m_cellColor); //cell color
	}
	
	//grid drawing if pixel_size is > 1
	if(m_pixelSize > 1){
		for(int i=0;i<window->getWidth();i+=m_pixelSize)
		{
			m_spriteBatch->draw(nullptr,i,0,1,window->getHeight(),m_gridColor);
		}

		for(int i=0;i<window->getHeight();i+=m_pixelSize)
		{
			m_spriteBatch->draw(nullptr,0,i,window->getWidth(),1,m_gridColor);
		}
	}
	m_spriteBatch->end();
}