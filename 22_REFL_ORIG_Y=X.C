#include <graphics.h>
#include <stdio.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to reflect a point about the origin
void reflectAboutOrigin(int *x, int *y) {
    *x = -*x;
    *y = -*y;
}

// Function to reflect a point about the line y = x
void reflectAboutLineYX(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to reflect a point about the x-axis
void reflectAboutXAxis(int *x, int *y) {
    *y = -*y;
}

// Function to reflect a point about the y-axis
void reflectAboutYAxis(int *x, int *y) {
    *x = -*x;
}

int main() {
    int gd = DETECT, gm;
        // Original triangle vertices
    int x1 = 100, y1 = 100;
    int x2 = 200, y2 = 100;
    int x3 = 150, y3 = 200;
        
        // Prompt user for reflection type
    int choice;
    
    // Variables to store reflected coordinates
    int x1_reflect, y1_reflect;
    int x2_reflect, y2_reflect;
    int x3_reflect, y3_reflect;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    delay(1000); // Delay to show the original triangle


    printf("Select the type of reflection:\n");
    printf("1. Reflection about the origin\n");
    printf("2. Reflection about the line y = x\n");
    printf("3. Reflection about the x-axis\n");
    printf("4. Reflection about the y-axis\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    // Perform reflection based on user's choice
    switch(choice) {
        case 1:
            x1_reflect = x1;
            y1_reflect = y1;
            x2_reflect = x2;
            y2_reflect = y2;
            x3_reflect = x3;
            y3_reflect = y3;

            reflectAboutOrigin(&x1_reflect, &y1_reflect);
            reflectAboutOrigin(&x2_reflect, &y2_reflect);
            reflectAboutOrigin(&x3_reflect, &y3_reflect);

            // Draw triangle after reflection about the origin (RED)
            drawTriangle(x1_reflect + getmaxx()/2, y1_reflect + getmaxy()/2,
                         x2_reflect + getmaxx()/2, y2_reflect + getmaxy()/2,
                         x3_reflect + getmaxx()/2, y3_reflect + getmaxy()/2, RED);
            break;

        case 2:
            x1_reflect = x1;
            y1_reflect = y1;
            x2_reflect = x2;
            y2_reflect = y2;
            x3_reflect = x3;
            y3_reflect = y3;

            reflectAboutLineYX(&x1_reflect, &y1_reflect);
            reflectAboutLineYX(&x2_reflect, &y2_reflect);
            reflectAboutLineYX(&x3_reflect, &y3_reflect);

            // Draw triangle after reflection about the line y = x (GREEN)
            drawTriangle(x1_reflect + getmaxx()/2, y1_reflect + getmaxy()/2,
                         x2_reflect + getmaxx()/2, y2_reflect + getmaxy()/2,
                         x3_reflect + getmaxx()/2, y3_reflect + getmaxy()/2, GREEN);
            break;

        case 3:
            x1_reflect = x1;
            y1_reflect = y1;
            x2_reflect = x2;
            y2_reflect = y2;
            x3_reflect = x3;
            y3_reflect = y3;

            reflectAboutXAxis(&x1_reflect, &y1_reflect);
            reflectAboutXAxis(&x2_reflect, &y2_reflect);
            reflectAboutXAxis(&x3_reflect, &y3_reflect);

            // Draw triangle after reflection about the x-axis (BLUE)
            drawTriangle(x1_reflect + getmaxx()/2, y1_reflect + getmaxy()/2,
                         x2_reflect + getmaxx()/2, y2_reflect + getmaxy()/2,
                         x3_reflect + getmaxx()/2, y3_reflect + getmaxy()/2, BLUE);
            break;

        case 4:
            x1_reflect = x1;
            y1_reflect = y1;
            x2_reflect = x2;
            y2_reflect = y2;
            x3_reflect = x3;
            y3_reflect = y3;

            reflectAboutYAxis(&x1_reflect, &y1_reflect);
            reflectAboutYAxis(&x2_reflect, &y2_reflect);
            reflectAboutYAxis(&x3_reflect, &y3_reflect);

            // Draw triangle after reflection about the y-axis (CYAN)
            drawTriangle(x1_reflect + getmaxx()/2, y1_reflect + getmaxy()/2,
                         x2_reflect + getmaxx()/2, y2_reflect + getmaxy()/2,
                         x3_reflect + getmaxx()/2, y3_reflect + getmaxy()/2, CYAN);
            break;

        default:
            printf("Invalid choice!\n");
            break;
    }

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
