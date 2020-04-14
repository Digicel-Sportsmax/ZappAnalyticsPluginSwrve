@import Foundation;
@import JavaScriptCore;

/*

 This class represents the XMLHttpRequest polyfill required to perform http requests from the javascript code evaluated in the JavaScriptCore context used by the custom data source module
 the JSExport protocol is required for properties and methods to be available from the Javascript code.
 Implementation of this class follows the XHR specs https://xhr.spec.whatwg.org/ to make the polyfill compliant with most common browser-based javascript XHR libraries like Axios
 
*/

@protocol APJSModuleXMLHttpRequestJSExport <JSExport>

#pragma mark - response properties

@property (nonatomic, strong) NSString *responseText;
@property (nonatomic, strong) NSString *responseType;
@property (nonatomic, strong) NSNumber *status;
@property (nonatomic, strong) NSString *statusText;

#pragma mark - event handlers

@property (nonatomic, strong) JSValue *onload;
@property (nonatomic, strong) JSValue *onerror;
@property (nonatomic, strong) JSValue *onreadystatechange;
@property (nonatomic, strong) JSValue *onloadstart;
@property (nonatomic, strong) JSValue *onprogress;
@property (nonatomic, strong) JSValue *onabort;
@property (nonatomic, strong) JSValue *ontimeout;
@property (nonatomic, strong) JSValue *onloadend;

#pragma mark - request properties

@property int32_t state;
@property JSValue *readyState;
# pragma mark - methods
-(instancetype)init;

-(void)open:(NSString*)httpMethod :(NSString*)url :(bool)async;
-(void)send:(NSString *)requestBody;

-(void)setRequestHeader: (NSString *)name :(NSString *)value;
-(NSString *)getAllResponseHeaders;
-(NSString *)getReponseHeader:(NSString *)name;
-(void)addEventListener: (NSString *)eventName : (JSValue *)handler;
-(void)removeEventListener: (NSString *)eventName;
-(void)abort;

@end

@interface APJSModuleXMLHttpRequest: NSObject <APJSModuleXMLHttpRequestJSExport>
@end
