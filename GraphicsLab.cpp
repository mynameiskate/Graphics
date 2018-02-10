#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#include <glut.h>


int r, n = 5;
const int m = 16385; double ang = 0.0, knx[m], kny[m];
void Traf(double xA, double yA,
	double xB, double yB, int r)
{
	knx[r] = xA; kny[r] = yA;
	knx[r + 1] = (2 * xA + xB) / 3; kny[r + 1] = (2 * yA + yB) / 3;
	knx[r + 2] = (xB + xA) / 2 + (yA - yB) / (2 * sqrt(3.0));
	kny[r + 2] = (yB + yA) / 2 + (xB - xA) / (2 * sqrt(3.0));
	knx[r + 3] = (xA + 2 * xB) / 3; kny[r + 3] = (yA + 2 * yB) / 3;
	knx[r + 4] = xB; kny[r + 4] = yB;
}

void Fract()
{
	double Ax = -0.7, Ay = -0.4, Bx = 0.7, By = -0.4, Cx, Cy;
	Cx = (Bx + Ax) / 2 + (Ay - By)*sqrt(3.0) / 2;
	Cy = (By + Ay) / 2 + (Bx - Ax)*sqrt(3.0) / 2;
	Traf(Bx, By, Ax, Ay, 0); Traf(Ax, Ay, Cx, Cy, 4);
	Traf(Cx, Cy, Bx, By, 8);
	for (int j = 0; j<n - 1; j++)
	{
		double kn1x[m], kn1y[m]; r = 3 * pow(4.0, j + 1);
		for (int i = 0; i <= r; i++)
		{
			kn1x[i] = knx[i]; kn1y[i] = kny[i];
		}
		for (int i = 0; i<r; i++)
		{
			Traf(kn1x[i], kn1y[i], kn1x[i + 1], kn1y[i + 1], 4 * i);
		}
	}


	Ax = -0.3;  Ay = -0.1; Bx = 0.5; By = 0.4; 
	Cx = (Bx + Ax) / 2 + (Ay - By)*sqrt(3.0) / 2;
	Cy = (By + Ay) / 2 + (Bx - Ax)*sqrt(3.0) / 2;
	Traf(Bx, By, Ax, Ay, 0); Traf(Ax, Ay, Cx, Cy, 4);
	Traf(Cx, Cy, Bx, By, 8);
	for (int j = 0; j<n - 1; j++)
	{
		double kn1x[m], kn1y[m]; r = 3 * pow(4.0, j + 1);
		for (int i = 0; i <= r; i++)
		{
			kn1x[i] = knx[i]; kn1y[i] = kny[i];
		}
		for (int i = 0; i<r; i++)
		{
			Traf(kn1x[i], kn1y[i], kn1x[i + 1], kn1y[i + 1], 4 * i);
		}
	}
}

void Draw()
{
	Sleep(1000 / 100);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotated(ang, 0.0, 1.0, 1.0);
	glColor3d(1.0, 1.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	for (int i = 0; i<4 * r; i++)
	{
		glVertex2d(knx[i], kny[i]);
		glVertex2d(knx[i + 1], kny[i + 1]);
	}
	glEnd();
	ang += 0.5;
	glPopMatrix();
	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("SnowFlake");
	glClearColor(0.498039, 0, 1, 1);
	//glClearColor(0.35, 0.35, 0.67, 1);
	Fract();
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
}