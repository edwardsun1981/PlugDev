========================================================================
     Plug 概况
========================================================================
Plug是一个组件化开发框架，它可以帮助开发人员快速建立组件模块，统一接口、开发规范，方便的创建，释放组件。同时Plug 规定了程序员开发组件的标准结构，并促使程序员将
软件按功能划分为组件,有用于提高软件开发效率，提高代码重用性，保护源代码， 提高软
件团队开发沟通速度的规则。支持插件, SDK，Plug支持Windows,linux,mac,andriod, ios平台。其他平台未测试但也应该支持。
是软件工程学的具体应用框架。

Plug如何保护源程序？
	Plug 开发框架使用每个程序员只能看到自己写的源程序，和自己需要调用的接口,
其它源程序，一个字节也不需要知道，当然，除非故意让他知道。
	

Plug 优点
	二进制兼容，最终编译出的二进制文件，可以直接放到其它软件中使用。灵活的二进制输出形式，可以在不改任何源码代码的情况下，把无数个组件编译成一个可执行文件， 或把任意多个组件编译成任意多个(.DLL,.so)，也就是说，最终要Release的程序，无论开发的时候用了多少组件(.DLL,.so)，发布的时候可以是只有一个可执行体EXE，也可以带任意多个(.DLL,.so)，可以随意定制.

Plug 特点
1、不需要引出函数
2、不需要CPP文件，任何类型的程序只需要包含盘plug.h就可以使用
3、只需要一句初始化语句，不需要手动释放
4、使用更简单，请见Plug使用原则



Plug使用原则:

1、标准Plug dll, 直接使用
2、EXE, 在任何全局的地方调用一下 INIT_PLUG
3、Dll(win32 dll、mfc dll、ocx dll、atl dll、DSFilter dll...), 在全局加一句PLUG_COMPONENT_AUTO_REG(ProjectName)就可以像标准Plug dll中一样使用了

4、所有标准Plug dll可以编译到一个Dll或可以和其中一个EXE编译到一个EXE文件里
5、编译选项，如果能在源文件中修改的就不要在编译选项中修改，如数据对齐，默认4字节，如果要修改成
	其它字节请在文件中修改，如果修改了编译选项请在本文件中说明，以使用联编时参照
6、Dll出现在本目录或 PlugDll目录及子目录中将会在EXE初始化时被load. 
	PlugDll目录及子目录只能放Dll文件

开发原则:
	

Plug 实现原理:
	

2.3版改进
1.支持动态load组件，及随时free; StandardPlug::DllLoadContorl c("core\\")
2.增加命名空间，使外部暴露更少的数据结构及定义单位
3.增加错误隔离系统
4.文件分开, 使用三个头文件(plug发展到现在己经很复杂了，使用多个文件有利于开发维护)
5.组件覆盖检测，在debug时如果出现重复组件，会检测出来并提示
6.去掉DllMain函数

2.6版改进
使用字符串做为ID，去掉IID_。
去掉全局变量g_pc
优先使用Open内存
完善提示

3.0版本改进
1)支持夸dll/so  使用LOG()
2)支持夸dll/so 存取指针，字符串，std::function。例如：Plug::GetApp()->set.../get...





Plug is a component-based development framework, it can help developers quickly build components module, unified interface, the development of norms to facilitate the creation, release of components. Plug programmers at the same time provides for the development of the standard structural components, and programmers will be prompted 
According to the functions of the software is divided into components, software developers have used to enhance efficiency, improve code reuse, the protection of source code, improve the soft 
Pieces of team communication and speed the development of rules. Supported plug-ins, SDK, Plug Supporting Windows, linux, mac platform.

Plug how to protect the source? 
Plug the use of each development framework can only see their own programmers to write the source code, and they need to call the interface, 
Other source, a byte not need to know, unless, of course, deliberately let him know. 


Plug the advantages of 
Binary compatible, and ultimately compile a binary file, can be directly put to use other software. Flexible forms of binary output can be switched without 

Ho-source code to compile numerous components into one executable file, or any number of components into any number of the compiler (. DLL,. So), that is to say 

Ultimately Release procedures, regardless of the time spent to develop the number of components (. DLL,. So), can be released when the body is only one executable EXE, can also bring 

Any number of (. DLL,. So), can be customized. 

Plug Features 
1, no extraction function 
2, do not need to CPP files, any type of program only need to contain plug.h disk you can use 
3, only need to initialize a statement, do not need to manually release 
4, the use of more simple, please refer to the use of the principle of Plug 
5, increase deal with the incident, far from the callback