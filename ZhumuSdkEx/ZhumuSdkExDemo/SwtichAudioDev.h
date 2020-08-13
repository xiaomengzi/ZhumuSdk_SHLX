#pragma once
#include "mmsystem.h"
#include "windows.h"
#include "Mmdeviceapi.h"
//#include "Propidl.h"
//#include "PolicyConfig.h"
class CSwtichAudioDev
{
protected:
    CSwtichAudioDev(void);
public:
    ~CSwtichAudioDev(void);
    static CSwtichAudioDev *    Instance();
    void        SetDefaultAud(CString  &strFri);
    void        EnumAudioDevice();
private:
    // HRESULT     SetDefaultAudioPlaybackDevice(LPCWSTR devID);

   
private:
    // char*     WideToMulti(TCHAR *pSrc);
    public:
    CStringArray   m_strId   ;
    CStringArray   m_strFriedlyName;
};

