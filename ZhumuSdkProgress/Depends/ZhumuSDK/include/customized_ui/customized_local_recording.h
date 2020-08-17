/*!
* \文件 customized_local_recording.h
* \brief zhumu 自定义本地录制接口
* 
*/
#ifndef ZHUMU_CUSTOMIZED_LOCAL_RECORDING_H_
#define ZHUMU_CUSTOMIZED_LOCAL_RECORDING_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
enum RECORDING_LAYOUT_MODE
{
	RECORDING_LAYOUT_MODE_NONE = 0,
	RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY = 1,
	RECORDING_LAYOUT_MODE_VIDEO_WALL = (1<<1),
	RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO = (1<<2),
	RECORDING_LAYOUT_MODE_ONLY_AUDIO = (1<<3),
	RECORDING_LAYOUT_MODE_ONLY_SHARE = (1<<4),
};
class ICustomizedLocalRecordingLayoutHelper
{
public:
	virtual int GetSupportLayout() = 0;
	virtual std::vector<unsigned int> GetValidVideoSourceList() = 0;
	virtual std::vector<unsigned int> GetValidRecvSharingSourceList() = 0;
	virtual bool IsSendSharingSourceAvailable() = 0;
	virtual bool HasActiveVideoSource() = 0;
	
	virtual SDKError SelectRecordingLayoutMode(RECORDING_LAYOUT_MODE mode_) = 0;
	virtual SDKError AddVideoSourceToRecList(unsigned int user_id) = 0;
	virtual SDKError SelectActiveVideoSource() = 0;
	virtual SDKError SelectRecvSharingSource(unsigned int user_id) = 0;
	virtual SDKError SelectSendSharingSource() = 0;
	virtual ~ICustomizedLocalRecordingLayoutHelper(){}
};
END_ZHUMU_SDK_NAMESPACE
#endif