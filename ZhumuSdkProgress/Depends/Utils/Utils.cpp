#include "stdafx.h"
#include "Utils.h"
#include <shlobj.h>
#include "plog/Log.h"
#include "DirectoryUtil.h"
#include "json.h"
#include <time.h>

std::string g_logPath;


CUtils::CUtils()
{
}


CUtils::~CUtils()
{
}


std::string CUtils::GetLogFilePath()
{
    if (g_logPath.empty())
    {
        std::wstring strTemp = GetCurrentPath();
        strTemp += L"\\ZhumuSdkProgress_Logs\\";
        if (!DirectoryUtil::IsDirExistW(strTemp.c_str()))
        {
            DirectoryUtil::CreateDirW(strTemp.c_str());
        }
        g_logPath = ws2s(strTemp);
        g_logPath.append(GetDate());
        g_logPath.append(".log");
    }
    return g_logPath;
}

std::string CUtils::GetDate()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&timep));
    return std::string(tmp);
}

std::wstring CUtils::GetCurrentPath()
{
    std::wstring currentPath = L"";
    TCHAR exeFullPath[MAX_PATH] = {};
    ::GetModuleFileName(NULL, exeFullPath, MAX_PATH);
    std::wstring pathTmp = exeFullPath;
    int index = pathTmp.find_last_of(L"\\");
    if (index > 0)
    {
        currentPath = pathTmp.substr(0, index);
    }
    return currentPath;
}

std::wstring CUtils::GetAppDataPath()
{
    wchar_t m_lpszDefaultDir[MAX_PATH];
    wchar_t szDocument[MAX_PATH] = { 0 };
    memset(m_lpszDefaultDir, 0, _MAX_PATH);

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDList(pidl, szDocument))
    {
        GetShortPathName(szDocument, m_lpszDefaultDir, _MAX_PATH);
    }

    std::wstring wsR = m_lpszDefaultDir;

    return wsR;
}

std::wstring CUtils::GetAppDataPath(const std::wstring& subfolder)
{
    std::wstring path = GetAppDataPath();
    path.append(L"\\");
    path.append(subfolder);

    if (_waccess(path.c_str(), 0) == -1)
    {
        _wmkdir(path.c_str());
    }

    return path;
}


std::string CUtils::ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

    setlocale(LC_ALL, "chs");

    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    std::string result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}

std::wstring CUtils::s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs");

    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    std::wstring result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, "C");

    return result;
}

std::wstring CUtils::utf82GBK(const std::string& s)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;
    return s2ws(strTemp);
}

//unicode 转为 ascii 
std::string CUtils::WideByte2Acsi(const std::wstring& wstrcode)
{
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (asciisize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<char> resultstring(asciisize);
    int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
    if (convresult != asciisize)
    {
        throw std::exception("La falla!");
    }
    return std::string(&resultstring[0]);
}

//Unicode 转 Utf8 
std::string CUtils::Unicode2Utf8(const std::wstring& widestring)
{
    int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8size == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<char> resultstring(utf8size);
    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
    if (convresult != utf8size)
    {
        throw std::exception("La falla!");
    }
    return std::string(&resultstring[0]);
}

//utf-8 转 ascii 
std::string CUtils::UTF_82ASCII(const std::string& strUtf8Code)
{
    std::string strRet("");
    //先把 utf8 转为 unicode 
    std::wstring wstr = Utf82Unicode(strUtf8Code);
    //最后把 unicode 转为 ascii 
    strRet = WideByte2Acsi(wstr);
    return strRet;
}

//ascii 转 Utf8 
std::string CUtils::ASCII2UTF_8(const std::string& strAsciiCode)
{
    std::string strRet("");
    //先把 ascii 转为 unicode 
    std::wstring wstr = ASCII2WideByte(strAsciiCode);
    //最后把 unicode 转为 utf8 
    strRet = Unicode2Utf8(wstr);
    return strRet;
}

//UTF-8转Unicode 
std::wstring CUtils::Utf82Unicode(const std::string& utf8string)
{
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<wchar_t> resultstring(widesize);
    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }
    return std::wstring(&resultstring[0]);
}

//ascii 转 Unicode 
std::wstring CUtils::ASCII2WideByte(const std::string& strascii)
{
    int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<wchar_t> resultstring(widesize);
    int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }
    return std::wstring(&resultstring[0]);
}

std::string CUtils::json2Str(const Json::Value& data)
{
    std::string s = data.toStyledString();
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    return s;
}
