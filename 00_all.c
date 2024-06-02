#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

// Function to draw a line using DDA algorithm
void dda(int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int i;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1;
    float y = y1;

    for ( i = 0; i <= steps; i++)
    {
        putpixel(x, y, color);
        x += xIncrement;
        y += yIncrement;
    }
}

// Function to perform flood fill algorithm
void flood_fill(int x, int y, int new_col, int old_col)
{
    if (getpixel(x, y) == old_col)
    {
        putpixel(x, y, new_col);
        flood_fill(x + 1, y, new_col, old_col);
        flood_fill(x - 1, y, new_col, old_col);
        flood_fill(x, y + 1, new_col, old_col);
        flood_fill(x, y - 1, new_col, old_col);
    }
}

// Function to fill a polygon using scan line fill algorithm
void scanline_fill(int x[], int y[], int n, int fill_color)
{
    int min_y = y[0];
    int max_y = y[0];
    int i, y_scan, j, x_fill;
    for ( i = 1; i < n; i++)
    {
	if (y[i] < min_y)
	    min_y = y[i];
	if (y[i] > max_y)
	    max_y = y[i];
    }

    for ( y_scan = min_y; y_scan <= max_y; y_scan++)
    {
	int intersections = 0;
	int intersections_x[10];
	for (i = 0; i < n; i++)
	{
	    int next = (i + 1) % n;
	    int y_curr = y[i];
	    int y_next = y[next];
	    if ((y_curr < y_scan && y_next >= y_scan) || (y_next < y_scan && y_curr >= y_scan))
	    {
		int dx = x[next] - x[i];
		int dy = y[next] - y[i];
		int x_intersection = x[i] + (y_scan - y[i]) * dx / dy;
		intersections_x[intersections++] = x_intersection;
	    }
	}

	// Sort the intersection points
	for ( i = 0; i < intersections - 1; i++)
	{
	    for ( j = i + 1; j < intersections; j++)
	    {
		if (intersections_x[i] > intersections_x[j])
		{
		    int temp = intersections_x[i];
		    intersections_x[i] = intersections_x[j];
		    intersections_x[j] = temp;
		}
	    }
	}

	// Fill the scan line between intersection points
	for ( i = 0; i < intersections; i += 2)
	{
	    for ( x_fill = intersections_x[i]; x_fill <= intersections_x[i + 1]; x_fill++)
            {
                putpixel(x_fill, y_scan, fill_color);
            }
        }
    }
}

// Function to translate points
void translate(int x[], int y[], int n, int tx, int ty)
{   int i;
    for ( i = 0; i < n; i++)
    {
        x[i] += tx;
        y[i] += ty;
    }
}

// Function to rotate points around a pivot
void rotate(int x[], int y[], int n, float angle, int pivot_x, int pivot_y)
{
    int i;
    angle = angle * (3.14159 / 180); // Convert angle to radians
    for ( i = 0; i < n; i++)
    {
        int new_x = pivot_x + (x[i] - pivot_x) * cos(angle) - (y[i] - pivot_y) * sin(angle);
        int new_y = pivot_y + (x[i] - pivot_x) * sin(angle) + (y[i] - pivot_y) * cos(angle);
        x[i] = new_x;
        y[i] = new_y;
    }
}

// Function to scale points around a pivot
void scale(int x[], int y[], int n, float sx, float sy, int pivot_x, int pivot_y)
{
    int i;
    for ( i = 0; i < n; i++)
    {
        x[i] = pivot_x + (x[i] - pivot_x) * sx;
        y[i] = pivot_y + (y[i] - pivot_y) * sy;
    }
}

// Function to reflect points along an axis (X or Y)
void reflect(int x[], int y[], int n, char axis)
{
int i;
    int mid_x = getmaxx() / 2;
    int mid_y = getmaxy() / 2;

    if (axis == 'x' || axis == 'X')
    {
	for ( i = 0; i < n; i++)
	{
	    y[i] = 2 * mid_y - y[i]; // Mirror about X-axis
	}
    }
    else if (axis == 'y' || axis == 'Y')
    {
	for ( i = 0; i < n; i++)
        {
            x[i] = 2 * mid_x - x[i]; // Mirror about Y-axis
        }
    }
}

// Function to shear points
void shear(int x[], int y[], int n, float shx, float shy)
{
int i;
    for ( i = 0; i < n; i++)
    {
        x[i] += shx * y[i];
        y[i] += shy * x[i];
    }
}

