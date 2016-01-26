
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

// 16位单片机的int型内存数据转化成32位的
int char2int(const char & temp1, const char &  temp2) 
{
	int stick = temp2;
	if ((stick & 0x80) == 1)	stick |= 0xFFFF00 ; // 如果标志位为负数,就把前面全部置为1.
	return (stick << 8) | temp1;
}

// 16位单片机的int型内存数据转化成32位的
short char2short(const char & temp1, const char &  temp2) 
{
	short stick = temp2;
	return (stick << 8) | temp1;
}

// 二进制 111111111111111100000000
// 十六进制 FFFF00


void runMEforMain()
{
	char a = 0x63;
	char b = 0xFD;
	int res = char2int(a,b);
	int res1 = (int)char2short(a,b);
	cout << res << endl;
	cout << res1 << endl;
}


/*
一、短数据类型扩展为长数据类型

1、要扩展的短数据类型为有符号数的

进行符号扩展，即短数据类型的符号位填充到长数据类型的高字节位（即比短数据类型多出的那一部分），
保证扩展后的数值大小不变

如1：char x=10001001b;   short y=x;  则y的值应为11111111 10001001b；

2：char x=00001001b;   short y=x;  则y的值应为00000000 00001001b；

2、要扩展的短数据类型为无符号数的

进行零扩展，即用零来填充长数据类型的高字节位

如1：unsigned char x=10001001b;   short y=x;  则y的值应为00000000 10001001b；

2：unsigned char x=00001001b;   short y=x;  则y的值应为00000000 00001001b；

*/