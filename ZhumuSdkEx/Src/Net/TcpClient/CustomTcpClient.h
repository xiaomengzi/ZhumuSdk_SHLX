#ifndef _CUSTOMTCPCLIENT_H_
#define _CUSTOMTCPCLIENT_H_

#include "SocketInterface.h"
#include "HPSocket.h"
#include <string>

class CCustomTcpClient :public CTcpClientListener
{
public:
    struct TPkgBody
    {
        char name[30];
        short age;
        char desc[1];
    };

public:
    CCustomTcpClient();
    ~CCustomTcpClient();


public:
    bool InterfaceCommunicate(const std::string strIp, const int nPort, const std::string strSend, std::string& strReceive);

    bool SendContentTcpClient(std::string strContent);

    bool StartTcpClient(const std::string strIp, const int nPort);

    void StopTcpClient();

private:
    virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
    virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
    virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);

private:
    bool AnalyzeFeedbackContent(std::string strReceive);
private:
    CTcpPackClientPtr m_pClient;
    bool m_bCanReturn;
    UINT64 m_nStartTime;
    std::string m_strReceive;
};


#endif //_CUSTOMTCPCLIENT_H_


