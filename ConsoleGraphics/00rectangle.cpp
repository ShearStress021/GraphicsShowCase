#include "myConsoleEngine.hpp"


class MyRectangle : public ConsoleEngine {

	bool userConstruct(){
		drawTriangle(10,10,40,10,10,20, 'o');
		drawTriangle(10,20,40,20,40,10, 'o');

		return true;
	}

};


int main(){
	MyRectangle res{};
	res.createWindow(130, 35, "renctangle");

	res.initConsoleEngine();

}



