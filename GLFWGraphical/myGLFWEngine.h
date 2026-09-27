#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

class GLFWEngine {
	public:
		GLFWEngine(){
			screenwidth = 800;
			screenheight = 600;

		}

		int createWindow(uint16_t width, uint16_t height ){
			screenwidth = width;
			screenheight = height;

			glfwnit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API)
			window = glfwCreateWindow(screenwidth, screenheight, "My 3d engine",nullptr,nullptr);
		}

		int initWindow(){

			while(!glfwWindowShouldClose(window)){
				glfwPollEvents();
			}
			glfwDestroyWindow(window);
			glfwTerminate();

		}

		~GLFWEngine(){
			delete [] screen;
		}



	private:
		uint32_t *screen{};
		uint16_t screenwidth{};
		uint16_t screenheight{};
		GLFWwindow * window{};
		bool running{false};
};


