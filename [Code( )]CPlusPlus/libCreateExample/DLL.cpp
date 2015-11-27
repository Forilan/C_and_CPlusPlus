// DLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#define DLL_API extern "C" _declspec(dllexport)

#include "ShareDLL.h"


// 给数据段起个名字。
#pragma data_seg("SharedDataInDll")				
int data[80][80][40] = {0};
#pragma data_seg()

//这里还需要告诉链接器表明 SharedDataInDll 数据段为可读可写可共享
#pragma comment(linker, "/SECTION:SharedDataInDll,RWS")

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


/// int 的版本，已经验证成功。
#if 0

//使用 #pragma data_seg() 来表明这一段数据为共享数据
//一定要注意给下面的变量初始化，否则将无法实现数据在多个进程间共 享
#pragma data_seg("SharedDataInDll")				// 是给这个数据段起了个名字。

//初始化为 0
int data = 0;

#pragma data_seg()


//这里还需要告诉链接器表明 SharedDataInDll 数据段为可读可写可共享
#pragma comment(linker, "/SECTION:SharedDataInDll,RWS")


//返回共享数据
int GetData()
{
	return data;
}

//设置共享数据
void SetData(int tmpData)
{
	data = tmpData;
}

#endif
