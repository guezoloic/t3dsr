#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "math/vec4.h"
#include "math.h"

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
    float zb = (zBuffer + 1.f) * 0.5f;
    
    if (zb > 1.f) zb = 1.f;
    if (zb < 0.f) zb = 0.f;


    if (zb < 0.25f) return '.';
    else if (zb < 0.5f) return '*';
    else if (zb < 0.75f) return 'o';
    else return '#';
}

void drawLine(Vec4f_t p0, Vec4f_t p1, int width, int height)
{
    int x0 = (int)roundf(p0.x);
    int y0 = (int)roundf(p0.y);
    int x1 = (int)roundf(p1.x);
    int y1 = (int)roundf(p1.y);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx - dy;

    int len = (int)sqrtf((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
    int step = 0;

    while (1) {
        float t = len == 0 ? 0.f : (float)step / (float)len;
        Vec4f_t p = vec4f_lerp(p0, p1, t);
        drawCanvas(p, width, height);

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2*err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }

        step++;
    }
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

void clearCanvas(int width, int height)
{
    printf("\033[2J\033[H");
    for (int i = 0; i<height; i++) {
        for (int j = 0; j<width; j++) {
            canvas[i*width + j] = ' ';
        }
    }
}

void freeCanvas(void)
{
    free(canvas);
}

