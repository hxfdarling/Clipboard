#include <windows.h>
#include <node.h>

using v8::Array;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

char *get_text(Isolate *isolate);
Local<Array> get_file_names(const FunctionCallbackInfo<Value> &args)