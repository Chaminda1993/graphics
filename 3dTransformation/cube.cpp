#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath> 
#include <ctime>
#include <iostream>
  using namespace std;

int WinWidth = 500, WinHeight = 500;

typedef struct{float x;float y;}Point2D;
typedef struct{float x;float y;float z;}Point3D;

Point3D A,B,C,D,E,F,G,H;	// Vertices of the cube


void InitCube(){
	A.x = -100; A.y = -100; A.z = 100;		
	B.x = 100; B.y = -100; B.z = 100;		
	C.x = 100; C.y = 100; C.z = 100;		
	D.x = -100; D.y = 100; D.z = 100;		

	E.x = -100; E.y = -100; E.z = -100;	
	F.x = 100; F.y = -100; F.z = -100;	
	G.x = 100; G.y = 100; G.z = -100;	
	H.x = -100; H.y = 100; H.z = -100;	
}

void DrawCube(Point2D A, Point2D B, Point2D C, Point2D D, Point2D E, Point2D F, Point2D G, Point2D H){
	glPointSize(1.0);
	glLineWidth(3.0);

	//DRAWING BACK FACE
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
			glVertex2i(E.x, E.y); glVertex2i(F.x, F.y);	glVertex2i(G.x, G.y); glVertex2i(H.x, H.y);
	glEnd();
	
	//DRAWING FRONT FACE
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);	
			glVertex2i(A.x, A.y); glVertex2i(B.x, B.y);	glVertex2i(C.x, C.y); glVertex2i(D.x, D.y);
	glEnd();

	//DRAWING OTHER LINES
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2i(A.x, A.y); glVertex2i(E.x, E.y);

		glVertex2i(B.x, B.y); glVertex2i(F.x, F.y);

		glVertex2i(C.x, C.y); glVertex2i(G.x, G.y);

		glVertex2i(D.x, D.y); glVertex2i(H.x, H.y);
	glEnd();

	glFlush();
}

Point2D Project_OrthoXY(Point3D p){  // Orthographic parallel projection on 
	Point2D p2;
	p2.x = p.x; 
	p2.y = p.y;
	return p2;
}


Point3D translate3D(Point3D p, float tx, float ty, float tz){
    Point3D tp3;
	//.....wite the equations for 3D translation
	tp3.x = p.x+tx;
	tp3.y = p.y+ty;
	tp3.z = p.z+tz;

	return tp3;
} 

Point3D rotate_y(Point3D p, float ang){
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	pr.x = p.x * cos(ang) + p.z * sin(ang);
	pr.z = -p.x * sin(ang) + p.z * cos(ang);
	pr.y = p.y;

	return pr;
}

Point3D rotate_x(Point3D p, float ang){
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	pr.y = p.y * cos(ang) - p.z * sin(ang);
	pr.z = p.y * sin(ang) + p.z * cos(ang);
	pr.x = p.x; 
	
	return pr;
} 

Point3D gPoint(Point3D A,Point3D B,Point3D C,Point3D D,Point3D E,Point3D F,Point3D G,Point3D H){
	Point3D gp;
	gp.x =(A.x+B.x+C.x+D.x+E.x+F.x+G.x+H.x)/8;
	gp.y =(A.y+B.y+C.y+D.y+E.y+F.y+G.y+H.y)/8;
	gp.z =(A.z+B.z+C.z+D.z+E.z+F.z+G.z+H.z)/8;
	return gp;
}

void rotatebox_y(float ang){
	Point3D gp = gPoint(A,B,C,D,E,F,G,H);
	
	A = translate3D(rotate_y(translate3D(A,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	B = translate3D(rotate_y(translate3D(B,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	C = translate3D(rotate_y(translate3D(C,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	D = translate3D(rotate_y(translate3D(D,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	E = translate3D(rotate_y(translate3D(E,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	F = translate3D(rotate_y(translate3D(F,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	G = translate3D(rotate_y(translate3D(G,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	H = translate3D(rotate_y(translate3D(H,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	
		glutPostRedisplay();
}

void rotatebox_x(float ang){
	Point3D gp = gPoint(A,B,C,D,E,F,G,H);
	
	A = translate3D(rotate_x(translate3D(A,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	B = translate3D(rotate_x(translate3D(B,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	C = translate3D(rotate_x(translate3D(C,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	D = translate3D(rotate_x(translate3D(D,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	E = translate3D(rotate_x(translate3D(E,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	F = translate3D(rotate_x(translate3D(F,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	G = translate3D(rotate_x(translate3D(G,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	H = translate3D(rotate_x(translate3D(H,-gp.x,-gp.y,-gp.z), ang),gp.x,gp.y,gp.z);
	
		glutPostRedisplay();
}

void moveCube(int x,int y,int z){
	A = translate3D(A, x, y, z);
	B = translate3D(B, x, y, z);
	C = translate3D(C, x, y, z);
	D = translate3D(D, x, y, z);
	E = translate3D(E, x, y, z);
	F = translate3D(F, x, y, z);
	G = translate3D(G, x, y, z);
	H = translate3D(H, x, y, z);
		
	
	glutPostRedisplay();
}

Point3D zoomPoint(Point3D p,float val){
	Point3D tmp;
	tmp.x = p.x*val;
	tmp.y = p.y*val;
	tmp.z = p.z*val;
	return tmp;
}

void zoomCube(float val){
	Point3D gp = gPoint(A,B,C,D,E,F,G,H);
	
	A = translate3D(zoomPoint(translate3D(A,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	B = translate3D(zoomPoint(translate3D(B,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	C = translate3D(zoomPoint(translate3D(C,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	D = translate3D(zoomPoint(translate3D(D,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	E = translate3D(zoomPoint(translate3D(E,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	F = translate3D(zoomPoint(translate3D(F,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	G = translate3D(zoomPoint(translate3D(G,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	H = translate3D(zoomPoint(translate3D(H,-gp.x,-gp.y,-gp.z), val),gp.x,gp.y,gp.z);
	
		glutPostRedisplay();
}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: rotatebox_y(-1); break;
	case GLUT_KEY_RIGHT: rotatebox_y(1);break;
	case GLUT_KEY_UP: rotatebox_x(-1);break;
	case GLUT_KEY_DOWN: rotatebox_x(1);break;
	default: return;
	}
}

void keyboard(unsigned char key, int x, int y)
{

    if (key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);

	switch(key){
		case '2': moveCube(0,-1,0); break;
		case '8': moveCube(0,1,0);break;
		case '4': moveCube(-1,0,0);break;
		case '6': moveCube(1,0,0);break;
		case '7': moveCube(0,0,-1);break;
		case '9': moveCube(0,0,1);break;
		case '+': zoomCube(1.01);break;
		case '-': zoomCube(0.99);break;
		default: return;	
	}
}

void myMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) 
	{
		if(button == GLUT_LEFT_BUTTON) 
		{
			 
		}
		else if (button == GLUT_RIGHT_BUTTON) 
		{
			 
		}
	}
}

void myDisplay()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	
	// The TRANSFORMED vertices are PROJECTED on to the XY plane, then "DrawCube" draws the box
	DrawCube(		 
		Project_OrthoXY(A),	
		Project_OrthoXY(B),
		Project_OrthoXY(C),
		Project_OrthoXY(D),
		Project_OrthoXY(E),
		Project_OrthoXY(F),
		Project_OrthoXY(G),
		Project_OrthoXY(H)
	);
}


int main( int argc, char ** argv ) {
	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( WinWidth, WinHeight );
	glutCreateWindow( "Projection of a Cube" );

	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity();
	gluOrtho2D( 0, WinWidth, 0, WinHeight );
	glViewport(0, 0, WinWidth, WinHeight);

	InitCube();

	glutKeyboardFunc(keyboard); 
	glutSpecialFunc(special);
	
	glutMouseFunc( myMouse );
	glutDisplayFunc( myDisplay );
	glutMainLoop();

	return( 0 );
}
