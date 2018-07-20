#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 400;

struct Point{
	int x;
	int y;
};

Point str,end;

void drawLine(Point str,Point end){
	glPointSize(3.0);
	glBegin(GL_POINTS);	

		double m=(end.y-str.y)/(double)(end.x-str.x);
		int c=round(str.y-(str.x*m));
		if(m<1){
			if(str.x>end.x){
				Point tmp=str;
				str=end;
				end=tmp;
			}
			for(int i=str.x;i<=end.x;i++){
				double j=m*i+c;
				j=round(j);
				glVertex2i(i,j);
			}
		}else{
			if(str.y>end.y){
				Point tmp=str;
				str=end;
				end=tmp;
			}
			for(int j=str.y;j<=end.y;j++){
				double i=(j-c)/m;
				i=round(i);
				glVertex2i(i,j);
			}
		}

	glEnd();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON )
		if (state == GLUT_DOWN) 
		{
			str.x = x;
			str.y = (wh-y);
		}
		else if (state == GLUT_UP) {
			end.x = x;
			end.y = (wh-y);
			drawLine(str,end);
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

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
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
	glutCreateWindow("Lines");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
     
	return 0;
}