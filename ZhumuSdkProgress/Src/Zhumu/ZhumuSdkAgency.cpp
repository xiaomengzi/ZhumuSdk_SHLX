#include "stdafx.h"
#include "ZhumuSdkAgency.h"
#include "Business/CustomData.h"
#include "BusinessLogic.h"
#include "plog/Log.h"
#include "Utils.h"
#include "zhumu_sdk.h"
#include "meeting_service_components/meeting_configuration_interface.h"


CZhumuSdkAgency *CZhumuSdkAgency::m_pInstance = nullptr;

CZhumuSdkAgency::CZhumuSdkAgency()
{
    m_pAuthService = nullptr;
    m_pMeetingService = nullptr;
}


CZhumuSdkAgency::~CZhumuSdkAgency()
{
}

void CZhumuSdkAgency::Destory()
{
    DestroySettingService();
    DestroyMeetingService();
    DestroyAuthService();
}


CZhumuSdkAgency * CZhumuSdkAgency::Initialize()
{
    return CZhumuSdkAgency::GetInstance();
}

void CZhumuSdkAgency::Uninitialize()
{
    if (m_pInstance != nullptr)
    {
        delete m_pInstance;
    }
}

CZhumuSdkAgency * CZhumuSdkAgency::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CZhumuSdkAgency;
    }
    return m_pInstance;
}


void CZhumuSdkAgency::onAuthenticationReturn(AuthResult ret)
{
    CBusinessLogic::GetInstance()->AuthenticationReturn(ret);
    
}

void CZhumuSdkAgency::onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    CBusinessLogic::GetInstance()->LoginReturn(ret, pAccountInfo);
}

void CZhumuSdkAgency::onLogout()
{

}

void CZhumuSdkAgency::onIdentityExpired()
{

}

void CZhumuSdkAgency::onZoomAuthIdentityExpired()
{

}

void CZhumuSdkAgency::onMeetingStatusChanged(MeetingStatus status, int iResult /*= 0*/)
{
    CBusinessLogic::GetInstance()->MeetingStatusChanged(status, iResult);
    if (MEETING_STATUS_INMEETING == status)
    {
        // 进入会议成功 设置标志位
      
        IMeetingConfiguration* pMeetingConfig = nullptr;
        pMeetingConfig = m_pMeetingService->GetMeetingConfiguration();
        if (nullptr != pMeetingConfig)
        {
            pMeetingConfig->SetBottomFloatToolbarWndVisibility(true);
        }
    }
}

void CZhumuSdkAgency::onMeetingStatisticsWarningNotification(StatisticsWarningType type)
{

}

void CZhumuSdkAgency::onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler)
{

}

void CZhumuSdkAgency::onMeetingParameterNotification(const MeetingParameter* meeting_param)
{

}

