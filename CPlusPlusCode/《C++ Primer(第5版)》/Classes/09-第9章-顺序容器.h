
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <array>
using std::array;

// 09-第9章-顺序容器

/*
	本章是第3章内容的扩展

	顺序容器 为程序员 提供了 控制元素存储和访问顺序的能力。 
	这种顺序不依赖于 元素的值, 而是与元素加入容器时的位置相对应。

	与之相对的，我们将在11章介绍的 有序 和 无序关联容器，则根据 关键字的值 来存储元素。
*/


//=========================================================================
//
//							9.1 顺序容器概述
//
//=========================================================================


// 表 9.1 顺序容器类型 __________________________
/*
	vector
	deque
	list
	forward_list
	array
	string
*/

/*	【确定使用哪种顺序容器】
	通常，使用 vector 是最好的选择，除非你有很好的理由选择其他容器。

	1- 如果程序要求 在容器的中间插入或删除元素，应使用 list 或 forward_list
	2- 如果程序需要在头尾位置插入或删除元素，但不会在中间位置进行插入或删除操作，则使用 deque
*/ 


//=========================================================================
//
//							9.2 容器库概览
//
//=========================================================================

/*	容器类型上的 操作 形成了一种层次
	某些操作是所有容器类型都提供的
	另外一些操作仅针对顺序容器，关联容器，或 无序容器。
	还有一些操作只适用于一小部分容器。
*/


// 表 9.2 容器操作 __________________________
#if 0
	// 类型别名
	iterator					// 此容器的迭代类型
    const_iterator
	size_type					// 无符号整数型，足够保存此种容器类型最大可能容器的大小

	difference_type				// 带符号整数型，足够保存两个迭代器之间的距离
	value_type					// 元素类型
	reference					// 元素的左值类型
	const_reference

	// 构造函数
	C c;
	C c1(c2);
	C c(b, e);
	C c{a, b, c...};

	// 赋值与swap
	c1 = c2						// 将 c1 中的元素 替换为 c2 中的元素
	c1 = {a, b, c ...}			// 将 c1 中的元素 替换为 列表中元素（不适用于 array）
	a.swap(b)					// 交换 a 和 b 的元素
	swap(a, b)					// 与 a.swap(b) 等价

	// 大小
	c.size()					// c 中元素的数目（不支持 forward_list ）
	c.max_size()				// c 可保存的最大元素数目
	c.empty()

	// 添加/删除元素（不适用于 array）
	// 注：在不同容器中，这些操作的接口都不同
	c.insert(args)
	c.emplace(inits)
	c.erase(args)				// 删除 args 指定的元素
	c.clear()					// 删除c中的所有元素，返回 void

	// 关系运算符
	==, !=
	<, <=, >, >=				// 关系运算符（无序关联容器不支持）

	// 获取迭代器
	c.begin(), c.end()
	c.cbegin(), c.end()

	// 反向容器的额外成员【不支持 forward_list 容器】
	reverse_iterator			// 按逆序寻址元素的迭代器
	const_reverse_iterator
	c.rbegin(), c.rend()		// 返回指向 c 的尾元素 和 首元素之前位置的迭代器
	c.crbegin(), c.crend()
#endif


// 9.2.1 迭代器 __________________________

/*	【迭代器范围】
	迭代器范围的概念是标准库的基础。

	一个迭代器范围 由一对迭代器表示，两个迭代器分别指向同一个容器中的元素或者是尾元素之后的位置。

	这种元素范围被称为 左闭合区间，其数学描述为：
	[begin, end)
*/



/*	【使用左闭合范围蕴含的编程假定】
	1- 如果 begin 与 end 相等，则范围为空
	2- 如果 begin 与 end 不相等，则范围至少包含一个元素，且 begin 指向该范围中的第一个元素
	3- 我们可以对 begin 递增若干次，使得 begin == end
*/ 

// 这些性质意味着 我们可以像下面的代码一样用一个循环来处理一个元素范围，而这是安全的。
void sequential_container_study() 
{
	vector<int> er;
	auto begin = er.begin(), end = er.end();
	
	while(begin != end) {
		*begin = 1;
		++begin;
	}
}

// 9.2.2 容器类型成员 __________________________

