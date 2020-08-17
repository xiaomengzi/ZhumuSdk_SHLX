/*!
* \�ļ� auth_service_interface.h
* \�����������֤����ӿ�
*
*/
#ifndef ZHUMU_AUTH_SERVICE_INTERFACE_H_
#define ZHUMU_AUTH_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum AuthResult
\������SDK��֤���
����ϸ�Ľṹ����
*/
enum AuthResult
{
	AUTHRET_SUCCESS,///<�����֤�ɹ���
	AUTHRET_KEYORSECRETEMPTY,///<��Ҫ��֤����Կ����ԿΪ��.
	AUTHRET_KEYORSECRETWRONG,///<��Ҫ��֤����Կ����Կ����.
	AUTHRET_ACCOUNTNOTSUPPORT,///<�û��ʻ���֧��
	AUTHRET_ACCOUNTNOTENABLESDK,///<SDK�Ը��û��ʻ�������.
	AUTHRET_UNKNOWN,///<δ֪����.
	AUTHRET_SERVICE_BUSY,///<������æ.
	AUTHRET_NONE,///<��ʼ״̬.
	AUTHRET_OVERTIME,///<��ʱ.
	AUTHRET_NETWORKISSUE,///<�������.
};

/*! \enum LOGINSTATUS
\��������¼״̬��
����ϸ�Ľṹ����
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,///< δ��¼
	LOGIN_PROCESSING,///< ���ڵ�½
	LOGIN_SUCCESS,///< ��½�ɹ�
	LOGIN_FAILED,///< ��½ʧ��
};

/*! \struct tagAuthParam
\������ SDK��֤����.
����ϸ�Ľṹ����
*/
typedef struct tagAuthParam
{
	const wchar_t* appKey;///< APP Key �ַ���
	const wchar_t* appSecret;///< APP Secret �ַ���
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
\�������û���½����
����ϸ�Ľṹ����
*/
enum LoginType
{
	LoginType_Unknown,
	LoginType_Email,///<�û������½
	LoginType_SSO,///<SSO token��½
};

typedef struct tagLoginParam4Email
{
	const wchar_t* userName;///< �ʻ����ƣ������ʼ���
	const wchar_t* password;///< �˻�����
	bool bRememberMe;
}LoginParam4Email;

typedef struct tagLoginParam4SSO
{
	const wchar_t* ssoToken;///< �ʻ���¼ʱ��SSO����
	bool bRememberMe;
}LoginParam4SSO;

/*! \struct tagLoginParam
\�������˻���¼����
����ϸ�Ľṹ����
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

/// \�������˻���Ϣ�ӿ�
///
class IAccountInfo
{
public:
	/// \��������ȡ�˻�����
	/// \���أ�����ֵ���ʻ���ʾ����
	virtual const wchar_t* GetDisplayName() = 0;

	/// \��������ȡ��½����
	/// \���أ�����ֵ���ʻ���¼����
	virtual LoginType GetLoginType() = 0;
	virtual ~IAccountInfo() {};
};

/// \�����������֤����ص��¼�
///
class IAuthServiceEvent
{
public:
	/// \��������֤����Ļص�
	/// \������ret ��֤���. 
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \��������½����ص�
	/// \������ret��½״̬������鿴 LOGINSTATUS.
	/// \������pAccountInfo �������� LOGINRET_SUCCESS�����ǿ�ֵ��������һ����ֵ
	virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo) = 0;

	/// \�������ǳ�����ص�
	virtual void onLogout() = 0;

	/// \��������ݹ��ڣ������µ�¼��ͨ��REST api�����µ�zhumu��������
	virtual void onIdentityExpired() = 0;

	virtual void onZoomAuthIdentityExpired() = 0;
};

class IDirectShareServiceHelper;
class IOutlookPluginIntegrationHelper;
class IAuthService
{
public:
	/// \���������������֤����ص��¼�
	/// \������pEvent ָ����������֤�¼���IAuthServiceEvent*��ָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ�Ƿ�SDKErr_Success��ֵ. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \������ Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ�Ƿ�SDKErr_Success��ֵ. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \������ Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ�Ƿ�SDKErr_Success��ֵ. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError SDKAuth(AuthContext& authContext) = 0;

	/// \��������ȡ��֤���
	/// \���أ�����ֵ�������֤״̬��Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� AuthResult enum
	virtual AuthResult GetAuthResult() = 0;

	/// \��������ȡ SDK ���
	/// \���أ�SDK ���
	virtual const wchar_t* GetSDKIdentity() = 0;

	/// \�������˺ŵ�½
	/// \����: �����ʻ���¼�Ĳ�������ο�LoginParam��
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ�Ƿ�SDKErr_Success��ֵ. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	/// ����Ҫ��onAuthenticationReturn���سɹ�״̬����ô�api��
	virtual SDKError Login(LoginParam& param) = 0;

	// \�������˺ŵǳ�
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ�Ƿ�SDKErr_Success��ֵ. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError LogOut() = 0;

	// \��������ȡ��½�˺���Ϣ
	/// \���أ�����ɹ���¼�ʻ�������ֵΪ�ʻ���Ϣ������ΪNULL��
	virtual IAccountInfo* GetAccountInfo() = 0;

	// \��������ȡ��½״̬
	/// \���أ�����ֵ��login status��Ҫ�����չ�Ĵ�����Ϣ�������LOGINSTATUS enum
	virtual LOGINSTATUS GetLoginStatus() = 0;

	// \��������ȡoutlook����������֡� 
	/// \���أ������¼�ɹ�������ֵ��outlook���integreation helper��ָ�룬����ΪNULL��
	virtual IOutlookPluginIntegrationHelper* GetOutlookPluginHeler() = 0;

	// \��������ȡֱ����ʾ�������֡�
	/// \���أ�������ɹ���¼�ʻ�������ֵ��direct share service helper��ָ�룬����ΪNULL��
	virtual IDirectShareServiceHelper* GetDirectShareServiceHeler() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif
