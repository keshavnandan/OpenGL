#include "point.h"

point point::Translate(float tx,float ty,float tz){
	 Matrix T(4,4),P(4,1),P1(4,1);
	 int i,j;
	 for(i=0;i<4;i++)T[i][i]=1;
	 T[0][3]=tx;T[1][3]=ty;T[2][3]=tz;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1 = T*P;
	 point p(P1);
	 return p;
}	 

point point::RotateX(float theta){
	 Matrix R(4,4),P1(4,1),P(4,1);
	 R[1][1]=cos(theta);R[1][2]=-sin(theta);
	 R[2][1]=-R[1][2];R[2][2]=R[1][1];
	 R[0][0]=1;
	 R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}	

point point::RotateY(float theta){
	 Matrix R(4,4),P1(4,1),P(4,1);
	 R[0][0]=cos(theta);R[0][2]=sin(theta);
	 R[2][0]=-R[0][2];R[2][2]=R[0][0];
	 R[1][1]=1;
	 R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}	

point point::RotateZ(float theta){
	 Matrix R(4,4),P1(4,1),P(4,1);
	 R[0][0]=cos(theta);R[0][1]=-sin(theta);
	 R[1][0]=-R[0][1];R[1][1]=R[0][0];
	 R[2][2]=1;
	 R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}	

point point::Scale(float sx,float sy,float sz){
	 Matrix S(4,4),P1(4,1),P(4,1);
	 S[0][0]=sx;S[1][1]=sy;S[2][2]=sz;S[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=S*P;
	 point p(P1);
	 return p;
}	

point point::ReflectXY(){
	 Matrix R(4,4),P(4,1),P1(4,1);
	 R[0][0]=1;R[1][1]=1;R[2][2]=-1;R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}
point point::ReflectYZ(){
	 Matrix R(4,4),P(4,1),P1(4,1);
	 R[0][0]=-1;R[1][1]=1;R[2][2]=1;R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}

point point::ReflectZX(){
	 Matrix R(4,4),P(4,1),P1(4,1);
	 R[0][0]=1;R[1][1]=-1;R[2][2]=1;R[3][3]=1;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=R*P;
	 point p(P1);
	 return p;
}	 

point point::ShearZ(float a,float b){
	 Matrix S(4,4),P(4,1),P1(4,1);
	 S[0][0]=1;S[1][1]=1;S[2][2]=1;S[3][3]=1;S[0][2]=a;S[1][2]=b;
	 P[0][0]=x;P[1][0]=y;P[2][0]=z;P[3][0]=1;
	 P1=S*P;
	 point p(P1);
	 return p;
}

ostream& operator<<(ostream &os,const point &P){
	 cout<<"x: "<<P.x<<" y: "<<P.y<<" z: "<<P.z<<endl;
}	        	  

point point::operator+(const point& p){
	 point t;
	 t.x=x+p.x;t.y=y+p.y;t.z=z+p.z;
	 return t;
}

point& point::operator=(const point& p){
	  if(this!=&p){
	  	x=p.x;y=p.y;z=p.z;
	  }
	  return *this;
}

point point::operator-(const point& p){
	  point t;
	  t.x=x-p.x;t.y=y-p.y;t.z=z-p.z;
	  return t;
}		 

point point::operator*(const point& p){
	 point t;
	 t.x=x*p.x;t.y=y*p.y;t.z=z*p.z;
	 return t;
}

point operator*(float k,const point& p){
	 point t;
	 t.x=k*p.x;t.y=k*p.y;t.z=k*t.z;
}	 	  	 

point point::operator*(const float k){
	point t;
	t.x=x*k;t.y=y*k;t.z=z*k;
	return t;
}	
	
	
