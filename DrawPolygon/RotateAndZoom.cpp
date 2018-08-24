/*****************************************************************************************
The following program rotates a given point about the origin in 2D.

(Specify a point by the left mouse button, and click the right mouse button to rotate it).
*******************************************************************************************/

/*************************************************************************************************************
*****************		press 7 & 9 for rotate									******************************
*****************		press 4,6,2,8 for transition							******************************
*****************		press + & - for zoom									******************************
*****************		click mouse right for set origin						******************************
*****************		press q to exit											******************************
*****************		press e to clear										******************************
*****************		after clear left click four point to draw rectangle		******************************
*************************************************************************************************************/


#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
using namespace std;
 
int screenheight = 600;
int screenwidth = 800;
bool flag = true;

double angle = 30;                //The angle for the rotation (in degrees)

struct Point2D{
    float x;
    float y;
};

struct MyRect{
	Point2D A;
	Point2D B;
	Point2D C;
	Point2D D;
	Point2D Op;
};

Point2D p1,p2;
MyRect rect1;


Point2D zoomFrom(Point2D p,Point2D from,float scale){
	int dx,dy;
	dx =p.x-from.x;
	dy =p.y-from.y;
	p.x = (dx*scale)+from.x;
	p.y = (dy*scale)+from.y;
	return p;
}

void DrawPoint(int x,int y){
		glPointSize(6.0);
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd();
       glFlush();
}

void DrawLineSegment(Point2D pt1, Point2D pt2){
       glPointSize(1.0);
       glBegin(GL_LINES);
       glVertex2i(pt1.x, pt1.y);
       glVertex2i(pt2.x, pt2.y);
       glEnd();

       DrawPoint(rect1.Op.x,rect1.Op.y);

}

void drawRect(){
		
	DrawLineSegment(rect1.A,rect1.B);
	DrawLineSegment(rect1.B,rect1.C);
	DrawLineSegment(rect1.C,rect1.D);
	DrawLineSegment(rect1.D,rect1.A);
}

Point2D translate(Point2D p, float tx, float ty){
       p.x += tx; //.....wite the equations for translation 
       p.y += ty; //.....wite the equations for translation
       return p;
}

Point2D  rotate(Point2D p,Point2D from, float ang){
	p.x -= from.x;
	p.y -= from.y;
    ang = ang * 3.14 / 180.0;                                 //angle in radians
    Point2D ptemp;

    ptemp.x = p.x * cos(ang) - p.y * sin(ang);
    ptemp.y = p.x * sin(ang) + p.y * cos(ang);

	ptemp.x +=from.x;
	ptemp.y +=from.y;
	return ptemp;
}
int clickCount=0;
void myMouse(int button, int state, int x, int y) {
       if(state == GLUT_DOWN) {
              if(button == GLUT_LEFT_BUTTON) {
				  int rx=x;							//draw new rectangle
				  int ry=screenheight-y;
					 if(clickCount ==0){
						 rect1.A.x=rx;
						 rect1.A.y=ry;
						 DrawPoint(rx,ry);
						 clickCount++;
					 }else if(clickCount ==1){
						 rect1.B.x=rx;
						 rect1.B.y=ry;
						 DrawPoint(rx,ry);
						 clickCount++;
					 }else if(clickCount ==2){
						 rect1.C.x=rx;
						 rect1.C.y=ry;
						 DrawPoint(rx,ry);
						 clickCount++;
					 }else if(clickCount ==3){
						 rect1.D.x=rx;
						 rect1.D.y=ry;
						 DrawPoint(rx,ry);
						 drawRect();
					 }
              }
              else if (button == GLUT_RIGHT_BUTTON) {
                     /*Point2D Rotated_p2 = rotate(p2,angle);
                     DrawLineSegment(p1,Rotated_p2);*/
				  rect1.Op.x=x;										//select origin point to rotate
				  rect1.Op.y=screenheight - y;

				  
				   DrawPoint(rect1.Op.x,rect1.Op.y);
              }
       }
}

