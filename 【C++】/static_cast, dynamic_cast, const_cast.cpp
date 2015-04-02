

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

// C++提供了四个转换运算符：
static_cast 		<new_type> (expression)
dynamic_cast 		<new_type> (expression)
reinterpret_cast 	<new_type> (expression)
const_cast 			<new_type> (expression)




/*
	一. 函数描述：
		const_cast < type-id > ( expression )

	主要是用来去掉const属性，当然也可以加上const属性。主要是用前者，后者很少用。
*/

// 去掉const属性
const int constant = 21; 
int* modifier =  const_cast<int*>(&constant); 
/*
	常用，因为不能把一个const变量直接赋给一个非const变量，必须要转换。
*/


// 加上const属性
int a = 42;
int * j = &a;
const int* k = const_cast<const int*>(j);
/*
	一般很少用，因为可以把一个非const变量直接赋给一个const变量，
	比如：const int* k = j;
*/





// __________________________ const_cast __________________________
/*
	该运算符用来修改类型的const或volatile属性。除了const 或volatile修饰之外， type_id和expression的类型是一样的。

	•常量指针被转化成非常量指针，并且仍然指向原来的对象；
	•常量引用被转换成非常量引用，并且仍然指向原来的对象；
	•常量对象被转换成非常量对象。
*/

/*
	对于const变量，我们不能修改它的值，这是这个限定符最直接的表现。但是我们就是想违背它的限定希望修改其内容怎么办呢？

	下边的代码显然是达不到目的的：
*/
const int constant = 10;
int modifier = constant;
/*
	因为对modifier的修改并不会影响到constant，这暗示了一点:const_cast转换符也不该用在对象数据上，
	因为这样的转换得到的两个变量/对象并没有相关性。

	只有用指针或者引用，让变量指向同一个地址才是解决方案，可惜下边的代码在C++中也是编译不过的：
*/
const int constant = 21;
int* modifier = &constant 
// Error: invalid conversion from 'const int*' to 'int*'

/*
	把constant交给非const的引用也是不行的。
*/ 
const int constant = 21;
int& modifier = constant;
// Error: invalid initialization of reference of type 'int&' from expression of type 'const int'

/*
	于是const_cast就出来消灭const，以求引起程序世界的混乱。

	下边的代码就顺利编译功过了：
*/
const int constant = 21; 
const int* const_p = &constant; 
int* modifier = const_cast<int*>(const_p); 
*modifier = 7; 

// 当然我们可以用传统方式(C语言里的强制转换)代替：
/*
	准转换运算符是可以用传统转换方式实现的。实现原因就在于C++对于指针的转换是任意的，它不会检查类型，任何指针之间都可以进行互相转换，
	因此const_cast就可以直接使用显示转换(int*)来代替：
*/
const int constant = 21; 
int* modifier = (int*)(&constant); 



// 为何需要去除const限定 ____________________________________________________

/*
	从前面代码中已经看到，我们不能对constant进行修改，但是我们可以对modifier进行重新赋值。
	但是但是，程序世界真的混乱了吗？我们真的通过modifier修改了constatn的值了吗？
	修改const变量的数据真的是C++去const的目的吗？

	如果我们把结果打印出来：
*/

cout << "constant: "<< constant <<endl; 
cout << "const_p: "<< *const_p <<endl; 
cout << "modifier: "<< *modifier <<endl; 
/** 
constant: 21 
const_p: 7 
modifier: 7 
**/ 

// constant还是保留了它原来的值。可是它们的确指向了同一个地址呀：

cout << "constant: "<< &constant <<endl; 
cout << "const_p: "<< const_p <<endl; 
cout << "modifier: "<< modifier <<endl; 

/** 
constant: 0x7fff5fbff72c 
const_p: 0x7fff5fbff72c 
modifier: 0x7fff5fbff72c 
**/ 

/*
	这真是一件奇怪的事情，但是这是件好事：说明C++里是const，就是const，外界千变万变，我就不变。不然真的会乱套了，const也没有存在的意义了。

IBM的C++指南称呼“*modifier = 7;”为“未定义行为（Undefined Behavior）”。所谓未定义，是说这个语句在标准C++中没有明确的规定，由编译器来决定如何处理。

位运算的左移操作也可算一种未定义行为，因为我们不确定是逻辑左移，还是算数左移。

再比如下边的语句：v[i] = i++; 也是一种未定义行为，因为我们不知道是先做自增，还是先用来找数组中的位置。

对于未定义行为，我们所能做的所要做的就是避免出现这样的语句。对于const数据我们更要这样保证：绝对不对const数据进行重新赋值。

如果我们不想修改const变量的值，那我们又为什么要去const呢？

原因是，我们可能调用了一个参数不是const的函数，而我们要传进去的实际参数确实const的，但是我们知道这个函数是不会对参数做修改的。
于是我们就需要使用const_cast去除const限定，以便函数能够接受这个实际参数。
*/

#include <iostream>
using namespace std;

void Printer (int* val,string seperator = "\n")
{
	cout << val<< seperator;
}

int main(void) 
{	
	const int consatant = 20;
	//Printer(consatant);//Error: invalid conversion from 'int' to 'int*'
	Printer(const_cast<int *>(&consatant));
	
	return 0;
}

/*
	出现这种情况的原因，可能是我们所调用的方法是别人写的。还有一种我能想到的原因，是出现在const对象想调用自身的非const方法的时候，
	因为在类定义中，const也可以作为函数重载的一个标示符。有机会，我会专门回顾一下我所知道const的用法，C++的const真的有太多可以说的了。

	在IBM的C++指南中还提到了另一种可能需要去const的情况：
*/

#include <iostream>
using namespace std;

int main(void) {
	int variable = 21;
	const int* const_p = &variable;
	int* modifier = const_cast<int*>(const_p);
	
	*modifier = 7
	cout << "variable:" << variable << endl;
	
	return 0;
} 
/**
variable:7
**/	
/*
	我们定义了一个非const的变量，但用带const限定的指针去指向它，在某一处我们突然又想修改了，可是我们手上只有指针，
	这时候我们可以去const来修改了。上边的代码结果也证实我们修改成功了。

	不过我觉得这并不是一个好的设计，还是应该遵从这样的原则：使用const_cast去除const限定的目的绝对不是为了修改它的内容，只是出于无奈。
	（如果真像我说是种无奈，似乎const_cast就不太有用到的时候了，但的确我也很少用到它）
*/


// __________________________ dynamic_cast __________________________







//======================================================================================================
/*
	1.1  dynamic_cast

		dynamic_cast 支持运行时识别指针或引用所指向的对象。 

	1.2  const_cast

		const_cast ,顾名思义,将转换掉表达式的 const 性质。 

	1.3  static_cast

		编译器隐式执行的任何类型转换都可以由 static_cast 显式完成: 

	1.4  reinterpret_cast

		reinterpret_cast 通常为操作数的位模式提供较低层次的重新解释。 

	1.5  旧式强制类型转换 

		char *pc = (char*) ip; 

效果与使用 reinterpret_cast 符号相同,但这种强制转换的可视性比较 差,难以跟踪错误的转换。 

虽然标准 C++ 仍然支持旧式强制转换符号,但是我们 建议,只有在 C 语言或标准 C++ 之前的编译器上编写 代码时,才使用这种语法。 
	
*/	