

#include <GL/glut.h>

int ww = 600, wh = 400;
struct Point{
    int x;
    int y;
};

Point list[20];
int pointCounter=0;

void drawLine(Point start, Point end)
{	
	//glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);

	glBegin(GL_LINES);
		glVertex2i(start.x, start.y);
		glVertex2i(end.x, end.y);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
    Point temp;
    temp.x=x;
    temp.y=wh-y;
	if(btn==GLUT_LEFT_BUTTON ){
		if (state == GLUT_DOWN) 
		{
			list[pointCounter++]=temp;
		}
    }
	if(btn==GLUT_RIGHT_BUTTON ){
		if (state == GLUT_DOWN) 
		{
			list[pointCounter++]=temp;
            drawLine(list[0],list[pointCounter-1]);
		}
    }
    if(pointCounter>1){
        drawLine(list[pointCounter-2],list[pointCounter-1]);
    }
    if(btn==GLUT_RIGHT_BUTTON){
        pointCounter=0;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
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
	glutCreateWindow("Draw Polygon");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
     
	return 0;
}