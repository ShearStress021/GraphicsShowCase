#pragma once
#include <cmath>
#include <cstdint>


#define WIDTH 800
#define HEIGHT 600


extern uint32_t* buffer ;


struct Color {
//	uint8_t alpha{};
	uint8_t red{};
	uint8_t green{};
	uint8_t blue{};
};

// converting struct color to 0x00RRGGBB format
static inline uint32_t createPixel(Color color){
	uint8_t alpha = 255;
	uint32_t pixelColor =  alpha << 24 | color.red << 16 | color.green << 8 | color.blue;
	return pixelColor;
}
static inline void clearScreen(Color color){
	uint32_t colorClear = createPixel(color);
	const int screenSize = (size_t) WIDTH * HEIGHT;
	for(size_t i{}; i < screenSize; i++){
		buffer[i] = colorClear;
	}
}


// Coloring pixel
static inline void colorPixel(uint32_t *buff, int w, int x, int y, Color color) {
	uint32_t pixelColor = createPixel(color);
	if(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) return;
	buff[y * w + x] = pixelColor;
}

void drawLine(int x1, int y1, int x2, int y2, Color color);
void drawTriangle(int x1,int y1, int x2, int y2, int x3, int y3, Color color);










