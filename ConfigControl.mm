#import "ConfigControl.h"
@implementation ConfigControl



- (IBAction)Cancel:(id)sender
{

    [NSApp endSheet:[self window]];
		[NSApp stopModal];  
}

- (IBAction)OK:(id)sender
{
    ScreenSaverDefaults * UD;
    UD = [ScreenSaverDefaults defaultsForModuleWithName:@"woods"];
    [UD setFloat:[NumTrees floatValue] forKey:@"trees_NumTrees"];
	NSLog(  [NSString stringWithFormat: @"Numtree: %f",
			[NumTrees floatValue]]); 

    [UD setFloat:[TreeComplex floatValue] forKey:@"trees_TreeComplex"];
    [UD setFloat:[NumFlakes floatValue] forKey:@"trees_NumFlakes"];
	[NSApp stopModal];
    [NSApp endSheet:[self window]];
}
- (void) awakeFromNib {
    float z;
    ScreenSaverDefaults * UD;
    UD = [ScreenSaverDefaults defaultsForModuleWithName:@"woods"];
    [NumTrees setFloatValue:[UD floatForKey:@"trees_NumTrees"]];
    z = [UD floatForKey:@"trees_TreeComplex"];
    [TreeComplex setFloatValue:(z==0?0.8:z)];
    [NumFlakes setFloatValue:[UD floatForKey:@"trees_NumFlakes"]];
        
}
@end
