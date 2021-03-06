 /*
 * Module:   TRTCCloudCallback @ TXLiteAVSDK
 *
 * Function: 腾讯云视频通话功能的回调接口类
 *
 */
 
#ifndef __TRTCENGINECALLBACK_H__
#define __TRTCENGINECALLBACK_H__

#include "TRTCCloudDef.h"
#include "TRTCStatistics.h"
#include "TXLiteAVCode.h"

/**
 * 腾讯云视频通话功能的回调接口类
 */
class ITRTCCloudCallback
{
public:
    virtual ~ITRTCCloudCallback() {}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （一）通用事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 通用事件回调
    /// @{
    /**
    * \brief 1.1 错误回调，SDK 不可恢复的错误，一定要监听，并分情况给用户适当的界面提示
    *
    * \param errCode 错误码
    * \param errMsg 错误信息
    * \param arg 扩展信息字段，个别错误码可能会带额外的信息帮助定位问题
    */
    virtual void onError(TXLiteAVError errCode, const char* errMsg, void* arg) = 0;

    /**
    * \brief 1.2 警告回调
    *
    * \param warningCode 错误码
    * \param warningMsg 警告信息
    * \param arg 扩展信息字段，个别警告码可能会带额外的信息帮助定位问题
    */
    virtual void onWarning(TXLiteAVWarning warningCode, const char* warningMsg, void* arg) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （二）房间事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 房间事件回调
    /// @{
    /**
    * \brief 2.1 加入房间的事件回调
    *
    * \param elapsed 进房耗时
    */
    virtual void onEnterRoom(uint64_t elapsed) = 0;

    /**
    * \brief 2.2 离开房间的事件回调
    *
    * \param reason 离开房间原因
    */
    virtual void onExitRoom(int reason) = 0;

    /**
    * 2.3 切换角色结果回调
    *
    * @param errCode 错误码
    * @param errMsg  错误信息
    */
    virtual void onSwitchRole(TXLiteAVError errCode, const char* errMsg) {}

    /**
    * 2.4 请求跨房通话的结果回调
    *
    * \param userId 用户标识
    * \param errCode 错误码
    * \param errMsg 错误信息
    */
    virtual void onConnectOtherRoom(const char* userId, TXLiteAVError errCode, const char* errMsg) {}

    /**
    * 2.5 断开跨房通话的结果回调
    *
    * \param errCode 错误码
    * \param errMsg 错误信息
    */
    virtual void onDisconnectOtherRoom(TXLiteAVError errCode, const char* errMsg) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （三）成员事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 成员事件回调
    /// @{
    /**
    * \brief 3.1 有新的音视频用户加入房间
    *
    * 当有新的音视频用户（有开启音频或者视频上行的用户）加入房间后，房间里的其他用户会收到该通知。
    * 
    * 由于单个 TRTC 的房间可以容纳很多人的加入，所以并不是任何用户加入房间后都会出发 onUserEnter 事件，这可能会造成性能上的灾难。
    * 只有一个用户开启了音频或者视频上行的时候，房间里的其他用户才能收到该通知。
    *
    * 您可以在收到该通知后，在 UI 界面上增加一个用户的头像，但并不推荐立刻 startRemoteView，
    * 因为该用户可能只有声音没有视频，onUserVideoAvailable 则是真正的宣告某个用户的画面可以显示了。
    *
    * \warning - 并不是所有用户加入房间都会触发此通知，只有开启音频或者视频上行的用户才会触发此通知。
    *          - 收到该通知后，并不推荐立刻 startRemoteView，因为可能该用户只开启了音频而没有开启视频。
    *
    * \param userId 用户标识
    */
    virtual void onUserEnter(const char* userId) = 0;

    /**
    * \brief 3.2 有用户从当前房间中离开
    *
    * \param userId 用户标识
    * \param reason 离开原因代码，区分用户是正常离开，还是由于网络断线等原因离开。
    */
    virtual void onUserExit(const char* userId, int reason) = 0;

    /**
    * \brief 3.3 userId 对应的远端主路（即摄像头）画面的状态通知
    *
    * 当 available 为 true 时，您可以在这个回调中调用 startRemoteView 显示该 userId 的视频画面。
    * 
    * \param userId 用户标识
    * \param available 画面是否开启
    */
    virtual void onUserVideoAvailable(const char* userId, bool available) {}

