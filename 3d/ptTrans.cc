#include "ptTrans.h"


ptTrans::ptTrans(){
  clear();
}

ptTrans::~ptTrans(){
  return;
}

const ptTrans & ptTrans::clear() {
    (*this).identity(4);
    return(*this);
}

const ptTrans & ptTrans::translate(const double & x,const double & y,const double & z){
  Matrix a;
  a.identity(4);
  a[3][0] =x;
  a[3][1] =y;
  a[3][2] =z;
  this->lmul(a);
  return(*this);
}
const ptTrans & ptTrans::scale(const double & x,const double & y,const double & z){
  Matrix a;
  a.identity(4);
  a[0][0] =x;
  a[1][1] =y;
  a[2][2] =z;
  this->lmul(a);
  return(*this);

}

const ptTrans & ptTrans::rotatex(const double & angle) {
  Matrix a;
  double s,c;
  s = sin(DEG_TO_RAD * angle);
  c = cos(DEG_TO_RAD * angle);
  a.identity(4);
  a[1][1] = c;
  a[2][1] = -1*s;
  a[1][2] = s;
  a[2][2] = c;
  this->lmul(a);
  return(*this);
}


const ptTrans & ptTrans::rotatey(const double & angle) {
  Matrix a;
  double s,c;
  s = sin(DEG_TO_RAD * angle);
  c = cos(DEG_TO_RAD * angle);
  a.identity(4);
  a[0][0] = c;
  a[2][0] = -1*s;
  a[0][2] = s;
  a[2][2] = c;

  this->lmul(a);
  return(*this);
}


const ptTrans & ptTrans::rotatez(const double & angle) {
  Matrix a;
  double s,c;
  s = sin(DEG_TO_RAD * angle);
  c = cos(DEG_TO_RAD * angle);
  a.identity(4);
  a[0][0] = c;
  a[1][0] = -1*s;
  a[0][1] = s;
  a[1][1] = c;
  this->lmul(a);

  return(*this);
}
void ptTrans::spit_flat(double * a){
    int i,j,k;
    k=0;
    for(j=0;j<m;j++){
        for(i=0;i<n;i++){
            a[k] = (*this)[i][j];
        }
    }
    return;
}






