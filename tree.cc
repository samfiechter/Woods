#include "tree.h"

int r8(const int & z){
    int x = z;
    while(x > 7){
        x -= 8;
    }
    while(x < 0){
        x += 8;
    }
    return(x);
} 
tree::tree(){
// you can not setup here!!!! (it fucks up the recursion)
}

tree::tree(const double & a){
    setup(a);
}

tree::tree(const tree & t){
    clone(t);
}

tree::~tree(){
}

void tree::clone(const tree & t){
    int i,n;
    n = t.data.size();
    data.resize(n);
    for(i=0;i<n;i++){
        data[i].clone(t.data[i]);
    }
    width = t.width;
    n = t.branches.size();
    branches.resize(n);
    trees.resize(n);
    for(i=0;i<n;i++){
        branches[i].index = t.branches[i].index;
        branches[i].side = t.branches[i].side;
        branches[i].angle = t.branches[i].angle;
        trees[i].clone( t.trees[i]);
    }
}

struct s_flux {
    double x;
    double y;
    double w;
};

void setflx(s_flux * data,int a, int b){
    int n = a +(int) floor((float) (b-a)/2);
    data[n].w= data[a].w + ( ( (rnd() * 0.5) + 0.25) * (data[b].w -data[a].w));
    data[n].x= mid_rand(data[a].x,data[b].x) + (((rnd() - 0.5)* (data[a].x - data[b].x))*2);
    data[n].y= mid_rand(data[a].y,data[b].y) + (((rnd() - 0.5) * (data[a].y - data[b].y))*2);

}

void fluxuate(s_flux * data,int a, int b){
    if(a==b){
        return;
    }
    if((a+1) == b) {
        setflx(data,a,b);   
        return;
    } else{
        setflx(data,a,b);   
        fluxuate(data,a+(int) floor((float) (b-a)/2),b);
        fluxuate(data,a,a+(int) floor((float) (b-a)/2));
        return;
    }
}

void tree::setup(const double & scale){
    point p, ra;

    int ind,sid;

    width = scale * (0.7 + (rnd() * 0.3));

    int limbs,i;
    s_flux * init_widths;
    ptTrans t;
    data.resize(TREE_RINGS);
    init_widths = new s_flux[TREE_RINGS];
    init_widths[0].x = 0;
    init_widths[0].y = 0;
    init_widths[0].w = width;
    init_widths[TREE_RINGS-1].x =(rnd() - 0.5) * 2 * width;
    init_widths[TREE_RINGS-1].y =(rnd() - 0.5) * 2 * width;
    init_widths[TREE_RINGS -1].w = width / 6;
    fluxuate(init_widths, 0,TREE_RINGS -1);
    for(i=0;i<TREE_RINGS;i++){
        data[i].setup(init_widths[i].w); 	// init data in ring width w;
        t.clear();
        t.translate(init_widths[i].x, 3 * width * i,init_widths[i].y); 	
        data[i].lmul(t);
    }

    if(scale > TREE_RECUR_LIMIT) { 	// remember we are a recursive data structure...
        limbs = 3+RAND(TREE_OFFSHOOT_MAX);
        trees.resize(limbs);
        branches.resize(limbs);
        ind = (int) floor( (double) (TREE_RINGS/2));
        for(i=0;i<limbs;i++){
            ind += RAND((int) floor((TREE_RINGS - ind)/1.2));
            if (ind < (TREE_RINGS-3)){
                sid = RAND(8);	
                branches[i].index =ind;
                branches[i].side= sid;
                branches[i].angle=RAND(60)+35;
                p.set(init_widths[ind].w,0,0);
                p.rotatey(22.5+(sid*45));
                ra = (data[ind].data[r8(1+sid)] - data[ind].data[sid]);
                ra.scal_multiply(0.5);
                p = p + data[ind].data[sid] + ra;
                branches[i].marker.copy(p);
                trees[i].setup(init_widths[ind].w * TREE_DOWN_SCALE);
            } else {
                limbs = i;
                trees.resize(limbs);
                branches.resize(limbs);
            }
        }
    }else {
        branches.resize(0);
    }
    delete init_widths;
}

#define TREE_TEX_X 200
#define TREE_TEX_Y 150

void tree::draw(const point & wind ){
    int i,k,n;
    int ind,sid;
    float spin,flop;

    point blow[4];
    int x[9] = {0,1,2,1,0,-1,-2,-1,0};
    int y[9] = {-2,-1,0,1,2,1,0,-1,-2};
    point p;
    ring skirt;
    ptTrans unrot;

    glEnable(GL_TEXTURE_2D);


    n = data.size(); 				// draw my tree
    glBegin(GL_QUADS);
    for(i=1;i<n;i++){
        for(ind=0;ind<8;ind++){
            glTexCoord2f(0,0);
            data[i-1].data[r8(ind-1)].vertex();
            glTexCoord2f(TREE_TEX_X,0);
            data[i].data[r8(ind-1)].vertex();
            glTexCoord2f(TREE_TEX_X,TREE_TEX_Y);
            data[i].data[ind].vertex();	
            glTexCoord2f(0,TREE_TEX_Y);
            data[i-1].data[ind].vertex();
        }
    }
    glEnd();

  
    
  

   glBegin(GL_POLYGON);			//draw top
   for(i=7; i>=0;i--){
       switch(i){
           case 0:
            glTexCoord2f(0,0);
            break;
           case 2:
            glTexCoord2f(TREE_TEX_X,0);
            break;
           case 4:
            glTexCoord2f(TREE_TEX_X,TREE_TEX_Y);
            break;
           case 6:
            glTexCoord2f(0,TREE_TEX_Y);
            break;
           default:
            break;
       }
       data[n-1].data[i].vertex();
   }
   glEnd();

   n = trees.size();				// draw branches
   for(i=0;i<n;i++){
       ind =  branches[i].index;
        sid = branches[i].side;
        p.copy(branches[i].marker);
        flop = -1* branches[i].angle;
        spin =((sid*45)+22.5);

        unrot.clear();
        //unrot takes bottom ring of branch
        unrot.rotatez((double) flop);
        unrot.rotatey((double) spin); 	//into current coodrintes

//        blow.copy(wind);
//        blow.lmul(unrot);
        
        unrot.translate((*p.x),(*p.y),(*p.z));                                                
        skirt.clone(trees[i].data[0]);
        skirt.lmul(unrot);
        
        glEnable(GL_TEXTURE_2D);        
        glBegin(GL_QUADS);    
        for(k=0;k<8;k++){
            glTexCoord2f(0,0);				data[ind+y[k]].data[r8(sid+x[k])].vertex();
            glTexCoord2f(TREE_TEX_X,0);			data[ind+y[r8(k-1)]].data[r8(sid+x[r8(k-1)])].vertex();
            glTexCoord2f(TREE_TEX_X,TREE_TEX_Y); 	skirt.data[r8(k-1)].vertex();
            glTexCoord2f(0,TREE_TEX_Y);			skirt.data[r8(k)].vertex();
        }
        glEnd();


        p.glTranslate();        
        glRotatef( (float)   -1* spin,0,1,0);
        glRotatef( (float)   flop,0,0,1);


        trees[i].draw(blow[0]);

        glRotatef( (float) -1 * flop,0,0,1);
        glRotatef( (float)   spin,0,1,0);
        p.scale(-1,-1,-1);
        p.glTranslate();
    
   }
    

}
