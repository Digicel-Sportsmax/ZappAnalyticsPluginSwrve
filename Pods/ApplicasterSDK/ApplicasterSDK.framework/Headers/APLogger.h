//
//  APLogger.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 12/26/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@import CocoaLumberjack;

@class DDFileLogger;
/**
 APLogger is now based on lumberjack.
 Logger start method will do the following:
 1. Start ASL - printing logs to the device console
 2. When available - start Debug terminal logging
 3. Write logs into files in a cyclic manner - 10 files 100kb each
 4. Add a formatter that uses the Applicaster format - please look at APLoggerFormatter for more info on that
 
 @discussion:
 If you would like to see console logs in color please follow this guide:
 https://github.com/CocoaLumberjack/CocoaLumberjack/wiki/XcodeColors
 Everything is set up in the code to print:
 * Errors in red
 * Warnings in Orange
 But be sure you first download and do the configuration of the plugin (not the code which is in place) first.
 */
@interface APLogger : NSObject {
    
}

/**
 File logger - for use with support mail
 */
@property (nonatomic, strong) DDFileLogger *fileLogger;

/**
 Singleton method to get logger shared instance
 */
+ (instancetype)sharedInstance;

/**
 Start and setup logger
 */
- (void)startLogger;

/**
  + *  Get the log content with a maximum byte size
  + *  @param maxSize maximum byte size allowed
  + *  @return string of the logger with maximum byte size.
  + */
- (NSString *)logFilesContentWithMaxSize:(NSInteger)maxSize;

@end

#ifdef DEBUG
static const DDLogLevel ddLogLevel = DDLogLevelVerbose;
#else
static const DDLogLevel ddLogLevel = DDLogLevelWarning;
#endif

#define LOG_ASYNC_ENABLED YES

#define LOG_ASYNC_ERROR    ( NO && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_WARN     (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_INFO     (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_DEBUG    (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_VERBOSE  (YES && LOG_ASYNC_ENABLED)

#define APLoggerError(frmt, ...)   LOG_MAYBE(LOG_ASYNC_ERROR,   ddLogLevel, DDLogFlagError,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define APLoggerWarn(frmt, ...)    LOG_MAYBE(LOG_ASYNC_WARN,    ddLogLevel, DDLogFlagWarning,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define APLoggerInfo(frmt, ...)    LOG_MAYBE(LOG_ASYNC_INFO,    ddLogLevel, DDLogFlagInfo,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define APLoggerDebug(frmt, ...)   LOG_MAYBE(LOG_ASYNC_DEBUG,   ddLogLevel, DDLogFlagDebug,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define APLoggerVerbose(frmt, ...) LOG_MAYBE(LOG_ASYNC_VERBOSE, ddLogLevel, DDLogFlagVerbose, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

