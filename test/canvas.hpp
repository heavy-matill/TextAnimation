#include <iostream>
#include <unistd.h>
#include "../font_TomThumb.h"
char canvas[5][15]; 
uint8_t xWidth = 4;
std::string text = "Fertig! Klappt jetzt zumindest in der Simulation :) Wie ist die Bahnfahrt so? ;)";
int8_t xStart = 0;
uint16_t iStart = 0;
uint16_t iColor = 1;
uint16_t iColorTemp = 1;
uint16_t iColorBg = 0;
uint16_t stColorScheme = 2; 
bool bBgInv = true;
bool bSpacesBg = false;

void fillCanvas(char c) {
    for(uint8_t i = 0; i<15; i++) {
        for(uint8_t j = 0; j<5; j++) {
            canvas[j][i] = c;
        }
    }
}


void printCanvas() {
    std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    for(uint8_t j = 0; j<5; j++) {
        std::cout<<"|";
        for(uint8_t i = 0; i<15; i++) {
            std::cout<<canvas[j][i];
        }
        std::cout<<"|\n";
    } 
    for(uint8_t i = 0; i<=xStart; i++) 
        std::cout<<" ";
    std::cout<<"i xStart = -";
    std::cout<<-xStart;
    std::cout<<"\n";
    std::cout<<text+"\n";
    for(uint8_t i = 0; i<iStart; i++) 
        std::cout<<" ";
    std::cout<<"i iStart = ";
    std::cout<<iStart;
    std::cout<<"\n iColorTemp = ";
    std::cout<<iColorTemp;
}   

char colorASCII(uint8_t i) {
    switch(i) {
        case 1:
            return (char) 219;
        case 2:
            return (char) 178;
        case 3:
            return (char) 177;
        case 4:
            return (char) 176;
        default:
            return (char) 255;
    }
}

void initCanvas() {
    fillCanvas(colorASCII(0));
}
uint16_t fontChar(char c) {
    c = c<0x20?0x20:c;
    c = c>0x7E?0:c-0x20;
    return font[c];
}
void drawChar(int8_t x, char c, int8_t color, uint8_t bg) {//, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size) {
    for(int8_t i = 0; i<4 && i+x<15; i++) {
        if(i+x>=0) {
            for(uint8_t j = 0; j<5; j++) {
                if (fontChar(c) & 1<<(i*5+j)) {
                    canvas[j][i+x] = colorASCII(color);
                } else {
                    canvas[j][i+x] = colorASCII(bg);
                }
            }
        }
    }
    /*for(int8_t i = x; i<x+3 && i<15; i++) {
        if(i>=0) {
            canvas[0][i] = colorASCII(color);
            canvas[4][i] = colorASCII(color);
            if(i == x+1) {            
                canvas[1][i] = colorASCII(color);
                canvas[2][i] = colorASCII(color);
                canvas[3][i] = colorASCII(color);
            } else {
                canvas[1][i] = colorASCII
                (bg);
                canvas[2][i] = colorASCII(bg);
                canvas[3][i] = colorASCII(bg);
            }
        }
    }*/
}

void drawText() {
    fillCanvas(colorASCII(0));
    iColorTemp = iColor;
    for (uint8_t i = iStart; i<text.length() && (i-iStart)*xWidth+xStart<15; i++) {
        switch (stColorScheme) {
            case 1: 
                // Color each character
                // get Color from list or shift hue
                iColor = i%4+1;
                break;
            case 2:
                // Color each word
                if (text[i] == ' ') { 
                    if ((i-iStart)*xWidth+xStart >= 0) {                                             
                        iColor = iColor%4+1;
                    }
                    if ((i-iStart)*xWidth+xStart == 0) {
                        iColorTemp = iColor;
                    }
                }
                break;
            case 3:
                // Color from RBG Animator
                // TBD
                break;
            default:
                // Color warmwhite
                iColor = 1;
        }
        // select background color
        if (bBgInv && bSpacesBg || text[i] != ' ') {
            iColorBg = (iColor-1+2)%4+2;
        } else {
            iColorBg = 0;
        } 
        drawChar((i-iStart)*xWidth+xStart,text[i],iColor,iColorBg);
    }
    iColor = iColorTemp;
}

void shiftText() {
    xStart--;
    if(xStart<=-4) {
        xStart=0;
        iStart++;
    }
}

void shift() {
    for(uint8_t i = 0; i<14; i++) {
        for(uint8_t j = 0; j<5; j++) {
            canvas[j][i] = canvas[j][i+1];
        }
    }
    for(uint8_t j = 0; j<5; j++) {
        canvas[j][14] = ' ';
    }
}

void shiftBy(uint8_t x) {
    for(uint8_t i = 0; i<15; i++) {
        if(i<15-x) { 
            for(uint8_t j = 0; j<5; j++) {
                canvas[j][i] = canvas[j][i+x];
            }   
        } else { 
            for(uint8_t j = 0; j<5; j++) {
                canvas[j][i] = ' ';
            }   
        }
    }
}

void animate() {
    shiftText();
    drawText();
    /*shift();
    if(iStart<text.length()) {
        xStart--;
        drawText();
    }*/
}