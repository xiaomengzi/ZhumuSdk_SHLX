// ZhumuSdkEx.cpp : 定义 DLL 应用程序的导出函数。
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
    // 初始化日志
    plog::init(plog::info, CUtils::GetLogFilePath().c_str(), 1000000, 5);

    // 创建接口代理
    if (nullptr == g_pZhumuSdkImpl)
    {
        g_pZhumuSdkImpl = new CZhumuSdkImpl;
        g_pZhumuSdkImpl->SetEvent(event);
        // 启动tcp服务
        if (false == g_pZhumuSdkImpl->StartTcpServer())
        {
            return SDKERR_UNKNOWN;
        }

        //// 启动进程
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

    // 初始化sdk
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
    // 初始化sdk
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
    // 初始化sdk
    bool bRet = g_pZhumuSdkImpl->LoginSDK(loginParam);

    if (false == bRet)
    {
        return SDKERR_UNKNOWN;
    }

    return SDKERR_SUCCESS;
}

END_ZHUMUSDKEX_NAMESPACE