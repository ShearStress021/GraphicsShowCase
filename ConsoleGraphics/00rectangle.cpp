#include "myConsoleEngine.hpp"


class MyRectangle : public ConsoleEngine {

	bool userConstruct(){
		drawTriangle(30,10,20,20,40,10,20,40);

		return true;
	}

};


int main(){
	MyRectangle res{};
	res.createWindow(130, 35, "renctangle");

	res.initConsoleEngine();

}



