/*!
* \�ļ���meeting_claosecaptioin_interface.h
* \������ Meeting Service Closed Caption Interface.
* \ע�⣺������zhumu�����û��Զ������ģʽ.
*/
#ifndef _MEETING_CLOSEDCAPTION_INTERFACE_H_
#define _MEETING_CLOSEDCAPTION_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/// \������������Ļ�������ص��¼���
///
class IClosedCaptionControllerEvent
{
public:
	/// \������ָ���û�����������Ļ��Ϣʱ�Ļص��¼���
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	/// \�������û����յ�������Ļ��Ϣʱ�Ļص��¼���
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time) = 0;
};


class IClosedCaptionController
{
public:
	/// ����������Ļ(CC)�Ŀ������¼�
	virtual SDKError SetEvent(IClosedCaptionControllerEvent* pEvent) = 0;
	/// ȷ����ǰ�����Ƿ�֧��CC���ܡ�
	virtual bool IsMeetingSupportCC() = 0;
	/// ����ѯ�Ƿ��ܹ�ָ�����˷���CC��
	virtual bool CanAssignOthersToSendCC() = 0;
	/// ָ��һ���û�����CC��
	/// Zero(0)��ʾ�Լ����䵱ǰ�û�
	virtual SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned) = 0;
	/// ȷ���Ƿ���Խ����û�ָ��ΪCC���ͷ���
	virtual bool CanBeAssignedToSendCC(unsigned int userid) = 0;
	/// ��ѯ�û��Ƿ���Է���CC��
	virtual bool CanSendClosedCaption() = 0;
	/// ����CC��Ϣ��
	virtual SDKError SendClosedCaption(const wchar_t* ccMsg) = 0;
	/// ȷ���Ƿ��ܱ���CC
	virtual bool IsSaveCCEnabled() = 0;
	/// ����CC��ʷ��
	virtual SDKError SaveCCHistory() = 0;
	/// ��ȡ����CC��·����
	virtual const wchar_t* GetClosedCaptionHistorySavedPath() = 0;
	/// ��ȡ����������ʹ�õ�CC URL��
	virtual const wchar_t* GetClosedCaptionUrlFor3rdParty() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif