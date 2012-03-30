#include<iostream>
#include<fstream>
#include<cstdlib>
#include<GL/glut.h>
#include<GL/gl.h>
#include "../lib/matrix.cpp"
#include "../lib/point.h"
using namespace std;
float xmin,xmax,ymin,ymax;
int n;
//point P[n];
void wait(float seconds);
void computePoint(float u,point &pt,point pk,point pk1,point dpk,point dpk1){
	float blend,h0,h1,h2,h3;
	//hermite blending functions
	h0 =  2*u*u*u - 3*u*u + 1;
	h1 = -2*u*u*u + 3*u*u;
	h2 =    u*u*u - 2*u*u + u;
	h3 =    u*u*u -   u*u;
	 
	pt = pk*h0 + pk1*h1 + dpk*h2 + dpk1*h3;
}
	
void hermite(point pk,point pk1,point dpk,point dpk1,int m,point curve[]){
	for(int i=0;i<m;i++)
	computePoint(i/(float)m,curve[i],pk,pk1,dpk,dpk1);
}	
		
	
void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,0.0,0.0);	
	gluLookAt(0.0, 0.0, 0.0, -1.0, -2.0, -3.0, 0.0, 1.0, 0.0);
	
}

void Draw(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(2);
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
	glFlush();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,1.0);		
	glVertex3f(0.0,0.0,-1.0);
	glEnd();
	glFlush();
//	cout<<"Enter the number of points"<<endl;
	fstream fs("inhermite");
	fs>>n;
	point P[n],P1[n],C[250];
//	cout<<"Enter the points and derivatives at those points"<<endl;
	for(int i=0;i<n;i++)
	fs>>P[i].x>>P[i].y>>P[i].z>>P1[i].x>>P1[i].y>>P1[i].z;
	for(int i=0;i<n;i++)
	cout<<P[i].x<<"\t"<<P[i].y<<"\t"<<P[i].z<<endl;
	
	glEnable (GL_LINE_STIPPLE);
	glLineStipple (1, 0x00FF); // dashed 
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<n;i++)
	glVertex3f(P[i].x,P[i].y,P[i].z);
	glEnd();
	glFlush();
	glDisable (GL_LINE_STIPPLE);
	
	for(int i=0;i<n-1;i++){
	hermite(P[i],P[i+1],P1[i],P1[i+1],250,C);
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<250;i++){
	glBegin(GL_POINTS);
	glVertex3f(C[i].x,C[i].y,C[i].z);
	glEnd();
	glFlush();
	cout<<C[i]<<endl;
	wait(0.01);
	}
	}
	while(true);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(250,300);
	glutCreateWindow("Hermite Curves");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
}

void wait(float t){
	clock_t w;
	float k = t*CLOCKS_PER_SEC;
	w = (clock()+t*CLOCKS_PER_SEC);
	while(clock()<w){}
}			