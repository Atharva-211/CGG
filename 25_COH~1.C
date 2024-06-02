#include <stdio.h>
#include <graphics.h>

// Function to compute region code for a point (x, y)
int computeRegionCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
    int code = 0;

    if (x < xmin)
        code |= 1; // Left
    else if (x > xmax)
        code |= 2; // Right
    if (y < ymin)
        code |= 4; // Bottom
    else if (y > ymax)
        code |= 8; // Top

    return code;
}

// Function to clip a line using Cohen-Sutherland algorithm
void cohenSutherland(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax) {
    int code1 = computeRegionCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeRegionCode(x2, y2, xmin, ymin, xmax, ymax);
    int accept = 0;

    while (1) {
        if (!(code1 | code2)) {
            accept = 1; // Both endpoints are inside window
            break;
        } else if (code1 & code2) {
            break; // Both endpoints are outside window, trivially reject
        } else {
            int codeOut = code1 ? code1 : code2;
            int x, y;

            if (codeOut & 8) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & 4) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & 2) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & 1) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1, xmin, ymin, xmax, ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        setcolor(RED);
        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
	// Input window coordinates
    int xmin, ymin, xmax, ymax;
	// Input line endpoints
    int x1, y1, x2, y2;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");


    printf("Enter the coordinates of the clipping window (xmin ymin xmax ymax): ");
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);

    // Draw the clipping window
    rectangle(xmin, ymin, xmax, ymax);


    printf("Enter the coordinates of the line endpoints (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    // Draw the original line
    setcolor(WHITE);
    line(x1, y1, x2, y2);

    // Clip the line using Cohen-Sutherland algorithm
    cohenSutherland(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    getch();
    closegraph();

    return 0;
}

// 50 50 250 150
// 20 50 300 200