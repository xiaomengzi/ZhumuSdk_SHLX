// ZhumuSdkProgress.cpp : ����Ӧ�ó������ڵ㡣
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

    // �˳�ʱ����::PostQuitMessage(0);
    return 0;
}