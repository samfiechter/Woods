#include "rand.h"

double rnd(){
    return((double) random()/MAX_RAND);
};

int RAND(const int & k){
    return ( (int) random() % k);
};

double mid_rand(const double & a,const double & b){
    return(a+((b-a)*rnd()));
}

void time_seed(){
    unsigned long seed;
    seed = (unsigned long) time(NULL);
    srandom(seed);
};

double rnd_flp(const double & z)
{
	if(rnd() > z){
		return(1);
	} else {
		return(-1);
	}
};