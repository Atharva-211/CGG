#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

void drawFractalLine(int x1, int y1, int x2, int y2, int n) {
    if (n == 0) {
        line(x1, y1, x2, y2);
    } else {
        int mid_x = (x1 + x2) / 2;
        int mid_y = (y1 + y2) / 2;
        int offset = rand() % 51 - 25; // Random offset for variation

        mid_y += offset;

        drawFractalLine(x1, y1, mid_x, mid_y, n - 1);
        drawFractalLine(mid_x, mid_y, x2, y2, n - 1);
    }
}

int main() {
    int gd = DETECT, gm;
    
    int n = 5; // Number of iterations
    int x1 = 50, y1 = 300, x2 = 550, y2 = 300; // Initial line coordinates
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");


    drawFractalLine(x1, y1, x2, y2, n);

    getch();
    closegraph();
    return 0;
}
