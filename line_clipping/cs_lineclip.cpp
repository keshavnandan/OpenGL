#include<iostream>
#include<fstream>
#include<cstdlib>
#include<GL/glut.h>
#include<GL/gl.h>
#include "lineclip.h"
#define LEFT_EDGE 		0x1
#define RIGHT_EDGE  	0x2
#define BOTTOM_EDGE 	0x4
#define TOP_EDGE 		0x8
#define ACCEPT(a,b)	  (!(a|b))
#define REJECT(a,b)	    (a&b)
#define INSIDE(a)	     (!a)
using namespace std;
float xmin,xmax,ymin,ymax;
int n;
typedef unsigned char code;

void swapt(point &p1,point &p2){
	point tmp;
	tmp = p1;p1 = p2;p2 = tmp;
}	

void swapc(code *c1,code *c2){
	code c;
	c = *c1;*c1 = *c2;*c2 = c;
}	

code encode(const point& p){
	code C=0x00;
	if(p.x<xmin)
	C|=LEFT_EDGE;
	if(p.x>xmax)
	C|=RIGHT_EDGE;
	if(p.y<ymin)
	C|=BOTTOM_EDGE;
	if(p.y>ymax)
	C|=TOP_EDGE;
	return C;
}	

void clipLine(line l){
	cout<<"The Line to be clipped is "<<l<<endl;
	point p1 = l.p1,p2 = l.p2; 
	code code1,code2;
	bool draw = false,done = false;
	float m,f;

	while(!done){
	code1 = encode(p1);
	code2 = encode(p2);
	if(ACCEPT(code1,code2)){
	  done = true;
	  draw = true;
	  cout<<"line is accepted"<<endl;
	  cout<<p1<<p2;
	}
	else if(REJECT(code1,code2)){
	  done = true;
	  draw = false;
	  cout<<"line is rejected"<<endl;
	  cout<<p1<<p2;
	}
	else{
	  if(INSIDE(code1)){
	  	cout<<"before swap"<<p1<<p2<<endl;
	  	swapt(p1,p2);
	  	swapc(&code1,&code2);
	  	cout<<"p1 and p2 swapped "<<endl;
	  	cout<<p1<<p2;
	  }
	  if(p1.x != p2.x){
	   m = (p2.y-p1.y)/(p2.x-p1.x);
	   cout<<"m = "<<m<<endl;
	  if(code1 & LEFT_EDGE){
	   	f =m*(xmin-p1.x);
	   	p1.x = xmin;
	   	p1.y += f;
	 	cout<<"f="<<f<<endl;
	   	cout<<"line clipped from left"<<endl;
	   	cout<<p1<<p2;
	  }
	  else if(code1 & RIGHT_EDGE){
	    	f=m*(xmax-p1.x);
	  	p1.x = xmax;
	  	p1.y += f; 
	  	cout<<"line clipped from right"<<endl;
	  	cout<<p1<<p2<<endl;
	  }
	  else if(code1 & BOTTOM_EDGE){
	  	f = (ymin-p1.y)/m;
	  	p1.y = ymin;
	  	cout<<"f="<<f<<endl;
	  	p1.x += f;
	  	cout<<"line clipped from bottom"<<endl;
	  	cout<<p1<<p2;
	  }
	  else if(code1 & TOP_EDGE){
		f = (ymax-p1.y)/m;
	  	p1.y = ymax;
	  	p1.x += f;
	  	cout<<"line clipped from top"<<endl;
	  	cout<<p1<<p2;
	  }
	  }
	  else{
	   if(code1 & BOTTOM_EDGE)
	   	p1.y = ymin;
	   else if(code1 & TOP_EDGE)
	   	p1.y = ymax;		
	  }//end else
	 }//end else 
	}//end while
	  if(draw){
	  	glBegin(GL_LINES);
	  	glVertex3f(p1.x,p1.y,0.0);
	  	glVertex3f(p2.x,p2.y,0.0);
	  	glEnd();
	  	glFlush();
	  	cout<<"line is drawn"<<endl;
	  	cout<<p1<<p2;
	  }
}	  	
	     
void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,0.0,0.0);	
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
	glutCreateWindow("Cohen-Sutherland Line Clipping");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
}
		
