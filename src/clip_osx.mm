#include "clip_osx.h"
char* get_text(Isolate *isolate) {
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
  NSString* string = [pasteboard stringForType:NSStringPboardType];
  char*buf = new char[0];
  if(string){
    int reqsize = [string lengthOfBytesUsingEncoding:NSUTF8StringEncoding]+1;
    buf = new char[reqsize];
    memcpy(buf, [string UTF8String], reqsize);
  }
  return buf;
}
Local<Array> get_file_names(Isolate *isolate){
  NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];  
  NSArray* tempArray = [pasteboard pasteboardItems];
  int count = 0;
  for(NSPasteboardItem *tmpItem in tempArray){ 
    NSString *pathString = [tmpItem stringForType:@"public.file-url"];
    const char* str = [pathString UTF8String];
    if(str){
      count++;
    }
  }
  Local<Array> fileNames = Array::New(isolate, count);
  count =0;
  for(NSPasteboardItem *tmpItem in tempArray){ 
    NSString *pathString = [tmpItem stringForType:@"public.file-url"];
    const char* str = [pathString UTF8String];
    if(str){
      fileNames->Set(count,String::NewFromUtf8(isolate,str));
      count++;
    }
  }
  return fileNames;
}