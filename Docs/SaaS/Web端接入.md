### 拼接链接打开课堂

- URL启动

```
https://tedu.qcloudtrtc.com/#/class/sdkappid/:class_id/:user_id?/:user_sig?/:user_token?
```

- 参数描述

参数名称|参数类型|参数描述
:--:|:--:|:--
sdkappid|int|腾讯云应用程序标识
class_id|int|课堂id
user_id|string|用户帐号
user_sig|string|腾讯云用户签名(用于登录IMSDK)
user_token|string|用户签名


#### example - 不带登录态
```
sdkappid(腾讯云应用程序标识) => 1400162216
class_id（课堂id） => 1000713668
```

https://tedu.qcloudtrtc.com/#/class/1400162216/1000713668