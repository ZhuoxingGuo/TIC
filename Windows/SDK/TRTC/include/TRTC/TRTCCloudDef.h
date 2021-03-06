/*
 * Module:   TRTC 关键类型定义
 * 
 * Function: 分辨率、质量等级等枚举和常量值的定义
 *
 */

#ifndef __TRTCCLOUDDEF_H__
#define __TRTCCLOUDDEF_H__

#include "TXLiteAVBase.h"
#include <memory>

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif // !_WINSOCKAPI_

#include <Windows.h>

/////////////////////////////////////////////////////////////////////////////////
//
//                    【（一）视频相关枚举值定义】
//                   
/////////////////////////////////////////////////////////////////////////////////


/**
 * 1.1 视频分辨率
 *
 * 此处仅定义了横屏分辨率，如果要使用360 × 640这样的竖屏分辨率，需要同时指定 TRTCVideoResolutionMode 为 Portrait。
 */
enum TRTCVideoResolution
{
    /// 宽高比1:1
    TRTCVideoResolution_120_120   = 1,     ///< [C] 建议码率80kbps
    TRTCVideoResolution_160_160   = 3,     ///< [C] 建议码率100kbps
    TRTCVideoResolution_270_270   = 5,     ///< [C] 建议码率200kbps
    TRTCVideoResolution_480_480   = 7,     ///< [C] 建议码率350kbps
    
    /// 宽高比4:3
    TRTCVideoResolution_160_120   = 50,    ///< [C] 建议码率100kbps
    TRTCVideoResolution_240_180   = 52,    ///< [C] 建议码率150kbps
    TRTCVideoResolution_280_210   = 54,    ///< [C] 建议码率200kbps
    TRTCVideoResolution_320_240   = 56,    ///< [C] 建议码率250kbps
    TRTCVideoResolution_400_300   = 58,    ///< [C] 建议码率300kbps
    TRTCVideoResolution_480_360   = 60,    ///< [C] 建议码率400kbps
    TRTCVideoResolution_640_480   = 62,    ///< [C] 建议码率600kbps
    TRTCVideoResolution_960_720   = 64,    ///< [C] 建议码率1000kbps
    
    /// 宽高比16:9
    TRTCVideoResolution_160_90    = 100,   ///< [C]
    TRTCVideoResolution_256_144   = 102,   ///< [C]
    TRTCVideoResolution_320_180   = 104,   ///< [C] 建议码率250kbps
    TRTCVideoResolution_480_270   = 106,   ///< [C] 建议码率350kbps
    TRTCVideoResolution_640_360   = 108,   ///< [C] 建议码率550kbps
    TRTCVideoResolution_960_540   = 110,   ///< [C] 建议码率850kbps  
    TRTCVideoResolution_1280_720  = 112,   ///< [C] 摄像头采集 - 建议码率1200kbps  
	                                       ///< [S] 屏幕分享   - 建议码率 低清：400kbps 高清：600kbps
    TRTCVideoResolution_1920_1080 = 114,   ///< [S] 屏幕分享   - 建议码率800kbps
};

/**
 * 1.2 视频分辨率模式
 *
 * - 横屏分辨率：TRTCVideoResolution_640_360 + TRTCVideoResolutionModeLandscape = 640 × 360
 * - 竖屏分辨率：TRTCVideoResolution_640_360 + TRTCVideoResolutionModePortrait  = 360 × 640
 */
enum TRTCVideoResolutionMode
{
    TRTCVideoResolutionModeLandscape = 0,               ///< 横屏分辨率
    TRTCVideoResolutionModePortrait = 1,                ///< 竖屏分辨率
};

/**
 * 1.3 视频流类型
 *
 * TRTC 内部有三种不同的音视频流，分别是：
 * - 主画面：最常用的一条线路，一般用来传输摄像头的视频数据。
 * - 小画面：跟主画面的内容相同，但是分辨率和码率更低。
 * - 辅流画面：一般用于屏幕分享，以及远程播片（比如老师放一段视频给学生）。
 *
 * @note - 如果主播的上行网络和性能比较好，则可以同时送出大小两路画面。
 * @note - SDK 不支持单独开启小画面，小画面必须依附于主画面而存在。
 */
