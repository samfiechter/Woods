#ifndef draw_H
#define draw_H 1

#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>

#include "point.h"
#include "model.h"

void draw_line(const point & a, const point & b);
void change_color(const point & c);
void draw_model(const model & m);
#endif
