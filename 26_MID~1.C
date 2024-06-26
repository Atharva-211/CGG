#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <graphics.h>

// 20 50 300 200
typedef struct coordinate {
    int x,y;
    char code[4];
}PT;

void drawwindow();
void drawline (PT p1, PT p2);
PT setcode(PT p);
int visibility (PT p1, PT p2);
PT resetendpt (PT p1, PT p2);

midsub(PT p1,PT p2) {
    PT mid;
    int v;
    p1 = setcode(p1);
    p2 = setcode(p2);
    v = visibility(p1, p2);
    switch(v) {
        case 0:
            /* Line completely visible */
            drawline(p1, p2);
            break;
        case 1:
            /* Line completely invisible */
            break;
        case 2:
            /* line partly visible */
            mid.x = p1.x + (p2.x - p1.x) / 2;
            mid.y = p1.y + (p2.y - p1.y) / 2;
            midsub(p1, mid);
            mid.x = mid.x + 1;
            mid.y = mid.y + 1;
            midsub(mid, p2);
            break;
    }
}


int main() {
    int gd = DETECT, gm, v;
    PT p1, p2, ptemp;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    printf("ENTER END-POINT 1 (x,y): ");
    scanf("%d%d", &p1.x, &p1.y);
    printf("\nENTER END-POINT 2 (x,y): ");
    scanf("%d%d", &p2.x, &p2.y);

    cleardevice();
    drawwindow();

    drawline(p1, p2);
    getch();
    cleardevice();
    drawwindow();
    midsub(p1, p2);
    getch();
    closegraph();
    return(0);
}


void drawwindow() {
    setcolor(RED);
    line(150, 100, 450, 100);
    line(450, 100, 450, 400);
    line(450,400,150,400);
    line(150,400,150,100);
}

void drawline (PT p1,PT p2){
    setcolor(15);
    line(p1.x,p1.y,p2.x,p2.y);
}

PT setcode(PT p) {
    PT ptemp;
    if(p.y<=100)
        ptemp.code[0]='1';
    else
        ptemp.code[0]='0';

    if(p.y>=400)
        ptemp.code[1]='1';
    else
        ptemp.code[1]='0';

    if (p.x>=450)
        ptemp.code[2]='1';
    else
        ptemp.code[2]='0';

    if (p.x<=150)
        ptemp.code[3]='1';
    else
        ptemp.code[3]='0';

    ptemp.x=p.x;
    ptemp.y=p.y;
    return(ptemp);
}

int visibility (PT p1,PT p2) {
    int i, flag = 0;
    for(i = 0; i < 4; i++) {
        if((p1.code[i] != '0') || (p2.code[i] != '0'))
            flag = 1;
    }
    
    if(flag == 0)
        return(0);
    for(i = 0; i < 4; i++) {
        if((p1.code[i] == p2.code[i]) && (p1.code[i] == '1'))
            flag=0;
    }
    if(flag == 0)
        return(1);
    return(2);
}

/*#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#define xmin 150
#define ymin 100
#define xmax 450
#define ymax 400
struct Point{
int x, y;
char region;
};
void drawborder();
void drawline(Point p1, Point p2);
Point setcode(Point p);
int visibility(Point p1, Point p2);
void midsub(Point, Point);
int main() {
int gd = DETECT, gm;
Point p1, p2;
initgraph(&gd, &gm, "c:\\turboc3\\bgi");
cleardevice();
printf("Enter coordinates of point 1(x, y): ");
scanf("%d %d", &p1.x, &p1.y);
printf("\nEnter coordinates of point 2(x, y): ");
scanf("%d %d", &p2.x, &p2.y);
cleardevice();
drawborder();
getch();
// draw before clipping
drawline(p1, p2);
getch();
cleardevice();
drawborder();
// draw after clipping
midsub(p1, p2);
getch();
closegraph();
return 0;
}
void midsub(Point p1, Point p2) {
Point mid;
p1 = setcode(p1);
p2 = setcode(p2);
switch (visibility(p1, p2)) {
case 0: // if line is wholly visible then draw the line
drawline(p1, p2);
break;
case 1: // if line is completely invisible then don't draw
break;
case 2:
// if line is partially visible then clip and draw
mid.x = p1.x + (p2.x - p1.x) / 2;
mid.y = p1.y + (p2.y - p1.y) / 2;
midsub(p1, mid);
mid.x = mid.x + 1;
mid.y = mid.y + 1;
midsub(mid, p2);
break;
}
}
void drawborder() {
setcolor(RED);
line(xmin, ymin, xmax, ymin);
line(xmax, ymin, xmax, ymax);
line(xmax, ymax, xmin, ymax);
line(xmin, ymax, xmin, ymin);
}
void drawline(Point p1, Point p2) {
setcolor(WHITE);
line(p1.x, p1.y, p2.x, p2.y);
}
Point setcode(Point p) {
Point Pointemp;
Pointemp.region = (p.y <= ymin) << 3 | // Top
(p.y >= ymax) << 2 | // Bottom
(p.x >= xmax) << 1 | // Right
(p.x <= xmin); // Left
Pointemp.x = p.x;
Pointemp.y = p.y;
return Pointemp;
}
int visibility(Point p1, Point p2) {
// if both points are NOT in centre region
if (!(p1.region > 0 || p2.region > 0))
return 0;
// if both points are either top, bottom, left or right then they are completely invisible
if (p1.region & p2.region)
return 1;
return 2;
}
*/