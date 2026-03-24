#pragma once
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>




namespace cube {

	class Window {

		public:
			Window(int w, int h, std::string name);
			~Window();

			Window(const Window&) = delete;
			Window &operator=(const Window) = delete;

			void createWindowsurface(VkInstance instance, VkSurfaceKHR *surface);

		private:
			GLFWwindow *window{};
			uint32_t width{};
			uint32_t height{};

			std::string windowName{};

			void initWindow();
			void mainLoop();

			bool framebufferResized = false;

			static void framebufferResizeCallback(GLFWwindow *window, int width, int height);



	};

}
