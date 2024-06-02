#include <graphics.h>
#include <math.h>
#include <stdio.h>

void bezierCurve(int x[4], int y[4]) {
    double t;
    for (t = 0.0; t <= 1.0; t += 0.0005) {
        double xt = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        double yt = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];
        putpixel(xt, yt, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
	int x[4], y[4];
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");


    printf("Enter the coordinates of the four control points (x1, y1, x2, y2, x3, y3, x4, y4): ");
    scanf("%d %d %d %d %d %d %d %d", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);

    bezierCurve(x, y);

    getch();
    closegraph();
    return 0;
}