#include <GL/glut.h>
#include <iostream>
using namespace std;

int ww = 400, wh = 400;

struct Point{
    int x;
    int y;
};

Point p1,p2;
int count;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{	
	//glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);

	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

void drawOutline(int t){
    drawLine(p1.x,p1.y,p1.x,p2.y);
    drawLine(p1.x,p2.y,p2.x,p2.y);
    drawLine(p2.x,p2.y,p2.x,p1.y);
    drawLine(p2.x,p1.y,p1.x,p1.y);
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
	if(btn==GLUT_LEFT_BUTTON )
		if (state == GLUT_DOWN) 
		{
            if(count==0){
                p1.x=x;
                p1.y=wh-y;
                count++;
            }else if(count==1){
                p2.x=x;
                p2.y=wh-y;
                count++;
            }
            if(p1.y>p2.y){
                Point tmp=p1;
                p1=p2;
                p2=tmp;
            }
			
            for(int i=p1.y;i<=p2.y && count==3;i++){
                drawLine(p1.x,i,p2.x,i);
            }
            
            if(count==2){
                drawOutline(1);
                count++;
            }      
		}
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
        count=0;
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
    cout << "Enter bottom left point: ";
    cin >> p1.x;
    cin >> p1.y;
    cout << "Enter top right point: ";
    cin >> p2.x;
    cin >> p2.y;
    count=3;


    cout << "\nClick for fill rectangle"<< endl;
    cout << "Press e for clear"<< endl;
    cout << "Click two points to make rectangle"<< endl;

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("Fill Rectange");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
    glutTimerFunc(1,drawOutline,1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
     
	return 0;
}