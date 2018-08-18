#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 400;
struct point{
	int x;
	int y;
	int r;
};

point end,circle;

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.746, 0.934, 0.542);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void drawCircle(point c)
{	
	//glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);

	glBegin(GL_POINTS);
		
    glVertex2i(c.x,c.y);
	//midpoint
    int x=0,y=c.r,p=1-c.r;
    while(y > 0){
		if(x <= y){
			glVertex2i(c.x+x,c.y+y);
		}else{
			glVertex2i(c.x+x,c.y+y);
		}
        if(p<0){
            p=p+2*x+113;
        }else{
            p=p+2*(x-y)+5;
            y--;
        }
        x++;
    }


	glEnd();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON )
		if (state == GLUT_DOWN) 
		{
			circle.x = x;
			circle.y = (wh-y);
		}
		else if (state == GLUT_UP) {
			end.x = x;
			end.y = (wh-y);
			int dx=end.x-circle.x;
			int dy=end.y-circle.y;
			float val=(dx*dx)+(dy*dy);
			circle.r=sqrt(val);
			drawCircle(circle);
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
	glutCreateWindow("Midpoint circle");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
     
	return 0;
}