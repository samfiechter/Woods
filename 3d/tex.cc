#include "tex.h"
#include "matrix.h"


tex::tex(){
    delme = 1;
	bump =0;
};

void tex::rand( const int & texmode){
    int i,j,k,n,m;
    int x,y;
    int c;
    tex_image_h = 64;
    tex_image_w = 64;
    if(delme==0)
        delete tex_image;
    delme=0;
    tex_image = new GLubyte[4*tex_image_w*tex_image_h];
	switch(texmode){
        case 0:
            for( k=0; k<1000; k++ ) {
                i = RAND(tex_image_w);
                j = RAND(tex_image_h);
                c = RAND(55)+200;
                for (n=i;(n<(i+2)); n++) {
                    for(m=j;(m<(j+4)) ;m++){
                        x = ( (m< tex_image_w)? m : m - tex_image_w);
                        y = ( (n< tex_image_h)? n : n - tex_image_h);
                        tex_image[(y*tex_image_w + x)*4 + 0] = c;
                        tex_image[(y*tex_image_w + x)*4 + 1] = c;
                        tex_image[(y*tex_image_w + x)*4 + 2] = c;
                        tex_image[(y*tex_image_w + x)*4 + 3] = 255;
                    }
                }
            }
            break;
					
        default:
            for( i=0; i<tex_image_h; i++ ) {
                for( j=0; j<tex_image_w; j++ ) {
                    c = ((((i&0x8)==0)^((j&0x8))==0))*55+200;
                    tex_image[(i*tex_image_w + j)*4 + 0] = c;
                    tex_image[(i*tex_image_w + j)*4 + 1] = c;
                    tex_image[(i*tex_image_w + j)*4 + 2] = c;
                    tex_image[(i*tex_image_w + j)*4 + 3] = 255;                    
                }
            }
            break;	
    }
    do_gl(GL_RGBA);
}
void tex::use(GLubyte * that,const int & x, const int & y) {

    tex_image_w =x;
    tex_image_h =y;
    if(delme==0)
        delete tex_image;
    delme=1;
    tex_image = that;
    do_gl(GL_RGBA);
}

void tex::load_rgba(const char * fn) {
    //int i,j,
	int k,x;
    fstream file;
    file.open(fn,ios::in);
   // GLubyte *z;
    file >> tex_image_w ;
    file >> tex_image_h;
    if(delme==0)
        delete tex_image;
    delme =0;
    tex_image = new GLubyte[4 * tex_image_w * tex_image_h];
    k=0;
    for(k=0;k<(4 * tex_image_w * tex_image_h);k++) {
            file >> x;
            tex_image[k] = (GLubyte) x;
    }
    file.close();
 /*   k=0;
    x=0;
    z = new GLubyte[4*64*64];
    for(j=0;j<64;j++){
        for(i=0;i<64;i++){
            z[x] = tex_image[k]; k++; x++;
            z[x] = tex_image[k]; k++; x++;
            z[x] = tex_image[k]; k++; x++;
            z[x] = 255; k++; x++;
        }
        k += (tex_image_w -64)*4;
    }
    delete tex_image;
    tex_image =z;
    tex_image_h = 64;
    tex_image_w = 64;*/
    do_gl(GL_RGBA);	
}

void tex::draw(){
	//glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texName);
}

void tex::do_gl(const GLint & r) {
    glGenTextures(1,&texName);
	if (bump ==0) {
		glBindTexture(GL_TEXTURE_2D, texName);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL);		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, r, tex_image_w,
					 tex_image_h, 0, r, GL_UNSIGNED_BYTE, tex_image);
	}else {
		/*glVertexAttrib3f
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, texName);
		//GenerateNormalisationCubeMap();
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		*/
	}
	
}

tex::~tex(){
    if(delme==0)
        delete tex_image;

    
}