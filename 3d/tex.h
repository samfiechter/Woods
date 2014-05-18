#ifndef TEX_H
#define TEX_H 1
#include "open-gl.h"
#include "rand.h"
class tex{
public:
    tex();
    ~tex();
    void rand(const int & i);
    void use( GLubyte *,const int & x, const int & y);
    void draw();
    GLuint texName;
    void load_rgba(const char *);
	int bump;
private:
    void do_gl(const GLint &);
    int tex_image_w ;
    int tex_image_h ;
    GLubyte * tex_image;

    int delme;


};

#endif
