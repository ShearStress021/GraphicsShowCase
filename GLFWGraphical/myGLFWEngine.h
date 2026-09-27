#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include <Windows.h>

class GLFWEngine {
	public:
		GLFWEngine(){
			screenwidth = 800;
			screenheight = 600;
			appName = "GLFW window";

		}

		int createWindow(uint16_t width, uint16_t height, std::string_view titleName){
			screenwidth = width;
			screenheight = height;
			appName = titleName;

			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			window = glfwCreateWindow(screenwidth, screenheight, appName.c_str(),nullptr,nullptr);
			return 0;
		}

		void initWindow(){
			renderer();
		}



		~GLFWEngine(){
			delete [] screen;
		}
	private:
		void renderer(){
			while(!glfwWindowShouldClose(window)){
				glfwPollEvents();
			}
			glfwDestroyWindow(window);
			glfwTerminate();

		}

	private: uint32_t *screen{};
		uint16_t screenwidth{};
		uint16_t screenheight{};
		GLFWwindow * window{};
		bool running{false};
		std::string appName{};

};


