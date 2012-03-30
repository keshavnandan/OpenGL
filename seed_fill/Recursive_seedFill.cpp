#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include<time.h>
void wait(float seconds);

#define round(a)  ((int)(a+ (a>0)?0.5f:-1*0.5f))
const int NUMBER_VERTICES=100;
const int WINDOW_HEIGHT=500;
const int WINDOW_WIDTH=500;
float COLOR_R=1.0;
float COLOR_G=1.0;
float COLOR_B=1.0;
int n;

using namespace std;

void putpixel(int x, int y){
glBegin(GL_POINTS);
glPointSize(3);
glVertex2d((double)x/WINDOW_HEIGHT*2,(double)y/WINDOW_HEIGHT*2);
//glVertex2d((double)x/WINDOW_HEIGHT*2,(double)y/100);
glEnd();
glFlush();
}

struct vertex
{
	int x;
	int y;
};

vertex points[NUMBER_VERTICES];
vertex seed;

void seedfill(int x,int y)
{
float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	if((color[0]==COLOR_R && color[1]==COLOR_G && color[2]==COLOR_B))
		return;
	
	if((x>=WINDOW_WIDTH && y>=WINDOW_HEIGHT)||(x<0||y<0) )
		return;
	cout<<x<<" "<<y<<endl;
	//wait(0.0001);
	putpixel(x-WINDOW_HEIGHT/2,y-WINDOW_HEIGHT/2);
	seedfill(x+1,y);
	seedfill(x-1,y);
	seedfill(x,y+1);
	seedfill(x,y-1);
}

void SeedFill()
{
	float color[3];
	//glReadPixels(seed.x,seed.y,1,1,GL_RGB,GL_FLOAT,color);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<n;i++)
		glVertex2f((double)(points[i].x-WINDOW_HEIGHT/2)/WINDOW_HEIGHT*2,(double)(points[i].y-WINDOW_HEIGHT/2)/WINDOW_HEIGHT*2);
	glEnd();
	seedfill(seed.x,seed.y);
}    

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(COLOR_R,COLOR_G,COLOR_B);
   SeedFill();
   glFlush();
}  

void init()
{
    glClearColor(0,0,0,0);
}
       
int main(int argc, char** argv)
{
   fstream file("input_seedfill.txt");	
   if(!file)
   cerr<<"error opening the file"; 
   cout<<"getting no. of edges:\n";
   file>>n;
   for(int i=0;i<n;i++){
	file>>points[i].x>>points[i].y;
	points[i].x+=WINDOW_HEIGHT/2;
	points[i].y+=WINDOW_HEIGHT/2;
	}
   cout<<"getting the  point:";
   file>>seed.x>>seed.y;	
	seed.x+=WINDOW_HEIGHT/2;seed.y+=WINDOW_HEIGHT/2;
   glutInit(&argc, argv);
   glutInitWindowSize (WINDOW_WIDTH,WINDOW_HEIGHT); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Seed Fill Polygon Filling Algorithm using Recursion");
   init();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;
}

void wait(float t){
	clock_t w;
	int k = t*CLOCKS_PER_SEC;
	w=clock()+t*CLOCKS_PER_SEC;
	while(clock()<w){}
}	
