// ZhumuSdkProgress.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ZhumuSdkProgress.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    //CSDKDemoApp app_;
    //app_.Run(hInstance);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (WM_QUIT == msg.message)
        {
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 退出时发送::PostQuitMessage(0);
    return 0;
}