#include "myConsoleEngine.hpp"


class MyRectangle : public ConsoleEngine {

	bool userConstruct(){
		drawTriangle(10,10,40,10,10,20, 0x2588);
		drawTriangle(10,20,40,20,40,10, 0x2588);

		return true;
	}

};


int main(){
	MyRectangle res{};
	res.createWindow(130, 35, "renctangle");
	res.init();

}



