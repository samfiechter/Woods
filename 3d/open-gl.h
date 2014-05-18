#ifndef OPENGL_DERP_H
#define OPENGL_DERP_H 1

#ifdef NO_GL
#define NO_APPLE_GL 1
#define NO_UNIX_GL 1
#endif

#ifndef NO_APPLE_GL	/* default to apple gl */
#include <AGL/agl.h>
#include <OpenGL/gl.h>
#define NO_UNIX_GL 1
#endif

#ifndef NO_UNIX_GL   	/* keep linux opengl stuff tho */
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#endif


#endif
