
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

// 12-第12章-动态内存

/*
	全局对象在 程序启动时分配，在程序结束时销毁。

	对于局部自动对象，进入其定义所在的程序块时被创建，在离开块时销毁。

	局部static 对象在第一次使用前分配，在程序结束时销毁。

	动态分配的对象的生存期与它们在哪里创建是无关的，只有当显式地被释放时，这些对象才会被销毁。
*/


/*
	静态内存 和 栈内存

	静态内存 用来保存局部 static 对象， 类static数据成员 以及定义在任何函数之外的变量。

	栈内存 用来 保存定义 在函数内的 非static对象。

	除了静态内存和栈内存，每个程序还拥有一个内存池。这部分内存被称作 自由空间 或 堆。
*/


//=========================================================================
//
//							12.1 动态内存与智能指针
//
//=========================================================================


/*
	在 C++ 中，动态内存的管理是通过一对运算符来完成的： new ，delete.

	为了更容易的使用 动态内存，新的标准库 提供了 智能指针 来管理动态对象。

	shared_ptr 允许多个指针指向同一个对象
	unique_ptr 则“独占”所指向的对象
	weak_ptr 一种弱引用
*/


// 12.1.1 shared_ptr 类 __________________________
/*
	类似 vector， 智能指针也是模板。 因此，当我们创建一个智能指针时，必须提供额外的信息--指针可以指向的类型。
*/  

void study_shared_ptr_use()
{
	shared_ptr<string>		p1;		// 可以指向 string
	shared_ptr<list<int>>	p2;
}

/*	【make_shared 函数】
	最安全的分配和使用动态内存的方法是调用一个名为 make_shared 的标准库函数
*/

void study_shared_ptr_init()
{
	shared_ptr<int> p3 = make_shared<int>(42);				// p3 指向一个 值为42的 int 的 shared_ptr
	shared_ptr<string> p4 = make_shared<string>(10, '9');		// p4 指向一个值为 “9999999999” 的 string

	auto p5 = make_shared<int>();		// 空值，为0
}