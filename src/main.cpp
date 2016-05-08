#include <iostream>
#include <Infrastructure.hpp>
#include <ConwayGame.h>
using namespace std;

int main(){
    cout<<"Hello, World!"<<endl;
	Break::Infrastructure::Engine* engine = Break::Services::getEngine();
	engine->setup(std::make_shared<ConwayGameOfLife::ConwayGame>(), Break::Infrastructure::API::DirectX11);
	engine->join();
	engine->start();
    return 0;
}
