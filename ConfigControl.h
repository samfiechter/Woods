/* ConfigControl */

#import <ScreenSaver/ScreenSaver.h>


@interface ConfigControl : NSWindowController
{
    IBOutlet id NumFlakes;
    IBOutlet id NumTrees;
    IBOutlet id TreeComplex;
}
- (IBAction)Cancel:(id)sender;
- (IBAction)OK:(id)sender;
@end
