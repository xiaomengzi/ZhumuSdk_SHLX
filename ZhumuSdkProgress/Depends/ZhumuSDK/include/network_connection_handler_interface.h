/*!
* \文件 network_connection_handler_interface.h
* \描述：网络连接消息通知处理程序
*
*/

#ifndef ZHUMU_NETWORK_CONNECTION_HANDLER_H_
#define ZHUMU_NETWORK_CONNECTION_HANDLER_H_
/// \描述： Zhumu SDK Namespace
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
/// \描述： 代理设置信息回调接口
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler() {};
	/// \描述：返回代理主机的值
	virtual const wchar_t* GetProxyHost() = 0;
	/// \描述：返回代理端口的值
	virtual unsigned int GetProxyPort() = 0;
	/// \描述：返回代理描述的值
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \描述：为此代理的连接输入用户名和密码
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \描述：取消输入此代理的用户名和密码
	virtual void Cancel() = 0;

};

/// \描述：SSL证书验证回调接口
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler() {};

	// \描述：返回颁发给的SSL证书的值
	virtual const wchar_t* GetCertIssuedTo() = 0;
	// \描述：返回SSL证书的值
	virtual const wchar_t* GetCertIssuedBy() = 0;
	// \描述：返回SSL证书的序列号
	virtual const wchar_t* GetCertSerialNum() = 0;
	/// \描述：返回ssl证书的指纹
	virtual const wchar_t* GetCertFingerprint() = 0;
	// \描述：信任此SSL证书
	virtual void Trust() = 0;
	// \描述：不要信任此SSL证书
	virtual void Cancel() = 0;

};

/// \描述：网络连接处理程序回调事件
///
class INetworkConnectionHandler
{
public:
	/// \描述：代理检测完成通知
	virtual void onProxyDetectComplete() = 0;
	/// \描述：当收到此消息时，必须提示用户输入代理的用户名和密码
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	/// \描述：当收到此消息时，必须提示用户进行SSL证书验证吗
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

/// \描述：网络连接帮助接口
///
class INetworkConnectionHelper
{
public:
	/// \描述：为网络连接消息通知注册处理程序。
	/// \参数：pNetworkHandler 当接收到此消息类型时将调用Handler
	/// \返回: 如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \描述：注销网络连接消息通知的处理程序。
	/// \返回: 如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;

	/// \brief Set the proxy that the user want to use according to your net environment.
	/// \praam proxy_setting The proxy ip address and port that user want to use, should be organized like ip:port, such as '255.255.255.255:8080'. Using ';' to separate multi proxies.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ConfigureProxy(ProxySettings& proxy_setting) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif