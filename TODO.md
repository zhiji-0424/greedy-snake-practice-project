发布流程：
======================
    Native层: (1)添加v7a v8a x86 x86_64, (2)设置不调试
    Java层：  (1)debug_mode = false; (2)编译
    复制 libs/(两个ABI文件夹)
    [www.pgyer.com/app/publish]

新的测试方法：
======================

cpp端独立开发，测试器与正式版共存，测试器就在cpp端。只有Java端检测到Android应用目录有 `程序.so` 文件才启动测试器，否则正常启动自带程序文件。

需要另外加载的：`程序.so`、`assets/`

要记得正式发行时打包测试删掉 `程序.so`。

---

适配 Android 5~13
(android:exported="true"
android:debuggable)

