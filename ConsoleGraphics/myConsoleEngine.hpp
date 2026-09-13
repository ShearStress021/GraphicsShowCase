#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdint>

class ConsoleEngine {

	public:
		ConsoleEngine(){
			screenWidth = 130;
			screenHeight = 35;
			handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			appName = "Console Engine";
		}
		~ConsoleEngine(){
			SetConsoleActiveScreenBuffer(handleConsole);
			delete [] screen;
		}

		int createWindow(std::uint8_t width, std::uint8_t height, std::string_view gameName){
			screenWidth = width;
			screenHeight = height;
			appName = gameName;

			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Could make Console\n";
				return 1;

			}
			if(!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "Set ConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return 1;

			}


			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{};
			bufferSize = {(short)screenWidth, (short)screenHeight};
			if(!SetConsoleScreenBufferSize(handleConsole, bufferSize)){
				std::cerr << "Set Console Screen Buffer Size failed\n";
				CloseHandle(handleConsole);
				return 1;

			}


			CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
			if(!GetConsoleScreenBufferInfo(handleConsole, &screenInfo)){
				std::cerr << "GetConsoleScreenBufferInfo Failed\n";
				CloseHandle(handleConsole);
				return 1;


			}

			windowRect = {0,0, (short)(screenWidth - 1), (short)(screenHeight -1 )};

			if(!SetConsoleWindowInfo(handleConsole, TRUE, &windowRect)){
				std::cerr << "Set Console Window Info\n";
				return 1;

			}

			screen = new CHAR_INFO[screenWidth * screenHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

			return 0;


		}

		void helloWorld(){
			std::cout << "Hello, World\n";
		}

		virtual bool userConstruct() = 0;

		void init(){
			renderer();
		}

		void draw(int x, int y, short c= '-', short col = 0x0009){
			screen[y * screenWidth + x].Char.UnicodeChar = c;
			screen[y * screenWidth + x].Attributes = col;
		}

		void drawLine(int x1, int y1,int x2, int y2, short c = '-', short col = 0x0009){
			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);

			int x = x1;
			int y = y1;

			int cx = (x1 < x2) ? 1 : -1;
			int cy = (y1 < y2) ? 1 : -1;


			draw(x,y,c,col);

			// slope (dy/dx) <= 1;
			if(dx  >= dy){
				// 							// decision parameter
				int P = ((2*dy) - dx);
				while(x != x2){
					if (P < 0){
						x += cx;
						draw(x, y, c, col);
						P = P + 2 * dy;
					} else {
						x+=cx; y+= cy;
						draw(x, y, c, col);
						P = P + 2 * dy - 2 * dx;
					}

				}
			}else {    // slope (dy/dx) > 1;
				int P = ((2 *dx) - dy); // Decision Parameter
				while(y != y2){
					if(P < 0){
						y += cy;
						draw(x, y, c, col);
						P = P + 2 * dx;
					}
					else {
						x += cx, y += cy;
						draw(x,y,c , col);
						P = P + 2 * dx - 2 * dy;
					}

				}


			}

		}

		void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 'o', short col = 0x0009) {
			drawLine(x1,y1,x2,y2,c,col);
			drawLine(x2,y2,x3,y3,c,col);
			drawLine(x3,y3,x1,y1,c,col);
		}



		

	private:
		void renderer(){
			while(!running){

				// clear console
				for(int i{}; i < screenWidth * screenHeight; i++) {
					screen[i].Char.UnicodeChar= ' ';
					screen[i].Attributes = FOREGROUND_GREEN;
				}

				if(!userConstruct()){
					running = false;
				}
									

				// boarder 
				for(int i {}; i < screenWidth; i++){
					screen[i].Char.UnicodeChar = '=';
					screen[2* screenWidth + i].Char.UnicodeChar= '=';
				}


				char title[256];
				std::snprintf(title, sizeof(title), "My game Engine %s ",appName.c_str());
				SetConsoleTitle(title);
				WriteConsoleOutput(handleConsole, screen, 
						{(short)screenWidth , (short)screenHeight}, {0,0}, &windowRect);
				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) running = true;
				
			}

		}




	private:
		HANDLE handleConsole{};
		std::uint8_t screenWidth{};
		std::uint8_t screenHeight{};
		CHAR_INFO *screen{};
		SMALL_RECT windowRect{};
		bool running{false};
		std::string appName{};
};




