#include"obj_base.h"


obj_base::obj_base(){

}

obj_base::~obj_base(){

}

int obj_base::rotate(f3 a) {
	return(0);
};

  // translate the object 1 = sucess
   int obj_base::translate(f3 a)
    {return(0);};

  // scale the object 1 = sucess
   int obj_base::scale(f3 a)
    {return(0);};

  // draw the object 1 on sucess
   int obj_base::draw()
    {return(0);};

  // test for collision with another object
   int obj_base::collide(obj_base * c)
    {return(-1);};
	
  // what type of object is this?
   int obj_base::type()
    {return (0);};

  // animate the object through time
   int obj_base::timestep()
    {return (0);};
  
  // main location in space of this object
   f3 obj_base::position()
    { 
      f3 z;
      z.x =0;
      z.y =0;
      z.z =0;
      return(z);
    };

	

