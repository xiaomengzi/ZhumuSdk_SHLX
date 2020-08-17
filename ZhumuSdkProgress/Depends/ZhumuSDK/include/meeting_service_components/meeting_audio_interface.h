/*!
* \�ļ���meeting_audio_interface.h
* \������������Ƶ����ӿ�
*
*/
#ifndef ZHUMU_MEETING_AUDIO_INTERFACE_H_
#define ZHUMU_MEETING_AUDIO_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>

/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum AudioStatus
\��������Ƶ״̬.
�����Ǹ���ϸ�Ľṹ����
*/
enum AudioStatus
{
	Audio_None,///<��ʼ��.
	Audio_Muted,///<����״̬.
	Audio_UnMuted,///<δ����״̬
	Audio_Muted_ByHost,///<�������˾���.
	Audio_UnMuted_ByHost,///<�������˽Ӵ�����.
	Audio_MutedAll_ByHost,///<������ȫ�徲��.
	Audio_UnMutedAll_ByHost,///<֧���˽Ӵ�ȫ�徲��.
};
/*! \enum AudioType
\�����������û�����Ƶ����
�����Ǹ���ϸ�Ľṹ������
*/
enum AudioType
{
	AUDIOTYPE_NONE,///<��������Ƶ���͡�
	AUDIOTYPE_VOIP,///< VoIP ģʽ.
	AUDIOTYPE_PHONE,///< telephone ģʽ.
	AUDIOTYPE_UNKNOW,///<λ��ģʽ.
};

/// \���������û����������յ�����Ƶ��Ҫ�����д���
class IRequestStartAudioHandler
{
public:
	virtual ~IRequestStartAudioHandler() {};
	/// \��������ȡҪ�����Ƶ���û�ID��
	/// \���أ���������ɹ����򷵻��û�ID��
	virtual unsigned int GetReqFromUserId() = 0;
	/// \������ʵ����������ʲôҲ�����أ�����Ի١�
	virtual SDKError Ignore() = 0;
	/// \������ʵ������Ҫ�󣬴���Ƶ������Ի١�
	virtual SDKError Accept() = 0;
	/// \�����������ڻ�����������Ƶ���������ʵ���Ի١�
	virtual SDKError Cancel() = 0;
};

class IUserAudioStatus
{
public:
	virtual unsigned int GetUserId() = 0;
	virtual AudioStatus GetStatus() = 0;
	virtual AudioType   GetAudioType() = 0;
	virtual ~IUserAudioStatus() {};
};

/// \������������Ƶ�ص��¼�
///
class IMeetingAudioCtrlEvent
{
public:
	/// \���������뷭
	/// \������lstAudioStatusChange ��Ƶ״̬�ı���û���Ϣ�б�һ���������ý��������б�����ա�
	/// \������strAudioStatusList ��Ƶ״̬�ı���û���Ϣ�б���json��ʽ���档�˲���Ŀǰ��Ч�������ڱ�����
	virtual void onUserAudioStatusChange(std::vector<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \��������Ƶ���ڻ״̬���û����ĵĻص��¼���
	/// \������plstActiveAudio �洢��Ƶ���ڻ״̬���û���ID���б�
	virtual void onUserActiveAudioChange(std::vector<unsigned int>* plstActiveAudio) = 0;

	/// \������Ҫ�����������Ƶ�Ļص��¼���
	/// \������handler_ һ��ָ��IRequestStartAudioHandler��ָ�롣�й���ϸ��Ϣ����μ�IRequestStartAudioHandler
	virtual void onHostRequestStartAudio(IRequestStartAudioHandler* handler_) = 0;
};

/// \������������Ƶ�������ӿڡ�
///
class IMeetingAudioController
{
public:
	/// \���������û�����Ƶ�豸�������ص��¼�
	/// \������pEvent һ��ָ�� IMeetingAudioCtrlEvent* �����ָ��. 
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \���������� Voip ��Ƶ����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError JoinVoip() = 0;

	/// \�������뿪 Voip ��Ƶ����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError LeaveVoip() = 0;

	/// \����������
	/// \������userId ָ��Ҫ�����ĸ��û�����Ƶ��������㣬���������û�
	/// \������allowUnmuteBySelf ָ������ȫ�徲��ʱ�Ƿ����Լ�ȡ������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \������ȡ������
	/// \������userId ָ��Ҫȡ���������û���Ƶ�����Ϊ0����ȡ�������û��ľ���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \�������Ƿ���Ա��Լ��������
	/// \���أ��Ƿ���Ա��Լ��������
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual bool CanUnMuteBySelf() = 0;

	/// \���������û��μӻ���ʱ���þ�������
	/// \������bEnable ָ���������빦�����û���á�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \���������û��μӻ��뿪����ʱ�����ò����������ܡ�
	/// \����: bEnable ָ�����û�������뿪����ʱ�����������ܣ����û���á�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif