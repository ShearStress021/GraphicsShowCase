#include "../myGLFWEngine.h"

class Cube : public GLFWEngine {

};


int main(){
	GLFWEngine cube{};
	if(cube.createWindow(800,600, "3d Cube") != 0) return 1;
	cube.initWindow();
	
}
