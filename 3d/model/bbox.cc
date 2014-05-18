#include "bbox.h";					    
				                            
bbox::bbox(){
  point a;
  endpoints.resize(8);
  endpoints[0].set(1,1,1);
  endpoints[1].set(1,-1,1);
  endpoints[2].set(1,-1,-1);
  endpoints[3].set(1,1,-1);
  endpoints[4].set(-1,1,1);
  endpoints[5].set(-1,-1,1);
  endpoints[6].set(-1,-1,-1);
  endpoints[7].set(-1,1,-1);
}

bbox::bbox(const bbox & a) {
  int i;
  endpoints.resize(8);
  for(i=0;i<8;i++) {
    endpoints[i].set(a.endpoints[i].x,a.endpoints[i].y,a.endpoints[i].z);
  }
}

bbox::~bbox() {
  
};

bbox::operator=(const bbox & a){
  bbox z(a);
  return(z);
}


int bbox::thetest(const bbox & a, const point & axis) { 
  double dot;
  double min;
  double a_min;
  double max;
  double a_max;
  min = max = endpoints[0].dot(axis);
  a_min = a_max = a.endpoints[0].dot(axis);
  for(i=1;i<8;i++){
    dot = endpoints.[i].dot(axis);
    if (min > dot)
      min = dot;
    if (max < dot)
      max = dot;
    dot = a.endpoints.[i].dot(axis);
    if (a_min > dot)
      a_min = dot;
    if (a_max < dot)
      a_max = dot;
  }
  // min   max  a_min a_max  == no intersection this axis 
  if (max < a_min || a_max < min )                                         
    return(0);						
  else
    return(1);
}


int bbox::test(const bbox & a){
  float  min_x,max_x;   
  float  min_y,max_y;
  float  min_z,max_z;
  float  a_min_x,a_max_x;
  float  a_min_y,a_max_y;
  float  a_min_z,a_max_z;
  int i,j,k;
  bbox * axisguy;
  point axis;

  min_x = max_x = endpoints[0].x;
  a_min_x = a_max_x = a.endpoints[0].x;
  min_y = max_y = endpoints[0].y;
  a_min_y = a_max_y = a.endpoints[0].y;
  min_z = max_z = endpoints[0].z;
  a_min_z = a_max_z = a.endpoints[0].z;
  for(i=1;i<8;i++){
    if (min_x > endpoints.[i].x) 
      min_x = endpoints.[i].x;
    if (a_min_x > a.endpoints.[i].x) 
      a_min_x = a.endpoints.[i].x;
    if (min_y > endpoints.[i].y) 
      min_y = endpoints.[i].y;
    if (a_min_y > a.endpoints.[i].y) 
      a_min_y = a.endpoints.[i].y;
    if (min_z > endpoints.[i].z) 
      min_z = endpoints.[i].z;
    if (a_min_z > a.endpoints.[i].z) 
      a_min_z = a.endpoints.[i].z;
    if (max_x < endpoints.[i].x) 
      max_x = endpoints.[i].x;
    if (a_max_x < a.endpoints.[i].x) 
      a_max_x = a.endpoints.[i].x;
    if (max_y < endpoints.[i].y) 
      max_y = endpoints.[i].y;
    if (a_max_y < a.endpoints.[i].y) 
      a_max_y = a.endpoints.[i].y;
    if (max_z < endpoints.[i].z) 
      max_z = endpoints.[i].z;
    if (a_max_z < a.endpoints.[i].z) 
      a_max_z = a.endpoints.[i].z;
  }
  
  if (max_x < a_min_x || a_max_x < min_x)                                         
    return(0);						    // if there is no intersection       
  if (max_y < a_min_y || a_max_y < min_y ) 
    return(0);
  if (max_z < a_min_z || a_max_z < min_z ) 
    return(0);

   j =0;
   axisguy = this;
   k=1;
  for (i=0; k== 1 && i<12;i++) {
    if(i==6) {
      j=6;
      axisguy = & a;
    } 
    switch (i-j) {
    case 0:
      axis = axisguy.endpoints[0] - axisguy.endpoints[1];
      axis = axis.cross(axisguy.endpoints[2] - axisguy.endpoints[1]);
      break;
    case 1:
      axis = axisguy.endpoints[4] - axisguy.endpoints[7];
      axis = axis.cross(axisguy.endpoints[6] - axisguy.endpoints[7]);
      break;	
    case 2:
      axis = axisguy.endpoints[0] - axisguy.endpoints[4];
      axis = axis.cross(axisguy.endpoints[5] - axisguy.endpoints[4]);
      break;
    case 3:
      axis = axisguy.endpoints[1] - axisguy.endpoints[5];
      axis = axis.cross(axisguy.endpoints[6] - axisguy.endpoints[5]);
      break;
    case 4:
      axis = axisguy.endpoints[2] - axisguy.endpoints[6];
      axis = axis.cross(axisguy.endpoints[7] - axisguy.endpoints[6]);
      break;
    case 5:
      axis = axisguy.endpoints[3] - axisguy.endpoints[7];
      axis = axis.cross(axisguy.endpoints[4] - axisguy.endpoints[7]);
      break;
    }
    k = the_test(a,axis);
  }
  return(k);
}

void bbox::transform(const transform & a){
  int i;
  for(i=0;i<8;i++)
    endpoints[i] *= a;
}


void bbox::draw() {
  int i;
  for(i=0;i<3;i++){
    draw_line(endpoints[i],endpoints[i+1]);
    draw_line(endpoints[i],endpoints[i+4]);
    draw_line(endpoints[i+4],endpoints[i+5]);
  }
  draw_line(endpoints[0],endpoints[3]);
  draw_line(endpoints[3],endpoints[7]);
  draw_line(endpoints[4],endpoints[7]);
  return();  
}

const bbox & operator*=(const transform & t) {
  int i;
  for(i=0;i<8;i++)
    endpoints[i] *= t;
  return(*this);
}
