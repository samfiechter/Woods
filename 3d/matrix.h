#ifndef SAM_MATRIX_CLASS_H
#define SAM_MATRIX_CLASS_H 1
// #pragma interface
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>

/*
matrix.h class template for matrix calculations.

Sam Fiechter 08-02
*/

using namespace std;
template <class T> 
class matrix {

#define t_column vector<T>
#define t_matrix vector<t_column>
 private:
  t_matrix * this_matrix ;			       /* pointer to matrix data*/
 public:
  int m,n;					       /* m= cols n = rows */
  matrix();
  matrix(const matrix<T> &);
  virtual ~matrix();

  int resize(const int & m, const int & n);	       /* resize matrix to m,n */
  virtual int copy (const matrix<T> & );	       /* clone matrix */
  virtual const matrix<T> & operator=(const matrix<T> & a); 
						       /* this.copy(a) */
  virtual const matrix<T> & operator*=(const matrix<T> & b);
  						       /* multiply -> this = this*b */

  virtual const matrix<T> & lmul(const matrix<T> & b); /* left multiply -> this = b*this */
  
  virtual const matrix<T> & identity(const int & n);   /* create a n by n matrix  */
						       /* with 1 for each diagonal and */
						       /* zero else where */

  virtual const matrix<T> & transpose();	       /* rotate matrix 90 degrees*/
  const matrix<T> & elem_multiply(const matrix<T> &);  /* element by element mulitply*/
  const matrix<T> & scal_multiply(const T &);	       /* multiply each element by constant*/
  const matrix<T> & operator+=(const matrix<T> & );    /* add two matrix of same dim */
  const matrix<T> & operator-=(const matrix<T> & );    /* subtract two matrix of same dim */

  int push_row(const matrix<T> &);		       /* push rows onto the end of  */
												/* matrix */
  matrix<T> pop_row(int n);						/* pop n rows from the  end of */
  matrix<T> shift_row(int n);					/* like the pops but from fromnt */
  matrix<T> shift_col(int n);
						       /* matrix */
  int push_col(const matrix<T> &);		       /* push columns onto the end of */
						       /* matrix */
  matrix<T> pop_col(int n);			       /* pop n columns from the end of matrix */
  int push(const T &);				       /* push a row of const on end */
  T det();					       /* calcualte the determinant of this */


  virtual int save(const char * filename);	       /* save and load from disk */
  virtual int load(const char * filename);		       
  
  vector<T> & operator[](const int & a){	       /* to get a pointer to the second */
    return( (*this_matrix)[a]);			       /* column value of the first row */
  };						       /* of matrix a use a[0][1] */

  const T & c_item(const matrix<T> & z, const int & a, const int & b) {
    return( (*z.this_matrix)[a][b]);		       /* get a constant value from z */
  };


};

						       
/********Binary and not- Class Def's*********/
template<class T>
matrix<T> operator*(const matrix<T> & a, const matrix<T> & b){
  matrix<T> c;
  c=a;
  c*=b;
  return(c);
}

template<class T>
matrix<T> operator*(const matrix<T> & a, const T & b){
  matrix<T> c;
  c=a;
  c.scal_multiply(b);
  return(c);
}

template<class T>
matrix<T> operator*(const T & b,const matrix<T> & a){
  matrix<T> c;
  c=a;
  c.scal_multiply(b);
  return(c);
}

template<class T>
matrix<T> operator+(const matrix<T> & a, const matrix<T> & b){
  matrix<T>  z = a;
  z += b;
  return(z);
}

template<class T>
matrix<T> operator-(const matrix<T> & a, const matrix<T> & b){
  matrix<T> z =a;
  z -= b;
  return(z);
}

template<class T>				       /* copy and transpose */
matrix<T> transpose(matrix<T> a){		       /* return a copy of the */
  return(a.transpose());			       /* copied transpose */
}


template<class T>				       /* stringify */
ostream& operator<<(ostream & outStm,  matrix<T> & m) {
  int i,j;
    outStm << m.m << "\t" << m.n << endl;
    for(j=0 ; j<m.n ; j++) {
        for(i=0 ; i<m.m ; i++) {
            outStm << m[i][j];
            if (i != (m.m - 1))
                outStm << "\t";
        }
        outStm << endl;
    }
  return (outStm);
}

