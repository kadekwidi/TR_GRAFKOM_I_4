#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

enum gCameraMode
{
    NORMAL_MODE,
    BIRD_MODE
};

// convert hex to rgb
float *hextoRGB(std::string);
void glColorHex(std::string);

// resizing the window
void resizeWindow(int, int);

// computing camera position
void computeCameraPos(float, float);

void init(void);
void renderObjects(void);
void pressKey(unsigned char, int, int);
void releaseKey(unsigned char, int, int);
void mouseMove(int, int);
void mouseButton(int, int, int, int);

void dasar();
void awan(void);
void rumah();

#endif