#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath> 
#include <fstream>
using namespace std;

class Face{
  public:
		int nVerts;			// number of vertices in this face

		int* vert;	// the list of vertices
		
		Face(){nVerts = 0; vert = NULL;}	// constructor
		~Face(){delete[] vert; nVerts = 0;} // destructor
};


typedef struct{float x;float y;}Point2D;
typedef struct{float x;float y;float z;}Point3D;

int numVerts, numFaces;

Point3D* v_list;  /* Vertex list - will be filled in with X,Y,Z vertexes. */
Face* f_list;	/* Face list - for the 6 faces of a cube. */ 

int readmesh(char * fileName){
	fstream infile;
	infile.open(fileName, ios::in);
	if(infile.fail()) return -1; // error - can't open file
	if(infile.eof())  return -1; // error - empty file

	//the file is OK so read the 
	//number of vertices, and faces.
	infile >> numVerts >> numFaces;

	//create arrays to hold the vertices, nomrmals,
	//and faces.
	v_list = new Point3D[numVerts];
	f_list = new Face[numFaces];

	//read the vertices
	for(int p = 0; p < numVerts; p++) 
	{
		infile >> v_list[p].x >> v_list[p].y >> v_list[p].z;
	}

	//read the faces
	for(int f = 0; f < numFaces; f++)
	{
		infile >> f_list[f].nVerts;
		f_list[f].vert = new int[f_list[f].nVerts];
		
		for(int v = 0; v < f_list[f].nVerts; v++)
			infile >> f_list[f].vert[v];
	} 
	return 0; // success

}

void rotatebox_x(float deg_x){		// rotate the cube about a line which is parallel to X axis 
	float ang = deg_x * 3.14159265359 / 180.0;		//angle in radians 
	
	Point3D cp;
	float sumx=0,sumy=0,sumz=0;
	for(int i=0;i<numVerts;i++){
		sumx += v_list[i].x;
		sumy += v_list[i].y;
		sumz += v_list[i].z;
	}
	cp.x=sumx/10;
	cp.y=sumy/10;
	cp.z=sumz/10;

	// do the necessary transformations for each vertex
	for(int i=0;i<numVerts;i++){
		Point3D tmp=v_list[i];
		
		//combined 3 transformation in one equation
		tmp.y=v_list[i].y*cos(ang)-v_list[i].z*sin(ang)+cp.y-cp.y*cos(ang)+cp.z*sin(ang);
		tmp.z=v_list[i].y*sin(ang)+v_list[i].z*cos(ang)+cp.z-cp.y*sin(ang)-cp.z*cos(ang);

		v_list[i]=tmp;
	}
	
	glutPostRedisplay();	//this will call the function "myDisplay()" again
}

void rotatebox_y(float deg_y){		// rotate the cube about a line which is parallel to Y axis 
	float ang = deg_y * 3.14159265359 / 180.0;

	Point3D cp;
	float sumx=0,sumy=0,sumz=0;
	for(int i=0;i<numVerts;i++){
		sumx += v_list[i].x;
		sumy += v_list[i].y;
		sumz += v_list[i].z;
	}
	cp.x=sumx/10;
	cp.y=sumy/10;
	cp.z=sumz/10;
	
	// do the necessary transformations for each vertex
	for(int i=0;i<numVerts;i++){
		Point3D tmp=v_list[i];
		
		/*tmp.x=v_list[i].x*cos(ang)-v_list[i].z*sin(ang);
		tmp.z=v_list[i].x*sin(ang)+v_list[i].z*cos(ang);*/
		tmp.x=v_list[i].x*cos(ang)-v_list[i].z*sin(ang)+cp.x-cp.x*cos(ang)+cp.z*sin(ang);
		tmp.z=v_list[i].x*sin(ang)+v_list[i].z*cos(ang)+cp.z-cp.x*sin(ang)-cp.z*cos(ang);

		v_list[i]=tmp;
	}

	glutPostRedisplay();	//this will call the function "myDisplay()" again
}

void zoom(float scale){		// rotate the cube about a line which is parallel to Y axis 
	Point3D cp;
	cp.x=0;cp.y=0;cp.z=0;
	for(int i=0;i<numVerts;i++){
		cp.x += v_list[i].x;
		cp.y += v_list[i].y;
		cp.z += v_list[i].z;
	}
	cp.x=cp.x/10;
	cp.y=cp.y/10;
	cp.z=cp.z/10;
	
	// do the necessary transformations for each vertex
	for(int i=0;i<numVerts;i++){
		Point3D tmp=v_list[i];
		
		tmp.x = v_list[i].x*scale-cp.x*scale+cp.x;
		tmp.y = v_list[i].y*scale-cp.y*scale+cp.y;
		tmp.z = v_list[i].z*scale-cp.z*scale+cp.z;

		v_list[i]=tmp;
	}

	glutPostRedisplay();	//this will call the function "myDisplay()" again
}

Point2D Project_ortho(float x, float y, float z){	//orthogonal projection
	Point2D p0;
	p0.x = x ;
	p0.y = y ;
	return p0;
}

void drawMesh() 
{
	//loop through the faces of the object
	for(int f = 0; f < numFaces; f++) 
	{ 
		//drawing faces
		glBegin(GL_LINE_LOOP);
		  for(int v = 0; v < f_list[f].nVerts; v++) // for each one..
		  {
			  //finding the vertex index i
			  int i =  f_list[f].vert[v] ; 

			  Point2D p = Project_ortho(v_list[i].x, v_list[i].y, v_list[i].z);

			  //inform OpenGL of the vertex
			  glVertex2f(p.x, p.y);
		  }
		glEnd();		
	}
	glFlush();
}

void myDisplay()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawMesh();
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		exit(EXIT_SUCCESS);

	switch (key) {
	case '+': zoom(1.02); break;	
	case '-': zoom(0.98);break;	
	default: return;
	}
}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: rotatebox_y(-1); break;	//	decreasing the angle by 1 degree
	case GLUT_KEY_RIGHT: rotatebox_y(1);break;	//	increasing the angle by 1 degree
	case GLUT_KEY_UP: rotatebox_x(-1);break;	//	decreasing the angle by 1 degree
	case GLUT_KEY_DOWN: rotatebox_x(1);break;	//	increasing the angle by 1 degree
	default: return;
	}
}

int main( int argc, char ** argv ) {
	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Modelling Objects" );

	glViewport(0, 0, 800, 600);
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity();

	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	
	//readmesh("../BarnMeshFile.txt");
	readmesh("../newShape.txt");

	glutKeyboardFunc(keyboard); 
	glutSpecialFunc(special);
	glutDisplayFunc( myDisplay );
	glutMainLoop();

	return( 0 );
}