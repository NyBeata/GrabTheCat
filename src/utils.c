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

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, 1280, 720, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, float z, void *font, char *string)
{

	char *c;
	glRasterPos3f(x, y, z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void drawText(float x, float y, float size, float width, void *font, char *string, float r, float g, float b)
{
    // Projekciós mód átállítása
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
    renderStrokeFontString(x, y, size, width, font, string, r, g, b);
	glPopMatrix();

	// Proejkciós mód visszaállítása
	restorePerspectiveProjection();
}

void renderStrokeFontString(float x, float y, float size, float width, void *font, char *string, float r, float g, float b)
{  

	char *c;
	glPushMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
	glTranslatef(x, y, 0.1);
	glScalef(size, -(size), size);
    glLineWidth(width);
    glColor3f(r, g, b);
	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawMenu(GLuint texture)
{
	setOrthographicProjection();
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
        glVertex3d(0, 0, 0);
		glTexCoord2f(0.0, 1.0);
        glVertex3d(0, 720, 0);
		glTexCoord2f(1.0, 1.0);
        glVertex3d(1280, 720, 0);
		glTexCoord2f(1.0, 0.0);
        glVertex3d(1280, 0, 0);
	glEnd();
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glPopMatrix();
	
	restorePerspectiveProjection();
}