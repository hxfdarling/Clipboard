#include <node.h>
#include <windows.h>
using namespace std;
namespace moa
{
using v8::Array;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

char *WCharToChar(WCHAR *s)
{
  int w_nlen = WideCharToMultiByte(CP_ACP, 0, s, -1, NULL, 0, NULL, false);
  char *ret = new char[w_nlen];
  memset(ret, 0, w_nlen);
  WideCharToMultiByte(CP_ACP, 0, s, -1, ret, w_nlen, NULL, false);
  return ret;
}

void getFileNames(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  HWND hWnd = NULL;
  Local<Array> fileNames = Array::New(isolate, 0);
  OpenClipboard(hWnd);
  if (IsClipboardFormatAvailable(CF_HDROP))
  {
    HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP)); // 获取剪切板中复制的文件列表相关句柄
    if (hDrop != NULL)
    {
      char szFilePathName[MAX_PATH + 1] = {0};
      UINT nNumOfFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); // 得到文件个数
      fileNames = Array::New(isolate, nNumOfFiles);
      // 考虑到用户可能同时选中了多个对象(可能既包含文件也包含文件夹)，所以要循环处理
      for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex)
      {
        memset(szFilePathName, 0, MAX_PATH + 1);
        DragQueryFile(hDrop, nIndex, szFilePathName, MAX_PATH); // 得到文件名
        fileNames->Set(nIndex, String::NewFromUtf8(isolate, szFilePathName));
      }
    }
    ::CloseClipboard(); // 关闭剪切板
  }
  args.GetReturnValue().Set(fileNames);
}
void Init(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "getFileNames", getFileNames);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
}