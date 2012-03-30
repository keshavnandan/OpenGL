#include<GL/glut.h>
#include<cstdio>
#include<cmath>
#include<ctime>
#include "../lib/matrix.h"
#include "../lib/point.h"
void wait(float seconds);
int MODE;
#define pi 3.14159

void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void Initialize(){
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepth(1.0);
//	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(left,right,bottom,top,near,far);	
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	//gluLookAt(camera position,camera aim,camera up look);
	gluLookAt(0.0, 0.0, 0.0, -1.0, -2.0, -3.0, 0.0, 1.0, 0.0);

}

void Draw(){
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPointSize(2);
	glColor3f(1.0,0.0,0.0);

	float P1[8][3],T[8][3];	
	float P[8][3] = { {0.0,0.0,0.0},
	{0.0,0.0,0.2},
	{0.2,0.0,0.2},
	{0.2,0.0,0.0},
	{0.2,0.2,0.0},
	{0.0,0.2,0.0},
	{0.0,0.2,0.2},
	{0.2,0.2,0.2}
	};	
	int j=0;
	wait(1.2);
	while(true){


	int i;
	float tx,ty,tz;
	float theta;
	float sx,sy,sz;
	float a,b;
	cout<<"\tEnter 1 for Translation.\n\tEnter 2 for Rotation about Z axis.\n\tEnter 3 for Scaling.\n\tEnter 4 for Shearing.\n\tEnter 5 for Reflection about XY-Plane.\n\n";
	cout<<"\tEnter your choice here\t\t";
	cin>>i;
	switch(i){
	case 1:
	
	cout<<"Enter the translations along x-axis,y-axis,z-axis(value between -0.5 to 0.5)"<<endl;
	cin>>tx>>ty>>tz;
	for(int k=0;k<8;k++)
	   {
	    MODE = 1;
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.Translate(tx,ty,tz);
	    P1[k][0]=p2.x;P1[k][1]=p2.y;P1[k][2]=p2.z;
	    }
	 break;
	 case 2:
	 
	 cout<<"Enter the angle of rotation in degrees"<<endl;
	 cin>>theta;
	 theta=theta*pi/360;
	 for(int k=0;k<8;k++)
	   {
	    MODE = 2;
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.RotateZ(theta);
	    P1[k][0]=p2.x;P1[k][1]=p2.y;P1[k][2]=p2.z;
	    }
	 break;
	 case 3:
	 
	 cout<<"Enter the scaling factors along X-axis,Y-axis,Z-axis"<<endl;
	 cin>>sx>>sy>>sz;
	 for(int k=0;k<8;k++)
	   {
	    MODE = 3;
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.Scale(sx,sy,sz);
	    P1[k][0]=p2.x;P1[k][1]=p2.y;P1[k][2]=p2.z;
	    }
	 break;
	 case 4:
	 
	 cout<<"Enter the shearing factors a and b"<<endl;
	 cin>>a>>b;
	 for(int k=0;k<8;k++)
	   {
	    MODE = 4;
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.ShearZ(a,b);
	    P1[k][0]=p2.x;P1[k][1]=p2.y;P1[k][2]=p2.z;
	    }
	 break;
	 case 5:
	 for(int k=0;k<8;k++)
	   {
	    MODE=5;
	    point p1;
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.ReflectXY();
	    P1[k][0]=p2.x;P1[k][1]=p2.y;P1[k][2]=p2.z;
	    }
	 break;
	 default:
	 exit(0);
	 break;
	 
    }
	
	
	 
	
	int n=80;
	for(int j=0;j<2*n;j++){
	
	if(j<n){
	if(MODE==1||MODE==3||MODE==4){
	for(int u=0;u<8;u++)
	for(int v=0;v<3;v++)
	   T[u][v]=P[u][v]+(P1[u][v]-P[u][v])*j/n;
	   wait(0.1);
	 }
	 else if(MODE==2){
	    point p1;
	    for(int k=0;k<8;k++){
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.RotateZ(2*theta*j/n);
	    T[k][0]=p2.x;T[k][1]=p2.y;T[k][2]=p2.z;
	    wait(0.01);
	  }  
	 }
	else if(MODE==5){
		point p1;
	     for(int k=0;k<8;k++){
	     p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	     point p2=p1.ReflectXY();
	     T[k][0]=p2.x;T[k][1]=p2.y;T[k][2]=p2.z;
	  }  
	}
	}
	else if(j==n)
	wait(1.5);
	else{
	if(MODE==1||MODE==3||MODE==4){
	for(int u=0;u<8;u++)
	for(int v=0;v<3;v++)
	   T[u][v]=P1[u][v]+(P[u][v]-P1[u][v])*(j-n)/n;
	   wait(0.1);
	 }  
	else if(MODE==2){
	    point p1;
	    for(int k=0;k<8;k++){
	    p1.x=P[k][0];p1.y=P[k][1];p1.z=P[k][2];
	    point p2=p1.RotateZ(theta*2*(2*n-j)/n);
	    T[k][0]=p2.x;T[k][1]=p2.y;T[k][2]=p2.z;
	    wait(0.01);
	  }  
	 } 
	 
	}
	wait(0.002);
	glPushMatrix();

	//drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.7,0.0,0.0);
	glVertex3f(-0.7,0.0,0.0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.7,0.0);		
	glVertex3f(0.0,-0.7,0.0);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);		
	glVertex3f(0.0,0.0,0.7);				
	glVertex3f(0.0,0.0,-0.7);				
	glEnd();
	glFlush();	
	//drawing cube
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
	glColor3f(0.3,0.3,0.3);
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
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_QUADS);
	glVertex3fv(T[4]);	
	glVertex3fv(T[5]);
	glVertex3fv(T[6]);
	glVertex3fv(T[7]);
	glEnd();
	glFlush();	
	glFinish();
	glPopMatrix();
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	cout<<"x = "<<T[7][0]<<"\t y = "<<T[7][1]<<"\t z = "<<T[7][2]<<endl;
	}
	char c;
	printf("would you like to exit (y/n)");
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	exit(1);	
	}
}		


int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(950,950);
	glutInitWindowPosition(200,200);
	
	glutCreateWindow("3DTransformation");
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
