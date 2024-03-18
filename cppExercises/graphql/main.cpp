#include <iostream>
#include "graphics2.h"
#define WIDTH 640
#define HEIGHT 480

class Point
{
    int x = 0, y = 0;

public:
    void move_to_location(int const xn, int const yn) {
        x = xn;
        y = yn;
    }

    void draw() const {
        line(x, y, mousecurrentx(), mousecurrenty());
    }
};

int main() {
    int GraphDriver = 0, GraphMode = 0;
    initgraph(&GraphDriver, &GraphMode, "", WIDTH, HEIGHT);
    setcolor(CYAN);
    bar(0, 0, WIDTH, HEIGHT);

    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    setcolor(GREEN);
    outtextxy(5, 5, "Mouse Left Click: Starts Drawing");
    outtextxy(5, 20, "Mouse Right Click: Ends Drawing");

    setcolor(RED);
    Point P;
    bool STATUS = false;

    while(true) {
        if (mousedown() == true) {
            if (whichmousebutton() == LEFT_BUTTON) {
                STATUS = true;
                P.move_to_location(mouseclickx(), mouseclicky());
            }
            else if(whichmousebutton() == RIGHT_BUTTON) {
                STATUS = false;
            }
        }
        if (STATUS == true) {
            P.draw();
            P.move_to_location(mousecurrentx(), mousecurrenty());
        }
    }
}
