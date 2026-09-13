#include "myConsoleEngine.hpp"


class Cube3d : public ConsoleEngine {
	private:
		bool userConstruct(){

			return true;

		}

};


int main(){
	Cube3d res{};
	res.createWindow(130,35,"3d Cube");
	res.initConsoleEngine();
}

