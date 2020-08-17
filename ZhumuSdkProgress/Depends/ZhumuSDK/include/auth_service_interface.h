/*!
* \文件 auth_service_interface.h
* \描述：身份验证服务接口
*
*/
#ifndef ZHUMU_AUTH_SERVICE_INTERFACE_H_
#define ZHUMU_AUTH_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum AuthResult
\描述：SDK验证结果
更详细的结构描述
*/
enum AuthResult
{
	AUTHRET_SUCCESS,///<身份验证成功。
	AUTHRET_KEYORSECRETEMPTY,///<需要验证的密钥或密钥为空.
	AUTHRET_KEYORSECRETWRONG,///<需要验证的密钥或密钥错误.
	AUTHRET_ACCOUNTNOTSUPPORT,///<用户帐户不支持
	AUTHRET_ACCOUNTNOTENABLESDK,///<SDK对该用户帐户不可用.
	AUTHRET_UNKNOWN,///<未知错误.
	AUTHRET_SERVICE_BUSY,///<服务正忙.
	AUTHRET_NONE,///<初始状态.
	AUTHRET_OVERTIME,///<超时.
	AUTHRET_NETWORKISSUE,///<网络错误.
};

/*! \enum LOGINSTATUS
\描述：登录状态。
更详细的结构描述
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,///< 未登录
	LOGIN_PROCESSING,///< 正在登陆
	LOGIN_SUCCESS,///< 登陆成功
	LOGIN_FAILED,///< 登陆失败
};

/*! \struct tagAuthParam
\描述： SDK认证参数.
更详细的结构描述
*/
typedef struct tagAuthParam
{
	const wchar_t* appKey;///< APP Key 字符串
	const wchar_t* appSecret;///< APP Secret 字符串
	tagAuthParam()
	{
		appKey = NULL;
		appSecret = NULL;
	}
}AuthParam;

typedef struct tagAuthContext
{
	const wchar_t* jwt_token; /*!JWT token. You may generate your JWT token using the online tool https://jwt.io/. **It is highly recommended to generate your JWT token in your backend server.**
							  JWT is generated with three core parts: Header, Payload, and Signature. When combined, these parts are separated by a period to form a token: `aaaaa.bbbbb.cccc`.
							  Please follow this template to compose your payload for SDK initialization:
							  ** Header
							  {
							  "alg": "HS256",
							  "typ": "JWT"
							  }
							  ** Payload
							  {
							  "appKey": "string", // Your SDK key
							  "iat": long, // access token issue timestamp
							  "exp": long, // access token expire time
							  "tokenExp": long // token expire time
							  }
							  ** Signature
							  HMACSHA256(
							  base64UrlEncode(header) + "." +
							  base64UrlEncode(payload),
							  "Your SDK secret here"
							  )
							  */
	tagAuthContext()
	{
		jwt_token = NULL;
	}

}AuthContext;

/*! \enum LoginType
\描述：用户登陆类型
更详细的结构描述
*/
enum LoginType
{
	LoginType_Unknown,
	LoginType_Email,///<用户邮箱登陆
	LoginType_SSO,///<SSO token登陆
};

typedef struct tagLoginParam4Email
{
	const wchar_t* userName;///< 帐户名称，电子邮件等
	const wchar_t* password;///< 账户密码
	bool bRememberMe;
}LoginParam4Email;

typedef struct tagLoginParam4SSO
{
	const wchar_t* ssoToken;///< 帐户登录时的SSO令牌
	bool bRememberMe;
}LoginParam4SSO;

/*! \struct tagLoginParam
\描述：账户登录参数
更详细的结构描述
*/
typedef struct tagLoginParam
{
	LoginType loginType;
	union
	{
		LoginParam4Email emailLogin;
		LoginParam4SSO ssoLogin;
	}ut;

	tagLoginParam()
	{
		loginType = LoginType_Email;
		memset(&ut, 0, sizeof(ut));

	}
}LoginParam;

/// \描述：账户信息接口
///
class IAccountInfo
{
public:
	/// \描述：获取账户名称
	/// \返回：返回值是帐户显示名称
	virtual const wchar_t* GetDisplayName() = 0;

	/// \描述：获取登陆类型
	/// \返回：返回值是帐户登录类型
	virtual LoginType GetLoginType() = 0;
	virtual ~IAccountInfo() {};
};

/// \描述：身份验证服务回调事件
///
class IAuthServiceEvent
{
public:
	/// \描述：认证结果的回调
	/// \参数：ret 认证结果. 
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \描述：登陆结果回调
	/// \参数：ret登陆状态，具体查看 LOGINSTATUS.
	/// \参数：pAccountInfo 如果结果是 LOGINRET_SUCCESS将不是空值，否则是一个空值
	virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo) = 0;

	/// \描述：登出结果回调
	virtual void onLogout() = 0;

	/// \描述：身份过期，请重新登录或通过REST api生成新的zhumu访问令牌
	virtual void onIdentityExpired() = 0;

	virtual void onZoomAuthIdentityExpired() = 0;
};

class IDirectShareServiceHelper;
class IOutlookPluginIntegrationHelper;
class IAuthService
{
public:
	/// \描述：设置身份验证服务回调事件
	/// \参数：pEvent 指向接收身份验证事件的IAuthServiceEvent*的指针。
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值是非SDKErr_Success得值. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \描述： Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值是非SDKErr_Success得值. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \描述： Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值是非SDKErr_Success得值. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError SDKAuth(AuthContext& authContext) = 0;

	/// \描述：获取认证结果
	/// \返回：返回值是身份验证状态。要获取扩展的错误信息，请参考 AuthResult enum
	virtual AuthResult GetAuthResult() = 0;

	/// \描述：获取 SDK 身份
	/// \返回：SDK 身份
	virtual const wchar_t* GetSDKIdentity() = 0;

	/// \描述：账号登陆
	/// \参数: 用于帐户登录的参数，请参考LoginParam。
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值是非SDKErr_Success得值. 要获取扩展的错误信息，请参考 SDKError enum.
	/// 您需要在onAuthenticationReturn返回成功状态后调用此api。
	virtual SDKError Login(LoginParam& param) = 0;

	// \描述：账号登出
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值是非SDKErr_Success得值. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError LogOut() = 0;

	// \描述：获取登陆账号信息
	/// \返回：如果成功登录帐户，返回值为帐户信息，否则为NULL。
	virtual IAccountInfo* GetAccountInfo() = 0;

	// \描述：获取登陆状态
	/// \返回：返回值是login status。要获得扩展的错误信息，请参阅LOGINSTATUS enum
	virtual LOGINSTATUS GetLoginStatus() = 0;

	// \描述：获取outlook插件集成助手。 
	/// \返回：如果登录成功，返回值是outlook插件integreation helper的指针，否则为NULL。
	virtual IOutlookPluginIntegrationHelper* GetOutlookPluginHeler() = 0;

	// \描述：获取直接显示服务助手。
	/// \返回：如果您成功登录帐户，返回值是direct share service helper的指针，否则为NULL。
	virtual IDirectShareServiceHelper* GetDirectShareServiceHeler() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif
