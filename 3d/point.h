#ifndef point_H
#define point_H 1
#include "ptTrans.h"
#include "open-gl.h"


#include <iostream.h>

class point : public Matrix {

 public:
  double * x;
  double * y;
  double * z;

  void setxyz();
  point(const double & x1,const double & y1, const double & z1) ;
  point();
  point(const point & cpyme);
  ~point() ;
  const point & copy(const point & cpy);
  const point & set(const double & x1,const double & y1, const double & z1);
  const point & translate(const double & x1,const double & y1, const double & z1);
  const point & scale(const double & x1,const double & y1, const double & z1);
  const point & normalize();
  const point & rotatex(const double & angle);
  const point & rotatey(const double & angle);
  const point & rotatez(const double & angle);
  double distance() ;
  void vertex() ;
  void glTranslate();
  double dot (const point & b);
  point cross( const point & b);			// cross 0,myself and 0, b
  point cross( const point & a, const point & b);	// cross myself, a  and myself, b
  const point & operator=(const Matrix & b );
  const point & operator*=(const Matrix & b);
  const point & lmul(const Matrix & b);
  int load(const char * fn);
};


/*  
   ostream& operator <<(ostream& os){
    return (os << " " << *x
    << " " << *y 
    << " " << *z 
    << "\n");
    };

    istream& operator >>(istream & is, point & p){
    p.setxyz();
    is >> *p.x;
    is >> *p.y;
    is >> *p.z;
    return is;
    };
*/

#endif