int main()
{
    int gd = DETECT, gm;
	// Draw the dividing lines
    int mid_x = getmaxx() / 2;
    int mid_y = getmaxy() / 2;


	int poly_x[] = {100,260,260,100,100};
    int poly_y[] = {50 ,50 ,150,150,50};
    int i;
	int choice;
	//Calculate the center of the hexagon
    int hexagon_center_x = 230; // Center of the hexagon
    int hexagon_center_y = 100; // Center of the hexagon

    // Draw circle inside the hexagon
    int circle_radius = 30; // Original radius
//	int LIGHTGREEN = 3;

//int mouth_y = hexagon_center_y + 20; // Adjusted the mouth position
	    // Draw eyes as lines
    int eye_width = 10; // Adjust the width of the eyes
    int eye_height = 4; // Adjust the height of the eyes
    initgraph(&gd, &gm, (char *)"C:\\TURBOC3\\BGI");


    line(mid_x, 0, mid_x, getmaxy()); // Vertical line
    line(0, mid_y, getmaxx(), mid_y); // Horizontal line

    dda(319,2,319,477, WHITE);
    dda(2,239,637,239, WHITE);

    scanline_fill(poly_x, poly_y, 5, 3);

    for ( i = 0; i < 4; i++) {
	dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1],WHITE);
    }
    dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0],WHITE);


    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(BLACK);
    circle(hexagon_center_x, hexagon_center_y, circle_radius);
    floodfill(hexagon_center_x, hexagon_center_y, BLACK); // Fill circle with yellow color


    line(hexagon_center_x - 10, hexagon_center_y + 20, hexagon_center_x + 10, hexagon_center_y + 20); // Draw mouth line

    line(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height); // Left eye
    line(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height); // Right eye



    do
    {
        // Menu for transformation options
        printf("Transformation Options:\n");
        printf("1. Translate\n");
        printf("2. Rotate\n");
        printf("3. Scale\n");
        printf("4. Reflect\n");
        printf("5. Shear\n");
        printf("6. Exit Program\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
	case 1:
	{
	    int tx, ty, i;
	    printf("Enter translation values (tx ty): ");
	    scanf("%d %d", &tx, &ty);
	    translate(poly_x, poly_y, 5, tx, ty);
	    translate(&hexagon_center_x, &hexagon_center_y, 1, tx, ty);
	    scanline_fill(poly_x, poly_y, 5, 3);

	    // Draw the hexagon boundary
    for ( i = 0; i < 4; i++) {
	dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1],WHITE);
    }
    dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0],WHITE);

            // Draw circle inside the hexagon
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius);
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);

            dda(hexagon_center_x - 10, hexagon_center_y + 20, hexagon_center_x + 10, hexagon_center_y + 20, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height, RED); // Right eye

            break;
	}
	case 2:
	{
	    float angle;
	    int pivot_x, pivot_y;
	    int i;
	    printf("Enter rotation angle: ");
	    scanf("%f", &angle);
	    printf("Enter pivot point (x y): ");
	    scanf("%d %d", &pivot_x, &pivot_y);
	    rotate(poly_x, poly_y, 5, angle, pivot_x, pivot_y);
	    rotate(&hexagon_center_x, &hexagon_center_y, 1, angle, pivot_x, pivot_y);
	    scanline_fill(poly_x, poly_y, 5, 5);

    for ( i = 0; i < 4; i++) {
	dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1],WHITE);
    }
    dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0],WHITE);

            // Draw circle inside the hexagon
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius);
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);

            dda(hexagon_center_x - 10, hexagon_center_y + 20, hexagon_center_x + 10, hexagon_center_y + 20, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height, RED); // Right eye

	    break;
	}
	case 3:
	{
	    float sx, sy;
	    int pivot_x, pivot_y, i;
	    printf("Enter scaling factors (sx sy): ");
	    scanf("%f %f", &sx, &sy);
	    printf("Enter pivot point (x y): ");
	    scanf("%d %d", &pivot_x, &pivot_y);

	    // Scale the octagon
	    scale(poly_x, poly_y, 5, sx, sy, pivot_x, pivot_y);

	    // Scale the circle center
	    hexagon_center_x = pivot_x + (hexagon_center_x - pivot_x) * sx;
	    hexagon_center_y = pivot_y + (hexagon_center_y - pivot_y) * sy;

	    // Scale the circle radius
	    circle_radius *= (sx + sy) / 2;

	    // Redraw the octagon with the transformed coordinates
	    scanline_fill(poly_x, poly_y, 5, 4);

	    // Draw the octagon boundary
	    for ( i = 0; i < 4; i++)
            {
                dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1], WHITE);
            }
            dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0], WHITE);

            // Draw circle inside the octagon again after transformation
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius); // Adjusted radius
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);
            // Draw circle inside the octagon
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius);
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);

            // Draw circle inside the octagon
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius);
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);

            dda(hexagon_center_x - 10 * sx, hexagon_center_y + 20 * sy, hexagon_center_x + 10 * sx, hexagon_center_y + 20 * sy, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height, RED); // Right eye

			break;
    }

	case 4:
	{
	    char axis;
	    int i;
	    printf("Enter axis to reflect (X or Y): ");
	    scanf(" %c", &axis);
	    reflect(poly_x, poly_y, 5, axis);
	    reflect(&hexagon_center_x, &hexagon_center_y, 1, axis);
	    if (axis == 'X' || axis == 'x')
	    {
		scanline_fill(poly_x, poly_y, 5, 3);

		// Draw the hexagon boundary
		for ( i = 0; i < 4; i++)
		{
		    dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1], WHITE);
		}
		dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0], WHITE);

		// Draw circle inside the hexagon
		setfillstyle(SOLID_FILL, YELLOW);
		setcolor(YELLOW);
		circle(hexagon_center_x, hexagon_center_y, circle_radius);
		floodfill(hexagon_center_x, hexagon_center_y, YELLOW);

            dda(hexagon_center_x + 10, hexagon_center_y - 20, hexagon_center_x - 10, hexagon_center_y - 20, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y + 10 + eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y + 10 + eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y + 10 + eye_height, hexagon_center_x + 15, hexagon_center_y + 10 + eye_height, RED); // Right eye

	    }
	    else if (axis == 'Y' || axis == 'y')
	    {
		scanline_fill(poly_x, poly_y, 5, 4);

		// Draw the hexagon boundary
		for ( i = 0; i < 4; i++)
		{
		    dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1], WHITE);
		}
		dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0], WHITE);

		// Draw circle inside the hexagon
		setfillstyle(SOLID_FILL, YELLOW);
		setcolor(YELLOW);
		circle(hexagon_center_x, hexagon_center_y, circle_radius);
		floodfill(hexagon_center_x, hexagon_center_y, YELLOW);


            dda(hexagon_center_x - 10, hexagon_center_y + 20, hexagon_center_x + 10, hexagon_center_y + 20, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height, RED); // Right eye

	    }
	    else
	    {
		printf("Invalid Axis");
	    } // Reflect the circle center
	    break;
	}
	case 5:
	{
	    float shx, shy;
	    printf("Enter shear factors (shx shy): ");
	    scanf("%f %f", &shx, &shy);
	    shear(poly_x, poly_y, 5, shx, shy);
	    shear(&hexagon_center_x, &hexagon_center_y, 1, shx, shy);
	    scanline_fill(poly_x, poly_y, 5, 3);

	    // Draw the hexagon boundary
	    for ( i = 0; i < 4; i++)
            {
                dda(poly_x[i], poly_y[i], poly_x[i + 1], poly_y[i + 1], WHITE);
            }
            dda(poly_x[4], poly_y[4], poly_x[0], poly_y[0], WHITE);

            // Draw circle inside the hexagon
            setfillstyle(SOLID_FILL, YELLOW);
            setcolor(YELLOW);
            circle(hexagon_center_x, hexagon_center_y, circle_radius);
            floodfill(hexagon_center_x, hexagon_center_y, YELLOW);


            dda(hexagon_center_x - 10, hexagon_center_y + 20, hexagon_center_x + 10, hexagon_center_y + 20, RED); // Draw mouth line

            dda(hexagon_center_x - 15, hexagon_center_y - 10 - eye_height, hexagon_center_x - 15 + eye_width, hexagon_center_y - 10 - eye_height, RED); // Left eye
            dda(hexagon_center_x + 15 - eye_width, hexagon_center_y - 10 - eye_height, hexagon_center_x + 15, hexagon_center_y - 10 - eye_height, RED); // Right eye


            // Shear the circle center

            break;
        }
        case 6:
            printf("Exiting program.\n");
            break;

    default:
        printf("Invalid choice\n");
    }
} while (choice != 0);


    // Draw the dividing lines
    line(mid_x, 0, mid_x, getmaxy()); // Vertical line
    line(0, mid_y, getmaxx(), mid_y); // Horizontal line

getch();
closegraph();
return 0;
}