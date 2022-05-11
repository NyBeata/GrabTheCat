#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

vec3 Calculate3DCursorLocation(int cursorX, int cursorY);

float get_distance(float x1, float x2, float y1, float y2);

void setOrthographicProjection();

void restorePerspectiveProjection();

void drawText(float x, float y, float size, float width, void *font, char *string, float r, float g, float b);

void renderStrokeFontString(float x, float y, float size, float width, void *font, char *string, float r, float g, float b);

void drawMenu(GLuint texture);


#endif /* UTILS_H */
