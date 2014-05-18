#ifndef WRAPPER_H
#define WRAPPER_H 1
#include "tree.h"
#include "tex.h"

#include <AGL/agl.h>
#include <OpenGL/gl.h>

#define ANGLE_MOVE 0.1
struct s_tree {
    float x;
    float y;
    float z;
    tree lumber;
};

class Wrapper{
private:
    void grnd_rand(const int & ax,const int & ay,const int & bx,const int & by);

public:

    vector<s_tree> stand;
    tex mytexture;
    tex grass;
    float angle;
    int n;
    float fogden;
    vector<vector<float> > ground;
    int nflakes;
    int ntrees;
    float ctrees;
	float ictrees;
    
    Wrapper();
    ~Wrapper();
    void init(WindowRef window, const char * fn,float,float,float);
    void draw();
    void viewport(int,int);

};

#endif