#ifndef DRAW_H
#define DRAW_H

#include "math/vec4.h"

void initCanvas(int width, int height);
void editCanvas(int width, int height);
void drawCanvas(Vec4f_t p, int width, int height);
void drawLine(Vec4f_t p0, Vec4f_t p1, int width, int height);
void renderCanvas(int width, int height);
void freeCanvas(void);

#endif // DRAW_H