enum TRTCVideoStreamType
{
    TRTCVideoStreamTypeBig = 0,                         ///< 大画面视频流
    TRTCVideoStreamTypeSmall = 1,                       ///< 小画面视频流
    TRTCVideoStreamTypeSub = 2,                         ///< 辅流（屏幕分享）
};


/**
 * 1.4 画质级别
 *
 * TRTC SDK 对画质定义了六种不同的级别，Excellent 代表最好，Down 代表不可用。
 */
enum TRTCQuality
{
    TRTCQuality_Unknown   = 0,   ///< 未定义
    TRTCQuality_Excellent = 1,   ///< 最好
    TRTCQuality_Good      = 2,   ///< 好
    TRTCQuality_Poor      = 3,   ///< 一般
    TRTCQuality_Bad       = 4,   ///< 差
    TRTCQuality_Vbad      = 5,   ///< 很差
    TRTCQuality_Down      = 6,   ///< 不可用
};

/**
 * 1.5 视频画面填充模式
 *
 * 如果画面的显示分辨率不等于画面的原始分辨率，就需要您设置画面的填充模式:
 * - TRTCVideoFillMode_Fill，图像铺满屏幕，超出显示视窗的视频部分将被截掉，所以画面显示可能不完整。
 * - TRTCVideoFillMode_Fit，图像长边填满屏幕，短边区域会被填充黑色，但画面的内容肯定是完整的。
 */
enum TRTCVideoFillMode
{
    /// 图像铺满屏幕，超出显示视窗的视频部分将被截掉
    TRTCVideoFillMode_Fill = 0,
    /// 图像长边填满屏幕，短边区域会被填充黑色
    TRTCVideoFillMode_Fit = 1,
};

/**
 * 1.6 视频画面旋转方向
 * 
 * TRTC SDK 提供了对本地和远程画面的旋转角度设置 API，如下的旋转角度都是指顺时针方向的。
 * 
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVVideoRotation TRTCVideoRotation;
#define TRTCVideoRotation0 LiteAVVideoRotation0                                 ///< 顺时针旋转0度
#define TRTCVideoRotation90 LiteAVVideoRotation90                               ///< 顺时针旋转90度
#define TRTCVideoRotation180 LiteAVVideoRotation180                             ///< 顺时针旋转180度
#define TRTCVideoRotation270 LiteAVVideoRotation270                             ///< 顺时针旋转270度

/**
 * 1.7 美颜（磨皮）算法
 *
 * TRTC SDK 内置了多种不同的磨皮算法，您可以选择最适合您产品定位的方案。
 */
enum TRTCBeautyStyle
{
    TRTCBeautyStyleSmooth = 0,                         ///< 光滑，适用于美女秀场，效果比较明显。
    TRTCBeautyStyleNature = 1,                         ///< 自然，磨皮算法更多地保留了面部细节，主观感受上会更加自然。
};

/**
 * 1.8 视频像素格式
 *
 * TRTC SDK 提供针对视频的自定义采集和自定义渲染功能，在自定义采集功能中，您可以用如下枚举值描述您采集的视频像素格式。
 * 在自定义渲染功能中，您可以指定您期望 SDK 回调的视频像素格式。
 *
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVVideoPixelFormat TRTCVideoPixelFormat;
#define TRTCVideoPixelFormat_Unknown LiteAVVideoPixelFormat_Unknown
#define TRTCVideoPixelFormat_I420 LiteAVVideoPixelFormat_I420                   ///< I420
#define TRTCVideoPixelFormat_Texture_2D LiteAVVideoPixelFormat_Texture_2D       ///< OpenGL 2D 纹理
#define TRTCVideoPixelFormat_BGRA32 LiteAVVideoPixelFormat_BGRA32               ///< BGRA32


/**
 * 1.9 视频数据包装格式
 * 
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVVideoBufferType TRTCVideoBufferType;
#define TRTCVideoBufferType_Unknown LiteAVVideoBufferType_Unknown
#define TRTCVideoBufferType_Buffer LiteAVVideoBufferType_Buffer                 ///< 二进制 Buffer 类型
#define TRTCVideoBufferType_Texture LiteAVVideoBufferType_Texture               ///< 纹理类型


/////////////////////////////////////////////////////////////////////////////////
//
//                    【（二）网络相关枚举值定义】
//                   
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 应用场景
 *
 * TRTC 可用于视频会议和在线直播等多种应用场景，针对不同的应用场景，TRTC SDK 的内部会进行不同的优化配置：
 * - VideoCall：视频通话场景，即绝大多数时间都是两人或两人以上视频通话的场景，比如1v1的在线课程辅导，1vN (N < 8) 的视频会议或者小班课堂。
 * - LIVE：在线直播场景，即绝大多数时间都是一人直播，偶尔有多人视频互动的场景，比如美女秀场连麦等场景。
 */