template<class T>				       /* stringify */
istream& operator>>(istream & in, const matrix<T> & m) {
    int i,j;
    in >> i;
    in >> j;
    m.resize(i,j);
    for(j=0 ; j<m.n ; j++) {
        for(i=0 ; i<m.m ; i++) {
            in >> m[i][j];
        }
    }
    return (in);
}


/********Class Definitions*********/

template<class T>
matrix<T>::matrix(){
  this_matrix = new(t_matrix);
  m = 0;    
  n = 0;
  return;					       /* init to empty matrix */
}


template<class T>
matrix<T>::matrix(const matrix<T> & a){
  this_matrix = new(t_matrix);
  copy(a);
  return;
}


template<class T>
matrix<T>::~matrix() {
  delete(this_matrix);
  return;					       /* destruct */
}

template<class T>
int matrix<T>::resize(const int & rows, const int & cols) {
  int i;
  m = rows; n = cols;
  this_matrix->resize(m);
  for (i = 0 ; i < rows; i ++) {
    (*this_matrix)[i].resize(n);
  }
  return(1);
}



template<class T>
int matrix<T>::copy(const matrix<T> & a) {
  int i,j;
  m = a.m;
  n = a.n;
  this_matrix->resize(m);
  for(i=0;i<m;i++){
    (*this_matrix)[i].resize(n);
    for(j=0;j<n;j++){
      (*this_matrix)[i][j] = (*a.this_matrix)[i][j];   /* note element values are cloned */
						       /* to the extent that of T = operator */
    }
  }
  return(1);
}


template<class T>
const matrix<T> & matrix<T>::operator=(const matrix<T> & a) {
  copy(a);
  return(*this);
}

template<class T>
const matrix<T> & matrix<T>::identity(const int & M){
  int i,j;
  m = n = M;
  this_matrix->resize(M);
  for(i=0;i<M;i++){
    (*this_matrix)[i].resize(M);
    for(j=0;j<M;j++){ 
      if(i != j)
	(*this_matrix)[i][j] = (T) 0;
      else
        (*this_matrix)[i][j] = (T) 1;
    }

  }
  return(*this);
}

template<class T>
const matrix<T> &  matrix<T>::transpose() {
  int i,j;
  t_matrix * r;					       
  i = m;					       /* swap i and j */
  m = n;
  n = i;
  r = new(t_matrix);				       /* create new data struct */
  r->resize(m);
  for(i=0; i<m; i++){
    (*r)[i].resize(n);
    for(j=0; j<n; j++){     
      (*r)[i][j] = (*this_matrix)[j][i];	       /* copy */
    }
  }
  delete(this_matrix);				       /* switch new and old */
  this_matrix = r;
  return(*this);
}


template<class T>
const matrix<T> & matrix<T>::elem_multiply(const matrix<T> & b){
  int i,j;
  if (m != b.m ||  n != b.n) 
    return(*this);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      (*this_matrix)[i][j] *= (*b.this_matrix)[i][j] ;
    }
  }
  return(*this);
}

template<class T>
const matrix<T> & matrix<T>::scal_multiply(const T & b){
  int i,j;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      (*this_matrix)[i][j] *= b ;
    }
  }
  return(*this);
}

template<class T>
const matrix<T> & matrix<T>::operator+=(const matrix<T> & b){
  int i,j;
  if (m != b.m ||  n != b.n) 
    return(*this);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      (*this_matrix)[i][j] += (*b.this_matrix)[i][j] ;
    }
  }
  return(*this);
}
 
template<class T>
const matrix<T> & matrix<T>::operator-=(const matrix<T> & b){
  int i,j;
  if (m != b.m ||  n != b.n) 
    return(*this);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      (*this_matrix)[i][j] -= (*b.this_matrix)[i][j] ;
    }
  }
  return(*this);
}

