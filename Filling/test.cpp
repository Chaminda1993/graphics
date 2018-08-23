#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 500;
float bgCol[3] = {1.0,1.0,0.0};
float intCol[3] = {1.0,0.0,0.0};

void setPixel(int pointx, int pointy, float f[3])
{
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glColor3fv(f);
		glVertex2i(pointx,pointy);
	glEnd();
	glFlush();
}

void getPixel(int x, int y, float pixels[3])
{
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}

void changePixCol (int x, int y, float backgroundColor[3], float interiorColor[3])
{
	float pixels[3];
	getPixel(x,y,pixels);
	if(pixels[0]==interiorColor[0] && (pixels[1])==interiorColor[1] && (pixels[2])==interiorColor[2])
		setPixel (x, y, backgroundColor);
	else setPixel (x, y, interiorColor);
}

void drawPolygon(int x1, int y1, int x2, int y2)
{	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
		glVertex2i(x2, y1);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawPolygon(150,250,200,300);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		int xi = x;
		int yi = (wh-y);
		changePixCol(xi,yi,intCol,bgCol);
	}
}

void myinit()
{            
	glViewport(0,0,ww,wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("ChangePixelColour");
	glutDisplayFunc(display);
	myinit();
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
