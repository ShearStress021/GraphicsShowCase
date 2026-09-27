#include "drawUtils.hpp"



void drawLine(int x1, int y1, int x2, int y2, Color color){
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int x = x1;
	int y = y1;

	int cx = (x1 < x2) ? 1 : -1;
	int cy = (y1 < y2) ? 1 : -1;
	colorPixel(buffer,WIDTH,x,y,color);

	// Slope (dy/dx) <= 1;
	if(dx >= dy){
		int P = ((2 * dy) - dx);
		while(x !=  x2){
			if (P < 0){
				x += cx;
				colorPixel(buffer,WIDTH,x,y,color);
				P = P + 2 * dy;
			}else {
				x += cx;
				y += cy;
				colorPixel(buffer,WIDTH,x,y,color);
				P = P + 2 * dy - 2 * dx;
			}

		}

	}else { // Slope (dy/dx) > 1
		int P = ((2 * dx) - dy);
		while(y != y2){
			if(P < 0){
				y += cy;
				colorPixel(buffer,WIDTH,x,y,color);
				P = P + 2 * dx;
			}else {
				x += cx;
				y += cy;
				colorPixel(buffer,WIDTH,x,y,color);
				P = P + 2 * dy - 2 * dy;
			}

		}

	}


}


void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color){
	drawLine(x1,y1, x2, y2, color);
	drawLine(x2,y2, x3, y3, color);
	drawLine(x1,y1, x3, y3, color);

}
