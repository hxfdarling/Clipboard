#include <node.h>
#ifdef __WIN32__
#include "clip_win.h"
#elif __APPLE__
#include "clip_osx.h"
#endif
namespace moa
{
using v8::Array;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void getFileNames(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Array> fileNames = get_file_names(isolate);
  args.GetReturnValue().Set(fileNames);
}
void getText(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  char *text = get_text(isolate);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, text));
}
void Init(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "getFileNames", getFileNames);
  NODE_SET_METHOD(exports, "getText", getText);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
}