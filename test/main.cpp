#include <iostream>
#include <unistd.h>
#include "canvas.hpp"

int main()
{
    initCanvas();
    //drawChar(0,1,0);
    //drawChar(4,2,0);
    //drawChar(8,3,1);
    drawText();
    printCanvas();
    getchar();
    while(!animate()) {
        printCanvas();
        //getchar();
        usleep(100000);
    }
    printCanvas();
    getchar();
    return 0;
}