    /**
    * \brief 3.4 userId 对应的远端辅路（屏幕分享等）画面的状态通知
    * 
    * \note 显示辅路画面使用的函数不是 startRemoteView 而是 startRemoteSubStreamView。
    * \param userId 用户标识
    * \param available true：视频可播放；false：视频被关闭
    */
    virtual void onUserSubStreamAvailable(const char* userId, bool available) {}

    /**
    * \brief 3.5 userId  对应的远端声音的状态通知
    *
    * \param userId 用户标识
    * \param available 声音是否开启
    */
    virtual void onUserAudioAvailable(const char* userId, bool available) {}

    /**
    * \brief 3.6 userId 对应的成员语音音量
    * 
    * 您可以通过调用 TRTCCloud 中的 enableAudioVolumeEvaluation 接口来开关这个回调。
    * 
    * \param userVolumes 每位发言者的语音音量，取值范围0 - 100
    * \param userVolumesCount 发言者的人数，即 userVolumes 数组的大小
    * \param totalVolume 总的语音音量, 取值范围0 - 100
    */
    virtual void onUserVoiceVolume(TRTCVolumeInfo* userVolumes, uint32_t userVolumesCount, uint32_t totalVolume) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （四）统计和质量回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 统计和质量回调
    /// @{
    /**
    * \brief 4.1 网络质量：该回调每2秒触发一次，统计当前网络的上行和下行质量
    *
    * \param localQuality 上行网络质量
    * \param remoteQuality 下行网络质量的数组
    * \param remoteQualityCount 下行网络质量的数组大小
    */
    virtual void onNetworkQuality(TRTCQualityInfo localQuality, TRTCQualityInfo* remoteQuality, uint32_t remoteQualityCount) {}

    /**
    * \brief 4.2 技术指标统计回调，每2秒回调一次
    *
    * 如果您是熟悉音视频领域相关术语，可以通过这个回调获取 SDK 的所有技术指标。
    * 如果您是首次开发音视频相关项目，可以只关注 onNetworkQuality 回调。
    * 
    * \param statis 状态数据
    * \note 每2秒回调一次
    */
    virtual void onStatistics(const TRTCStatistics& statis) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （五）音视频事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 音视频事件回调
    /// @{
    /**
    * \brief 5.1 首帧视频画面到达，界面此时可以结束 Loading，并开始显示视频画面
    *
    * \param userId 用户 ID
    * \param width  画面宽度
    * \param height 画面高度
    */
    virtual void onFirstVideoFrame(const char* userId, TRTCVideoStreamType streamType, uint32_t width, uint32_t height) {}

    /**
    * \brief 5.2 首帧音频数据到达
    *
    * \param userId 用户 ID
    */
    virtual void onFirstAudioFrame(const char* userId) {}

    /**
    * \brief 5.3 开始播放背景音乐
    *
    * \param errCode 错误码
    */
    virtual void onPlayBGMBegin(TXLiteAVError errCode) {}

    /**
    * \brief 5.3 播放背景音乐的进度
    *
    * \param progressMS 已播放时间
    * \param durationMS 总时间
    */
    virtual void onPlayBGMProgress(uint32_t progressMS, uint32_t durationMS) {}

    /**
    * \brief 5.4 播放背景音乐结束
    *
    * \param errCode 错误码
    */
    virtual void onPlayBGMComplete(TXLiteAVError errCode) {}
    /// @}
    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （六）服务器事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 服务器事件回调
    /// @{
    /**
    * \brief 6.1 SDK 跟服务器的连接断开
    */
    virtual void onConnectionLost() {}

    /**
    * \brief 6.2 SDK 尝试重新连接到服务器
    */
    virtual void onTryToReconnect() {}

    /**
    * \brief 6.3 SDK 跟服务器的连接恢复
    */
    virtual void onConnectionRecovery() {}

    /**
    * \brief 6.4 服务器测速的回调，SDK 对多个服务器 IP 做测速，每个 IP 的测速结果通过这个回调通知
    *
    * \param currentResult 当前完成的测速结果
    * \param finishedCount 已完成测速的服务器数量
    * \param totalCount 需要测速的服务器总数量
    */
    virtual void onSpeedTest(const TRTCSpeedTestResult& currentResult, uint32_t finishedCount, uint32_t totalCount) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （七）硬件设备事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 硬件设备事件回调
    /// @{
    /**
    * \brief 7.1 摄像头准备就绪
    */
    virtual void onCameraDidReady() {}

