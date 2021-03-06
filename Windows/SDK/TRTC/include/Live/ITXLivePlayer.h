#ifndef __ITXLIVEPLAYER_H__
#define __ITXLIVEPLAYER_H__
/*
* Module:  ITXLivePlayer @ TXLiteAVSDK
*
* Function: 直播拉流功能的主要接口类
*
* 创建/使用/销毁ITXLivePlayer对象的示例代码：
* ITXLivePlayer *livePlayer = createTXLivePlayer();
* if(livePlayer)
* {
*     int nDevice = livePlayer->speakerDeviceCount();
* }
* destroyTXLivePlayer(&livePlayer);
* livePlayer = NULL;
*/
#include "TXLiveTypeDef.h"
#include "TXLiteAVBase.h"
#include <Windows.h>
#include <memory>

#define SPEAKER_DEVICE_NAME_MAX_SIZE    (512)
class ITXLivePlayerCallback;
class ITXLivePlayer;

extern "C" {
    /**
    * \brief 用于动态加载dll时，导出TXLivePlayer C++对象。
    *
    * \return TXLivePlayer对象指针，注意：delete ITXLivePlayer*会编译错误，需要调用destroyTXLivePlayer释放。
    */
    LITEAV_API ITXLivePlayer* createTXLivePlayer();

    /**
    * \brief 析构ITXLivePlayer对象
    */
    LITEAV_API void destroyTXLivePlayer(ITXLivePlayer** pTXlivePlayer);
}


class ITXLivePlayer
{
protected:
    virtual ~ITXLivePlayer() {};

public:
	/**
	* \brief：设置回调 TXLivePlayer 的回调代理，监听播放事件
	* \param：callback  - ITXLivePlayerCallback 类型的代理指针
	* \param：pUserData - 透传用户数据到 ITXLivePusherCallback 的回调函数,一般情况下传 NULL 就可以了
	* \return 无
	*/
    virtual void setCallback(ITXLivePlayerCallback *callback, void *pUserData) = 0;

    /**
    * \brief：查询可用的扬声器设备的数量
    * \return：若查询成功，则返回值>=0；若查询失败，则返回值为-1
    */
    virtual int speakerDeviceCount() const = 0;

    /**
    * \brief：查询扬声器设备的名称
    * \param：index - 扬声器设备的索引，要求index值小于 speakerDeviceCount 接口的返回值
    * \param：name - 用于存放扬声器设备的名称的字符串数组，数组大小要求 <= SPEAKER_DEVICE_NAME_MAX_SIZE，查询得到的字符编码格式是UTF-8
    * \return：若查询成功，则返回值true；若查询失败或者index非法，则返回值为false
    */
    virtual bool speakerDeviceName(unsigned int index, char name[SPEAKER_DEVICE_NAME_MAX_SIZE]) = 0;

    /**
    * \brief：选择指定的扬声器作为音频播放的设备，不调用该接口时，默认选择索引为0的扬声器
    * \param：index - 扬声器设备的索引，要求index值小于 speakerDeviceCount 接口的返回值
    */
    virtual void selectSpeakerDevice(unsigned int index) = 0;

    /**
    * \brief：查询SDK播放的音量，注意查询得到不是系统扬声器的音量大小
    * \return：音量值，范围是[0, 65535]
    */
    virtual unsigned int speakerVolume() = 0;

    /**
    * \brief：设置SDK播放的音量，注意设置的不是系统扬声器的音量大小
    * \param：volume - 设置的音量大小，范围是[0, 65535]
    */
    virtual void setSpeakerVolume(unsigned int volume) = 0;

    /**
    * \brief：查询已选择扬声器的能量值，指示音量的大小
    * \return：能量值，范围是[0, 65535]
    */
    virtual uint32_t speakerVolumeIndication() = 0;

	/**
	* \brief：设置视频图像渲染
	* \param：rendHwnd - 承载预览画面的 HWND，目前 SDK 内部会向 rendHwnd (整个窗口)上绘制图像的
	* \return:无
	*/
    virtual void setRenderFrame(HWND rendHwnd) = 0;

	/**
	* \brief：重设图像渲染窗口
	* \param：rendHwnd - 承载预览画面的 HWND，目前 SDK 内部会向 rendHwnd (整个窗口)上绘制图像的
	* \return:无
	*/
    virtual void updateRenderFrame(HWND rendHwnd) = 0;

	/**
	* \brief：关闭图像渲染
	*/
    virtual void closeRenderFrame() = 0;

	/**
	* \brief：开始播放，请在 startPlay 之前 setRenderFrame
    * \param：url   - 视频播放 URL
    * \param：type  - 播放类型，参考 TXLiveTypeDef.h 中定义的 TXEPlayType 枚举值
	* \return：无 
	*/
    virtual void startPlay(const char * url, TXEPlayType type) = 0;

	/**
	* \brief：停止播放
	*/
    virtual void stopPlay() = 0;

	/**
	* \brief：暂停播放
	*/
    virtual void pause() = 0;

	/**
	* \brief：恢复播放
	*/
    virtual void resume() = 0;

	/**
	* \brief：是否正在播放
	*/
    virtual bool isPlaying() = 0;

	/**
	* \brief：静音接口
	* \param：mute - 是否静音
	* \return:无
	*/
    virtual void setMute(bool mute) = 0;

    /**
    * \brief：设置图像的渲染（填充）模式
    * \param：mode - 参考 TXLiveTypeDef.h 中定义的 TXERenderMode 枚举值
    * \return:无
    */
    virtual void setRenderMode(TXERenderMode mode) = 0;

    /**
    * \brief：设置图像的顺时针旋转角度
    * \param：rotation - 参考 TXLiveTypeDef.h 中定义的 TXEVideoRotationType 枚举值
    * \return:无
    */
    virtual void setRotation(TXEVideoRotationType rotation) = 0;

	/**
	* \brief：设置渲染的镜像效果
	* \param：mirror - true表示画面左右反转，false表示保持原样
	* \return:无
	*/
    virtual void setRenderYMirror(bool mirror) = 0;

    /**
    * \brief：设置视频编码格式，默认格式是TXE_OUTPUT_VIDEO_WITHOUT_OUTPUT
    * \param：format - 视频编码格式，参考 TXLiveTypeDef.h 中定义的 TXEOutputVideoFormat 枚举值
    * \return:无
    */
    virtual void setOutputVideoFormat(TXEOutputVideoFormat format) = 0;

    /**
    * \brief：是否开启消息通道， 默认值为 false
    * \param：enableMessage - true：开启，false：关闭
    */
    /// 
    virtual void setEnableMessage(bool enableMessage) = 0;

	/**
	* \brief：截图当前拉流的图像到本地，
	* \param：filePath - 存储路径，
	* \param: length - 路径大小
	* \return：0成功，非0失败
	* \errorRet:  -1:失败，-2路径非法，-3文件存在，-4未拉流
	*/
    virtual int captureVideoSnapShot(const wchar_t * filePath, unsigned int length) = 0;
};
#endif //__ITXLIVEPLAYER_H__