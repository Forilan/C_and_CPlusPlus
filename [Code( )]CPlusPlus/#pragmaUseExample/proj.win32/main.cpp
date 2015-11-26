// NamedPipeClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "#pragmaUseExample.h"



#if 1
int _tmain(int argc, _TCHAR* argv[])
{

	if(app_count>1)    // 如果计数大于0，则退出应用程序。
	{

		exit(1);
	}
	app_count++;

	printf("sdfssd");
	system("pause");

	return 0;
}
#endif


