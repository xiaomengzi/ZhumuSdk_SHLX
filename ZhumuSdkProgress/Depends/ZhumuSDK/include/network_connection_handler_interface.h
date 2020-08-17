/*!
* \�ļ� network_connection_handler_interface.h
* \����������������Ϣ֪ͨ�������
*
*/

#ifndef ZHUMU_NETWORK_CONNECTION_HANDLER_H_
#define ZHUMU_NETWORK_CONNECTION_HANDLER_H_
/// \������ Zhumu SDK Namespace
/// 
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \struct tagProxySettings
    \brief The proxy that the user want to use according to the net environment.
    Here are more detailed structural descriptions.
*/
typedef struct tagProxySettings
{
	const wchar_t* proxy;///<The proxy ip address and port that user want to use, should be organized like ip:port, such as '255.255.255.255:8080'. Use ';' to separate multi proxies.
	bool auto_detect;///<TRUE indicates automatic detection.
	tagProxySettings()
	{
		proxy = NULL;
		auto_detect = false;
	}
}ProxySettings;
/// \������ ����������Ϣ�ص��ӿ�
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler() {};
	/// \���������ش���������ֵ
	virtual const wchar_t* GetProxyHost() = 0;
	/// \���������ش���˿ڵ�ֵ
	virtual unsigned int GetProxyPort() = 0;
	/// \���������ش���������ֵ
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \������Ϊ�˴�������������û���������
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \������ȡ������˴�����û���������
	virtual void Cancel() = 0;

};

/// \������SSL֤����֤�ص��ӿ�
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler() {};

	// \���������ذ䷢����SSL֤���ֵ
	virtual const wchar_t* GetCertIssuedTo() = 0;
	// \����������SSL֤���ֵ
	virtual const wchar_t* GetCertIssuedBy() = 0;
	// \����������SSL֤������к�
	virtual const wchar_t* GetCertSerialNum() = 0;
	/// \����������ssl֤���ָ��
	virtual const wchar_t* GetCertFingerprint() = 0;
	// \���������δ�SSL֤��
	virtual void Trust() = 0;
	// \��������Ҫ���δ�SSL֤��
	virtual void Cancel() = 0;

};

/// \�������������Ӵ������ص��¼�
///
class INetworkConnectionHandler
{
public:
	/// \���������������֪ͨ
	virtual void onProxyDetectComplete() = 0;
	/// \���������յ�����Ϣʱ��������ʾ�û����������û���������
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	/// \���������յ�����Ϣʱ��������ʾ�û�����SSL֤����֤��
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

/// \�������������Ӱ����ӿ�
///
class INetworkConnectionHelper
{
public:
	/// \������Ϊ����������Ϣ֪ͨע�ᴦ�����
	/// \������pNetworkHandler �����յ�����Ϣ����ʱ������Handler
	/// \����: ��������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \������ע������������Ϣ֪ͨ�Ĵ������
	/// \����: ��������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;

	/// \brief Set the proxy that the user want to use according to your net environment.
	/// \praam proxy_setting The proxy ip address and port that user want to use, should be organized like ip:port, such as '255.255.255.255:8080'. Using ';' to separate multi proxies.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ConfigureProxy(ProxySettings& proxy_setting) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif