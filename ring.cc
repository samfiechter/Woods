#include "ring.h"
ring::ring() {
    data.resize(8);
};

ring::ring(const double & a){
    data.resize(8);
    setup(a);
}

ring::ring(const ring & r) {
    data.resize(8);
    clone(r);
}

const ring & ring::clone(const ring & r){
    int i;
    for(i=0;i<8;i++){
        data[i] = r.data[i];
    }
    return(*this);
}

ring::~ring(){
};

const ring & ring::setup(const double & a){
    point b(a,0,0);
    int i;
    for (i=0;i<8;i++){
        data[i].copy(b);
        b.rotatey(45);
    }
    return(*this);
}

const ring & ring::operator+=(const point & a){
	int i;
    for(i=0;i<8;i++){
        data[i] += a;
    }
    return( *this);
}


const ring & ring::lmul(const ptTrans & a){
    int i;
    for(i=0;i<8;i++){
        data[i].lmul(a);
    }
    return( *this);
}