enum TRTCAppScene
{
    TRTCAppSceneVideoCall    = 0,  ///< 视频通话场景，内部编码器和网络协议优化侧重流畅性，降低通话延迟和卡顿率。			
    TRTCAppSceneLIVE         = 1,  ///< 在线直播场景，内部编码器和网络协议优化侧重性能和兼容性，性能和清晰度表现更佳。
};

/**
* 2.2 角色，仅适用于直播场景（TRTCAppSceneLIVE）
*
* 在直播场景中，多数用户只是观众，只有个别用户是主播，这种角色区分可以有利于 TRTC 进行更好的定向优化。
*
* - Anchor：主播，可以上行视频和音频，一个房间里的主播人数不能超过 50 人。
* - Audience：观众，只能观看，不能上行视频和音频，一个房间里的观众人数没有上限。
*/
enum TRTCRoleType
{
    TRTCRoleAnchor = 20,     ///< 主播
    TRTCRoleAudience = 21,   ///< 观众
};

/**
 * 2.3 流控模式
 *
 * TRTC SDK 内部需要时刻根据网络情况调整内部的编解码器和网络模块，以便能够对网络的变化做出反应。
 * 为了支持快速算法升级，SDK 内部设置了两种不同的流控模式：
 * - ModeClient： 本地控制，用于 SDK 开发内部调试，客户请勿使用。
 * - ModeServer： 云端控制，推荐模式，也是默认默认。
 *
 * @note 推荐您使用云端控制，这样每当我们升级 Qos 算法时，您无需升级 SDK 即可体验更好的效果。
 */
enum TRTCQosControlMode
{
    TRTCQosControlModeClient,                           ///< 客户端控制（用于 SDK 开发内部调试，客户请勿使用）
    TRTCQosControlModeServer,                           ///< 云端控制 （默认）
};

/**
 * 2.4 画质偏好
 *
 * 指当 TRTC SDK 在遇到弱网络环境时，您是希望“保清晰”还是“保流畅”：
 *
 * - Smooth：弱网下保流畅，在遭遇弱网环境时首先确保声音的流畅和优先发送，画面会变得模糊且会有较多马赛克，但可以保持流畅不卡顿。
 * - Clear：弱网下保清晰，在遭遇弱网环境时，画面会尽可能保持清晰，但可能会更容易出现卡顿。
 */
enum TRTCVideoQosPreference
{
    TRTCVideoQosPreferenceSmooth = 1,                   ///< 弱网下保流畅
    TRTCVideoQosPreferenceClear = 2,                    ///< 弱网下保清晰
};


/////////////////////////////////////////////////////////////////////////////////
//
//                    【（三）继承 TXLiteAVBase 的定义】
//
/////////////////////////////////////////////////////////////////////////////////


/**
* \brief 3.1 音频帧的格式
* 
* 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
*/
typedef LiteAVAudioFrameFormat TRTCAudioFrameFormat;
#define TRTCAudioFrameFormatNone LiteAVAudioFrameFormatNone
#define TRTCAudioFrameFormatPCM LiteAVAudioFrameFormatPCM                

