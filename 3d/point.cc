#include "point.h"

void point::setxyz(){
    x = & (*this)[0][0];
    y = & (*this)[0][1];
    z = & (*this)[0][2];
    (*this)[0][3] =1;
};

point::point(const double & x1,const double & y1, const double & z1) {
    resize(1,4);
    setxyz();
    set(x1,y1,z1);

};

point::point() {
    resize(1,4);
    setxyz();
    set(0,0,0);
};

point::point(const point & cpyme) {
    resize(1,4);
    setxyz();
    set(*cpyme.x,*cpyme.y,*cpyme.z);

};

point::~point() {
};

const point & point::copy(const point & cpy){
    set((*cpy.x),(*cpy.y),(*cpy.z));
    return(*this);
}

const point & point::set(const double & x1,const double & y1, const double & z1) {
    (*this)[0][0]=x1;
    (*this)[0][1]=y1;
    (*this)[0][2]=z1;

    return(*this);
};


const point & point::translate(const double & x1,const double & y1, const double & z1) {
    (*this)[0][0] += x1;
    (*this)[0][1] += y1;
    (*this)[0][2] += z1;
    return (*this);
};

const point & point::scale(const double & x1,const double & y1, const double & z1) {
    (*this)[0][0] *= x1;
    (*this)[0][1] *= y1;
    (*this)[0][2] *= z1;    
    return (*this);
};


const point & point::normalize(){
    double a;
    a = 1/ distance();
    (*x) *= a;
    (*y) *= a;
    (*z) *= a;
    return (*this);
};

const point & point::rotatex(const double & angle){
    ptTrans t;
    t.rotatex(angle);
    this->lmul(t);
    return (*this);
};
const point & point::rotatey(const double & angle){

    ptTrans t;
    t.rotatey(angle);
    this->lmul(t);
    return (*this);
};
const point & point::rotatez(const double & angle){
    ptTrans t;
    t.rotatez(angle);
    this->lmul(t);
    return (*this);
};
double point::distance() {
    return(sqrt(((*x)*(*x))+((*y)*(*y))+((*z)*(*z))));
};

void point::vertex() {
#ifndef NO_GL
    glVertex3d((*x),(*y),(*z));
#endif
};

void point::glTranslate() {
#ifndef NO_GL
    glTranslated((*x),(*y),(*z));
#endif
};


double point::dot (const point & b){
    return((*x)*(*b.x)) +((*y)*(*b.y)) + ((*z)*(*b.z));
}

point point::cross( const point & b){
    point crpr;
    (*crpr.x) = ((*y) * (*b.z)) - ((*z) * (*b.y));
    (*crpr.y) = ((*z) * (*b.x)) - ((*x) * (*b.z));
    (*crpr.z) = ((*x) * (*b.y)) - ((*y) * (*b.x));
    return (crpr);
}

point point::cross(const point & aa,  const point & ba){
    point a,b;
    a = aa - (*this);
    b = ba - (*this);
    return(a.cross(b));
}

const point & point::operator=(const Matrix & b ){
Matrix::operator=(b);
    setxyz();
    return(*this);
};
 const point & point::operator*=(const Matrix & b){
Matrix::operator*=(b);
    setxyz();
    return(*this);
}
 const point & point::lmul(const Matrix & b){
Matrix::lmul(b);
    setxyz();
    return(*this);
}

 int point::load(const char * fn){
    int a;
    a = Matrix::load(fn);
    setxyz();
    return(a);
}

