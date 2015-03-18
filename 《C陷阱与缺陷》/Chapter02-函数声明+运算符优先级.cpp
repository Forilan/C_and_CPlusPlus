﻿
#include "Chapter02.h"
#include "stdafx.h"

// __________________________2.1 理解函数声明__________________________
void chapter02::declarationFunction( void )
{
	(* (void (*)() ) 0  )();			// 如何理解这句话


/*
	任何C变量的声明都由两部分组成：类型以及一组类似表达式的声明符（declarator）.
	声明符 从表面上看与表达式有些类似，对它求值应该返回一个 声明中给定类型的 结果。
*/

	//for example:
	float f;		// 对f求值，返回的是 float 类型。
	float ff();		// ff() 函数的返回值 是 float 类型。
	float * pf;		// pf 是一个指向 浮点数 的指针。

	// 然后我们把上面的声明结合起来。
	float *g();		// g是一个函数，返回的是 指向浮点数的指针。
	pf = g();

	float (*h)();	// h是一个函数指针，所指向的函数的返回值 是浮点类型。
	h = ff;

	// 类型转换符：
	// (float (*)()) 	// 转换成上面的 h.

	// 然后 h 是一个函数指针，如何调用这个函数呢。调用方法如下：
	(*h)();

	// 然后就可以理解下面这句话了吧。
	(* (void (*)() ) 0  )();


	// 补充：
	//(* 0)();		
	// 上式并不能生效，因为运算符 * 必须要一个指针来 做操作数。而且这个指针还应该是一个函数指针。

	// 然后用 typedef 来解决这个问题就 更加清晰了。
	typedef void (* funcptr)();
	(* (funcptr)0)();

	// 再看一个例子。
	void (* signal(int,void(*)(int)))(int);
	// 等价于下面这2行
	typedef void ( *HANDLER)(int);
	HANDLER signal(int,HANDLER);

}

// __________________________2.2 运算符的 优先级问题__________________________
void chapter02::operatorPriority( void )
{
	// 本节核心观点：
	/* 用添加括号的方法虽然可以完全避免这类问题，但是表达式中有了太多的括号反而不容易理解，
	因此，记住C语言中运算符的优先级是有益的。
	
	但是运算符优先级有15个之多，因此记住它们并不是一件容易的事。

	但是如果把这些运算符进行恰当分组，并且理解了各组运算符之间的相对优先级，那么其实并不难记。
	*/
	
	/* 记忆规则：
		优先级最高的其实并不是真正意义上的运算符，包括：数组下标，函数调用操作符，各结构成员选择操作符。

		其次为 单目运算符。类型转换也是单目运算符。

		比单目运算符低的就是双目运算符。在双目运算符中：
		【算术运算符】的优先级最高，【移位运算符】次之，【关系运算符】再次之，接着是【逻辑运算符】，然后是条件运算符【即三目运算符】，
		最后是 赋值运算符。
	*/


	/*
				【运算符】			|				【结合性】
			() [] -> .				|				自左向右
	! ~ ++ -- - (type) * & sizeof 	|				自右向左		// 【单目运算符】	这里面的 - 是负号的意思
			* /	%					|				自左向右		// 【双目运算符】
			+	-					|				自左向右
			<<	>>					|				自左向右		//			【移位运算符】
		<	<=	>	>=				|				自左向右		//			【关系运算符】	
		==		!=					|				自左向右
			&						|				自左向右		//			【按位运算符】
			^						|				自左向右
			|						|				自左向右
			&&						|				自左向右		//			【逻辑运算符】
			||						|				自左向右
			?:						|				自右向左
		assignments					|				自右向左		//			【赋值运算符： =  /=  *=  %=  -=  += <<=  >>=  &=  ^=  |= 】
			,						|				自左向右


									|				自左向右
									|				自左向右
									|				自左向右
									|				自左向右
									|				自左向右
									|				自左向右
	*/
}


// __________________________2.3 注意作为语句结束标志的分号__________________________
/*	
	仔细认真，不要漏掉分号，或者加了多余的 分号
*/


// __________________________2.4 switch 语句__________________________
void chapter02::switchSentence( void )
{
	int color = 0;

	switch(color){
	case 1: printf("red");
		break;
	case 2: printf("yellow");
		break;
	case 3: printf("blue");
		break;
	}

	/*
		switch 中的 break 被省略后，会继续往下执行下面的 case.
		这种特性即是它的 优势所在，也是它的一大弱点。 
		弱点：因为万一遗漏了一个break,造成一些难以理解的程序行为。
		优点：如果故意略去 一个 break 语句，则可以表达出一些采用其他方式 很难方便地加以 实现的程序控制结构。
	*/
}


// __________________________2.5 函数调用__________________________
/*
	C语言要求：在函数调用时即使 函数不带参数，也应该包括参数列表。
	f();		// 是一个函数调用语句。
	f;			// 却是一个什么也不做的语句。
*/