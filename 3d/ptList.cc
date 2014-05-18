#include "ptList.h"

ptList::ptList() {
    set(0,0,0,0);
};

ptList::ptList(const ptList & cpyme) {
    (*this).copy(cpyme);
};

ptList::~ptList() {
};

void ptList::push(const double & x1,const double & y1, const double & z1) {
    set(m+1,x1,y1,z1);	
};

void ptList::push(const point & p) {
	push_row(p);
};
 
const point & ptList::get(const int & row){
	 point a((*this)[row][0],
			 (*this)[row][1],
			 (*this)[row][2]);
	 return(a);
};

const ptList & ptList::set(const int & row,const double & x1,const double & y1, const double & z1){
	if (m < (row+1)) {
		resize(row,4);
	}
	(*this)[row][0] = x1;
	(*this)[row][1] = y1;
	(*this)[row][2] = z1;
	return (*this);
};





