#include<iostream>
#include<cstdlib>
#include<cmath>
#include<GL/glut.h>
#include<GL/gl.h>
#define pi 3.14159
using namespace std;
float xmin,xmax,ymin,ymax;
int n;
void wait(float t){
	clock_t w;
	float k = t*CLOCKS_PER_SEC;
	w = (clock()+t*CLOCKS_PER_SEC);
	while(clock()<w){}
}	

void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,2.0,0.0,2.0,0.0,0.0);	
	gluLookAt(0.0, 0.0, 0.0, -2.0, -4.0, -6.0, 0.0, 1.0, 0.0);
}

void drawCircle(float x,float y,float z,float r){
	int i,n = 250;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	for(int j=0;j<60/2;j++){
	for(i=0;i<n;i++){
	float theta = (2*i*pi)/n;
	glVertex3f(x+r*cos(theta),y+(j/100),z+r*sin(theta));
	glVertex3f(x+r*cos(theta),y-(j/100),z+r*sin(theta));
	}
	}
	glEnd();
	glFlush();
}	

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(2);
	xmin=-0.5;ymin=-0.4;xmax=0.5;ymax=0.4;
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.0,0.0,0.60);
	glVertex3f(0.0,0.60,0.60);	
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.60,0.0);
	glColor3f(0.3,0.3,0.3);
	glVertex3f(0.60,0.0,0.0);		
	glVertex3f(0.60,0.60,0.0);
	glEnd();
	glColor3f(0.60,0.60,0.60);
	glBegin(GL_QUADS);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.60,0.0,0.0);
	glVertex3f(0.60,0.0,0.60);	
	glVertex3f(0.0,0.0,0.60);
	glEnd();		
	glFlush();
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
	glEnable (GL_LINE_STIPPLE);
	glLineStipple (2, 0x00FF); // dashed 
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.60,0.60,0.0);
	glVertex3f(0.60,0.60,0.60);
	glVertex3f(0.0,0.60,0.60);		
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.60,0.0,0.60);		
	glVertex3f(0.60,0.60,0.60);
	glEnd();			
	glDisable (GL_LINE_STIPPLE);
	glFlush ();

	int i,n = 500;
	float x,y,z,k=60.0/2;
	x = y = z = k/100;
	glColor3f(1.0,1.0,0.0);
	wait(2.0);
	for(int j=0;j<=(int)k;j++){
	glBegin(GL_POINTS);
	glPointSize(3);
	float r = (float)j/100;
	for(i=0;i<n;i++){
	cout<<"i = "<<i<<"\tj = "<<j<<endl;
	float theta = (2*i*pi)/(float)n;
	cout<<"theta = "<<theta<<endl;
//	glBegin(GL_POINTS);
	glVertex3f(x+r*cos(theta),y+r,z+r*sin(theta));
	glVertex3f(x+r*cos(theta),y-r,z+r*sin(theta));
//	glEnd();
//	glFlush();
	cout<<"x = "<<r*cos(theta)<<"\ty = "<<y+r<<"\tz = "<<z+r*sin(theta)<<endl;
	}
	glEnd();
	glFlush();
	
	wait(0.15);
	}

//	while(true);
	
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(250,300);
	glutCreateWindow("Cyrus Beck Line Clipping");
	Initialize();
//	cout<<"Enter the coordinates of diagonal of Rectangle"<<endl;
//	cin>>xmin>>xmax>>ymin>>ymax;
	glutDisplayFunc(Draw);
	glutMainLoop();
}

