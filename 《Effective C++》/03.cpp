
// 条款03：尽可能使用 const  ______  Use const whenever possible



/* 	______________________ 修饰 指针 ______________________  */


/* 下面的语句，主要取决于 const 在*的左边 还是 在*的右边 */
char greeting[] = "Hello";
char* p = greeting;
const char* p = greeting;			// non-const pointer,const data
char* const p = greeting;			// const pointer,non-const data
const char* const p = greeting;		// const pointer,const data


/* 下面的这两种形式是一样的 */
void f1(const Widget* pw);
void f2(widget const *pw);


/* ______________________ 修饰 STL 迭代器系列	______________________  */
STL 迭代器系以指针为根据塑模出来，所以迭代器的作用就像个 T* 指针。
声明迭代器为 const 就像声明指针为 const 一样（即声明一个 T* const 指针），表示这个迭代器不得指向不同的东西，
但它所指的东西的值是可以改动的。
如果你希望迭代器所指的东西不可被改动（即希望 STL 模拟一个 const T* 指针），你需要的是 const_iterator:

std::vector<int> vec;

const std::vector<int>::iterator iter = vec.begin();		// iter 的作用像个 T* const
*iter = 10;			// 没问题，改变 iter 所指物
++iter;				// error 错误！ iter是 const

std::vector<int>::const_iterator cIter = vec.begin();		// cIter 的作用像个 const T* 
*cIter = 10;		// error 错误！ *cIter 是 const
++cIter;			// 没问题，改变 cIter 所指物


/* ______________________ 修饰 函数声明时的应用	______________________  */
在一个函数声明式内，const可以和函数返回值，各参数，函数自身（如果是成员函数）产生关联。

01 令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃安全性和高效性。

class Rational{};
const Rational operator* ( const Rational& lhs, const Rational& rhs );
// 这个例子看不懂---P41

02 const 成员函数

// 重载操作符，这里看不懂 在讲些什么。---P41

/* ______________________ 总结	______________________  */
/*
 
*/
