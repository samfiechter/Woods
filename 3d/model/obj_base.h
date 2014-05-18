#ifndef obj_base_H
#define obj_base_H 1
#include<math.h>

typedef struct {
  float x;
  float y;
  float z;
} f3;

class obj_base
{
public:
  obj_base();
  ~obj_base();
  
  // rotate the object
  virtual int rotate(f3 a) ;

  // translate the object 1 = sucess
  virtual int translate(f3 a);


  // scale the object 1 = sucess
  virtual int scale(f3 a);


  // draw the object 1 on sucess
  virtual int draw();


  // test for collision with another object
  virtual int collide(obj_base * c);

	
  // what type of object is this?
  virtual int type();


  // animate the object through time
  virtual int timestep();

  
  // main location in space of this object
  virtual f3 position();
	
};


#endif

