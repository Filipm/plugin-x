//
//  ISpeech.m
//  PluginiSpeech
//
//  Created by Ignacio Esteban Cossini Benchimol on 09/10/13.
//  Copyright (c) 2013 zhangbin. All rights reserved.
//

#import "ISpeech.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation ISpeech

@synthesize debug = __debug;
@synthesize m_voiceType;

- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo    
{
   }

- (void) setVoiceType:(NSString *)voiceType
{
    m_voiceType = voiceType;
}

- (void) speak:(NSString *)text
{
    iSpeechSDK* sdk = [iSpeechSDK sharedSDK];
    sdk.APIKey = @"developerdemokeydeveloperdemokey";

    ISSpeechSynthesis * synthesis = [[ ISSpeechSynthesis alloc] initWithText:text];
    [synthesis setVoice:m_voiceType];
    [synthesis setDelegate:self];
    NSError *error;
    
    if ( [synthesis speak:&error])
        OUTPUT_LOG(@"Error while trying to speak: %@", [error localizedDescription]);
}

- (void) setDebugMode:(BOOL)isDebugMode
{
    self.debug = isDebugMode;
}


- (NSString*) getSDKVersion
{
    return @"1.0.5";
}
- (NSString*) getPluginVersion
{
    return @"PluginVersion";
}


@end
