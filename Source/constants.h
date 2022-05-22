#ifndef CONSTANTS
#define CONSTANTS


const char * version  = "1.0.0";

const char * helpinfo = "SBer 你的随笔记录小帮手\n\n用法：\n    sber [[-h|-help] || [-v|-ver|-version] || [-config] || [-i|-in|-input [path?]] || [-o|-out|-output path]] [thought?] options are as followed:\nuni:\n    -v, -ver, -version      获取当前 SBer 版本\n    -h, -help               获取帮助\n    --default               将输入文件设置为 config.json 中 default 对应的 input 和 output，可以搭配 -config 实现恢复默认设置模式\npair:\n    -o, -out, -output       输出重定向到该文件时间格式字符串\n    -i, -in, -input         输入从文件中获取，当且仅当本参数指定才可省略content参数，且必须省略content参数\n    -config               n中的服务\n";
const int time_format_max_len = 64;

#endif