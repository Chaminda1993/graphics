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

        if(str.x>end.x){
            Point tmp=str;
            str=end;
            end=tmp;
        }

		int dx = end.x-str.x, dy = end.y-str.y;
        double m=dy/(double)dx;
        if(m>=0 && m<1){
            int dT=2*(dy-dx),dS=2*dy,d=(2*dy)-dx;
            int x = str.x, y = str.y;
            glVertex2i(x,y);

            while(x<end.x){
                x++;
                if(d<0){
                    d+=dS;
                }else{
                    y++;
                    d+=dT;
                }
                glVertex2i(x,y);
            }
        }else if(m>1){
            int tmp=str.x;
            str.x=str.y;
            str.y=tmp;
            tmp=end.x;
            end.x=end.y;
            end.y=tmp;
            tmp=dx;
            dx=dy;
            dy=tmp;

            int dT=2*(dy-dx),dS=2*dy,d=(2*dy)-dx;
            int x = str.x, y = str.y;
            glVertex2i(y,x);

            while(x<end.x){
                x++;
                if(d<0){
                    d+=dS;
                }else{
                    y++;
                    d+=dT;
                }
                glVertex2i(y,x);
            }
        }else if(m<0 && m>-1){
            dy*=-1;
            int dT=2*(dy-dx),dS=2*dy,d=(2*dy)-dx;
            int x = str.x, y = str.y;
            glVertex2i(x,y);

            while(x<end.x){
                x++;
                if(d>0){
                    d-=dS;
                }else{
                    y--;
                    d-=dT;
                }
                glVertex2i(x,y);
            }
        }else{  //m<-1
			int tmp=str.x;
            str.x=str.y;
            str.y=tmp;
            tmp=end.x;
            end.x=end.y;
            end.y=tmp;
            tmp=dx;
            dx=dy;
            dy=tmp;
			
			dx *= -1;
            int dT=2*(dy-dx),dS=2*dy,d=(2*dy)-dx;
            int x = str.x, y = str.y;
            glVertex2i(y,x);
			
            while(x>end.x){
                x--;
                if(d<0){
                    d+=dS;
                }else{
                    y++;
                    d+=dT;
                }
                glVertex2i(y,x);
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