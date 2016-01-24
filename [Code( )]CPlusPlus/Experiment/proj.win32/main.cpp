// NamedPipeClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


#include "2char拼接成int.h"
#include "200次for循环测量时间.h"

#if 1
int _tmain(int argc, _TCHAR* argv[])
{

#if 0
	char a = 0x63;
	char b = 0xFD;
	int res = char2int(a,b);
	cout << res;
#endif


	//	for200times();

	//getchar();		// 防止 窗口闪掉

	int negaive = -2;
	unsigned int er = 0 , ers = 0, erh = 0;

	ers = negaive;
	er = (unsigned int) negaive;
	int h = er + negaive;

	cout << ers << endl;
	cout << h << endl;

	cout << erh -2 << endl;

	system("pause");

	return 0;
}
#endif


