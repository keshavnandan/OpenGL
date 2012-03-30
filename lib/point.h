#ifndef POINT_H
#define POINT_H
#include "matrix.h"

struct point{
	  float x,y,z;
	  point(float xx=0,float yy=0,float zz=0):x(xx),y(yy),z(zz){/*P[0][0]=x;P[1][0]=y;P[2][0]=z;*/}
	  point(Matrix& M){x=M[0][0];y=M[1][0];z=M[2][0];}
	  point operator+(const point& p);
	  point operator-(const point& p);
	  point operator*(const point& p);
	  point operator*(const float k);
	  point& operator=(const point& p);
	  point Translate(float tx,float ty,float tz);
	  point RotateX(float theta);
	  point RotateY(float theta);
	  point RotateZ(float theta);	  
       point Scale(float sx,float sy,float sz);
       point ReflectXY();
       point ReflectYZ();
       point ReflectZX();
       point ShearZ(float a,float b); 
       friend ostream& operator<<(ostream &os,const point &P);
       friend point operator*(float k,const point& p);	  
};

#endif 
