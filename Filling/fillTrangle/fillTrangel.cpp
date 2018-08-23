#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 500;
float bgCol[3] = {1.0,1.0,0.0};
float intCol[3] = {1.0,0.0,0.0};
float fillCol[3] = {0.0,0.0,1.0};
float fillCol1[3] = {1.0,0.0,1.0};
float fillCol2[3] = {0.0,1.0,1.0};

void setPixel(int pointx, int pointy, float f[3])
{
	glPointSize(1.0);
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

void drawLine(int x1, int y1, int x2, int y2,float f[3])
{	
	glColor3fv(f);
	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

void boundaryFill4(int x,int y,float fillCol[3],float intCol[3]){
    float color[3];
    getPixel(x,y,color);
    
    if(!(color[0]==intCol[0] && color[1]==intCol[1] && color[2]==intCol[2]) &&     // not be outside color
    !(color[0]==fillCol[0] && color[1]==fillCol[1] && color[2]==fillCol[2])){   // not already fill pixel
        setPixel(x,y,fillCol);
        boundaryFill4(x+1,y,fillCol,intCol);
        boundaryFill4(x-1,y,fillCol,intCol);
        boundaryFill4(x,y+1,fillCol,intCol);
        boundaryFill4(x,y-1,fillCol,intCol);
    }
}

void display()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int clickCount=0;
void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		int xi = x;
		int yi = (wh-y);
        if(clickCount==0){
            drawLine(100,100,400,400,intCol);
	        drawLine(100,100,400,100,intCol);
        	drawLine(400,100,400,400,intCol);
        }else if(clickCount==1){
            boundaryFill4(102,101,fillCol,intCol);
        }else if(clickCount == 2){
            drawLine(100,100,300,400,fillCol1);
	        drawLine(100,100,450,100,fillCol1);
        	drawLine(450,100,300,400,fillCol1);
        }else if(clickCount==3){
            boundaryFill4(102,101,fillCol2,fillCol1);
        }

        clickCount++;
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
