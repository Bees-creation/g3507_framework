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
