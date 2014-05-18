//
//  woodsView.h
//  woods
//
//  Created by Sam Fiechter on Mon Mar 17 2003.
//  Copyright (c) 2003, __MyCompanyName__. All rights reserved.
//

#import <ScreenSaver/ScreenSaver.h>
#import "wrapper.h"
#import "ConfigControl.h"


@interface woodsView : ScreenSaverView 
{
    NSOpenGLView * glView;
    WindowRef wnd;
    Wrapper *wrp;
    BOOL binitedGL;
    int my_h,my_w;
    ConfigControl * sheet;
}
- (id)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview;

@end
