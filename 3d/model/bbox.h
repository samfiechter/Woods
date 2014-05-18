#ifndef bbox_H
#define bbox_H 1
#include <vector>
#include "point.h"
#include "ptTrans.h"

#define ptlst vector<point>

class bbox
{         
 public:
  bbox();
  bbox(const bbox & );
  ~bbox();
  bbox operator=(const bbox & );							     /* copy  */
  const bbox & operator*=(const ptTrans & t);					     /* multiply by a ptTrans */

  int test(const bbox &);							     // test for intersection 
  const bbox & operator*=(const ptTrans &);					     // multiply by a transfromation mtx 
  void draw();									     // wireframe the box 
 private:
  ptlst endpoints;
  int the_test(const bbox & a, const point & axis );
 
}
#endif