/*
	类型别名，通过类型别名，我们可以在不了解容器中元素类型的情况下使用它。
	如果需要元素类型，可以使用容器的 value_type.
	如果需要元素类型的一个引用，可以使用 reference 或 const_reference.
	这些元素相关的类型别名在 泛型编程中 非常有用。

	
*/ 

//	为了使用这些类型，我们必须显示使用其类名：
#if 0
 list<string>::iterator iter;
 vector<int>::difference_type count;
#endif

// 9.2.3 begin 和 end 成员 __________________________

void begin_end_study()
{
	list<string> a;
	auto it1 = a.begin();		// list<string>::iterator
	auto it2 = a.rbegin();		// list<string>::reverse_iterator			//反向
	auto it3 = a.cbegin();		// list<string>::const_iterator
	auto it4 = a.crbegin();		// list<string>::const_reverse_iterator
}


// 9.2.4 容器定义和初始化 __________________________

/*
	当将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同。
*/ 

void vector_study_init()
{
	vector<int> v1;
	vector<int> v2(v1);
	

#if 0	//error
	vector<float> v3(v1);
	list<int> v4(v1);
#endif

	list<int>v5(v1.begin(), v1.end());

#if 0	// VS2012 不支持-[列表初始化]
	vector<int> v6 = {1, 2, 3};
#endif

	vector<int> v7(10, -1);		// 10个 int 元素， 都初始化为 -1
	vector<int> v7(10);			// 10个 int 元素， 都初始化为 0
}

/*	【标准库 array 具有固定大小】
	当定义一个 array 时，除了指定元素类型，还要指定容器大小。
*/
void array_study_init()
{
	array<int, 10> ial;
	array<string, 42> sal;

#if 0	// VS2012 不支持-[]
	int digs[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	array<int, 10> ials = digs;
#endif
	
}


// 9.2.5 赋值和 swap __________________________

/*
	赋值相关运算会导致 指向左边容器内部的迭代器、引用和指针失效。
	而 swap 操作将容器内容交换不会导致 指向容器内部的迭代器、引用和指针失效。（容器为 array 和 string 的情况除外）
*/ 

/*	【使用 assign(仅顺序容器)】
	赋值运算符 要求 左边 和 右边的 运算对象 具有相同的类型。
	它将右边运算对象中所有元素拷贝到 左边运算对象中。

	顺序容器（array 除外）定义了一个名为 assign 的成员，允许我们从一个不同但相容的类型赋值，或者从容器的一个子序列赋值。
*/

void assgin_study_use()
{
	list<string> names;
	vector<const char*> oldstyle;
	// names = oldstyle;		// 错误：容器类型不匹配
	names.assign(oldstyle.cbegin(), oldstyle.cend());		// 

	// assign 的第二个版本 接受一个整型值和一个元素值。
	list<string> slist1(1);		// 1个元素，为空 string
	slist1.assign(10, "Hiya");	// 10个元素，每个都是 “Hiyda!”
}

/*	【使用 swap】
	除 array 外， swap 不对任何元素 进行拷贝，删除，或插入操作，因此可以保证在常数时间【O(1)】内完成。
*/

// 9.2.6 容器大小操作 __________________________
/*
	成员函数 size 返回容器中元素的数目;
	empty 当size为0时，返回布尔值true;
	max_size 返回一个或等于 该类型容器 所能容纳的最大元素数的值。

	// forward_list 支持 max_size 和 empty ,但不支持 size 
*/ 


// 9.2.7 关系运算符 __________________________
/*
	
*/ 


//=========================================================================
//
//							9.3 顺序容器操作
//
//=========================================================================
/*
	上一节 介绍了所有容器都支持的操作。
	本章剩余部分将介绍顺序容器所特有的操作。
*/ 


// 9.3.1 向顺序容器添加元素 __________________________
/*
	
*/ 

// 表 9.5 : 向顺序容器添加元素的操作
// P305























//=========================================================================
//
//							9.6 容器适配器
//
//=========================================================================
/*
	除了顺序容器外，标准库还定义了 三个顺序容器适配器：stack queue 和 priority_queue 

	适配器 是标准库中一个通用概念。

	一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。
*/

/*	【栈适配器】

*/


/*	【队列适配器】

*/
