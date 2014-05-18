#ifndef Matrix
#define Matrix matrix<double>
#endif

#ifndef ptTrans_CLASS_H
#define ptTrans_CLASS_H 1

#include <math.h>
#include "matrix.h"

#define DEG_TO_RAD 0.01745329252


class ptTrans : public Matrix {
 public:
    ptTrans();
    ~ptTrans();
    virtual const ptTrans & clear();
    const ptTrans & translate(const double &,const double &, const double &);
    const ptTrans & scale(const double &,const double &,const double &);
    const ptTrans & rotatex(const double &);
    const ptTrans & rotatey(const double &);
    const ptTrans & rotatez(const double &);
    void spit_flat(double * a);
};
#define transform ptTrans
#endif
