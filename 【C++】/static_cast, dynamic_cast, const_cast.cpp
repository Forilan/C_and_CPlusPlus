

// static_cast, dynamic_cast, const_cast
/*
首先回顾一下C++类型转换：
C++类型转换分为：隐式类型转换和显式类型转换
*/

// __________________________1 隐式类型转换 __________________________

/*
	又称为“标准转换”，包括以下几种情况：
*/

// 1) 算术转换(Arithmetic conversion) : 在混合类型的算术表达式中, 最宽的数据类型成为目标转换类型。	

int 	i_val = 3;
double 	d_val = 3.14159;

i_val + d_val;	// i_val 被提升为 double 类型


// 2)一种类型表达式赋值给另一种类型的对象：目标类型是被赋值对象的类型

int *pi = 0;	// 0被转化为 int* 类型
i_val = d_val;	// double->int

// 例外：void指针赋值给其他指定类型指针时，不存在标准转换，编译出错。

// 3)将一个表达式作为实参传递给函数调用，此时形参和实参类型不一致：目标转换类型为形参的类型
extern double sqrt(double);
cout << "The square root of 2 is "<<sqrt(2)<<endl;
// 2被提升为double类型2.0

// 4)从一个函数返回一个表达式，表达式类型与返回类型不一致：目标转换类型为函数的返回类型
double difference(int i_val,int i_ful)
{
	return i_val - i_ful;	// 返回值 被提升为 double 类型
}

// __________________________2 显示类型转换 __________________________
/*
	被称为“强制类型转换”（cast）
	C  风格：(type-id)
	C++风格：static_cast、dynamic_cast、reinterpret_cast、和const_cast.


关于强制类型转换的问题，很多书都讨论过，写的最详细的是C++ 之父的《C++ 的设计和演化》。
最好的解决方法就是不要使用C风格的强制类型转换，而是使用标准C++的类型转换符：static_cast, dynamic_cast。
标准C++中有四个类型转换符：static_cast、dynamic_cast、reinterpret_cast、和const_cast。下面对它们一一进行介绍。
*/

// __________________________ static_cast __________________________