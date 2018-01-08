#include "clip_win.h";

char *GBK2Utf8(const char *strGBK)
{
  WCHAR *str1;
  int n = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
  str1 = new WCHAR[n];
  MultiByteToWideChar(CP_ACP, 0, strGBK, -1, str1, n);
  n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
  char *str2 = new char[n];
  WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
  delete[] str1;
  str1 = NULL;
  return str2;
}

char *get_text(Isolate *isolate)
{
  char *pBuf;
  HANDLE hWnd;

  if (IsClipboardFormatAvailable(CF_TEXT)) //判断格式是否是我们所需要
  {
    OpenClipboard(hWnd);
    //读取数据
    hWnd = GetClipboardData(CF_TEXT);
    pBuf = (char *)GlobalLock(hWnd);
    GlobalUnlock(hClip);
    CloseClipboard();
  }
  return GBK2Utf8(pBuf);
}

Local<Array> get_file_names(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  HWND hWnd = NULL;
  Local<Array> fileNames = Array::New(isolate, 0);
  if (IsClipboardFormatAvailable(CF_HDROP))
  {
    OpenClipboard(hWnd);
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
        fileNames->Set(nIndex, String::NewFromUtf8(isolate, GBK2Utf8(szFilePathName)));
      }
    }
    CloseClipboard(); // 关闭剪切板
  }
  return fileNames;
}