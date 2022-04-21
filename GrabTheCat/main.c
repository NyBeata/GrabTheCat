#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "model.h"
#include "draw.h"

Model cat;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	//set_view(&(app->camera));
	//render_scene(&(app->scene));
	gluLookAt(0, 0, 0, 10, 10, 10, 0, 0, 1);
	draw_model(&cat);
	glPopMatrix();


	glFlush();

	printf("mukodok! :D\n");
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);

	init_model(&cat);
	load_model(&cat, "models/cat.obj");
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grab The Cat");
	glutDisplayFunc(display);
	glutIdleFunc(display);

	myinit();

		
	glutMainLoop();
}