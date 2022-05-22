
# SBer
这是一个通过命令行帮助你随时随地记录随笔的工具。<br>
<br>当前版本：1.0.0
<br>仅支持Windows平台。

## To use
Put the whole package "SBer" under "D:\\".<br>
Add "SBer\bin" to your Path. Open cmd.exe, input 
```
sber -v
```
to test if it could work.
## Full Usage
```
sber [[-h|-help] || [-v|-ver|-version] || [-config] || [-i|-in|-input [path?]] || [-o|-out|-output path]] [--default] [thought?]
```

<aside>注意</aside>
<ul>
<li>如果你想要保存中文随笔或重定向中文路径，请以<b>ANSI编码</b>方式保存输出文件，且不要以除ANSI编码之外的其他编码方式打开config.json并手动编写其中内容。不然乱码了别骂骂咧咧的。
</ul>

# Options
## -h
It give you a simple guide about how to use this tool via console output.
```s
sber -h
```
## -v
It give you a info about the current version that sber is.
```s
sber -v
```

## -i
Wether open the input mode or specifying an input file.If there is an option after this option, the option will open getting input file from the configured input path.If there is an normal string after this option, it will be resolved as a path of a new input stream.

```s
sber -i "Today I pictured a number of beautiful flowers."
```
The usage above will firstly add the content of the configured file in SB\src\config.json['input'] to the configured file in SB\src\config.json['output'], and put the last sentence to the same output target at its tail. Rember to keep a newline token in your input file.
```s
sber -i d:\mythought.txt "My thought."
```
The usage above will just redirected the input file to d:\mythought.txt，and the last sentence will be add as usual.


## -config
You can configure the input file and output file in an inner json file mannally, or use this option. When appear, the given path after `-o` and the probably given path after `-i` will be writen to the json file automatically as an addtional function.
```s
sber -i c:\mythought.txt -o d:\mysb.txt -config
```
With `-config`, we have the path after `-i` and/or `-o` saved in the SB\src\config.json.
```
sber -config -i -o d:\mysb.txt
```
This usage will only save the new output path after `-o` option. And `-i` option will work as usual.
## --default
If appears, only `-config` can be recognized, other options will be ignored.<br>
With this option, input file will set to config.json["default"]["input"], and output file will be set to config.json["default"]["output"], and timeformat string will be set to config.json["default"]["timeformat"].
```shell
sber --default -config
```
The above usage will be the same as followed:
```shell
sber -config -i ..\default\input.txt -o ..\default\output.txt -tf \n%Y年%m月%d日 %H:%M:%S\n -config
```
All other options will be ignored. 
## thought
Your thought, may usually should be quoted by 
' " ' around, will be added at last.
<hr/>

# 如果对作者小哥哥做的小游戏也感兴趣的话，欢迎轻访<a href="http://www.cmtheit.com">我的网站</a>下载玩耍喔！

骚扰方式
<address>QQ:2905432378</address>
<address>微信：zc2905432378</address>
<address>E-mail: cmtheit@outlook.com</address>