#include <GL/glut.h>
#include <vector>
#include <iostream>
using namespace std;

int ww = 800, wh = 600;

struct Point{
    int x;
    int y;
};

struct Shape{
    vector<Point> pList;
    Point locator;
};

Point origin,mid;

void printShp(Shape shp){
    int size = shp.pList.size();
    cout << "Start shape"<< endl;
    for(int i=0;i<size;i++){
        Point cur=shp.pList.at(i);
        cout << "\tpoint " << i << " - (" << cur.x << "," << cur.y << ")" <<endl;
    }
}

void drawLine(Point str,Point end){
    //cout << "prePoint - (" << str.x << "," << str.y << ") " ;
    //cout << "curpoint - (" << end.x << "," << end.y << ")" <<endl;
    glPointSize(1.0);
    glBegin(GL_LINES);
    glVertex2i(str.x,str.y);
    glVertex2i(end.x,end.y);
    glEnd();
    glFlush();
}

void myinit(){
    glViewport(0,0,ww,wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

Shape addMirror(Shape shp,char axis){
    int size = shp.pList.size();
    Shape tmp = shp;
    for(int i = size-1;i >=0 ; i--){
        Point p = shp.pList.at(i);
        if(axis == 'y'){
            p.x = p.x * -1;
        }else if(axis == 'x'){
            p.y = p.y * -1;
        }else{
            return shp;
        }
        tmp.pList.push_back(p);
    }
    return tmp;
}

Shape scaleUp(Shape shp,int scale,Point cntr){
    int size = shp.pList.size();
    Shape tmpS;
    for(int i=0;i<size;i++){
        Point cur=shp.pList.at(i);
        int dx = cur.x-cntr.x;
        int dy = cur.y-cntr.y;
        cur.x=(dx * scale)+cntr.x;
        cur.y=(dx * scale)+cntr.y;
        tmpS.pList.push_back(cur);
    }
    return tmpS;
}

Shape translateShp(Shape shp,int tx,int ty){
    int size = shp.pList.size();
    Shape tmpS;
    for(int i=0;i<size;i++){
        Point cur=shp.pList.at(i);
        cur.x += tx;
        cur.y += ty;
        tmpS.pList.push_back(cur);
    }
    return tmpS;
}

void drawShp(Shape shp){
    //printShp(shp);
    int size = shp.pList.size();
    Point prePoint;
    prePoint=shp.pList.at(0);
    for(int i=1;i<size;i++){
        drawLine(prePoint,shp.pList.at(i));
        prePoint = shp.pList.at(i);
    }
}

void drawMyPattern(){
    origin.x = 0;
    origin.y = 0;
    mid.x = ww/2;
    mid.y = wh/2;
    Point p1,p2,p3;
    p1.x = 0;
    p1.y = 0;
    p2.x = 30;
    p2.y = 20;
    p3.x = 70;
    p3.y = 0;

    Shape basicShp,combined,scalled;
    basicShp.pList.push_back(p1);
    basicShp.pList.push_back(p2);
    basicShp.pList.push_back(p3);

    combined = addMirror(basicShp,'x');
    drawShp(translateShp(combined,mid.x+10,mid.y));

    scalled = scaleUp(combined,1.3,mid);
    printShp(scalled);
    drawShp(translateShp(scalled,mid.x,mid.y));

}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    glFlush();

    drawMyPattern();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww,wh);
    glutCreateWindow("Pattern");
    myinit();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}