/**
 * \brief 3.2 屏幕分享目标信息
 *
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVScreenCaptureSourceType TRTCScreenCaptureSourceType;
#define TRTCScreenCaptureSourceTypeUnknown LiteAVScreenCaptureSourceTypeUnknown
#define TRTCScreenCaptureSourceTypeWindow  LiteAVScreenCaptureSourceTypeWindow             
#define TRTCScreenCaptureSourceTypeScreen  LiteAVScreenCaptureSourceTypeScreen             
#define TRTCScreenCaptureSourceTypeCustom  LiteAVScreenCaptureSourceTypeCustom      

typedef LiteAVImageBuffer TRTCImageBuffer;
typedef LiteAVScreenCaptureSourceInfo TRTCScreenCaptureSourceInfo;
typedef ILiteAVScreenCaptureSourceList ITRTCScreenCaptureSourceList;


/**
 * \brief 3.3 设备列表
 *
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef ILiteAVDeviceCollection ITRTCDeviceCollection;

/**
* \brief 3.4 设备Item信息
*
* 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
*/
typedef ILiteAVDeviceInfo ITRTCDeviceInfo;

/////////////////////////////////////////////////////////////////////////////////
//
//                    【（四）更多枚举值定义】
//                   
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 Log 级别
 */
enum TRTCLogLevel
{
    TRTCLogLevelNone      = 0,   ///< 不输出任何 SDK Log
    TRTCLogLevelVerbose   = 1,   ///< 输出所有级别的 Log
    TRTCLogLevelDebug     = 2,   ///< 输出 DEBUG，INFO，WARNING，ERROR 和 FATAL 级别的 Log
    TRTCLogLevelInfo      = 3,   ///< 输出 INFO，WARNNING，ERROR 和 FATAL 级别的 Log
    TRTCLogLevelWarn      = 4,   ///< 只输出WARNNING，ERROR 和 FATAL 级别的 Log
    TRTCLogLevelError     = 5,   ///< 只输出ERROR 和 FATAL 级别的 Log
    TRTCLogLevelFatal     = 6,   ///< 只输出 FATAL 级别的 Log
};

/**
 * 4.2 设备操作
 */
enum TRTCDeviceState
{
    TRTCDeviceStateAdd    = 0,                          ///< 添加设备
    TRTCDeviceStateRemove = 1,                          ///< 移除设备
    TRTCDeviceStateActive = 2,                          ///< 设备已启用
};


/**
 * 4.3 设备类型
 */
enum TRTCDeviceType
{
    TRTCDeviceTypeUnknow  = -1,
    TRTCDeviceTypeMic     = 0,                          ///< 麦克风
    TRTCDeviceTypeSpeaker = 1,                          ///< 扬声器
    TRTCDeviceTypeCamera  = 2,                          ///< 摄像头
};


/**
 * 4.4 水印图片的源类型
 */
enum TRTCWaterMarkSrcType
{
	TRTCWaterMarkSrcTypeFile   = 0,                     ///< 图片文件路径，支持 BMP、GIF、JPEG、PNG、TIFF、Exif、WMF 和 EMF 文件格式
	TRTCWaterMarkSrcTypeBGRA32 = 1,                     ///< BGRA32格式内存块
	TRTCWaterMarkSrcTypeRGBA32 = 2,                     ///< RGBA32格式内存块
};


/////////////////////////////////////////////////////////////////////////////////
//
//                      【（五）TRTC 核心类型定义】
//                   
/////////////////////////////////////////////////////////////////////////////////

/// \brief 5.1 进房相关参数
///
/// 只有该参数填写正确，才能顺利调用 enterRoom 进入 roomId 所指定的音视频房间。
struct TRTCParams
{

    ///【字段含义】应用标识（必填），腾讯视频云基于 sdkAppId 完成计费统计。
    ///【推荐取值】在腾讯云 [TRTC 控制台](https://console.cloud.tencent.com/rav/) 中创建应用，之后可以在账号信息页面中得到该 ID
    uint32_t sdkAppId;

    ///【字段含义】用户标识（必填）。当前用户的 userId，相当于用户名，UTF-8编码。
    ///【推荐取值】如果一个用户在您的账号系统中的 ID 为“abc”，则 userId 即可设置为“abc”。
    const char* userId;
	
    ///【字段含义】用户签名（必填），当前 userId 对应的验证签名，相当于登录密码。
    ///【推荐取值】请参考 [如何计算UserSig](https://cloud.tencent.com/document/product/647/17275)。
    const char* userSig;
	
