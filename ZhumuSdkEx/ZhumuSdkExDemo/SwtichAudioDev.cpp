#include "stdafx.h"
#include "SwtichAudioDev.h"
#include "Functiondiscoverykeys_devpkey.h"

CSwtichAudioDev::CSwtichAudioDev(void)
{
}


CSwtichAudioDev::~CSwtichAudioDev(void)
{
    CoUninitialize();
}

CSwtichAudioDev *  CSwtichAudioDev::Instance()
{
    static CSwtichAudioDev s_obj;
    return &s_obj;
}

//HRESULT CSwtichAudioDev::SetDefaultAudioPlaybackDevice(LPCWSTR devID)
//{	
//    //IPolicyConfigVista *pPolicyConfig;
//    //ERole reserved = eConsole;
//
//    //HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient), 
//    //    NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
//    //if (SUCCEEDED(hr))
//    //{
//    //    hr = pPolicyConfig->SetDefaultEndpoint(devID, reserved);
//    //    pPolicyConfig->Release();
//    //}
//    return hr;
//}

 void  CSwtichAudioDev::EnumAudioDevice()
 {
     m_strId.RemoveAll();
     m_strFriedlyName.RemoveAll();
     HRESULT hr = CoInitialize(NULL);
     if (SUCCEEDED(hr))
     {
         IMMDeviceEnumerator *pEnum = NULL;
         // Create a multimedia device enumerator.
         hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
             CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
         if (SUCCEEDED(hr))
         {
             IMMDeviceCollection *pDevices;           
             hr = pEnum->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pDevices);

             if (SUCCEEDED(hr))
             {
                 UINT count;
                 pDevices->GetCount(&count);
                 if (SUCCEEDED(hr))
                 {
                     for (int i = 0; i < count; i++)
                     {
                         IMMDevice *pDevice;
                         hr = pDevices->Item(i, &pDevice);
                         if (SUCCEEDED(hr))
                         {
                             LPWSTR wstrID = NULL;
                             hr = pDevice->GetId(&wstrID);
                             CString  str ;
                             BSTR  bRs =::SysAllocString(wstrID);
                             str = (CString)bRs;
                             m_strId.Add(str);
                             SysFreeString(bRs);
                             if (SUCCEEDED(hr))
                             {
                                 IPropertyStore *pStore;
                                 hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);
                                 if (SUCCEEDED(hr))
                                 {
                                     PROPVARIANT friendlyName;
                                     PropVariantInit(&friendlyName);
                                     hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);
                                     if (SUCCEEDED(hr))
                                     {  
                                         BSTR  bRes = ::SysAllocString(friendlyName.pwszVal);
                                         CString  str =(CString) bRes;                                       
                                         m_strFriedlyName.Add(str);
                                         PropVariantClear(&friendlyName);
                                     }
                                     pStore->Release();
                                 }
                             }
                             pDevice->Release();
                         }
                     }
                 }
                 pDevices->Release();
             }
             pEnum->Release();
         }
     }     
 }

void  CSwtichAudioDev::SetDefaultAud(CString  &strFri)
{
    //int iCnt = m_strFriedlyName.GetCount();
    //for(int i=0;i<iCnt;i++)
    //{
    //    CString str = m_strFriedlyName.GetAt(i);
    //    if(strFri==str)
    //    {
    //        SetDefaultAudioPlaybackDevice(m_strId.GetAt(i).AllocSysString());
    //    }
    //}
}