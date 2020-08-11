#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include "writer.h"

class CUtils
{
public:
    CUtils();
    ~CUtils();

public:

    static std::string GetLogFilePath();
    static std::string GetDate();

    static std::wstring GetCurrentPath();
    static std::wstring GetAppDataPath();
    static std::wstring GetAppDataPath(const std::wstring& appName);

    static std::string ws2s(const std::wstring& ws);
    static std::wstring s2ws(const std::string& s);
    static std::wstring utf82GBK(const std::string& s);
    static std::string WideByte2Acsi(const std::wstring& wstrcode);
    static std::string Unicode2Utf8(const std::wstring& widestring);
    static std::string UTF_82ASCII(const std::string& strUtf8Code);
    static std::string ASCII2UTF_8(const std::string& strAsciiCode);
    static std::wstring Utf82Unicode(const std::string& utf8string);
    static std::wstring ASCII2WideByte(const std::string& strascii);


    static std::string json2Str(const Json::Value& data);
};

#endif // _UTILS_H_
