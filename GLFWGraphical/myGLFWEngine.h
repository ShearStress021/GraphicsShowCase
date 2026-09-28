#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <cstdint>
#include <string>
#include <cmath>
#include <chrono>
#include <thread>

struct Color {
	uint8_t red{};
	uint8_t green{};
	uint8_t blue{};
};



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
			hwnd = glfwGetWin32Window(window);

			screen =  new uint32_t[(size_t) screenwidth * screenheight];

			return 0;
		}

		void initWindow(){
			renderer();
		}

		uint16_t getScreenWidth(){
			return screenwidth;
		}

		uint16_t getScreenHeight(){
			return screenheight;
		}



		~GLFWEngine(){
			delete [] screen;
		}
	protected:
		virtual bool userConstruct() = 0;
		int CustomError(const char * text){
			char msg[256];
			std::snprintf(msg, sizeof(msg), "Error %s", text);
			return 1;
		}

		//virtual bool userUpdate(float deltaTime) = 0;


	private:
		void handlePixel(HWND hwnd){
			BITMAPINFO bitMapInfo{};
			bitMapInfo.bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
			bitMapInfo.bmiHeader.biWidth = screenwidth;
			bitMapInfo.bmiHeader.biHeight = screenheight;
			bitMapInfo.bmiHeader.biPlanes = 1;
			bitMapInfo.bmiHeader.biBitCount = 32;
			bitMapInfo.bmiHeader.biCompression = BI_RGB;

			HDC hdc = GetDC(hwnd);
			StretchDIBits(hdc,0,0,screenwidth,screenheight,0, 0,screenwidth,screenheight,screen,
					&bitMapInfo,DIB_RGB_COLORS,SRCCOPY);
			ReleaseDC(hwnd,hdc);
		} 
		void renderer(){
			while(!glfwWindowShouldClose(window) && running){
				glfwPollEvents();
				clearScreen({0,0,0});
				if(!userConstruct()) running = false;






				handlePixel(hwnd);
			}


			glfwDestroyWindow(window);
			glfwTerminate();



		}

		// formating pixel from Color {r,g,b} to 0xFFRRGGBB
		static inline uint32_t createPixel(Color color){
			uint8_t alpha  = 255;
			uint32_t pixelColor = alpha << 24 | color.red << 16 | color.green << 8 | color.blue;
			return pixelColor;
		}
		inline void ColorPixel(uint32_t *buff, int width, int x, int y,Color color){
			uint32_t pixelColor = createPixel(color);
			if(x < 0 || y < 0 || x >= screenwidth || y >= screenheight) return ;
			buff[y * width + x] = pixelColor;
		}

		void clearScreen(Color color){
			uint32_t pixelColor = createPixel(color);
			size_t screenSize = (size_t)screenwidth * screenheight ;
			for (size_t i{}; i < screenSize;i++) screen[i] = pixelColor;
		}

	public:
		void drawLine(int x1, int y1, int x2, int y2, Color color){
			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);

			int x = x1;
			int y = y1;

			int cx = (x1 < x2) ? 1 : -1;
			int cy = (y1 < y2) ? 1 : -1;


			ColorPixel(screen,screenwidth,x,y,color);

			// slope (dy/dx) <= 1;
			if(dx  >= dy){
				// 							// decision parameter
				int P = ((2*dy) - dx);
				while(x != x2){
					if (P < 0){
						x += cx;
						ColorPixel(screen,screenwidth,x,y,color);
						P = P + 2 * dy;
					} else {
						x+=cx; y+= cy;
						ColorPixel(screen,screenwidth,x,y,color);
						P = P + 2 * dy - 2 * dx;
					}

				}
			}else {    // slope (dy/dx) > 1;
				int P = ((2 *dx) - dy); // Decision Parameter
				while(y != y2){
					if(P < 0){
						y += cy;
						ColorPixel(screen,screenwidth,x,y,color);
						P = P + 2 * dx;
					}
					else {
						x += cx, y += cy;
						ColorPixel(screen,screenwidth,x,y,color);
						P = P + 2 * dx - 2 * dy;
					}

				}

			}
		}

		void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color){
			drawLine(x1, y1, x2, y2, color);
			drawLine(x2, y2, x3, y3, color);
			drawLine(x3, y3, x1, y1, color);

		}
	private: 
		uint32_t *screen{};
		uint16_t screenwidth{};
		uint16_t screenheight{};
		GLFWwindow * window{};
		bool running{true};
		std::string appName{};
		HWND hwnd;

};