    /**
    * \brief 7.2 麦克风准备就绪
    */
    virtual void onMicDidReady() {}

    /**
    * \brief 7.3 设备事件的回调
    *
    * \param deviceId 设备 ID
    * \param type 设备类型
    * \param state 事件类型
    */
    virtual void onDeviceChange(const char* deviceId, TRTCDeviceType type, TRTCDeviceState state) {}

    /**
    * \brief 7.4 麦克风测试音量回调
    * 
    * 麦克风测试接口 startMicDeviceTest 会触发这个回调
    *
    * \param volume 音量值，取值范围0 - 100
    */
    virtual void onTestMicVolume(uint32_t volume) {}

    /**
    * \brief 7.5 扬声器测试音量回调
    * 
    * 扬声器测试接口 startSpeakerDeviceTest 会触发这个回调
    *
    * \param volume 音量值，取值范围0 - 100
    */
    virtual void onTestSpeakerVolume(uint32_t volume) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （八）自定义消息的接收回调
	//
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 自定义消息的接收回调
    /// @{
    /**
    * \brief 8.1 收到自定义消息回调
    * 
    * 当房间中的某个用户使用 sendCustomCmdMsg 发送自定义消息时，房间中的其它用户可以通过 onRecvCustomCmdMsg 接口接收消息
    *
    * \param userId 用户标识
    * \param cmdId 命令 ID
    * \param seq   消息序号
    * \param msg 消息数据
    * \param msgSize 消息数据大小
    */
    virtual void onRecvCustomCmdMsg(const char* userId, int32_t cmdId, uint32_t seq, const uint8_t* msg, uint32_t msgSize) {}

    /**
    * \brief 8.2 自定义消息丢失回调
    * 
    * TRTC 所使用的传输通道为 UDP 通道，所以即使设置了 reliable，也做不到100%不丢失，只是丢消息概率极低，能满足常规可靠性要求。
    * 在过去的一段时间内（通常为5s），自定义消息在传输途中丢失的消息数量的统计，SDK 都会通过此回调通知出来。
    *
    * \note  只有在发送端设置了可靠传输(reliable)，接收方才能收到消息的丢失回调
    * \param userId 用户标识
    * \param cmdId 命令 ID
    * \param errCode 错误码，当前版本为-1
    * \param missed 丢失的消息数量
    */
    virtual void onMissCustomCmdMsg(const char* userId, int32_t cmdId, int32_t errCode, int32_t missed) {}


    /**
     * \brief 收到 SEI 消息的回调
     * 
     * 当房间中的某个用户使用 sendSEIMsg 发送数据时，房间中的其它用户可以通过 onRecvSEIMsg 接口接收数据。
     * 
     * @param userId   用户标识
     * @param message  数据
     * @param msgSize  数据大小
     */
    virtual void onRecvSEIMsg(const char* userId, const uint8_t* message, uint32_t msgSize) {};
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （九）CDN 旁路转推回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name CDN 旁路转推回调
    /// @{
    /**
    * \brief 9.1 旁路推流到 CDN 的回调
    * 
    * 对应于 TRTCCloud 的 startPublishCDNStream() 接口
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    *
    * \note Start 回调如果成功，只能说明转推请求已经成功告知给腾讯云，如果目标 CDN 有异常，还是有可能会转推失败。
    */
    virtual void onStartPublishCDNStream(int errCode, const char* errMsg) {};

    /**
    * \brief 9.2 停止旁路推流到 CDN 的回调
    * 
    * 对应于 TRTCCloud 中的 stopPublishCDNStream() 接口
    * 
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    virtual void onStopPublishCDNStream(int errCode, const char* errMsg) {};

    /**
    * \brief 9.3 混流接口的状态回调
    *
    * 对应于 TRTCCloud 中的 setMixTranscodingConfig() 接口
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    virtual void onSetMixTranscodingConfig(int errCode, const char* errMsg) {};
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （十）屏幕分享回调
	//
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 屏幕分享回调
    /// @{
    /**
    * \brief 10.1 当屏幕分享窗口被遮挡无法正常捕获时，SDK 会通过此回调通知，可在此回调里通知用户移开遮挡窗口
    */
    virtual void onScreenCaptureCovered() {};

    /**
    * \brief 10.2 当屏幕分享开始时，SDK 会通过此回调通知
    */
    virtual void onScreenCaptureStarted() {};

