# g3507_framework

## 项目简介

本项目是TI MSPM0G3507开发板代码框架，适配立创天猛星开发板，移植自nrtos下的empty项目+FreeRTOS核心文件
> FreeRTOS移植参考https://blog.csdn.net/m0_58759897/article/details/152089580

## vscode编辑器

因为CCS不好用而且不稳定，<del>而且copilot太好用了，</del>建议使用vscode作为编辑器，CCS用于引脚分配、烧录和调试。CCS环境搭建参考网络，vscode配置方式如下：
1. 安装C/C++、C/C++ Extension Pack插件
2. 在项目根目录下创建`.vscode`文件夹，在文件夹内创建`c_cpp_properties.json`文件，并写入下述代码，如果是克隆本工程，则可以直接进行下一步操作
```json
{
    "configurations": [
        {
            "name": "MSPM0G3507_Config",
            "includePath": [
                "C:/software/ti/mspm0_sdk_2_05_01_00/source",
                "C:/software/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include",
                "C:/software/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/include",
                "${workspaceFolder}",
                "${workspaceFolder}/Debug",
                "${workspaceFolder}/Middlewares/**",
                "${workspaceFolder}/Users"
            ],
            "defines": [
                "__MSPM0G3507__"
            ],
            "windowsSdkVersion": "10.0.18362.0",
            "compilerPath": "C:/software/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-clang-arm"
        }
    ],
    "version": 4
}
```
3. 将`includePath`键值中所有的`C:/software/ti/...`改为你实际的sdk/complier安装目录；将`compilerPath`键值改为你实际的clang编译器目录
4. 在CCS先Build工程，编译通过之后，在vscode编写代码就不会有报错了

## 外设和引脚分配

| 外设 | 引脚 | 功能（天猛星） |
| --- | --- | --- |
| SYSCTL |  |  |
| DEBUGSS | PA20 | Debug Clock |
| DEBUGSS | PA19 | Debug Data In Out |
| GPIO | PB22 | 板载LED |
| UART0 TX | PA28 | 串口通信 |
| UART0 RX | PA31 | 串口通信 |
| GPIO | PB23 | 红外巡线 |
| GPIO | PB26 | 红外巡线 |
| GPIO | PB27 | 红外巡线 |
| GPIO | PA29 | 红外巡线 |
| GPIO | PA14 | 软件编码器 |
| GPIO | PA15 | 软件编码器 |
| GPIO | PA16 | 软件编码器 |
| GPIO | PA17 | 软件编码器 |
| GPIO | PA24 | 电机驱动 |
| GPIO | PA25 | 电机驱动 |
| GPIO | PA26 | 电机驱动 |
| TIMA0 | PA0 | PWM CH0 |
| TIMA0 | PA1 | PWM CH1 |

## 常见问题

1. 抽象层函数的调用方法参考Tasks层函数

2. 链接错误。C/C++函数相互调用的时候，需要在C/C++函数对应的头文件加入声明
```cpp
#ifdef __cplusplus
extern "C" {
#endif
/* C/C++相互调用的函数声明 */
#ifdef __cplusplus
}
#endif
```
在修改程序源码、文件名、文件夹名之后，CCS可能会出现编译缓存不刷新的问题，导致链接出错，通常的报错是修改过的文件中被调用的函数未定义，此时只需要删除Debug文件夹（Clean Projects不一定有效），清理缓存之后再进行编译即可

3. 硬件配置问题。在检查软件逻辑无误之后，如果无法触发某种功能，请首先打开.syscfg文件检查引脚配置（PinMux）、中断配置（Interrupt Configuration），使用中断需要调用`NVIC_Enable_IT()`使能对应的中断