void zoomRect(float scale){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	Point2D mid;
	mid.x=((rect1.A.x+rect1.B.x+rect1.C.x+rect1.D.x)/4.0);
	mid.y=((rect1.A.y+rect1.B.y+rect1.C.y+rect1.D.y)/4.0);

	rect1.A = zoomFrom(rect1.A,mid,scale);
	rect1.B = zoomFrom(rect1.B,mid,scale);
	rect1.C = zoomFrom(rect1.C,mid,scale);
	rect1.D = zoomFrom(rect1.D,mid,scale);
		
	DrawLineSegment(rect1.A,rect1.B);
	DrawLineSegment(rect1.B,rect1.C);
	DrawLineSegment(rect1.C,rect1.D);
	DrawLineSegment(rect1.D,rect1.A);
}

void rotateRect(float angle){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
	rect1.A = rotate(rect1.A,rect1.Op,angle);
	rect1.B = rotate(rect1.B,rect1.Op,angle);
	rect1.C = rotate(rect1.C,rect1.Op,angle);
	rect1.D = rotate(rect1.D,rect1.Op,angle);
		
	DrawLineSegment(rect1.A,rect1.B);
	DrawLineSegment(rect1.B,rect1.C);
	DrawLineSegment(rect1.C,rect1.D);
	DrawLineSegment(rect1.D,rect1.A);
}

void translateRect(int x,int y){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
	rect1.A = translate(rect1.A,x,y);
	rect1.B = translate(rect1.B,x,y);
	rect1.C = translate(rect1.C,x,y);
	rect1.D = translate(rect1.D,x,y);
		
	DrawLineSegment(rect1.A,rect1.B);
	DrawLineSegment(rect1.B,rect1.C);
	DrawLineSegment(rect1.C,rect1.D);
	DrawLineSegment(rect1.D,rect1.A);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		clickCount=0;
	}else if(key == '+'){
		zoomRect(1.05);
	}else if(key == '-'){
		zoomRect(0.99);
	}else if(key == '7'){
		rotateRect(1);
	}else if(key == '9'){
		rotateRect(-1);
	}else if(key == '8'){
		translateRect(0,5);
	}else if(key == '4'){
		translateRect(-5,0);
	}else if(key == '6'){
		translateRect(5,0);
	}else if(key == '2'){
		translateRect(0,-5);
	}
}

void myDisplay(){
       glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
       glClear(GL_COLOR_BUFFER_BIT);
       glColor3f(0.0f, 0.0f, 0.0f);

	   rect1.A.x=10;
		rect1.A.y=10;
		rect1.B.x=150;
		rect1.B.y=10;
		rect1.C.x=150;
		rect1.C.y=130;
		rect1.D.x=10;
		rect1.D.y=130;
		rect1.Op.x=60;
		rect1.Op.y=60;
	   drawRect();
}
 
int main( int argc, char ** argv ) {
		std::cout << "press 7 & 9 for rotate" << endl;
		std::cout << "press 4,6,2,8 for transition" << endl;
		std::cout << "press + & - for zoom" << endl;
		std::cout << "click mouse right for set origin" << endl;
		std::cout << "press q to exit" << endl;
		std::cout << "press e to clear" << endl;
		std::cout << "after clear left click four point to draw rectangle" << endl;
       glutInit( &argc, argv );
       glutInitWindowPosition( 0, 0 );
       glutInitWindowSize( 800, 600 );
       glutCreateWindow( "My Drawing Screen" );
	   glMatrixMode( GL_PROJECTION );
       glLoadIdentity();
       gluOrtho2D( 0, 800, 0, 600 );
       glViewport(0, 0, 800, 600);
	   
       glutMouseFunc( myMouse );
	   glutKeyboardFunc(keyboard); 
       glutDisplayFunc( myDisplay );

       glutMainLoop();
       return( 0 );
}