//
//  woodsView.m
//  woods0
//
//  Created by Sam Fiechter on Mon Mar 17 2003.
//  Copyright (c) 2003, __MyCompanyName__. All rights reserved.
//

#import "woodsView.h"


@implementation woodsView

- (id)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview
{
  
    GLuint attribs[] =
    {
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADepthSize, 16,
        NSOpenGLPFAMinimumPolicy,
        NSOpenGLPFAClosestPolicy, 0
    };    
	binitedGL = 0;

    NSOpenGLPixelFormat* fmt ;
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {
		[sheet initWithWindowNibName:@"trees"];
        fmt = [[[NSOpenGLPixelFormat alloc]
              initWithAttributes:(NSOpenGLPixelFormatAttribute*) attribs] autorelease];
        glView = [[NSOpenGLView alloc] 
					initWithFrame:[self bounds] 
					pixelFormat: [fmt autorelease]]; 
		//NSZeroRect
        [self addSubview:glView ]; 
		[self setAnimationTimeInterval: (1/10)];  // was 1/30
            }

    return self;
}

- (void)dealloc
{

    [glView removeFromSuperview];
    [sheet dealloc];
//    [super dealloc];
    if (1 == binitedGL) {
        binitedGL = 0;
        delete wrp;
    }
        
}

- (void)setFrameSize:(NSSize)newSize
{
    [super setFrameSize:newSize];
    [glView setFrameSize:newSize];
    [[glView openGLContext] makeCurrentContext];
    if (1 == binitedGL) {
        binitedGL = 0;
        delete wrp;
    }
    

}

- (void)startAnimation
{
    [[glView openGLContext] makeCurrentContext];
    [self animateOneFrame];
    [super startAnimation];	
}

- (void)stopAnimation
{

    [super stopAnimation];
    binitedGL = 0;
    delete wrp;

}

- (void)drawRect:(NSRect)rect
{
    [super drawRect:rect];
}

- (void)animateOneFrame
{
    ScreenSaverDefaults * UD;
    float z;

    if ( 0 == binitedGL ) {
        const char *fn=[[[NSBundle bundleForClass:[woodsView class]] pathForResource:@"tree" ofType:@"rgba"] cString];
		wrp = new Wrapper;
        UD = [ScreenSaverDefaults defaultsForModuleWithName:@"woods"];
        z = [UD floatForKey:@"trees_TreeComplex"];
		if (z==0) {
			wrp->init(wnd,fn,1,0.8,50);
		} else {
			wrp->init(wnd,fn,[UD floatForKey:@"trees_NumTrees"],
					  (z==0?0.8:z),[UD floatForKey:@"trees_NumFlakes"]);
		}
		
		[[glView openGLContext] makeCurrentContext];

        wrp->viewport((int)[self frame].size.height,(int)[self frame].size.width);
        binitedGL = 1;
    }
    [[glView openGLContext] makeCurrentContext];
    wrp->draw();   
    return;
}

- (BOOL)hasConfigureSheet
{
    return YES;
}

- (NSWindow*)configureSheet
{
    if (sheet == nil) // Check to see if we've already loaded the second window controller
    {

        sheet = [[ConfigControl alloc] initWithWindowNibName:@"trees"];
    }
    return [sheet window]; 
}

@end
