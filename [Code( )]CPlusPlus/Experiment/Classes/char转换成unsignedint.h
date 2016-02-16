
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;



// 好像没有发现有什么问题。

unsigned int charChangeInt(const char & a) 
{
	unsigned int c = (unsigned)a;
	return c;
}

void runCharChangeInt()
{
	char a = 0x63;
	char b = 0xFD;
	//unsigned int res =charChangeInt(b);
	//unsigned int res1 =charChangeInt(a);
	int res = char2int(a,b);
	int res1 = (int)char2short(a,b);

	cout << res << endl;
	cout << res1 << endl;
	cout << sizeof(char) << endl;
	cout << sizeof(short) << endl;
	cout << sizeof(int) << endl;
}