    ///【字段含义】房间号码（必填），指定房间号，在同一个房间里的用户（userId）可以彼此看到对方并进行视频通话。
    ///【推荐取值】您可以随意指定，但请不要重复，如果您的用户账号 ID 是数字类型的，可以直接用创建者的用户 ID 作为 roomId。
    uint32_t roomId;

    ///【字段含义】直播场景下的角色，仅适用于直播场景（TRTCAppSceneLIVE），视频通话场景下指定无效。
    ///【推荐取值】默认值：主播（TRTCRoleAnchor）
    TRTCRoleType role;
	
    ///【字段含义】房间签名（非必填），如果您希望某个房间只能让特定的某些 userId 进入，就需要使用 privateMapKey 进行权限保护。
    ///【推荐取值】仅建议有高级别安全需求的客户使用，参考文档：[进房权限保护](https://cloud.tencent.com/document/product/647/32240)
    const char* privateMapKey;

    ///【字段含义】业务数据（非必填），某些非常用的高级特性才需要用到此字段。
    ///【推荐取值】不建议使用
    const char* businessInfo;

    TRTCParams()
        : sdkAppId(0)
        , roomId(0)
        , userId(NULL)
        , userSig(NULL)
        , privateMapKey(NULL)
        , businessInfo(NULL)
    {

    }
};

/// \brief 5.2 视频编码参数
///
/// 该设置决定了远端用户看到的画面质量（同时也是云端录制出的视频文件的画面质量）。
struct TRTCVideoEncParam
{
    ///【字段含义】 视频分辨率
    ///【推荐取值】 - 视频通话建议选择360 × 640及以下分辨率，resMode 选择 Portrait。
    ///           - 手机直播建议选择 540 × 960，resMode 选择 Portrait。
    ///           - Window 和 iMac 建议选择 640 × 360 及以上分辨率，resMode 选择 Landscape。
    ///【特别说明】 您在 TRTCVideoResolution 只能找到横屏模式的分辨率，例如：640 × 360 这样的分辨率。
    ///             如果想要使用竖屏分辨率，请指定 resMode 为 Portrait，例如：640 × 360 + Portrait = 360 × 640。
    TRTCVideoResolution videoResolution;
	
    ///【字段含义】分辨率模式（横屏分辨率 - 竖屏分辨率）
    ///【推荐取值】手机直播建议选择 Portrait，Window 和 Mac 建议选择 Landscape。
    ///【特别说明】如果 videoResolution 指定分辨率 640 × 360，resMode 指定模式为 Portrait，则最终编码出的分辨率为360 × 640。
    TRTCVideoResolutionMode resMode;

    ///【字段含义】视频采集帧率
    ///【推荐取值】15fps 或 20fps，10fps 以下会有轻微卡顿感，5fps 以下卡顿感明显，20fps 以上的帧率则过于浪费（电影的帧率也只有 24fps）。
    ///【特别说明】很多 Android 手机的前置摄像头并不支持15fps以上的采集帧率，部分过于突出美颜功能的 Android 手机前置摄像头的采集帧率可能低于10fps。
    uint32_t videoFps;

    ///【字段含义】视频上行码率
    ///【推荐取值】推荐设置请参考本文件前半部分 TRTCVideoResolution 定义处的注释说明
    ///【特别说明】码率太低会导致视频中有很多的马赛克
    uint32_t videoBitrate;

    TRTCVideoEncParam()
        : videoResolution(TRTCVideoResolution_640_360)
        , resMode(TRTCVideoResolutionModeLandscape)
        , videoFps(15)
        , videoBitrate(550)
    {

    }
};

/// \brief 5.3 网络流控相关参数
///
/// 网络流控相关参数，该设置决定了SDK在各种网络环境下的调控方向（比如弱网下是“保清晰”还是“保流畅”）
struct TRTCNetworkQosParam
{
    ///【字段含义】弱网下是“保清晰”还是“保流畅”
    ///【特别说明】
    ///   - 弱网下保流畅：在遭遇弱网环境时，画面会变得模糊，且会有较多马赛克，但可以保持流畅不卡顿
    ///   - 弱网下保清晰：在遭遇弱网环境时，画面会尽可能保持清晰，但可能会更容易出现卡顿
    TRTCVideoQosPreference preference;

