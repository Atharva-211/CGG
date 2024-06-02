#include <graphics.h>
#include <stdio.h>
#include <math.h>

// Function to draw a line using DDA algorithm
void drawLineDDA(int X1, int Y1, int X2, int Y2) {
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = X1;
    float Y = Y1;
    int i;
    for ( i = 0; i <= steps; i++) {
        putpixel(X, Y, WHITE);
        X += Xinc;
        Y += Yinc;
        delay(10);
    }
}

// Function to implement Fence Fill algorithm for concave polygons
void fenceFillConcave(int x[], int y[], int n, int fill_color, int boundary_color) {
    // Draw the polygon boundary
    int i, minX, minY, maxX, maxY;
    int j,k;
    for ( i = 0; i < n; i++) {
	drawLineDDA(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }

    minX = x[0], maxX = x[0];
    minY = y[0], maxY = y[0];

    // Find the minimum and maximum coordinates
    for ( i = 1; i < n; i++) {
	if (x[i] < minX) minX = x[i];
	if (x[i] > maxX) maxX = x[i];
	if (y[i] < minY) minY = y[i];
	if (y[i] > maxY) maxY = y[i];
    }

    // Perform the fence fill algorithm
    for ( i = minY + 1; i < maxY; i++) {
	int intersectionPoints[1000];
	int count = 0;

	for ( j = 0; j < n; j++) {
	    int x1 = x[j];
	    int y1 = y[j];
	    int x2 = x[(j + 1) % n];
	    int y2 = y[(j + 1) % n];

	    if ((y1 <= i && i < y2) || (y2 <= i && i < y1)) {
		int intersectX = x1 + (float)(i - y1) * (x2 - x1) / (y2 - y1);
		intersectionPoints[count++] = intersectX;
	    }
	}

	// Sort the intersection points in ascending order
	for ( j = 0; j < count - 1; j++) {
	    for ( k = 0; k < count - j - 1; k++) {
                if (intersectionPoints[k] > intersectionPoints[k + 1]) {
                    int temp = intersectionPoints[k];
                    intersectionPoints[k] = intersectionPoints[k + 1];
                    intersectionPoints[k + 1] = temp;
                }
            }
        }

        // Fill the scanline between intersection points
	for ( j = 0; j < count - 1; j += 2) {
	    for ( k = intersectionPoints[j]; k < intersectionPoints[j + 1]; k++) {
                putpixel(k, i, fill_color);
                delay(10);
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int n, i;
    int *x, *y;
    int fill_color = GREEN;
    int boundary_color = WHITE;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI"); // Adjust path as necessary

    printf("Enter the number of vertices of the concave polygon: ");
    scanf("%d", &n);

    // Allocate memory for the coordinates
    x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));

    if (x == NULL || y == NULL) {
        printf("Memory allocation failed\n");
        closegraph();
        return 1;
    }

    printf("Enter the coordinates of the vertices:\n");
    for (i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    fenceFillConcave(x, y, n, fill_color, boundary_color);

    getch();
    closegraph();

    // Free allocated memory
    free(x);
    free(y);

    return 0;
}
// (100, 100)
// (200, 100)
// (150, 150)
// (200, 200)
// (100, 200)
