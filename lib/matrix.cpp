#include "matrix.h"


Matrix::Matrix(int r,int c)
 {
     row=r;
     column=c;
     allocate();
 }

 void Matrix::allocate()
 { 
   int m=row,n=column;
   p=new float*[m];
   for(int i=0;i<m;i++)
   *(p+i)=new float[n];
   for(int k=0;k<m;k++)
   for(int j=0;j<n;j++)
   put_value(k,j,0.0);
 }

 float Matrix::get_value(int row,int col)
 {
     return(p[row][col]);
 }

  void Matrix::put_value(int row,int col,float item)
  {
      p[row][col]=item;
  }

  float Matrix::det()
  {
   ///assert
   if(row!=column)
     cerr<<"row and column of matrix are unequal";
   
   else{
   int order=row;
   if(order==1)
     
   return p[0][0];
   int i,j,sum=0;
   for(int k=0;k<order;k++)
   {
       int l=0,m=0;
       Matrix M(order-1,order-1);
       for(i=1;i<order;i++)
       {
           for(j=0;j<order;j++)
         {
            if(j==k)
            continue;
            M.put_value(l,m,get_value(i,j));
            m++;
         }
         m=0;
         l++;
         }
         sum+=(pow(-1,k)*M.det()*get_value(0,k));
   }
         return sum; 
   }      
  }
  
  Matrix::~Matrix()
  {
   for(int i=0;i<row;i++){
   delete []*(p+i);
   //cout<<"row "<<i<<" is deleted"<<endl;
   }
   delete []p; 
   //cout<<"pointer p is deleted now"<<endl; 
  }
  
  Matrix& Matrix::operator=(const Matrix& m)
  {
  if(this!=&m){
  
  if(row!=m.row||column!=m.column)
  {
   cerr<<"both matrices have different row and column";
     
  }
  else{
  for(int i=0;i<row;i++)
  for(int j=0;j<column;j++)
  p[i][j]=m.p[i][j];
  }
  
  return *this;
  }
  }
  
 Matrix::Matrix(Matrix& m) {
  row = m.row;
  column=m.column;
  allocate(); 	
  if(row!=m.row||column!=m.column)
  {
  cerr<<"both matrices have different row and column";//error
  }
  else{
  for(int i=0;i<row;i++)
  for(int j=0;j<column;j++)
  p[i][j]=m.p[i][j];
  }
 }
 
  Matrix::Matrix()
  {
  row=1,column=1;
  }
  
  Matrix operator+(const Matrix& P,const Matrix& Q){
  
  if(P.row!=Q.row||P.column!=Q.column)
  {
   cerr<<"both matrices have different row and column";//error
  }
  else{
  int row=P.row,column=Q.column;
  Matrix M(row,column);
  for(int i=0;i<row;i++)
  for(int j=0;j<column;j++)
  M.p[i][j]=P.p[i][j]+Q.p[i][j];
  return M;
  }
  }
  
  Matrix operator*(const Matrix& P,const Matrix& Q){
  
  if(P.column!=Q.row)
  {
   cerr<<"both matrices cannot be multiplied";//error
  }
  else{
  int row=P.row,column=Q.column;
  Matrix M(row,column);
  
  for(int i=0;i<row;i++){
  for(int j=0;j<column;j++){
  for(int k=0;k<P.column;k++)
     M.p[i][j]=M.p[i][j]+(P.p[i][k])*(Q.p[k][j]);
   }
  } 
  return M;
  }
  }
  
  ostream& operator<<(ostream &os,const Matrix &M){
  int m=M.row,n=M.column;
  cout<<"row of Matrix is "<<m<<endl<<"col of matrix is "<<n<<endl;
  for(int i=0;i<m;i++){
     for(int j=0;j<n;j++)
       os<<M.p[i][j]<<"\t";
       if(!os)
         cerr<<"error writing to output";
       os<<endl;
      } 
   return os;
  }    
        
  istream& operator>>(istream &is,Matrix &M){
  int m=M.row,n=M.column;
  for(int i=0;i<m;i++){
     for(int j=0;j<n;j++)
       is>>M.p[i][j];
       if(!is){
         cerr<<"error reading input";
         exit(1);
       }  
      } 
   return is;
  }	       
       
 	   	       
