#pragma  once



/*
lib和dll 
lib和dll文件的区别和联系

.dll是在你的程序运行的时候才连接的文件，因此它是一种比较小的可执行文件格式，.dll还有其他的文件格式如.ocx等，所有的.dll文件都是可执行。

.lib是在你的程序编译连接的时候就连接的文件，因此你必须告知编译器连接的lib文件在那里。

一般来说，与动态连接文件相对比，lib文件也被称为是静态连接库。
当你把代码编译成这几种格式的文件时，在以后他们就不可能再被更改。如果你想使用lib文件，就必须：

1 包含一个对应的头文件告知编译器lib文件里面的具体内容

2 设置lib文件允许编译器去查找已经编译好的二进制代码
*/

#define _DLL_SAMPLE

// ------------------------------------------------------------------------------------------------------------------
//						建立头文件	【ShareDLL.h】【这个头文件会分别被 DLL和调用DLL的应用程序引入】	
// ------------------------------------------------------------------------------------------------------------------
#if 0

#pragma  once

// 在头文件中，对需要导出的函数进行声明。

// 通过宏来控制是导入还是导出
#ifdef _DLL_SAMPLE
#define DLL_SAMPLE_API __declspec(dllexport)
#else
#define DLL_SAMPLE_API __declspec(dllimport)
#endif

// 导出/导入函数声明
DLL_SAMPLE_API void		SetData(int tmpData, int i, int j, int k);
DLL_SAMPLE_API int		GetData(int i, int j, int k);
DLL_SAMPLE_API int*		GetDataPoint();

/*
这个头文件会分别被DLL和调用DLL的应用程序引入，当被DLL引入时，在DLL中定义_DLL_SAMPLE宏，
这样就会在DLL模块中声明函数为导出函数；当被调用DLL的应用程序引入时，就没有定义_DLL_SAMPLE，
这样就会声明头文件中的函数为从DLL中的导入函数。 
*/
#endif

// ------------------------------------------------------------------------------------------------------------------
//						编写 DllMain函数 - 【dllmain.cpp】
// ------------------------------------------------------------------------------------------------------------------
#if 0

#include "stdafx.h"

//APIENTRY声明DLL函数入口点
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	　switch (ul_reason_for_call)
	 　{
	 　 case DLL_PROCESS_ATTACH:
	    case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	 　}
	 　return TRUE;
}

#endif

/*
如果程序员没有为DLL模块编写一个DLLMain函数，系统会从其它运行库中引入一个不做任何操作的缺省DLLMain函数版本。
在单个线程启动和终止时，DLLMain函数也被调用。
然后，F7编译，就得到一个DLL了。
*/

// ------------------------------------------------------------------------------------------------------------------
//						编写 导出函数 - 【DLL.cpp】
// ------------------------------------------------------------------------------------------------------------------
#if 0

#include "stdafx.h"
#define DLL_API extern "C" _declspec(dllexport)
#include "ShareDLL.h"

int data[80][80][40] = {0};

//返回指向共享数据的指针，by adress
int* GetDataPoint()
{
	int * pos = &data[0][0][0];
	return pos;
}

//写数据，通过值传递
void SetData(int tmpData, int i, int j, int k)
{
	data[i][j][k] = tmpData;
}

//读数据，通过值传递
int	GetData(int i, int j, int k)
{
	return data[i][j][k];
}

#endif

// ------------------------------------------------------------------------------------------------------------------
//						如何使用DLL
// ------------------------------------------------------------------------------------------------------------------
/*
隐式链接-【编译时把静态库 .lib 链接进来】

这里有两个方法来载入一个DLL；一个方法是捷径另一个则相比要复杂些。
捷径是只链接到你.lib 文件并将.dll文件置入你的新项目的路径中去。
因此，创建一个新的空的Win32控制台项目并添加一个源文件。
将你做的DLL放入你的新项目相同的目录下,也可以在项目属性中设置库的链接,也可以放到系统库里面去。
*/
#if 0

#include "stdafx.h"
#include "ShareDLL.h"

#pragma comment(lib, "DLLSample.lib") //你也可以在项目属性中设置库的链接

int main()
{
	GetDataPoint();			//dll中的函数，在ShareDLL.h中声明
	return(1);
}

#endif


/*
显式链接-【运行时，把动态库.dll 链接进来】

显式链接 的加载DLL的方法稍微有点复杂。你将需要函数指针和一些Windows函数。
但是，通过这种载入DLLs的方法，你不需要DLL的.lib或头文件，而只需要DLL。
*/
#if 0

#include <iostream>
#include <windows.h>
typedef void (*DLLFunc)(int);
int main()
{
	DLLFunc dllFunc;
	HINSTANCE hInstLibrary = LoadLibrary("DLLSample.dll");		// 自己LoadLibary调入DLL文件到内存里面

	if (hInstLibrary == NULL)
	{
		FreeLibrary(hInstLibrary);
	}
	dllFunc = (DLLFunc)GetProcAddress(hInstLibrary, "TestDLL");	// 再手工GetProcAddress获得对应函数
	if (dllFunc == NULL)
	{
		FreeLibrary(hInstLibrary);
	}
	dllFunc(123);
	std::cin.get();
	FreeLibrary(hInstLibrary);									// 最后要记得使用FreeLibrary函数释放内存
	return(1);
}




#endif