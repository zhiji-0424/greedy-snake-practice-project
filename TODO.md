发布流程：
======================
[蒲公英](www.pgyer.com/app/publish)

新的测试方法：（只在Android）在手机上开发的特殊原因
======================

> ~~cpp端独立开发，测试器与正式版共存，测试器就在cpp端。只有Java端检测到Android应用目录有 `程序.so` 文件才启动测试器，否则正常启动自带程序文件。
> 
> 调试加载器需要传参数(argc==2025)以免无限循环加载。
> 
> 需要另外加载的：`程序.so`、`assets/`  
> 
> 要记得正式发行时打包测试删掉 `程序.so`。  
> 
> activity load libmain.so  
> if (is_debug) (no)argc==2025,(yes)file  
    copy  
    load  
    run  
    return0;  
else  
    new game ...end  
必须 检测文件 和 检测命令行参数 来判断。~~

~~伪代码：
``` python
if not debug: 此时是APP正常启动
    if would be debug (so文件存在):
        启动加载器（加载的程序从这个代码片段头部再运行）
    else
        正常启动game
else: 此时作为待调试的程序启动，已加载完成
    不启动加载器
    game
```
所以开发调试时必须设置debug模式，否则会陷入循环加载器。~~

**调试与正式发行**：修改包名、编译列表的开关、签名

不需要加载器了。
修改包名：安装调试与正式版本签名不冲突；
开关编译列表：选择编译加载器（给调试版本）或编译正式版本。

---

适配 Android 5~13
(android:exported="true"
android:debuggable)

