#include "draw.h"
/**************************************DRAW A LINE FROM A TO B****************************************************/
void draw_line(const point & a, const point & b) {	    
  glPushMatrix(); 
  glBegin(GL_LINES);
  glVertex3f(a.x,a.y,a.z);
  glVertex3f(b.x,b.y,b.z);
  glEnd();
  glPopMatrix();
}
/**************************************CHANGE COLOR****************************************************************/
void change_color(const point & c){			    // change to color c
  glColor3f(c.x,c.y,c.z);
}

/**************************************DRAW A MODEL ***************************************************************/
// This spits data from the model set into the GC
void draw_model(const model & m){  
  surfacelist::iterator surface;			    // array of surface def's
  intlist::iterator pointidx;				    // array of points
  obj_point a;
  int z;

  for (surface = m.surfaces.begin(); surface <  m.surfaces.end(); surface++) {
    glBegin(m.surface->mode);				    // the mode defines what we are drawing...

    for (pointidx = m.surface->point_idx.begin() ; pointidx < m.surface->point_idx.end() ; pointidx++ ) {
      a = m.points[ *pointidx ];
      if ( a.type ) {
	glVertex3f(a.x, a.y, a.z);
      } else {
	glColor3f(a.x, a.y, a.z);
      }
    }
    glEnd();
  }
  return();
}
