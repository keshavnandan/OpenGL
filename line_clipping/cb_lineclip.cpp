#include<iostream>
#include<fstream>
#include<cstdlib>
#include<GL/glut.h>
#include<GL/gl.h>
#include "lineclip.h"
using namespace std;
float xmin,xmax,ymin,ymax;
int n;

void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,0.0,0.0);	
}

bool clipTest(float p,float q,float &u1,float &u2){
	float r;
	bool ret = true;
	cout<<"u1 = "<<u1<<"\tu2 = "<<u2<<endl;
	
	if(p<0.0){
	r = q/p;
	if(r>u2)
	 ret = false;
	else if(r>u1)
		  u1 = r;
	}	  
	 
	else if(p>0.0){
	r = 	q/p;
	if(r<u1)
	 ret = false;
	else if(r<u2)
		u2 = r;
	}
	
	else if(q<0.0)
	ret = false;
	cout<<"u1 = "<<u1<<"\tu2 = "<<u2<<endl;	
	return ret;
}

void clipLine(line l){
	float x1 = l.p1.x,x2 = l.p2.x,y1 = l.p1.y,y2 = l.p2.y,u1 = l.u1,u2 = l.u2;
	float dx = x2 - x1,dy = y2 - y1;
	if(clipTest(-dx,x1-xmin,u1,u2)){
	cout<<"first test done"<<endl;
	 if(clipTest(dx,xmax-x1,u1,u2)){
	 cout<<"second test done"<<endl; 
	  if(clipTest(-dy,y1-ymin,u1,u2)){
	  cout<<"third test done"<<endl; 
	   if(clipTest(dy,ymax-y1,u1,u2)){
	   cout<<"fourth test done"<<endl;	
	     if(u2<1.0){
	     x2 = x1+u2*dx;
	     y2 = y1+u2*dy;
	     }
	   	if(u1>0.0){
	   	x1 += u1*dx;
		y1 += u1*dy; 
	     }
	     glBegin(GL_LINES);
	     glVertex3f(x1,y1,0.0);
	     glVertex3f(x2,y2,0.0);
	     glEnd();
	     glFlush();
	    }
	   }
	  }
	 }    
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(2);
	xmin=-0.5;ymin=-0.4;xmax=0.5;ymax=0.4;
	glColor3f(0.1,0.1,0.1);
	glRectf(xmin,ymin,xmax,ymax);
	glEnd();
	glFlush();
	fstream fs("input");

	//input no. of lines.
	fs>>n;
	line llist[n]; 
	//input the coordinates of end-points of line segment.
	for(int i=0;i<n;i++)
	fs>>llist[i];
	for(int i=0;i<n;i++)
	cout<<"............\n"<<llist[i];
	glPointSize(3);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	for(int i=0;i<n;i++){
	glVertex3f(llist[i].p1.x,llist[i].p1.y,0.0);
	glVertex3f(llist[i].p2.x,llist[i].p2.y,0.0);
	}
	glEnd();
	glFlush();
	sleep(2.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glColor3f(0.1,0.1,0.1);
	glRectf(xmin,ymin,xmax,ymax);	
	glColor3f(1.0,0.5,0.0);
	for(int i = 0;i < n;i++)
		clipLine(llist[i]);
	glEnd();
	glFlush();
	while(true);
	
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(250,300);
	glutCreateWindow("Cyrus Beck Line Clipping");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
}
