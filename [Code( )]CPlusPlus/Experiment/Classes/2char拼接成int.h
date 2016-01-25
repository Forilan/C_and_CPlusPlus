
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

 

// 二进制 111111111111111100000000
// 十六进制 FFFF00