#ifndef RING_H
#define RING_H 1
#include "point.h"


class ring {
public:
    ring();
    ring(const ring &);
    ring(const double &);
    ~ring();
    const ring & clone(const ring & a);
    const ring & setup(const double & a);
    
    vector<point> data;

    const ring & operator+=(const point & );
    const ring & lmul(const ptTrans & );

};

#endif
