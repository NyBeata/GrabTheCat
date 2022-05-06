#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

vec3 Calculate3DCursorLocation(int cursorX, int cursorY)
{
	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (float)cursorX;
    winY = (float)viewport[3] - (float)cursorY;
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    vec3 cursor;
	cursor.x = posX;
    cursor.y = posY;
    cursor.z = posZ;

	return cursor;
}

float get_distance(float x1, float x2, float y1, float y2)
{
    float dtn;

    float x = pow((x2- x1), 2);
    float y = pow((y2- y1), 2);
    
    dtn = sqrt(x + y);

    return dtn;
}
