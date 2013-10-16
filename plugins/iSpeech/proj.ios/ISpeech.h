//
//  ISpeech.h
//  PluginiSpeech
//
//  Created by Ignacio Esteban Cossini Benchimol,Dawid Drozd on 09/10/13.
//  Copyright (c) 2013 zhangbin. All rights reserved.
//

#import "Headers/ISSpeechSynthesis.h"
#import "InterfaceRaw.h"
#import "iSpeechSDK.h"


@interface ISpeech : NSObject <InterfaceRaw ,ISSpeechSynthesisDelegate>
{
}

@property BOOL debug;
@property (copy, nonatomic) NSString* m_voiceType;

- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo;
- (void) setVoiceType: (NSString * ) voiceType;
- (void) speak : (NSString * ) text;
- (void) setDebugMode: (BOOL) isDebugMode;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;


@end
