#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include "drawUtils.hpp"
#include "cube.hpp"



uint32_t * buffer = new uint32_t[(size_t) WIDTH * HEIGHT];

void handlePixel(HWND hwnd){
	BITMAPINFO bitmapinfo{};
	bitmapinfo.bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biWidth = WIDTH;
	bitmapinfo.bmiHeader.biHeight = HEIGHT;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biCompression  = BI_RGB;

	HDC hdc = GetDC(hwnd);
	StretchDIBits(hdc, 0,0,WIDTH,HEIGHT,0,0,WIDTH,HEIGHT, buffer, &bitmapinfo,DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(hwnd,hdc);
}

Color black{0,0,0};
Color green{0,255,0};


int main(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // no OpenGL / Vulkan context
													//
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "glfw 3D renderer", nullptr, nullptr);
//	glfwSetFramebufferSizeCallback(window, onResize);
	HWND hwnd = glfwGetWin32Window(window);

	Cube3d cube{};

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		clearScreen(black);
		cube.createCube();


		handlePixel(hwnd);

	}

	delete [] buffer;

	glfwDestroyWindow(window);
	glfwTerminate();


}
