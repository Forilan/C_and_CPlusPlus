// NamedPipeClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>


#include "2charƴ�ӳ�int.h"
#include "200��forѭ������ʱ��.h"

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

	//getchar();		// ��ֹ ��������

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