    ///【字段含义】视频分辨率（云端控制 - 客户端控制）
    ///【推荐取值】云端控制
    ///【特别说明】
    ///   - Client 模式：客户端控制模式，用于 SDK 开发内部调试，客户请勿使用
    ///   - Server 模式（默认）：云端控制模式，若没有特殊原因，请直接使用该模式
    TRTCQosControlMode controlMode;
	
    TRTCNetworkQosParam()
        : preference(TRTCVideoQosPreferenceClear)
        , controlMode(TRTCQosControlModeServer)
    {

    }
};

/** 
 * \brief 5.4 视频质量
 *
 * 表示视频质量的好坏，通过这个数值，您可以在 UI 界面上用图标表征 userId 的通话线路质量
 */
struct TRTCQualityInfo
{
    const char* userId;                        ///< 用户标识
    TRTCQuality quality;                    ///< 视频质量

    TRTCQualityInfo()
        : userId(NULL)
        , quality(TRTCQuality_Unknown)
    {

    }
};

/** 
 * \brief 5.5 音量大小
 *
 * 表示语音音量的评估大小，通过这个数值，您可以在 UI 界面上用图标表征 userId 是否有在说话。
 */
struct TRTCVolumeInfo
{
    /// 说话者的 userId，字符编码格式是 UTF-8
    const char* userId;            
    /// 说话者的音量， 取值范围0 - 100              
    uint32_t volume;                       

    TRTCVolumeInfo()
        : userId(NULL)
        , volume(0)
    {

    }
};


/**
 * \brief 5.6 视频帧数据
 * 
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVVideoFrame TRTCVideoFrame;

/**
 * \brief 5.7 音频帧数据
 * 
 * 该定义仅用于兼容原有接口，具体定义参见 TXLiteAVBase.h 文件
 */
typedef LiteAVAudioFrame TRTCAudioFrame;


/**
 * \brief 5.8 网络测速结果
 *
 * 您可以在用户进入房间前通过 TRTCCloud 的 startSpeedTest 接口进行测速 （注意：请不要在通话中调用），
 * 测速结果会每2 - 3秒钟返回一次，每次返回一个 IP 地址的测试结果。
 *
 * @note - quality 是内部通过评估算法测算出的网络质量，loss 越低，rtt 越小，得分也就越高。
 * @note - upLostRate 是指上行丢包率，例如0.3代表每向服务器发送10个数据包，可能有3个会在中途丢失。
 * @note - downLostRate 是指下行丢包率，例如0.2代表从服务器每收取10个数据包，可能有2个会在中途丢失。
 * @note - rtt 是指当前设备到腾讯云服务器的一次网络往返时间，正常数值在10ms - 100ms之间。
 */
struct TRTCSpeedTestResult
{
    /// 服务器 IP 地址
    const char* ip;

    /// 网络质量，内部通过评估算法测算出的网络质量，loss 越低，rtt 越小，得分也就越高
    TRTCQuality quality;

    /// 上行丢包率，范围是[0 - 1.0]，例如0.3代表每向服务器发送10个数据包，可能有3个会在中途丢失。
    float upLostRate;

    /// 下行丢包率，范围是[0 - 1.0]，例如0.2代表从服务器每收取10个数据包，可能有2个会在中途丢失。
    float downLostRate;

    /// 延迟（毫秒），代表 SDK 跟服务器一来一回之间所消耗的时间，这个值越小越好，正常数值在10ms - 100ms之间。
    int rtt;

    TRTCSpeedTestResult()
        : ip(NULL)
        , upLostRate(0.0f)
        , downLostRate(0.0f)
        , rtt(0)
    {

    }
};

/** 
* \brief 5.9 云端混流中每一路子画面的位置信息
*
* TRTCMixUser 用于指定每一路（即每一个 userId）视频画面的具体摆放位置
*/
struct TRTCMixUser
{
    /// 参与混流的 userId
    const char* userId;

    /// 参与混流的 roomId，跨房流传入的实际 roomId，当前房间流传入 roomId = NULL
    const char* roomId;

    /// 图层位置坐标以及大小，左上角为坐标原点(0,0) （绝对像素值）
    RECT rect;

    /// 图层层次（1 - 15）不可重复
    int zOrder;

    /// 是否纯音频
    bool pureAudio;

