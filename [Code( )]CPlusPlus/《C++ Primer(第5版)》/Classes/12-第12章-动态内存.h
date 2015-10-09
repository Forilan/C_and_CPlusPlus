
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

#include <memory>			// shared_ptr 需要

#include <list>
using std::list;

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

// shared_ptr 和 unique_ptr 都支持的操作
void study_shared_ptr_unsingle_use()		// shared_ptr 和 unique_ptr 都支持的操作。
{
	// 空智能指针，可以指向 int 类型。
	shared_ptr<int>		sp0;
	unique_ptr<int>		up0;

	sp0 = make_shared<int>(43);

// *p 解引用，获得 p 所指向的对象。
	int test = *sp0;
	std::cout << test << std::endl;

// p.get()		
/*
	返回 p 中保存的指针，要小心使用，若智能指针释放了其对象，返回的指针所指向的对象也就消失了。
	p.get()	返回的 其实就是一种弱引用了。
*/
	int * i_p = sp0.get();
	int test1 = * i_p;
	std::cout << test1 << std::endl;
	
// swap(p,q)  or p.swap(q);
/*
	p 和 q 都必须是智能指针类型的。不支持 * T类型。
*/
	shared_ptr<int> sp1 = make_shared<int>(44);
	swap(sp0, sp1);
	std::cout << *sp0 << " " << *sp1  << std::endl;

	sp0.swap(sp1);
	std::cout << *sp0 << " " << *sp1  << std::endl;



	* i_p = 11;
	int test2 = *sp0;
	std::cout << test2 << std::endl;
}

// 获得固定数组的大小。
template <typename T, unsigned N>
int getArrayLength(const T (&p1)[N])
{
	return N;
}

// 12.1.? unique_ptr 类 __________________________
void study_unique_ptr_single_use()		
{
	float a[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

	std::unique_ptr<float[]> verticesImage(nullptr);
	verticesImage.reset(a);

	// 遍历数组
	int j = getArrayLength(a);
	for (int i = 0; i < j; ++i)
	{
		std::cout << verticesImage[i] << std::endl;
	}
}


// 12.1.6 weak_ptr 类 __________________________
/*
	一旦最后一个指向对象的 shared_ptr 被销毁，对象就会被释放，即使有 weak_ptr 指向对象，对象还是会被释放。

*/  

void study_weak_ptr_init()
{
	shared_ptr<int> p1 = make_shared<int>(42);	
	weak_ptr<int> wp;
	
	//wp = make_shared<int>(p1);		//	当我们创建一个 weak_ptr 时，要用一个 shared_ptr 来初始化它。

	//int a = wp;



}


// 循环引用

// 循环引用 __________________________
/*
	可以理解为用 weak_ptr 才比较好的解决的棘手问题。

*/

#if 0

class B;
class A
{
public:
	　　shared_ptr<B> m_b;
};

class B
{
public:
	　　shared_ptr<A> m_a;
};

int main()
{
	while (true)
	{
		shared_ptr<A> a(new A);		//new出来的A的引用计数此时为1
		shared_ptr<B> b(new B);		//new出来的B的引用计数此时为1
		a->m_b = b;		//B的引用计数增加为2
		b->m_a = a;		//A的引用计数增加为2
	}

	  //b先出作用域，B的引用计数减少为1，不为0，所以堆上的B空间没有被释放，且B持有的A也没有机会被析构，A的引用计数也完全没减少

	  //a后出作用域，同理A的引用计数减少为1，不为0，所以堆上A的空间也没有被释放
}

#endif

/*
	如此一来，A和B都互相指着对方吼，“放开我的引用！“，“你先放我的我就放你的！”，于是悲剧发生了。

	所以在使用基于引用计数的智能指针时，要特别小心循环引用带来的内存泄漏，
	循环引用不只是两方的情况，只要引用链成环都会出现问题。
	当然循环引用本身就说明设计上可能存在一些问题，如果特殊原因不得不使用循环引用，
	那可以让引用链上的一方持用普通指针（或弱智能指针weak_ptr）即可。

*/