//
//  APMacros.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 1/22/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#define IS_NOT_NULL(val) (val && ((NSNull*)val != [NSNull null]))
#define NA_STRING @"N/A"
#define STRING_OR_NA(str) (str ? str : NA_STRING)

#define AP_EXTERN_STRING_CONST(constant_name) extern NSString *constant_name;
#define AP_STRING_CONST(constant_name) NSString *constant_name = @#constant_name;

#define AP_SYNTHESIZE_DATA_ATTRIBUTE(attr_name, attr_type, attr_key) \
- (attr_type *)attr_name { \
if ([_object isKindOfClass:[NSDictionary class]] == NO) return nil;\
id ret = [(NSDictionary *)_object objectForKey:attr_key];\
if (ret && [attr_type class] == [NSString class] && [ret respondsToSelector:@selector(stringValue)])\
ret = [ret stringValue];\
if (IS_NOT_NULL(ret) == NO) return nil;\
return ret; \
}

#define AP_REGISTER_COMMAND(command_class) [self registerCommand:k##command_class commandClassRef:[command_class class]]
#define AP_INT2STR(i) [NSString stringWithFormat:@"%d", i]

#define SAFE_NOTIFICATION_NAME(notification_name) x_##notification_name

#define SAFE_REGISTER_NOTIFICATION(notification_name, selector_name, notification_object) \
NSString * SAFE_NOTIFICATION_NAME(notification_name) = *(NSString**)dlsym(RTLD_DEFAULT, #notification_name); \
if (SAFE_NOTIFICATION_NAME(notification_name) != nil) { \
[[NSNotificationCenter defaultCenter] addObserver:self \
selector:selector_name \
name:SAFE_NOTIFICATION_NAME(notification_name) \
object:notification_object]; \
}

#define SAFE_REMOVE_NOTIFICATION(notification_name, notification_object) \
NSString * SAFE_NOTIFICATION_NAME(notification_name) = *(NSString**)dlsym(RTLD_DEFAULT, #notification_name); \
if (SAFE_NOTIFICATION_NAME(notification_name) != nil) { \
[[NSNotificationCenter defaultCenter] removeObserver:self \
name:SAFE_NOTIFICATION_NAME(notification_name) \
object:notification_object]; \
}


#define IS_IPAD() ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
#define IS_568H() ([UIScreen mainScreen].bounds.size.height >= 568.0 || [UIScreen mainScreen].bounds.size.width >= 568.0) && !IS_IPAD()
#define IS_812H() ([UIScreen mainScreen].bounds.size.height >= 812.0 || [UIScreen mainScreen].bounds.size.width >= 812.0) && !IS_IPAD()

#define SCREEN_WIDTH [[UIScreen mainScreen] bounds].size.width
#define SCREEN_HEIGHT [[UIScreen mainScreen] bounds].size.height
#define SCREEN_SIZE CGSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT)

#define APP_HOURS_IN_DAY 24
#define APP_MINUTES_IN_HOUR 60.0

#define APP_PIXELS_IN_MINUTE (224 / APP_MINUTES_IN_HOUR)
#define APP_PIXELS_IN_HOUR (APP_MINUTES_IN_HOUR * APP_PIXELS_IN_MINUTE)
#define APP_PIXELS_IN_DAY (APP_HOURS_IN_DAY * APP_PIXELS_IN_HOUR)

#define SuppressPerformSelectorLeakWarning(Stuff) \
do { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
Stuff; \
_Pragma("clang diagnostic pop") \
} while (0)