template<class T>
T matrix<T>::det() {
  matrix<T> z;
  int i,j;
  if(m != n) 
    return((T) 0);
  switch (m) {
  case 1:
    return((*this_matrix)[0][0]);		       /* det of 1x1 matrix = value */
  case 2:
    return(((*this_matrix)[0][0]*(*this_matrix)[1][1]) /* 2x2 det */
	   -((*this_matrix)[1][0]*(*this_matrix)[0][1]));
  case 3:					       /* 3x3 det */
    return( ((*this_matrix)[0][0]*(*this_matrix)[1][1]*(*this_matrix)[2][2]) +
	    ((*this_matrix)[1][0]*(*this_matrix)[2][1]*(*this_matrix)[0][2]) +
	    ((*this_matrix)[2][0]*(*this_matrix)[0][1]*(*this_matrix)[1][2]) -
	    ((*this_matrix)[0][0]*(*this_matrix)[2][1]*(*this_matrix)[1][2]) -
	    ((*this_matrix)[1][0]*(*this_matrix)[0][1]*(*this_matrix)[2][2]) -
	    ((*this_matrix)[2][0]*(*this_matrix)[1][1]*(*this_matrix)[0][2]));
  default:					       /* if matrix is larger than 3x3  */
						       /* calcuate recursively using Knuth */
    z.resize(m-1,m-1);				       /* Vol 2 Page 498 */
    if ((*this_matrix)[0][0] != (T) 0) { 
      for(i=0;i<(m-1);i++)
	for(j=0;j<(m-1);j++) 
	  z[i][j] = (*this_matrix)[i+1][j+1] - 
	    ((*this_matrix)[0][j+1] * (*this_matrix)[i+1][0] / (*this_matrix)[0][0]);
      return((*this_matrix)[0][0]* z.det());  
    } else {
      z = (*this);
      for(i=1; i<m ;i++)			       /* row reduction. */
	if(z[0][i] != 0) {			       /* the elementary operation of */
	  for(j=0;j<m;j++)			       /* subtracting a multiple of one */
	    z[j][0] -= z[j][i];			       /* row from another leaves a*/
	  i=m;					       /* determinant unchanged. */
	}
      if(z[0][0] == (T) 0)			       /* if rows are LC of each other */
	return(0);				       /* then det is zero */
      else
	return(z.det());			       /* return det of smaller matrix */
    }	  
  }
}

template<class T>				       /* (this) = (this) * b */
const matrix<T> & matrix<T>::operator*=(const matrix<T> & b){  
  int i,j,k,q;					       /* loops */
  t_matrix * r;
  if (m != b.n )				       /* dim check */
    return(*this);

  r = new(t_matrix);				       /* create new matrix struct */
  q = m;
  m = b.m;

  r->resize(m);
  for(i=0;i<m;i++){
    (*r)[i].resize(n);
    for(j=0;j<n;j++){
      (*r)[i][j] = 0;
      for(k=0;k<q;k++) {			       /* add and sum */
	(*r)[i][j] += (*this_matrix)[k][j] * (*b.this_matrix)[i][k] ;
      }
    }
  }
  delete(this_matrix);				       /* switch new and old */
  this_matrix = r;
  return(*this);
}

template<class T>
const matrix<T> & matrix<T>::lmul(const matrix<T> & b){  // (this) = b * (this)
  int i,j,k,q;
  t_matrix * r;

  if (n != b.m ) 
    return(*this);

  r = new(t_matrix);
  q = n;
  n = b.n;

  r->resize(m);
  for(i=0;i<m;i++){
    (*r)[i].resize(n);
    for(j=0;j<n;j++){
      (*r)[i][j] = 0;
      for(k=0;k<q;k++) {
	(*r)[i][j] +=  (*b.this_matrix)[k][j] * (*this_matrix)[i][k] ;
      }
    }
  }
  delete(this_matrix);
  this_matrix = r;
  return(*this);
}

template<class T>
int matrix<T>::push_row(const matrix<T> & pm){
  int i,j;
  if (n ==0 || m == 0){
    copy(pm);
    return(1);
  }
  if( pm.n == 0  || m < pm.m)					
    return(0);							 
  for(i=0;i<m;i++) {					
    for(j=n;j<n+pm.n;j++){				
      (*this_matrix)[i].resize(n+pm.n);
      (*this)[i][j] = (*this).c_item(pm,i,(j-n));
    }
  }
  n += pm.n;
  return(1);
}

