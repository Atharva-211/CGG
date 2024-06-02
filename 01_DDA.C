#include <graphics.h>  // Include the graphics library

// Function to draw a line using DDA algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;

    float x = x1;
    float y = y1;
    int i;
    for (i = 0; i <= steps; i++) {
	putpixel(x, y, WHITE);
	x += xIncrement;
	y += yIncrement;
    }
}

int main() {
    // Initialize the graphics mode and driver
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");  // Adjust the path according to your setup

    // Set the color of the line
    setcolor(WHITE);

    // Draw a line from (100, 100) to (300, 200) using DDA algorithm
    drawLineDDA(100, 100, 300, 200);

    // Wait for the user to press a key
    getch();

    // Close the graphics mode and clean up
    closegraph();
    return 0;
}
