#ifndef _SETTING_SERVICE_INTERFACE_H_
#define _SETTING_SERVICE_INTERFACE_H_

#include "ZhumuSdkEx_def.h"


BEGIN_ZHUMUSDKEX_NAMESPACE


class ISettingService
{
public:
    ////////////////////// 通用设置 //////////////////////////////

    /// 加入会议时启用或禁用自动进入全屏视频模式
    virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

    /// 会议过程中是否始终显示会议控制栏
    virtual SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable) = 0;

    /// 无管理员入会
    virtual SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable) = 0;

    ////////////////////// 音频设置 //////////////////////////////

    /// 加入会议时启用或禁用自动加入音频
    virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

    /// 允许参会人解除静音
    virtual SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable) = 0;

    /// 设置是否启用回声消除功能
    virtual SDKError EnableEchoCancellation(bool bEnable) = 0;

    ////////////////////// 视频设置 //////////////////////////////

    /// 启用或禁用高清视频
    virtual SDKError EnableHDVideo(bool bEnable) = 0;

    /// 启用或禁用在加入会议时关闭视频
    virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

};


END_ZHUMUSDKEX_NAMESPACE
#endif //_SETTING_SERVICE_INTERFACE_H_
