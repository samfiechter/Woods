#ifndef model_H
#define model_H 1
#define PI2 6.28318530718;

#include <math.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>

#include "draw.h"
#include "obj_base.h"
#include "point.h"
#include "ptTrans.h"
#include "bbox.h"

#define FI_POINTS (char) 'T'
#define FI_POINT (char)  'P'
#define FI_SURFACES (char) 'Z'
#define FI_SURFACE  (char) 'S'
#define FI_POINT_IDX (char) 'X'
#define FI_SEND (char) 'E'

struct obj_point {						    /* type and point */
  int type;						    /* 0=color 1=vertex */
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

typedef std::vector<obj_point> floatlist;
typedef std::vector<int> intlist;

typedef std::vector<point> pointlist;


struct surface {
  GLenum mode;
  intlist point_idx;
};

typedef std::vector<surface> surfacelist;



class model
{							    
 public:

  model();					       /* construct */
  ~model();						/* destruct */

  int draw();			     /* draw the object 1 on sucess */

  int load( string filename );		      /* load from glo file */
  int save( string filename );		      /* save from glo file */
  int addpoint(int type,GLfloat x,GLfloat y,GLfloat z);	/* add a point */           
  int addsurface(GLenum);
  int clear();

  floatlist points;					  /* points */
  surfacelist surfaces;					/* surfaces */
  bbox bounding_box;
 private:

};

#endif
