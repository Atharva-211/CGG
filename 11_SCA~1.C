#include<stdio.h>
#include<graphics.h>
#include<math.h>

//structure for holding 2D coordinates
typedef struct
{
    int x;
    int y;
} Point;

//structure for holding queue elements
typedef struct
{
    int x;
    int y;
} QueueElement;

//function to add an element to the queue
void enqueue(QueueElement queue[], int* rear, QueueElement value)
{
    queue[*rear] = value;
    (*rear)++;
}

//function to remove an element from the queue
QueueElement dequeue(QueueElement queue[], int* front)
{
    QueueElement value = queue[*front];
    (*front)++;
    return value;
}

int isInside(Point seed, Point vertices[], int numVertices)
{
    int i, j, c = 0;
    for (i = 0, j = numVertices - 1; i < numVertices; j = i++)
    {
        if (((vertices[i].y > seed.y) != (vertices[j].y > seed.y)) &&
                (seed.x < (vertices[j].x - vertices[i].x) * (seed.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
            c = !c;
    }
    return c;
}
//function to implement DDA algorithm for line drawing
void DDA(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int i;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;
    float x = p1.x, y = p1.y;
    for (i = 0; i < steps; i++)
    {
        putpixel(x, y, WHITE);
        x += xIncrement;
        y += yIncrement;
    }
}



// Function to implement scanline filling algorithm
void scanFill(Point vertices[], int numVertices) {
    int i, y, j;
    int INT_MAX, INT_MIN;
    int minY = INT_MAX, maxY = INT_MIN;
    QueueElement queue[100];
    int front = 0, rear = 0;
    int intersects[100];
    int numIntersects = 0;

    // Find min and max Y values
    for (i = 0; i < numVertices; i++) {
        if (vertices[i].y < minY) {
            minY = vertices[i].y;
        }
        if (vertices[i].y > maxY) {
            maxY = vertices[i].y;
        }
    }

    for (y = minY; y <= maxY; y++) {
        numIntersects = 0;

        for (i = 0; i < numVertices; i++) {
            int j = (i + 1) % numVertices;
            if ((vertices[i].y <= y && vertices[j].y > y) || (vertices[j].y <= y && vertices[i].y > y)) {
                float x = (float)(vertices[i].x + (float)(y - vertices[i].y) / (vertices[j].y - vertices[i].y) * (vertices[j].x - vertices[i].x));
                intersects[numIntersects++] = (int)x;
            }
        }

        if (numIntersects > 1) {
            // Sort the intersection points
            for (i = 0; i < numIntersects - 1; i++) {
                for (j = 0; j < numIntersects - i - 1; j++) {
                    if (intersects[j] > intersects[j + 1]) {
                        int temp = intersects[j];
                        intersects[j] = intersects[j + 1];
                        intersects[j + 1] = temp;
                    }
                }
            }

            // Draw lines between pairs of intersections
            for (i = 0; i < numIntersects; i += 2) {
                Point startPoint;
                Point endPoint;
                
                startPoint.x = intersects[i];
                startPoint.y = y;
                
                endPoint.x = intersects[i + 1];
                endPoint.y = y;
                
                DDA(startPoint, endPoint);
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int numVertices, i;
    
     Point *vertices;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    printf("Enter the number of vertices of the polygon: ");
    scanf("%d", &numVertices);
    
    // Dynamically allocate memory for vertices
    vertices = (Point *)malloc(numVertices * sizeof(Point));
    if (vertices == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (i = 0; i < numVertices; i++) {
        printf("Enter the x and y coordinates of vertex %d: ", i + 1);
        scanf("%d %d", &vertices[i].x, &vertices[i].y);
    }

    // Draw the polygon
    for (i = 0; i < numVertices; i++) {
        int j = (i + 1) % numVertices;
        DDA(vertices[i], vertices[j]);
    }

    // Fill the polygon
    scanFill(vertices, numVertices);

    getch();
    closegraph();
    
    // Free dynamically allocated memory
    free(vertices);
    
    return 0;
}
//(100, 100)
//(200, 100)
//(150, 150)
//(200, 200)
//(100, 200)