	/// 参与混合的是主路画面（TRTCVideoStreamTypeBig）或屏幕分享（TRTCVideoStreamTypeSub）画面
    TRTCVideoStreamType streamType;

    TRTCMixUser()
        : userId(NULL)
        , roomId(NULL)
        , rect()
        , zOrder(0)
        , pureAudio(false)
        , streamType(TRTCVideoStreamTypeBig)
    {
        rect.left = 0;
        rect.top = 0;
        rect.right = 0;
        rect.bottom = 0;
    }
};

/**
 * \brief 5.10 混流参数配置模式
 *
 * 目前暂仅支持手动配置这一种模式，即需要指定 TRTCTranscodingConfig 的全部参数。
 */
enum TRTCTranscodingConfigMode {
    /// 未定义
    TRTCTranscodingConfigMode_Unknown = 0,

    /// 手动配置混流参数
    TRTCTranscodingConfigMode_Manual = 1,
};

/** 
* \brief 5.11 云端混流（转码）配置
*
* 包括最终编码质量和各路画面的摆放位置
*/
struct TRTCTranscodingConfig
{
    ///【字段含义】转码config模式
    TRTCTranscodingConfigMode mode;

    ///【字段含义】腾讯云直播 AppID
    ///【推荐取值】请在 [实时音视频控制台](https://console.cloud.tencent.com/rav) 选择已经创建的应用，单击【帐号信息】后，在“直播信息”中获取
    uint32_t appId;

    ///【字段含义】腾讯云直播 bizid
    ///【推荐取值】请在 [实时音视频控制台](https://console.cloud.tencent.com/rav) 选择已经创建的应用，单击【帐号信息】后，在“直播信息”中获取
    uint32_t bizId;

    ///【字段含义】最终转码后的视频分辨率的宽度（px）
    uint32_t videoWidth;

    ///【字段含义】最终转码后的视频分辨率的高度（px）
    uint32_t videoHeight;

    ///【字段含义】最终转码后的视频分辨率的码率（kbps）
    uint32_t videoBitrate;

    ///【字段含义】最终转码后的视频分辨率的帧率（FPS）
    ///【推荐取值】15
    uint32_t videoFramerate;

    ///【字段含义】最终转码后的视频分辨率的关键帧间隔（也被称为 GOP），单位秒
    ///【推荐取值】3
    uint32_t videoGOP;

    ///【字段含义】最终转码后的音频采样率
    ///【推荐取值】48000
    uint32_t audioSampleRate;

    ///【字段含义】最终转码后的音频码率，单位：K
    ///【推荐取值】64
    uint32_t audioBitrate;

    ///【字段含义】最终转码后的音频声道数
    ///【推荐取值】2
    uint32_t audioChannels;

    ///【字段含义】每一路子画面的位置信息
    TRTCMixUser* mixUsersArray;

    ///【字段含义】 数组 mixUsersArray 的大小
    uint32_t mixUsersArraySize;

    TRTCTranscodingConfig()
        : mode(TRTCTranscodingConfigMode_Unknown)
        , videoWidth(-1)
        , videoHeight(-1)
        , videoBitrate(-1)
        , videoFramerate(-1)
        , videoGOP(-1)
        , audioSampleRate(-1)
        , audioBitrate(-1)
        , audioChannels(-1)
        , mixUsersArray(nullptr)
        , mixUsersArraySize(0)
    {}
};

/**
 * \brief 5.12 CDN 旁路推流参数 
 */
struct TRTCPublishCDNParam
{
    /// 腾讯云 AppID，请在 [实时音视频控制台](https://console.cloud.tencent.com/rav) 选择已经创建的应用，单击【帐号信息】后，在“直播信息”中获取
    uint32_t appId;

    /// 腾讯云直播 bizid，请在 [实时音视频控制台](https://console.cloud.tencent.com/rav) 选择已经创建的应用，单击【帐号信息】后，在“直播信息”中获取
    uint32_t bizId;

    /// 旁路转推的 URL
    const char* url;

    TRTCPublishCDNParam()
        : url(NULL)
        , appId(0)
        , bizId(0)
    {

    }
};

#endif /* __TRTCCLOUDDEF_H__ */
