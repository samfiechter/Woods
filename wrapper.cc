#include "wrapper.h"


Wrapper::Wrapper(){
};

Wrapper::~Wrapper(){
};

#define GROUND_SIZE 65
#define GROUND_VAR2 1
#define GROUND_VAR GROUND_VAR2*2

#define f_NEAR 4
#define f_FAR 65

void Wrapper::grnd_rand(const int & ax,const int & ay,const int & bx,const int & by){
    int cx = ax;
    int cy = ay + (by-ay)/2;
    int dx = ax + (bx-ax)/2;
    int dy = cy;
    int ex = dx;
    int ey = ay;
    int fx = dx;
    int fy = by;
    int gx = bx;
    int gy = dy;

    if ( 0==(by-ay)%2 && 0 == (bx-ax)%2 ){
	ground[cx][cy] = ground[ax][ay] + rnd() * ( ground[ax][by] - ground[ax][ay]);
	ground[dx][dy] = ground[ax][ay] + rnd() * ( ground[bx][by] - ground[ax][ay]);
	ground[ex][ey] = ground[ax][ay] + rnd() * ( ground[bx][ay] - ground[ax][ay]);
	ground[fx][fy] = ground[ax][by] + rnd() * ( ground[bx][by] - ground[ax][by]);
	ground[dx][dy] = ground[bx][ay] + rnd() * ( ground[bx][by] - ground[bx][ay]);
	grnd_rand(ax,ay,dx,dy);
	grnd_rand(cx,cy,fx,fy);
	grnd_rand(dx,dy,bx,by);
	grnd_rand(ex,ey,gx,gy);
    }
    return;
}

void Wrapper::init( WindowRef window,const char* fn,float nt, float ct, float nf){
    int i;
	
	time_seed();

    ntrees =  1 + (int) floor(nt);
    ctrees = 1.5 - (1/(ct==0?1.12:ct));
	ictrees = 0.2/ctrees;
    nflakes = (int) floor(nf);
    ground.resize(GROUND_SIZE);
    for(i=0;i<GROUND_SIZE;i++){
		ground[i].resize(GROUND_SIZE);
    }
    ground[0][0]					= 0;
    ground[0][GROUND_SIZE-1] 		 = 0;
    ground[GROUND_SIZE-1][0] 		 = (rnd()*GROUND_VAR);
    ground[GROUND_SIZE-1][GROUND_SIZE-1] = (rnd()*GROUND_VAR);
    grnd_rand(0,0,GROUND_SIZE-1,GROUND_SIZE-1);
	
	
    stand.resize(ntrees);
    for(i = 0;i<ntrees;i++){
        stand[i].lumber.setup(ctrees);
        stand[i].z = (rnd() * 35) - 40;
        stand[i].x = 0.5 * stand[i].z * (rnd() - 0.5);
		stand[i].y = 0;
    }
	 
	 
    angle= 0;
    fogden= 0.00001;
    
    grass.rand(0);
    mytexture.load_rgba(fn);
    //mytexture.rand(3);
    
    glBindTexture(GL_TEXTURE_2D, mytexture.texName);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// correct perspective
    glEnable(GL_CULL_FACE);
}



void Wrapper::viewport(int height, int width){
    GLdouble aspect;
    double z = ( (double) 10 * f_NEAR) / f_FAR;
    aspect = z* ((GLfloat) height  / (GLfloat) width);
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1 * z , z,-1 * aspect, aspect,f_NEAR,f_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);                            

    glPolygonMode(GL_FRONT, GL_FILL);
    //glPolygonMode(GL_BACK, GL_POINT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    

    return;
};



void Wrapper::draw(){
    int i,j;
    GLfloat fogColor[4] = {0.6, 0.6, 0.6, 1.0};
    GLfloat position [] = { 3.0, 5.0, 1.0, 1.0 };
    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    point x;

    fogden += (float) ((rnd()-0.5)/ (double) 400);
    fogden = (fogden<.01?.01: (fogden>1?1:fogden));
    //Enable fog
    glEnable(GL_FOG);
    glFogi(GL_FOG_END,f_FAR);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, fogden);

    angle += (rnd()-0.5)*0.01;
    
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT + GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0, -6.0,-10.0);
    glRotatef(3,1,0,0);
    glRotatef(angle,0,1,0);    

    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    x.set(3,5,1);
    glEnable(GL_LIGHT0);
    x.rotatey(120);
    position[0] = *x.x;
    position[1] = *x.y;
    position[2] = *x.z;
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glEnable(GL_LIGHT1);
    x.rotatey(120);
    position[0] = *x.x;
    position[1] = *x.y;
    position[2] = *x.z;
    glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glEnable(GL_LIGHT3); 
    glEnable(GL_LIGHTING);

    /*
    glBegin(GL_LINES);
        glColor3f(1,0,0); 	glVertex3f(0,0,0);    glVertex3f(20,0,0);
        glColor3f(0,1,0); 	glVertex3f(0,0,0);    glVertex3f(0,20,0);
        glColor3f(0,0,1); 	glVertex3f(0,0,0);    glVertex3f(0,0,20);
        glEnd();
     */

    grass.draw();
    glEnable(GL_TEXTURE_2D);

	#define TEX_PLOP 32
    glColor3f(0.1,0.8,0.1);
    for(i=0;i<GROUND_SIZE-1;i++){
		for(j=0;j<GROUND_SIZE-1;j++){
			glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex3f((2*i) - GROUND_SIZE,		ground[i][j],   (2*j) -GROUND_SIZE);

			glTexCoord2f(0,TEX_PLOP);
			glVertex3f((2*i)  - GROUND_SIZE,	ground[i][j+1], 2*(j+1) -GROUND_SIZE);

			glTexCoord2f(TEX_PLOP,TEX_PLOP);
			glVertex3f(2*(i+1) -GROUND_SIZE,	ground[i+1][j+1],2*(j+1) -GROUND_SIZE);

			glTexCoord2f(TEX_PLOP,0);
			glVertex3f(2*(i+1) -GROUND_SIZE,	ground[i+1][j], 2*j -GROUND_SIZE);
	    
			glEnd();
		}
	}

    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.3,0.3,0.3);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_DST_ALPHA );
    glEnable(GL_BLEND);

    glBegin(GL_QUADS);
    glVertex3f(64,-64,50); // backdrop ??
    glVertex3f(64,64,50);
    glVertex3f(-64,64,50);
    glVertex3f(-64,-64,50);
    glEnd();
    
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_SRC_COLOR );
    glBegin(GL_QUADS);
    glVertex3f(-64,2,-64);  //ground level fog
    glVertex3f(-64,2,64);
    glVertex3f(64,2,64);
    glVertex3f(64,2,-64);

    glEnd();
    glDisable(GL_BLEND);
    
    
    glColor3f(0.8,0.8,0.8);
    mytexture.draw();

//    glColor3f(0.52,0.51,0.49);

    for(i=0;i<ntrees;i++){
        glPushMatrix();
        glTranslatef(stand[i].x,stand[i].y,stand[i].z);
		//glTranslatef((2*i)-15,0,-10);
		//glScalef(0.2,0.2,0.2);
        glScalef(ictrees,ictrees,ictrees);
		stand[i].lumber.draw(x);
        glPopMatrix();
    }

    glPopMatrix();
    glFlush();
}