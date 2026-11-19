#include <graphics.h>
#include <conio.h>
#include <math.h>

// Transformation variables
float angle = 0.0;
float scaleX = 1.0, scaleY = 1.0;
int transX = 0, transY = 0;
int reflectX = 1, reflectY = 1;
float shearX = 0.0, shearY = 0.0;

const float PI = 3.14159265;

// Apply transformations and draw a line
void drawLine(float x1, float y1,
              float x2, float y2, int color)
{
    // Scaling
    x1 *= scaleX;
    x2 *= scaleX;
    y1 *= scaleY;
    y2 *= scaleY;

    // Shearing
    float a1 = x1 + shearX * y1;
    float b1 = y1 + shearY * x1;

    float a2 = x2 + shearX * y2;
    float b2 = y2 + shearY * x2;

    // Reflection
    a1 *= reflectX;
    a2 *= reflectX;
    b1 *= reflectY;
    b2 *= reflectY;

    // Rotation
    float r1 = angle * PI / 180.0;

    float rx1 = a1 * cos(r1) - b1 * sin(r1);
    float ry1 = a1 * sin(r1) + b1 * cos(r1);

    float rx2 = a2 * cos(r1) - b2 * sin(r1);
    float ry2 = a2 * sin(r1) + b2 * cos(r1);

    // Translation and screen coordinates
    int sx1 = 320 + (int)rx1 + transX;
    int sy1 = 280 - (int)ry1 + transY;

    int sx2 = 320 + (int)rx2 + transX;
    int sy2 = 280 - (int)ry2 + transY;

    setcolor(color);
    line(sx1, sy1, sx2, sy2);
}

// Draw house
void drawHouse()
{
    // House body
    drawLine(-80,-70, 80,-70, WHITE);
    drawLine(80,-70, 80,40, WHITE);
    drawLine(80,40, -80,40, WHITE);
    drawLine(-80,40, -80,-70, WHITE);

    // Roof
    drawLine(-100,40, 0,120, RED);
    drawLine(0,120, 100,40, RED);
    drawLine(-100,40, 100,40, RED);

    // Door
    drawLine(-20,-70, -20,0, YELLOW);
    drawLine(-20,0, 20,0, YELLOW);
    drawLine(20,0, 20,-70, YELLOW);

    // Door handle
    drawLine(12,-35, 15,-35, YELLOW);

    // Left window
    drawLine(-65,0, -40,0, CYAN);
    drawLine(-40,0, -40,25, CYAN);
    drawLine(-40,25, -65,25, CYAN);
    drawLine(-65,25, -65,0, CYAN);

    // Window cross
    drawLine(-52,0, -52,25, CYAN);
    drawLine(-65,12, -40,12, CYAN);

    // Right window
    drawLine(40,0, 65,0, CYAN);
    drawLine(65,0, 65,25, CYAN);
    drawLine(65,25, 40,25, CYAN);
    drawLine(40,25, 40,0, CYAN);

    drawLine(52,0, 52,25, CYAN);
    drawLine(40,12, 65,12, CYAN);

    // Ground
    setcolor(GREEN);
    line(50,380,590,380);
}

// Display instructions
void instructions()
{
    setcolor(WHITE);
    outtextxy(10,10,"3D STYLE HOUSE - CG PROJECT");

    outtextxy(10,410,"A/D : Rotate");
    outtextxy(10,430,"+/- : Scale");
    outtextxy(10,450,"Arrow keys : Translation");
    outtextxy(10,470,"F : Reflection X");
    outtextxy(10,490,"G : Reflection Y");
    outtextxy(10,510,"H : Shearing");
    outtextxy(10,530,"R : Reset");
    outtextxy(10,550,"ESC : Exit");
}

int main()
{
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "");

    char ch;

    do
    {
        cleardevice();

        drawHouse();
        instructions();

        ch = getch();

        // Arrow keys
        if(ch == 0 || ch == 224)
        {
            ch = getch();

            if(ch == 75) transX -= 10;  // Left
            if(ch == 77) transX += 10;  // Right
            if(ch == 72) transY -= 10;  // Up
            if(ch == 80) transY += 10;  // Down
        }
        else
        {
            // Rotation
            if(ch == 'a' || ch == 'A')
                angle -= 5;

            if(ch == 'd' || ch == 'D')
                angle += 5;

            // Scaling
            if(ch == '+' || ch == '=')
            {
                scaleX += 0.1;
                scaleY += 0.1;
            }

            if(ch == '-' && scaleX > 0.3)
            {
                scaleX -= 0.1;
                scaleY -= 0.1;
            }

            // Reflection about X direction
            if(ch == 'f' || ch == 'F')
                reflectX *= -1;

            // Reflection about Y direction
            if(ch == 'g' || ch == 'G')
                reflectY *= -1;

            // Shearing
            if(ch == 'h' || ch == 'H')
            {
                shearX += 0.1;

                if(shearX > 0.5)
                    shearX = 0;
            }

            // Reset
            if(ch == 'r' || ch == 'R')
            {
                angle = 0;
                scaleX = scaleY = 1.0;

                transX = transY = 0;

                reflectX = reflectY = 1;

                shearX = shearY = 0;
            }
        }

    } while(ch != 27);

    closegraph();
    return 0;
}