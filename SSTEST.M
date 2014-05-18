#import "SSTEST.h"

@implementation SSTEST

- (id)init
{	
	NSLog(@"init");
	self = [super init];
	return self;
}

- (void)awakeFromNib
{
/*	NSLog(@"init SS");	
	MySS = [[woodsView alloc] initWithFrame:[myView frame] isPreview:YES]; */
	[myView startAnimation];

}

-(void)dealloc
{
/*	NSLog(@"dealloc");
	[MySS dealloc];*/
}

- (IBAction)butPref:(id)sender
{
	NSLog(@"Config button");
	[[myView configureSheet] makeKeyAndOrderFront:self];
	/*
	[NSApp beginSheet: [myView configureSheet]
		modalForWindow: myWin
		modalDelegate: nil
		didEndSelector: nil
		contextInfo: nil];
	*/
	
}


@end