SDKError CZhumuSdkAgency::InitZhunmuSDK(ZHUMU_SDK_NAMESPACE::InitParam& zm_param)
{
    return ZHUMU_SDK_NAMESPACE::Zhumu_InitSDK(zm_param);
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::AuthSDK(wchar_t *key, wchar_t *secret)
{
    if (nullptr != m_pAuthService)
    {
        AuthParam authParam;
        authParam.appKey = key;
        authParam.appSecret = secret;

        SDKError err = m_pAuthService->SDKAuth(authParam);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_SUCCESS;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::LoginSDK(std::wstring account, std::wstring password)
{
    LoginParam emailLoginParam;
    emailLoginParam.loginType = LoginType_Email;
    emailLoginParam.ut.emailLogin.userName = account.c_str();
    emailLoginParam.ut.emailLogin.password = password.c_str();
    emailLoginParam.ut.emailLogin.bRememberMe = false;
    SDKError err = SDKERR_SUCCESS;
    
    if (nullptr != m_pAuthService)
    {
        err = m_pAuthService->Login(emailLoginParam);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] login SDK failure ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::LogOutSDK()
{
    SDKError err = SDKERR_SUCCESS;

    if (nullptr != m_pAuthService)
    {
        err = m_pAuthService->LogOut();
        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] LogOut SDK failure ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::LeaveMeeting()
{
    if (nullptr == m_pMeetingService)
    {
        LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
        return SDKERR_VIDEO_NOTREADY;
    }

    SDKError err = SDKERR_SUCCESS;
    err = m_pMeetingService->Leave(LEAVE_MEETING);
    if (err != SDKError::SDKERR_SUCCESS)
    {
        LOGE << "[" << __FUNCTION__ << "] Opening an appointment meeting failed ! error code: " << err << std::endl;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::StartAppointmentMeeting(ZHUMU_SDK_NAMESPACE::StartParam& startParam)
{
    if (nullptr == m_pMeetingService)
    {
        LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
        return SDKERR_VIDEO_NOTREADY;
    }

    SDKError err = SDKERR_SUCCESS;
    err = m_pMeetingService->Start(startParam);
    if (err != SDKError::SDKERR_SUCCESS)
    {
        LOGE << "[" << __FUNCTION__ << "] Opening an appointment meeting failed ! error code: " << err << std::endl;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::StartInstantMeeting(ZHUMU_SDK_NAMESPACE::StartParam& startParam)
{
    if (nullptr == m_pMeetingService)
    {
        LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
        return SDKERR_VIDEO_NOTREADY;
    }

    SDKError err = SDKERR_SUCCESS;
    err = m_pMeetingService->Start(startParam);
    if (err != SDKError::SDKERR_SUCCESS)
    {
        LOGE << "[" << __FUNCTION__ << "] Opening an instant meeting failed ! error code: " << err << std::endl;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::JoinMeeting(JoinParam& joinParam)
{
    if (nullptr == m_pMeetingService)
    {
        LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
        return SDKERR_VIDEO_NOTREADY;
    }

    SDKError err = SDKERR_SUCCESS;
    err = m_pMeetingService->Join(joinParam);
    if (err != SDKError::SDKERR_SUCCESS)
    {
        LOGE << "[" << __FUNCTION__ << "] Failed to join meeting ! error code: " << err << std::endl;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::AnonymityJoinMeeting(JoinParam& joinParam)
{
    if (nullptr == m_pMeetingService)
    {
        LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
        return SDKERR_VIDEO_NOTREADY;
    }

    SDKError err = SDKERR_SUCCESS;
    err = m_pMeetingService->Join(joinParam);
    if (err != SDKError::SDKERR_SUCCESS)
    {
        LOGE << "[" << __FUNCTION__ << "] Failed to join meeting ! error code: " << err << std::endl;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::DirectSharing(UINT64 nMeetingNumber)
{
    SDKError err = SDKERR_SUCCESS;
    //if (nullptr == m_pMeetingService)
    //{
    //    LOGE << "[" << __FUNCTION__ << "] The conference server was not created! " << std::endl;
    //    return SDKERR_VIDEO_NOTREADY;
    //}

    //err = m_pMeetingService->Join(joinParam);
    //if (err != SDKError::SDKERR_SUCCESS)
    //{
    //    LOGE << "[" << __FUNCTION__ << "] Failed to join meeting ! error code: " << err << std::endl;
    //}
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetGeneralSettings()->EnableAutoFullScreenVideoWhenJoinMeeting(bEnable);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable to enter the full screen video mode automatically when join meeting ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    //if (err == SDKERR_SUCCESS)
    //{
    //    err = m_pSettingService->GetGeneralSettings()->EnableAutoFullScreenVideoWhenJoinMeeting(bEnable);
    //    if (err != SDKERR_SUCCESS)
    //    {
    //        LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable to enter the full screen video mode automatically when join meeting ! error code: " << err << std::endl;
    //    }
    //    return err;
    //}
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    //if (err == SDKERR_SUCCESS)
    //{
    //    err = m_pSettingService->GetGeneralSettings()->EnableAutoFullScreenVideoWhenJoinMeeting(bEnable);
    //    if (err != SDKERR_SUCCESS)
    //    {
    //        LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable to enter the full screen video mode automatically when join meeting ! error code: " << err << std::endl;
    //    }
    //    return err;
    //}
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::SelectMic(const wchar_t* deviceId, const wchar_t* deviceName)
{
    SDKError err = SDKERR_UNKNOWN;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->SelectMic(deviceId, deviceName);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to select microphone device ! error code: " << err << std::endl;
        }
        return err;
    }
    return err;
}


ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::SetMicVol(float& value)
{
    SDKError err = SDKERR_UNKNOWN;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->SetMicVol(value);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to set the volume of the selected mic ! error code: " << err << std::endl;
        }
        return err;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName)
{
    SDKError err = SDKERR_UNKNOWN;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->SelectSpeaker(deviceId, deviceName);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to select speaker device ! error code: " << err << std::endl;
        }
        return err;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::SetSpeakerVol(float& value)
{
    SDKError err = SDKERR_UNKNOWN;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->SetSpeakerVol(value);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to set the volume of the selected speaker ! error code: " << err << std::endl;
        }
        return err;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableAutoJoinAudio(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->EnableAutoJoinAudio(bEnable);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable the audio automatically when join meeting ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableParticipantsUnmuteWhenMeeting(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    //if (err == SDKERR_SUCCESS)
    //{
    //    err = m_pSettingService->GetAudioSettings()->EnableAutoJoinAudio(bEnable);
    //    if (err != SDKERR_SUCCESS)
    //    {
    //        LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable the audio automatically when join meeting ! error code: " << err << std::endl;
    //    }
    //    return err;
    //}
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableEchoCancellation(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetAudioSettings()->EnableEchoCancellation(bEnable);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to Set whether to enable the function of echo cancellation or not ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::SelectCamera(const wchar_t* deviceId)
{
    SDKError err = SDKERR_UNKNOWN;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetVideoSettings()->SelectCamera(deviceId);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to select camera device ! error code: " << err << std::endl;
        }
        return err;
    }
    return err;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableHDVideo(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetVideoSettings()->EnableHDVideo(bEnable);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable HD video ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable)
{
    SDKError err;
    err = CreateSettingService();
    if (err == SDKERR_SUCCESS)
    {
        err = m_pSettingService->GetVideoSettings()->EnableAutoTurnOffVideoWhenJoinMeeting(bEnable);
        if (err != SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to Enable or disable to turn off the video when join meeting ! error code: " << err << std::endl;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::CreateAuthService()
{
    if (nullptr == m_pAuthService)
    {
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_CreateAuthService(&m_pAuthService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to create the authentication service ! error code: " << err << std::endl;
            return err;
        }

        m_pAuthService->SetEvent(this);
        
        return SDKERR_SUCCESS;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::DestroyAuthService()
{
    if (nullptr != m_pAuthService)
    {
        m_pAuthService->SetEvent(nullptr);
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_DestroyAuthService(m_pAuthService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to destroy the authentication service ! error code: " << err << std::endl;
            return err;
        }
        return SDKERR_SUCCESS;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::CreateMeetingService()
{
    if (nullptr == m_pMeetingService)
    {
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_CreateMeetingService(&m_pMeetingService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to create the meeting service ! error code: " << err << std::endl;
            return err;
        }

        m_pMeetingService->SetEvent(this);

        return SDKERR_SUCCESS;
    }
    return SDKERR_SUCCESS;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::DestroyMeetingService()
{
    if (nullptr != m_pMeetingService)
    {
        m_pMeetingService->SetEvent(nullptr);
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_DestroyMeetingService(m_pMeetingService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to destroy the meeting service ! error code: " << err << std::endl;
            return err;
        }
        return SDKERR_SUCCESS;
    }
    return SDKERR_UNKNOWN;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::CreateSettingService()
{
    if (nullptr == m_pSettingService)
    {
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_CreateSettingService(&m_pSettingService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to create the setting service ! error code: " << err << std::endl;
            return err;
        }

        return SDKERR_SUCCESS;
    }
    return SDKERR_SUCCESS;
}

ZHUMU_SDK_NAMESPACE::SDKError CZhumuSdkAgency::DestroySettingService()
{
    if (nullptr != m_pSettingService)
    {
        SDKError err = ZHUMU_SDK_NAMESPACE::Zhumu_DestroySettingService(m_pSettingService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] Failed to destroy the setting service ! error code: " << err << std::endl;
            return err;
        }
        return SDKERR_SUCCESS;
    }
    return SDKERR_UNKNOWN;
}
