#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

int screenheight = 600;
int screenwidth = 1200;

//Point object
struct Point{
	int x;
	int y;
};

//Basic points and colors decleration
Point curLoc;
Point bldLoc;
int prevLoc;
float bodyColor[4] = {0.0,1.0,0.0,1.0};
float paddleColor[4] = {1.0,0.0,1.0,1.0};
float boltColor[4] = {0.0,0.0,1.0,1.0};
float buildingColor[4] = {1.0,0.0,0.0,1.0};

//function for rotate point
Point rotate(Point p,Point from, float ang){
	p.x -= from.x;
	p.y -= from.y;
    ang = ang * 3.14 / 180.0;                                 
    Point ptemp;

    ptemp.x = p.x * cos(ang) - p.y * sin(ang);
    ptemp.y = p.x * sin(ang) + p.y * cos(ang);

	ptemp.x +=from.x;
	ptemp.y +=from.y;
	return ptemp;
}

//Object of paddle of boat
struct Paddle{
	float color [4];
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	int angle;
	void mount(Point p){
		p1.x = p.x - 2;
		p1.y = p.y + 85;
		p2.x = p.x + 2;
		p2.y = p.y + 85;
		p3.x = p.x + 7;
		p3.y = p.y - 85;
		p4.x = p.x - 7;
		p4.y = p.y - 85;

		if(angle < -40) {
			angle = 40;
		}else if(angle >40){
			angle = -40;
		}
		angle += prevLoc-p.x;
		prevLoc = p.x;

		p1 = rotate(p1,p,angle);
		p2 = rotate(p2,p,angle);
		p3 = rotate(p3,p,angle);
		p4 = rotate(p4,p,angle);
	}
	void setColor(float col[4]){
		color[0] = col[0];
		color[1] = col[1];
		color[2] = col[2];
		color[3] = col[3];
	}
};

//Object of bolt of boat
struct Bolt{
	float color [4];
	Point bottomLeft;
	Point topRight;
	void mount(Point p){
		bottomLeft.x = p.x - 8;
		bottomLeft.y = p.y - 3;
		topRight.x = p.x + 8;
		topRight.y = p.y + 3;
	}
	void setColor(float col[4]){
		color[0] = col[0];
		color[1] = col[1];
		color[2] = col[2];
		color[3] = col[3];
	}
};

//Object of body of boat
struct Boat{
	float color [4];
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	void mount(Point p){
		p1.x = p.x - 100;
		p1.y = p.y + 20;
		p2.x = p.x + 100;
		p2.y = p.y + 20;
		p3.x = p.x + 75;
		p3.y = p.y - 20;
		p4.x = p.x - 75;
		p4.y = p.y - 20;
	}
	void setColor(float col[4]){
		color[0] = col[0];
		color[1] = col[1];
		color[2] = col[2];
		color[3] = col[3];
	}
};

//Object of building
struct Building{
	float color [4];
	Point bottomLeft;
	Point topRight;
	void mount(Point p){
		bottomLeft.x = p.x - 80;
		bottomLeft.y = p.y - 150;
		topRight.x = p.x + 80;
		topRight.y = p.y + 150;
	}
	void setColor(float col[4]){
		color[0] = col[0];
		color[1] = col[1];
		color[2] = col[2];
		color[3] = col[3];
	}
};

Building bld;

//draw paddle
void drawPaddle(Paddle pdl){
	glColor4fv(pdl.color);
	glBegin(GL_QUADS);
	glVertex2f(pdl.p1.x,pdl.p1.y);
	glVertex2f(pdl.p2.x,pdl.p2.y);
	glVertex2f(pdl.p3.x,pdl.p3.y);
	glVertex2f(pdl.p4.x,pdl.p4.y);
	glEnd();
}

//draw bolt
void drawBolt(Bolt blt){
	glColor4fv(blt.color);
	glRectf(blt.bottomLeft.x,blt.bottomLeft.y,blt.topRight.x,blt.topRight.y);
}

//draw building
void drawBuilding(Building bldg){
	glColor4fv(bldg.color);
	glRectf(bldg.bottomLeft.x,bldg.bottomLeft.y,bldg.topRight.x,bldg.topRight.y);
}

//draw boat body
void drawBoat(Boat boat){
	glBegin(GL_QUADS);
	glColor4fv(boat.color);
	glVertex2f(boat.p1.x,boat.p1.y);
	glVertex2f(boat.p2.x,boat.p2.y);
	glVertex2f(boat.p3.x,boat.p3.y);
	glVertex2f(boat.p4.x,boat.p4.y);
	glEnd();
}

struct CBoat{
	Boat body;
	Bolt bolt;
	Paddle paddle;
	Point location;
	void setLocation(Point p){
		location = p;
		body.mount(p);
		bolt.mount(p);
		paddle.mount(p);
	}
	void drawCBoat(){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		drawBuilding(bld);
		drawBoat(body);
		drawPaddle(paddle);
		drawBolt(bolt);
	}
};

CBoat myboat;

void myDisplay(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	//draw a building
	bldLoc.x = 600;
	bldLoc.y = 400;
	bld.mount(bldLoc);
	bld.setColor(buildingColor);
	drawBuilding(bld);

	//draw a boat
	curLoc.x =300;
	curLoc.y =200;
	prevLoc = 0;
	myboat.setLocation(curLoc);
	myboat.body.setColor(bodyColor);
	myboat.paddle.setColor(paddleColor);
	myboat.paddle.angle = 0;
	myboat.bolt.setColor(boltColor);
	myboat.drawCBoat();

	glFlush();
} 

void special(int key, int, int) {
	Point tmp = myboat.location;
	switch (key) {
		case GLUT_KEY_LEFT:  
			tmp.x = tmp.x - 3;
			break;
		case GLUT_KEY_RIGHT:  
			tmp.x = tmp.x + 3;
			break;
		case GLUT_KEY_UP: 
			tmp.y = tmp.y + 2;
			break;
		case GLUT_KEY_DOWN:
			tmp.y = tmp.y - 2;
			break;
		default: return;
	}
	myboat.setLocation(tmp);
	myboat.drawCBoat();
	
	glFlush();
}

int main( int argc, char ** argv ) {

	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( screenwidth, screenheight );
	glutCreateWindow( "Boat" );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, screenwidth, 0, screenheight );
	glViewport(0, 0, screenwidth, screenheight);
	glutDisplayFunc( myDisplay );


	glutSpecialFunc(special);
	glutMainLoop();

	return( 0 );
}