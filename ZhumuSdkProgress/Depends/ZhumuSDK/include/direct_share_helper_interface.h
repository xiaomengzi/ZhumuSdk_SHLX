/*!
* \�ļ���direct_share_service_helper_interface.h
* \������ֱ�ӹ����������ӿ�
*
*/
#ifndef ZHUMU_DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#define ZHUMU_DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*
typedef enum DirectShareStatusType_Enum
{
DirectShare_Unknown = 0,
DirectShare_In_SIP_Call,
//DirectShare_Called_Too_Frequency, //move it to return value as SDKERR_TOO_FREQUENT_CALL
DirectShare_Start_Connecting,
DirectShare_UltraSound_Detect_Failed,
DirectShare_Need_MeetingID_Or_ParingCode,
DirectShare_AccountID_Not_Same,
DirectShare_NetWork_Error,
DirectShare_Target_Version_Old,
DirectShare_Direct_Share_Start,
DirectShare_Direct_Share_Stop,
}DirectShareStatusType;
*/
typedef enum DirectShareStatusStatus_Enum
{
	DirectShare_Unknown = 0,  // Ŀǰû��ʹ�á�Ϊ�˳�ʼ��
	DirectShare_Connecting,  // ���Կ�ʼֱ�ӷ����ȴ���
	DirectShare_In_Direct_Share_Mode, //ֱ�ӹ���ģʽ
	DirectShare_Ended,  //ֱ�ӹ������
	DirectShare_Need_MeetingID_Or_PairingCode, // ��Ҫ�û����û���id/paring����
	DirectShare_NetWork_Error, // ��������Ժ�����
	DirectShare_Other_Error,   //����������Ҫ������SIP����ģʽ
	DirectShare_WrongMeetingID_Or_SharingKey,///<Wrong meeting id or sharing key.
}DirectShareStatus;

/// \������ͨ������ID������ֱ�ӹ���ӿڡ�
///
class IDirectShareViaMeetingIDOrPairingCodeHandler
{
public:
	virtual ~IDirectShareViaMeetingIDOrPairingCodeHandler() {};

	/// \������������ָ���Ļ������ƥ�䡣
	/// \������meetingNumber ָ������š�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError \endlink
	virtual SDKError TryWithMeetingNumber(UINT64 meetingNumber) = 0;

	/// \����������ƥ�乲���롣
	/// \������pairingCode ָ�������롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	virtual SDKError TryWithPairingCode(const wchar_t* pairingCode) = 0;

	/// \������ɾ����ǰ��ֱ�ӹ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	virtual SDKError Cancel() = 0;
};

/// \������ֱ�ӹ������ֻص��¼�
///
class IDirectShareServiceHelperEvent
{
public:
	/// \���������ֱ�ӹ����״̬�������ģ��������ص��¼���
	/// \������status ָ��ֱ�ӹ����״̬���й���ϸ��Ϣ����μ�DirectShareStatus enum��
	/// \������handler ָ��IDirectShareViaMeetingIDOrPairingCodeHandler��ָ�롣ֻ�е�״ֵ̬ΪDirectShare_Need_MeetingID_Or_ParingCodeʱ����Ч��
	/// SDK�û�����ͨ��IDirectShareViaMeetingIDOrPairingCodeHandler��������_paring_code��_meeting_number��ֵ���ܿ�ʼֱ�ӹ����й���ϸ��Ϣ����μ� IDirectShareViaMeetingIDOrPairingCodeHandler
	virtual void OnDirectShareStatusUpdate(DirectShareStatus status, IDirectShareViaMeetingIDOrPairingCodeHandler* handler) = 0;

};

/// \������ֱ�ӹ������ӿ�
///
class IDirectShareServiceHelper
{
public:

	/// \����������ֱ�ӹ������ص��¼�
	/// \������pEvent ָ�����ֱ�ӹ�������¼���IDirectShareServiceHelperEvent*��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	virtual SDKError SetEvent(IDirectShareServiceHelperEvent* pEvent) = 0;

	/// \������ȷ���Ƿ���Կ�ʼֱ�ӹ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	virtual SDKError CanStartDirectShare() = 0;

	/// \������ȷ���Ƿ����ڽ���ֱ�ӹ���
	/// \���أ�TRUE��ʾֱ�ӹ������ڽ�����
	virtual bool	 IsDirectShareInProgress() = 0;

	/// \��������ʼֱ�ӹ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	/// \remarks Only login user can call this API.
	virtual SDKError StartDirectShare() = 0;

	// \������ֱֹͣ�ӹ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum
	/// \remarks Only login user can call this API.
	virtual SDKError StopDirectShare() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif