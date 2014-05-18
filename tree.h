#ifndef TREE_H
#define TREE_H 1
#include "ring.h"
#include "rand.h"
#include "tex.h"

#define TREE_RECUR_LIMIT 0.2
#define TREE_DOWN_SCALE 0.8
#define TREE_OFFSHOOT_MAX 11	// 3- max number of offshoots
#define TREE_RINGS 20

struct branch{    
    int index;			// used for branches
    int side;
    int angle;
    point marker;
};


class tree {
private:
   public:
    tree();
    tree(const double &);
    tree(const tree &);
    ~tree();
    void clone(const tree &);
    void setup(const double &);
    void draw(const point & wind );
    vector<ring> data;		// tree data
    double width;		// width of tree
    vector<branch> branches;	// branches
    vector<tree> trees;
    
    point loc;
    float xrot;
    float yrot;
    float zrot;
    
};
#endif
