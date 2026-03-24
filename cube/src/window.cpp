#include "window.hpp"




namespace cube {

	Window::Window(int w, int  h, std::string name)
		:
			width(w),
			height(h),
			windowName(name)
	{
		initWindow();
		mainLoop();

	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
  		glfwTerminate();
	}

	void Window::initWindow()
	{
		  glfwInit();
		  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		  window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		  glfwSetWindowUserPointer(window, this);
		  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	}

	

	void Window::createWindowsurface(VkInstance instance, VkSurfaceKHR *surface)
	{
		 if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to craete window surface");
	  	 }
	}

	void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height)
	{
		auto resizedWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
		resizedWindow->framebufferResized = true;
		resizedWindow->width = width;
		resizedWindow->height = height;

	}
	void Window::mainLoop()
	{
	   while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
     //       drawFrame();
        }

	}




}
