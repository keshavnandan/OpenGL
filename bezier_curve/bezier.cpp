#include<iostream>
#include<fstream>
#include<cstdlib>
#include<GL/glut.h>
#include<GL/gl.h>
#include "../lib/point.h"
#include "../lib/matrix.h"
using namespace std;
float xmin,xmax,ymin,ymax;
int n;
//point P[n];
void wait(float seconds);
void computeCoefficients(int n,int *c){
	int k,i;
	for(k=0;k<=n;k++){
	c[k]=1;
	for(i=n;i>=k+1;i--)
	c[k]*=i;
	for(i=n-k;i>=2;i--)
	c[k]/=i;
	}
}	

void computePoint(float u,point &pt,int nc,point ct[],int *c){
	int k,n=nc-1;
	float blend;
	pt.x=pt.y=pt.z=0.0;
	for(k=0;k<nc;k++){
	blend=c[k]*powf(u,k)*powf(1-u,n-k);
	pt.x+=ct[k].x*blend;
	pt.y+=ct[k].y*blend;
	pt.z+=ct[k].z*blend;
	}
}
	
void bezier(point ct[],int nc,int m,point curve[]){
	int *c = (int*)malloc(nc*sizeof(int));
	int i;
	computeCoefficients(nc-1,c);
	for(i=0;i<m;i++)
	computePoint(i/(float)m,curve[i],nc,ct,c);
	free(c);
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
	fstream fs("inbezier");
	//cout<<"Enter the number of points"<<endl;
	//cin>>n;
	fs>>n;

	point P[n],C[250];
	//cout<<"Enter the points"<<endl;
	for(int i=0;i<n;i++)
	//cin>>P[i].x>>P[i].y>>P[i].z;
	fs>>P[i].x>>P[i].y>>P[i].z;
	//for(int i=0;i<n;i++)
	//cout<<P[i].x<<"\t"<<P[i].y<<"\t"<<P[i].z<<endl;
	
	glEnable (GL_LINE_STIPPLE);
	glLineStipple (1, 0x00FF); // dashed 
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<n;i++)
	glVertex3f(P[i].x,P[i].y,P[i].z);
	glEnd();
	glFlush();
	glDisable (GL_LINE_STIPPLE);
	
	bezier(P,n,250,C);
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<250;i++){
	glBegin(GL_POINTS);
	glVertex3f(C[i].x,C[i].y,C[i].z);
	glEnd();
	glFlush();
	wait(0.01);
	}
	while(true);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(250,300);
	glutCreateWindow("Bezier Curves");
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
