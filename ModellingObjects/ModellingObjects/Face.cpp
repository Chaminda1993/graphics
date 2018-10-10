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