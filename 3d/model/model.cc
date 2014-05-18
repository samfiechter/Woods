#include "model.h"

int model::addpoint(int type,GLfloat x,GLfloat y,GLfloat z)
{
  obj_point tz;
  int i;
  i =(points.end()-points.begin());				   // the count = i
  tz.type =type; tz.x = x; tz.y = y; tz.z=z; 
  points.resize(i+1);  
  points[i] = tz;						   // i is now the last vector
  return (i);
}

int model::addsurface(GLenum mode)
{
  surface tz;
  int i;
  tz.mode = mode;
  i =(surfaces.end()-surfaces.begin());				   // the count = i
  surfaces.resize(i+1);  
  surfaces[i] = tz;						   // i is now the last vector
  return (i);
}


int model::draw(){
  draw_model(this);   //call the routine in draw.cc (fo' porting)
}

int model::load(string filename){
  fstream file;
  string input;
  obj_point p;
  surface s;
  float f;
  int i,n,x;

  file.open(filename.c_str(),ios::in);
  while ( !file.eof()){
    file >> input;
    switch((int)* input.c_str()) {
    case FI_POINTS:
	  file >> i;
	  points.resize(i);
	  break;
    case FI_POINT:
	  file >> i;
	  file >> p.type;
	  file >> p.x;
	  file >> p.y;
	  file >> p.z;
	  points[i] = p;
	  break;
    case FI_SURFACES:
	  file >> i;
	  surfaces.resize(i);
	  break;
    case FI_SURFACE:
	  file >> i;
	  file >> s.mode;
	  s.point_idx.resize(i);
	  break;
    case FI_POINT_IDX:
	  file >> n;
	  file >> x;
	  s.point_idx[n] = x;
	  break;
    case FI_SEND:
	  file >> i;	  
	  surfaces[i] = s;
	  break;
    }
  }
  file.close();
  return(1);
}

int model::clear(){
  bbox.resize(8);
  bbox[0].set(1,1,1);
  bbox[1].set(-1,1,1);
  bbox[2].set(-1,-1,1);
  bbox[3].set(1,-1,1);
  bbox[4].set(1,1,-1);
  bbox[5].set(-1,1,-1);
  bbox[6].set(-1,-1,-1);
  bbox[7].set(1,-1,-1);
  points.resize(0);
  surfaces.resize(0);
  return(1);
}

model::model()
{
  clear();
}


int model::save(string filename) {
  fstream file;
  file.open(filename.c_str(),ios::out);

  floatlist::iterator f;
  surfacelist::iterator s;
  intlist::iterator intg;
  int i;
  int j;

  file << FI_POINTS << " " << points.end() - points.begin() << "\n";
  i = 0;
  for(f = points.begin(); f < points.end() ; f++) {
    file << FI_POINT << " " << i << " " << f->type << " " <<  f->x << " " << f->y << " " << f->z << "\n";
    i++;
  }
  i = 0;
  file << FI_SURFACES << " " << (surfaces.end() - surfaces.begin()) << "\n";
  for(s = surfaces.begin(); s< surfaces.end() ; s++) {
    file << FI_SURFACE << " " << s->point_idx.end() - s->point_idx.begin() << " " <<  s->mode << "\n"; 
    j = 0;
    for (intg = s->point_idx.begin() ; intg <  s->point_idx.end() ; intg ++) 
      {
	file << FI_POINT_IDX << " " << j << " " << *intg << "\n";
	  j++;
      }
    file << FI_SEND << " " << i << "\n";
    i++;
  }
  return(1);
}

model::~model()
{

}