template<class T>
matrix<T> matrix<T>::pop_row(int k){
  matrix<T> out;
  int i,j;
  t_matrix * temp_t;
  if(k<0 || k>n)
    k=0;
  if(k == n ){
    temp_t = this_matrix;
    this_matrix = out.this_matrix;
    out.this_matrix = temp_t;
    i=out.m;
    j=out.n;
    out.m = m;
    out.n = n;
    m =i;
    n=j;
    resize(out.m,0);
    return(out);
  } 
  out.resize(m,k);  

  for (i=0;i<m;i++) {
    for(j=0;j<k;j++){
      out[i][j]= (*this_matrix)[i][(n-k)+j];
    }
  }
  resize(m,n-k);
  return(out);
}


template<class T>
matrix<T> matrix<T>::shift_row(int k){
  matrix<T> out;
  int i,j;
  t_matrix * temp_t;
  if(k<0 || k>n)
    k=0;
  if(k == n ){
    temp_t = this_matrix;
    this_matrix = out.this_matrix;
    out.this_matrix = temp_t;
    i=out.m;
    j=out.n;
    out.m = m;
    out.n = n;
    m =i;
    n=j;
    resize(out.m,0);
    return(out);
  } 
  out.resize(m,k);  

  for (i=0;i<m;i++) {
    for(j=0;j<k;j++){
      out[i][j]= (*this_matrix)[i][j];
    }
    for(j=k;j<n;j++){
      (*this_matrix)[i][j-k] = (*this_matrix)[i][j];
    }
  }
  resize(m,n-k);
  return(out);
}


template<class T>
matrix<T> matrix<T>::shift_col(int k){
  matrix<T> out;
  int i,j;
  t_matrix * temp_t;
  if(k<0 || k>m)
    k=0;
  if(k == m ){
    temp_t = this_matrix;
    this_matrix = out.this_matrix;
    out.this_matrix = temp_t;
    i=out.m;
    j=out.n;
    out.m = m;
    out.n = n;
    m =i;
    n=j;
    resize(0,out.n);
    return(out);
  } 
  out.resize(k,n);  
  for(j=0;j<n;j++){
    for (i=0;i<k;i++) {
      out[i][j]= (*this_matrix)[i][j];
    }
    for (i=k;i<n;i++) {
      (*this_matrix)[i-k][j] = (*this_matrix)[i][j];
    }
  }
  resize(m-k,n);
  return(out);
}

template<class T>
int matrix<T>::push_col(const matrix<T> & pm){
  int i,j;
  if (n ==0 || m == 0){
    copy(pm);
    return(1);
  }
  if ( pm.m == 0 || n < pm.n )
    return(0);
  this_matrix->resize(m+pm.m);
  for (i=0;i < pm.m ;i++){
    (*this_matrix)[i+m].resize(n);
    for (j=0;j<n;j++) 
      (*this_matrix)[i+m][j] = c_item(pm,i,j);
  }
  m += pm.m;
  return(1);
}


template<class T>
matrix<T> matrix<T>::pop_col(int k){
  matrix<T> out;
  t_matrix * temp_t;
  int i,j;
  if(k<0 || k>m)
    k=0;
  if(k == n ){
    temp_t = this_matrix;
    this_matrix = out.this_matrix;
    out.this_matrix = temp_t;
    i=out.m;
    j=out.n;
    out.m = m;
    out.n = n;
    m =i;
    n=j;
    resize(0,out.n);
    return(out);
  } 
  out.resize(k,n);
  m -= k;
  for(i=0;i<k;i++)
    for(j=0;j<n;j++){
      out[i][j]= (*this_matrix)[m+i][j];
    }
  this_matrix->resize(m);
  return(out);
}

template<class T> int matrix<T>::push(const T & cst){
  int i;
  for(i=0;i<m;i++){
    (*this_matrix)[i].resize(n+1);
    (*this)[i][n] = cst;
  }
  n++;
  return(1);
}


template<class T>
int matrix<T>::save(const char * filename) {
  fstream file;
  file.open(filename,ios::out);
  file << m << "\t" <<n <<endl << (*this);
  file.close();
  return(1);
}


template<class T>
int matrix<T>::load(const char * filename) {
  int i,j;
  fstream file;
  string input;
  file.open(filename,ios::in);
  
  file >> m;
  file >> n;
  resize(m,n);
  for(j=0;j<n;j++){
    for(i=0;i<m;i++){
      file >> (*this_matrix)[i][j] ;
    }
  }
  file.close();
  return(1);
}
#define Matrix matrix<double>
#endif




