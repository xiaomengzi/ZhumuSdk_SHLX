#ifndef _CUSTOMTCPSERVER_H_
#define _CUSTOMTCPSERVER_H_

#include <string>
#include "HPSocket.h"
#include "SocketInterface.h"


 class CCustomTcpServerEvent
 {
 public:
     virtual int OnReceive(std::string strReceive, int iLength) = 0;
     virtual int OnInitResult(int nInitResult) = 0;
     virtual int OnAuthResult(int nAuthResult) = 0;
     virtual int OnLoginResult(int nLoginResult) = 0;
    
 };
 


class CCustomTcpServer
    :public CTcpPullServerListener
{
public:
    CCustomTcpServer();
    ~CCustomTcpServer();

    void SetEvent(CCustomTcpServerEvent* _event);

    // 开启服务
    bool StartServer(int nServerPort);
    // 关闭服务
    bool StopServer();

public:
    virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
    virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, SOCKET soClient);
    virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
    virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
    virtual EnHandleResult OnShutdown(ITcpServer* pSender);

private:
    CCustomTcpServerEvent* m_pEvent;
    //CTcpPullServerPtr m_pTcpServer;
    CTcpPackServerPtr m_pTcpServer;
};

#endif // _CUSTOMTCPSERVER_H_