    /**
    * \brief 10.3 当屏幕分享暂停时，SDK 会通过此回调通知
    *
    * \param reason 停止原因，0：表示用户主动暂停；1：表示设置屏幕分享参数导致的暂停；2：表示屏幕分享窗口被最小化导致的暂停；3：表示屏幕分享窗口被隐藏导致的暂停
    */
    virtual void onScreenCapturePaused(int reason) {};

    /**
    * \brief 10.4 当屏幕分享恢复时，SDK 会通过此回调通知
    *
    * \param reason 停止原因，0：表示用户主动恢复，1：表示屏幕分享参数设置完毕后自动恢复；2：表示屏幕分享窗口从最小化被恢复；3：表示屏幕分享窗口从隐藏被恢复
    */
    virtual void onScreenCaptureResumed(int reason) {};

    /**
    * \brief 10.5 当屏幕分享停止时，SDK 会通过此回调通知
    *
    * \param reason 停止原因，0：表示用户主动停止；1：表示屏幕分享窗口被关闭
    */
    virtual void onScreenCaptureStoped(int reason) {};
    /// @}
};


/////////////////////////////////////////////////////////////////////////////////
//
//                      （十一）视频相关回调
//
/////////////////////////////////////////////////////////////////////////////////

/// 视频数据帧的自定义处理回调
class ITRTCVideoRenderCallback
{
public:
    virtual ~ITRTCVideoRenderCallback() {}
    /**
    * \brief 11.1 自定义视频渲染回调
    * 
    * 可以通过 setLocalVideoRenderCallback 和 setRemoteVideoRenderCallback 接口设置自定义渲染回调
    *
    * \param userId     用户标识
    * \param streamType	流类型：即摄像头还是屏幕分享
    * \param frame      视频帧数据
    */
    virtual void onRenderVideoFrame(const char* userId, TRTCVideoStreamType streamType, TRTCVideoFrame* frame) {}
};


/////////////////////////////////////////////////////////////////////////////////
///         \brief 声音数据帧的自定义处理回调（只读）
///
///         \warning 回调函数是在 SDK 内部线程同步抛出来的，请不要做耗时操作。
///          提示：请按需定义相关函数实现，减少不必要的性能损耗。
/////////////////////////////////////////////////////////////////////////////////

class ITRTCAudioFrameCallback
{
public:
    virtual ~ITRTCAudioFrameCallback() {}
    /**
    * \brief 12.1 本地麦克风采集到的音频数据回调
    * \note - 请不要在此回调函数中做任何耗时操作，建议直接拷贝到另一线程进行处理，否则会导致各种声音问题。
    *       - 此接口回调出的音频数据是只读的，不支持修改。
    */
    virtual void onCapturedAudioFrame(TRTCAudioFrame *frame) {};

    /**
    * \brief 12.2 混音前的每一路远程用户的音频数据（比如您要对某一路的语音进行文字转换，必须要使用这里的原始数据，而不是混音之后的数据）
    * 
    * \param frame      音频数据
    * \param userId     用户标识
    * \note - 请不要在此回调函数中做任何耗时操作，建议直接拷贝到另一线程进行处理，否则会导致各种声音问题。
    *       - 此接口回调出的音频数据是只读的，不支持修改。
    */
    virtual void onPlayAudioFrame(TRTCAudioFrame *frame, const char* userId) {};
    /**
    * \brief 12.3 各路音频数据混合后送入喇叭播放的音频数据
    * \note - 请不要在此回调函数中做任何耗时操作，建议直接拷贝到另一线程进行处理，否则会导致各种声音问题。
    *       - 此接口回调出的音频数据是只读的，不支持修改。
    */
    virtual void onMixedPlayAudioFrame(TRTCAudioFrame *frame) {};
};

/////////////////////////////////////////////////////////////////////////////////
//
//                      （十三）Log 信息回调
//
/////////////////////////////////////////////////////////////////////////////////

/// 日志相关回调
class ITRTCLogCallback
{
public:
    virtual ~ITRTCLogCallback() {}
    /**
    * \brief 11.1 有日志打印时的回调
    *
    * \param log 日志内容
    * \param level 日志等级 参见 TRTCLogLevel
    * \param module 暂无具体意义，目前为固定值 TXLiteAVSDK
    */
    virtual void onLog(const char* log, TRTCLogLevel level, const char* module) {}
};

#endif /* __TRTCENGINECALLBACK_H__ */
