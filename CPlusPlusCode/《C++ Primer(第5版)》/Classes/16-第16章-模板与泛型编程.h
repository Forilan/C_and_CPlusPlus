
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

// 16-第16章-模板与泛型编程

/*
	模板是C++中泛型编程的基础。一个模板就是一个创建类或函数的蓝图或者说公式。
*/

//=========================================================================
//
//							16.1 定义模板
//
//=========================================================================

// 16.1.1 函数模板 __________________________
/*
	我们可以定义一个通用的函数模板，而不是为每个类型都定义一个新函数。
	一个函数模板就是一个公式，可用来生成针对特定类型的函数版本。

	模板定义以关键字 template 开始，后跟一个模板参数列表，这是一个逗号分隔的一个或多个 模板参数 的列表，
	用小于号< 和 >大于号 包围起来。
*/  

template <typename T>
int compares(const T &v1, const T &v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}

// 在模板定义中，模板参数列表不能为空。

/*	【实例化函数模板】
	下面编译器 会生成两个实例函数， 
	一个是 int compares(const int &v1, const int &v2)
	一个是 int compares(const double &v1, const double &v2)
*/

void sumer(int &j)
{
	j = 4;
}

void study_template_compares()
{
	int j = 2;
	int i;

	sumer(j);

	i = compares(1,0);		// 实例出： int compares(const int &v1, const int &v2)

	j = compares(1.0,2.0);	// 实例出： int compares(const double &v1, const double &v2)

	cout << i << endl;
}


/*	【模板类型参数】
	类型参数前 必须使用关键字 class 或 typename
	在模板参数列表中，这两个关键字的含义相同，可以互换使用。
*/

template <typename T, class U>
T cale(const T &v1, const U &v2)
{
	T er;
	return er;
}


/*	【非类型模板参数】
	一个非类型参数 表示一个值 而非一个类型。
	我们通过一个特定的类型名 而非关键字 class 或 typename 来指定非类型参数。

	实际用法：可以获得数组的大小。
	可以获得 char 数组的大小。
*/

template <unsigned N, unsigned M>
int comparteChar(const char (&p1)[N], const char (&p2)[M])
{
	if (N > M)	return 1;
	if (M > N)	return -1;
	return 0;
}

void study_nontype_parameter_template_compares()
{
	int i = comparteChar("hi", "mo3");	// 实例出：	int comparteChar(const char (&p1)[3], const char (&p2)[4])

	int j = comparteChar("h", "");		// 实例出：	int comparteChar(const char (&p1)[2], const char (&p2)[1])

	int k = comparteChar("h12", "213");	// 实例出：	int comparteChar(const char (&p1)[4], const char (&p2)[4])
}


/*	【inline 和 constexpr 的函数模板】
	函数模板可以声明为 inline 或 constexpr 的.
	inline 要放在 模板参数列表之后，返回类型之前。
*/

#if 0
template <typename T> inline
int compares(const T &v1, const T &v2)
#endif

/*	【编写类型无关的代码】
	编写泛型代码的两个重要原则：
	1 - 模板中的函数参数 是 const 的引用
	2 - 函数体中的条件判断仅使用 < 比较运算 【这样传递来的参数类型，就可以不用支持 > 比较运算符，只要支持 < 运算符就可以】

	模板程序应该 尽量减少对实参类型的要求。
*/


/*	【模板编译】
	当我们使用（而不是定义）模板时，编译器才生成代码。
*/

/*	【大多数编译错误在实例化期间报告】
	第一个阶段是编译模板本身时。
	第二个阶段是编译器遇到模板使用时。
	第三个阶段是模板实例化时。
*/



// 16.1.2 类模板 __________________________
/*
	类模板 是用来生成类的蓝图的。 
*/ 

/*	【定义类模板】
	
*/

template <typename T> class Blob {
public:
	typedef T value_type;

	void push_back(const T&t) { data->push_back(t); }

private:
	std::shared_ptr<std::vector<T>> data;
};

/*	【实例化类模板】
	当时有一个类模板时，我们必须提供额外信息。
	我们现在知道这些 额外信息是 显示模板实参 列表。 比如 Blob<int> ia; 中的 int
*/

void study_class_template_init()
{
	Blob<int> ia;
	Blob<int> ia2 = {0, 1, 2, 3, 4,};

	Blob<string> names;
	Blob<double> prices;

	/*		这两个定义会实例化出两个不同的类。
		
		一个类模板的每个实例都会形成一个独立的类。
	*/  
}

// P584 页，看不下去了啊。