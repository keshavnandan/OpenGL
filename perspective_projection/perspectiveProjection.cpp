#include<iostream>
#include<cstdlib>
#include<GL/glut.h>
#include<GL/gl.h>
#include<cmath>
#include "../lib/matrix.h"
#include "../lib/point.h"
#define pi 3.14159
using namespace std;
float xmin,xmax,ymin,ymax;
	     
void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0,1.0,-1.0,1.0,-1.5,1.5);
	gluLookAt(0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 1.0, 0.0);
}


void drawCube(float T[8][3]){
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0,0.0,0.0);
	glVertex3fv(T[3]);
	glVertex3fv(T[0]);
	glVertex3fv(T[1]);
	glVertex3fv(T[2]);
	glVertex3fv(T[3]);
	glVertex3fv(T[4]);
	glVertex3fv(T[5]);
	glVertex3fv(T[6]);
	glVertex3fv(T[7]);
	glVertex3fv(T[4]);
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	glVertex3fv(T[1]);
	glVertex3fv(T[6]);
	glVertex3fv(T[2]);
	glVertex3fv(T[7]);
	glVertex3fv(T[0]);
	glVertex3fv(T[5]);
	glColor3f(1.0,1.0,0.0);
	glEnd();
	glFlush();
	glFinish();
}

void DrawCube(float T[8][3]){
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_QUADS);
	glVertex3fv(T[0]);
	glVertex3fv(T[1]);		
	glVertex3fv(T[2]);
	glVertex3fv(T[3]);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.1,0.1,0.1);
	glVertex3fv(T[3]);
	glVertex3fv(T[4]);
	glVertex3fv(T[0]);
	glVertex3fv(T[5]);
	glVertex3fv(T[1]);		
	glVertex3fv(T[6]);
	glColor3f(0.4,0.4,0.4);
	glVertex3fv(T[2]);
	glVertex3fv(T[7]);	
	glColor3f(0.7,0.7,0.7);		
	glVertex3fv(T[3]);
	glVertex3fv(T[4]);
	glEnd();
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_QUADS);
	glVertex3fv(T[4]);	
	glVertex3fv(T[5]);
	glVertex3fv(T[6]);
	glVertex3fv(T[7]);
	glEnd();
	glFlush();	
	//drawing object outline
	glColor3f(1.0,1.0,0.0);						
	glBegin(GL_LINE_STRIP);
	glVertex3fv(T[3]);
	glVertex3fv(T[0]);
	glVertex3fv(T[1]);
	glColor3f(1.0,1.0,1.0);
	glVertex3fv(T[2]);
	glVertex3fv(T[3]);
	glVertex3fv(T[4]);
	glVertex3fv(T[5]);
	glVertex3fv(T[6]);
	glVertex3fv(T[7]);
	glVertex3fv(T[4]);
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	glVertex3fv(T[1]);
	glVertex3fv(T[6]);
	glVertex3fv(T[2]);
	glVertex3fv(T[7]);
	glColor3f(1.0,1.0,0.0);
	glVertex3fv(T[0]);
	glVertex3fv(T[5]);
	glEnd();
	glFlush();
	glFinish();

}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_SINGLE|GLUT_RGB);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPointSize(2);
	float xmin=-0.6,ymin=-0.4,xmax=0.6,ymax=0.5;
	glColor3f(0.1,0.1,0.1);
	glRectf(xmin,ymin,xmax,ymax);
	//drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glVertex3f(-1.0,0.0,0.0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,1.0,0.0);		
	glVertex3f(0.0,-1.0,0.0);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);		
	glVertex3f(0.0,0.0,1.0);				
	glVertex3f(0.0,0.0,-1.0);				
	glEnd();
	glFlush();	
	float P1[8][3],T[8][3];
	float P[8][3]={ {0.0,0.0,0.0},
	{0.0,0.0,0.2},
	{0.2,0.0,0.2},
	{0.2,0.0,0.0},
	{0.075,0.1,0.025},
	{0.025,0.1,0.025},
	{0.025,0.1,0.075},
	{0.075,0.1,0.075} } ;

	glColor3f(1.0,1.0,0.0);
	//drawing cube
	for(int i=0;i<8;i++)
	   for(int j=0;j<3;j++)
	       T[i][j]=P[i][j];
	float tx=-0.2,ty=0.08,tz=0.55;
	for(int k=0;k<8;k++)
	   {
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2;
	    p2=p1.Scale(1.5,1.5,1.5);
	    p2=p2.Translate(tx,ty,tz);
	    T[k][0]=p2.x;T[k][1]=p2.y;T[k][2]=p2.z;
	    }
	
	DrawCube(T);
	
	float zprp=-0.6,h=1.0;
	glBegin(GL_POINTS);
	glColor3f(1.0,1.0,1.0);
	glPointSize(3);
	glVertex3f(0.0,0.0,zprp);
	glEnd();
	glFlush();
	for(int k=0;k<8;k++)
	   {
	    float z = T[k][2];
	    cout<<"T["<<k<<"][0] = "<<T[k][0]<<"\tT["<<k<<"][1] = "<<T[k][1]<<"\tT["<<k<<"][2] = "<<T[k][2]<<endl;	
	    P1[k][0]=T[k][0]*(zprp/(zprp-z));
	    P1[k][1]=T[k][1]*(zprp/(zprp-z));
	    P1[k][2]=0.0;
	    }

	glColor3f(0.05,0.05,0.05);
//	glRectf(P1[1][0],P1[1][1],P1[7][0],P1[7][1]);
	glEnable (GL_LINE_STIPPLE);
	glLineStipple (1, 0x00FF); // dashed 
	glColor3f(0.9,0.6,0.4);
	float R[3]={0,0,zprp};
	glBegin(GL_LINES);
	glVertex3fv(T[0]);
	glVertex3fv(R);
	glVertex3fv(T[5]);
	glVertex3fv(R);
	glVertex3fv(T[3]);
	glVertex3fv(R);
	glVertex3fv(T[4]);
	glVertex3fv(R);
	glEnd();
	glFlush();
//	sleep(1.5);
	
	glDisable (GL_LINE_STIPPLE);
	glFlush ();
	drawCube(P1);    
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
//	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(250,300);
	glutCreateWindow("Perspective Projection");
	Initialize();
//	cout<<"Enter the coordinates of diagonal of Rectangle"<<endl;
//	cin>>xmin>>xmax>>ymin>>ymax;
	glutDisplayFunc(Draw);
	glutMainLoop();
}
		
