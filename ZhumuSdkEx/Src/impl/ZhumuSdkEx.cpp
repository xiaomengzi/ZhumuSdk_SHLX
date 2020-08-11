// ZhumuSdkEx.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ZhumuSdkEx.h"
#include "ZhumuSdkImpl.h"
#include "plog/Log.h"
#include "Utils.h"


CZhumuSdkImpl* g_pZhumuSdkImpl = nullptr;

BEGIN_ZHUMUSDKEX_NAMESPACE

ZHUMUSDKEX_API SDKError Zhumu_CreateSDK(ZhumuSdkEx_Event* event, const char* exePath)
{
    bool bRet = false;
    // ��ʼ����־
    plog::init(plog::info, CUtils::GetLogFilePath().c_str(), 1000000, 5);

    // �����ӿڴ���
    if (nullptr == g_pZhumuSdkImpl)
    {
        g_pZhumuSdkImpl = new CZhumuSdkImpl;
        g_pZhumuSdkImpl->SetEvent(event);
        // ����tcp����
        if (false == g_pZhumuSdkImpl->StartTcpServer())
        {
            return SDKERR_UNKNOWN;
        }

        //// ��������
        //if (false == g_pZhumuSdkImpl->StartSdkProcess(exePath))
        //{
        //    return SDKERR_UNKNOWN;
        //}
    }

    return SDKERR_SUCCESS;
}

ZHUMUSDKEX_API SDKError Zhumu_InitSDK(ZmSdkInitParam initParam)
{
    if (nullptr == g_pZhumuSdkImpl)
    {
        return SDKERR_UNKNOWN;
    }

    // ��ʼ��sdk
    bool bRet = g_pZhumuSdkImpl->InitSDK(initParam);

    if (false == bRet)
    {
        return SDKERR_UNKNOWN;
    }

    return SDKERR_SUCCESS;
}

ZHUMUSDKEX_API SDKError Zhumu_DestorySDK()
{
    if (nullptr == g_pZhumuSdkImpl)
    {
        return SDKERR_UNKNOWN;
    }
    // ��ʼ��sdk
    bool bRet = g_pZhumuSdkImpl->DestorySDK();

    if (false == bRet)
    {
        return SDKERR_UNKNOWN;
    }

    return SDKERR_SUCCESS;
}

ZHUMUSDKEX_API SDKError Zhumu_SLoginSDK(ZmSdkLoginParam loginParam)
{
    if (nullptr == g_pZhumuSdkImpl)
    {
        return SDKERR_UNKNOWN;
    }
    // ��ʼ��sdk
    bool bRet = g_pZhumuSdkImpl->LoginSDK(loginParam);

    if (false == bRet)
    {
        return SDKERR_UNKNOWN;
    }

    return SDKERR_SUCCESS;
}

END_ZHUMUSDKEX_NAMESPACE