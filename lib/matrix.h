#ifndef MATRIX_H
#define MATRIX_H
#include<cstdio>
#include<cmath>
#include<stdexcept>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

class Matrix{
    public:
    
    float get_value(int row,int col);
    void put_value(int row,int col,float item);
    float* operator[](const int i){return p[i];}
    Matrix& operator=(const Matrix& m);
    float det();
    
    Matrix(int,int);
    Matrix(Matrix&);
    Matrix();
    ~Matrix();
    
    friend Matrix operator+(const Matrix& P,const Matrix& Q);
    friend Matrix operator*(const Matrix& P,const Matrix& Q);
    friend ostream& operator<<(ostream &os,const Matrix &M);
    friend istream& operator>>(istream &is,Matrix &M);
    
    /*Matrix Translate(float tx,float ty,float tz);
    Matrix RotateZ(float theta);
    Matrix Scale(float sx,float sy,float sz);
    Matrix ReflectXY();
    Matrix ShearZ(float a,float b);*/
    private:
    void allocate();
    int row,column;
    float **p;
};

 
#endif
