#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "math/vec4.h"

char* canvas; 

void initCanvas(int width, int height)
{
    int size = width*height;
    canvas = malloc(size);
    if (!canvas) exit(1);
    memset(canvas, ' ', size);
}

void editCanvas(int width, int height)
{
    int size = width * height;
    canvas = realloc(canvas, size);
    if (!canvas) exit(1);
}

static char drawPixel(float zBuffer)
{
    if (zBuffer < 0.25f) return '.';
    else if (zBuffer < 0.5f) return '*';
    else if (zBuffer < 0.75f) return 'o';
    else return '#';
}

void drawCanvas(Vec4f_t p, int width, int height)
{
    int x = (int)p.x;
    int y = (int)p.y;
    if(x >= 0 && x < width && y >= 0 && y < height)
        canvas[y*width + x] = drawPixel(p.z);
}

void renderCanvas(int width, int height)
{
    for (int i = 0; i<height; i++) {
        for (int j = 0; j<width; j++) {
            putchar(canvas[i*width+j]);
        }
        putchar('\n');
    }
}

void freeCanvas(void)
{
    free(canvas);
}

