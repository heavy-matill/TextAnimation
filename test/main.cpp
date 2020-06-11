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
    for(uint8_t i = 0; i<500; i++) {
        animate();
        printCanvas();
        //getchar();
        usleep(100000);
    }
    return 0;
}