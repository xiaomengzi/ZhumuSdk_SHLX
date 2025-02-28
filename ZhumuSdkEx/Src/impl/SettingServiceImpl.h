#ifndef _SETTINGSERVICEIMPL_H_
#define _SETTINGSERVICEIMPL_H_

#include "setting_service_interface.h"

using namespace ZHUMUSDKEX_NAMESPACE;

class CSettingServiceImpl
    :public ZHUMUSDKEX_NAMESPACE::ISettingService
{
public:
    CSettingServiceImpl();
    ~CSettingServiceImpl();

public:
    ////////////////////// 通用设置 //////////////////////////////
    // 设置默认麦克风
    virtual SDKError SelectMic(const char* deviceId, const char* deviceName);

    // 设置所选麦克风的音量。0~100
    virtual SDKError SetMicVol(int& value);

    // 选择扬声器装置。
    virtual SDKError SelectSpeaker(const char* deviceId, const char* deviceName);

    // 设置所选扬声器的音量。0~100
    virtual SDKError	SetSpeakerVol(int& value);

    /// 加入会议时启用或禁用自动进入全屏视频模式
    virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable);

    /// 会议过程中是否始终显示会议控制栏
    virtual SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable);

    /// 无管理员入会
    virtual SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable);

    ////////////////////// 音频设置 //////////////////////////////

    /// 加入会议时启用或禁用自动加入音频
    virtual SDKError EnableAutoJoinAudio(bool bEnable);

    /// 允许参会人解除静音
    virtual SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable);

    /// 设置是否启用回声消除功能
    virtual SDKError EnableEchoCancellation(bool bEnable);

    ////////////////////// 视频设置 //////////////////////////////
    // 设置默认摄像头
    virtual SDKError SelectCamera(const char* deviceId);

    /// 启用或禁用高清视频
    virtual SDKError EnableHDVideo(bool bEnable);

    /// 启用或禁用在加入会议时关闭视频
    virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);

};

#endif //_SETTINGSERVICEIMPL_H_

