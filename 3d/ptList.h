#ifndef Matrix
#define Matrix matrix<double>
#endif

#ifndef pointLIST_H
#define pointLIST_H 1
#include "point.h"
#include "open-gl.h"
#include <iostream.h>

class ptList : public Matrix {

 public:

  ptList();
  ptList(const ptList & cpyme);
  ~ptList() ;
  
  void push(const double & x1,const double & y1, const double & z1) ;
  void push(const point & p);
  const point & get(const int & row);
  const ptList & set(const int & row,const double & x1,const double & y1, const double & z1) ;


};


#endif




