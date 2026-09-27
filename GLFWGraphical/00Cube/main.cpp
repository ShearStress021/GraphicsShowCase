#include "../myGLFWEngine.h"

class Cube : public GLFWEngine {
	protected:
		bool userConstruct(){
			drawLine(100,200,550,450, {0,0,255});
			return true;
		}
	


};


int main(){
	Cube cube{};
	if(cube.createWindow(800,600, "3d Cube") != 0) return 1;
	cube.initWindow();
	
}
