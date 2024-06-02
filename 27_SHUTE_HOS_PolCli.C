#include <stdio.h>
#include <graphics.h>

typedef struct {
    int x, y;
} Point;
// Enter the minimum and maximum coordinates of the clipping window (x1 y1 x2 y2): 150 150 300 300
// Enter the number of vertices of the subject polygon: 5
// Enter the coordinates of the subject polygon vertices:
// Vertex 1: 150 150
// Vertex 2: 200 100
// Vertex 3: 250 150
// Vertex 4: 250 200
// Vertex 5: 200 250

// Function to find intersection point of a line with a clip boundary
Point intersect(Point p1, Point p2, int x1, int y1, int x2, int y2) {
    Point intersect_point;
    float m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    float b = p1.y - m * p1.x;

    // If line is parallel to boundary, return original point
    if (x1 == x2) {
        intersect_point.x = x1;
        intersect_point.y = m * x1 + b;
    } else {
        float x = (float)(y1 - b) / m;
        intersect_point.x = x;
        intersect_point.y = y1;
    }
    return intersect_point;
}

// Function to perform polygon clipping
void sutherlandHodgman(Point subject[], int n, Point clipper[]) {
    Point result[20];
    int k = 0;
    int next, i;

    for (i = 0; i < n; i++) {
        Point current = subject[i];
        Point prev = subject[(i + n - 1) % n];

        if ((current.x >= clipper[0].x && current.x <= clipper[2].x) &&
            (current.y >= clipper[0].y && current.y <= clipper[2].y)) {
            if ((prev.x >= clipper[0].x && prev.x <= clipper[2].x) &&
                (prev.y >= clipper[0].y && prev.y <= clipper[2].y)) {
                result[k++] = current;
            } else {
                result[k++] = intersect(prev, current, clipper[0].x, clipper[0].y, clipper[1].x, clipper[1].y);
                result[k++] = current;
            }
        } else if ((prev.x >= clipper[0].x && prev.x <= clipper[2].x) &&
                   (prev.y >= clipper[0].y && prev.y <= clipper[2].y)) {
            result[k++] = intersect(prev, current, clipper[0].x, clipper[0].y, clipper[1].x, clipper[1].y);
        }
    }

    cleardevice();
    setcolor(RED);
    rectangle(clipper[0].x, clipper[0].y, clipper[2].x, clipper[2].y);

    setcolor(WHITE);
    for (i = 0; i < k; i++) {
        next = (i + 1) % k;
        line(result[i].x, result[i].y, result[next].x, result[next].y);
    }
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2;
    int n, i;
    Point subject[20];
    Point clipper[4];

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter the minimum and maximum coordinates of the clipping window (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    printf("Enter the number of vertices of the subject polygon: ");
    scanf("%d", &n);

    printf("Enter the coordinates of the subject polygon vertices:\n");
    for (i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%d %d", &subject[i].x, &subject[i].y);
    }

// Initialize clipper array
clipper[0].x = x1;
clipper[0].y = y1;
clipper[1].x = x2;
clipper[1].y = y1;
clipper[2].x = x2;
clipper[2].y = y2;
clipper[3].x = x1;
clipper[3].y = y2;


    sutherlandHodgman(subject, n, clipper);

    getch();
    closegraph();
    return 0;
}
