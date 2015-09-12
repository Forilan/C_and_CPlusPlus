
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

// 01-第1章 开始

#if 0
// __________________________1.1 编写一个简单的 C++ 程序 __________________________
int main()
{
	return 0;
}

/*
	一个函数的定义包含四个部分：
		return type
		function name
		parameter list
		function body
*/ 

/*
	int 类型是一种内置类型（built-in type）,即语言自身定义的类型。

	类型是程序设计最基本的概念之一。一种类型不仅定义了数据元素的内容，还定义了这类数据上可以进行的运算。
*/
#endif

// __________________________1.2 初识输入输出 __________________________
int sumTwoNum()
{
	std::cout << "Enter two numbers:" << std::endl;
	int v1 = 0, v2 = 0;
	std::cin >> v1 >> v2;
	std::cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << std::endl;

	getchar();		// 防止 窗口闪掉

	return 0;
}

// << 输出运算符 __________________________
/*
	<< 输出运算符 接受两个运算对象：左侧的运算对象必须是一个 ostream 对象，右侧的运算对象是要打印的值。
	<< 输出运算符 返回其左侧的 运算对象。
*/ 

// >> 输入运算符 __________________________
/*
 *	>> 输入运算符 接受 一个 istream 作为其 左侧对象，接受一个对象作为其右侧运算对象。
 *	>> 输入运算符 返回其左侧的 运算对象。
 *
 *	总结：
 *	<< 和 >> 都返回左侧 的运算对象。这样就 好记忆 哪个是 输入 ，哪个是输出了吧。
 */ 

// endl __________________________
/*
	这是一个 操纵符的特殊值。写入 endl 的效果是结束当前行，并将与设备关联的缓存区(buffer)中的内容刷到设备中。
	缓冲刷新操作可以保证到目前为止程序所产生的所有输出都真正写入输出流中，而不是金停留在内存中等待写入流。
*/ 

/*	【WARNING】
	程序员常常在调试时添加打印语句。这里语句应该保证“一直”刷新流。
	否则，如果程序崩溃，输出可能还留在缓冲区中，从而导致关于程序崩溃位置的错误推断。

	cocos2dx 游戏 在 android 运行时，在 ondestory() 打印的LOG信息,有的时候看不到，估计就是 游戏异常退出时，缓存区被干掉了。
*/

// __________________________1.4 控制流 __________________________

// 1.4.3 读取数量不定的输入数据
int main2()
{
	int sum = 0, value = 0;

	while( std::cin >> value)
		sum += value;

	std::cout << "Sum is: " << sum << std::endl;

	return 0;
}	

/*
	当 istream 对象作为条件时，其效果是检测流的状态。如果流是有效的，即流未遇到错误，那么检测成功。
	当遇到文件结束符，或遇到一个无效输入时，istream 对象的状态会变为无效。
	处于无效状态的 istream 对象会使条件变为假。

	因此 while 循环会一直执行直至 遇到文件结束符(或输入错误)。

	文件结束符：
	Windows系统中，Ctrl + Z ,然后按 Enter 或 Return 键。
	UNIX 系统中，包括Mac OS X 系统中， Ctrl + D
*/

// 1.4.4 用if语句写一个程序，来统计在输入中每个值【连续出现】了多少次；

int main1()
{
	int value,nextValue,count;
	if(std::cin >> value)
	{
		count = 1;
		while(std::cin >> nextValue)
		{
			if( nextValue == value )
			{
				++count;
			}else{
				std::cout << value << " has show " << count << " time" << endl;
				value = nextValue;
				count = 1;
			}
		}
		std::cout << value << " has show " << count << " time" << endl;
	}

	return 0;
}	

/*
e.g.
cin:
42 42 42 42 42 55 55 62 100 100 100
cout:
42 has show 5 times
55 has show 5 times
62 has show 5 times
100 has show 5 times

*/


