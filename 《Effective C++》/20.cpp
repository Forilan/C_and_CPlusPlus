
// 条款20：宁以 引用 pass-by-reference-to-const 替换 传值 pass-by-value  ______  Prefer pass-by-reference-to-const to pass-by-value.

/*
	缺省情况下 C++ 以 by value 方式（一个继承自C的方式）传递对象至（或来自）函数。除非你另外指定，否则函数参数都是以实际实参的复件（副本）为初值，
	而调用端所获得的亦是函数返回值的一个复件。这些复件（副本）系由对象的copy构造函数产出，这可能使得 pass-by-value 成为昂贵（费时的）操作。
*/




/* 	______________________  切割问题（slicing problem）  ______________________  */
	当传递 一个 子类 对象 给一个函数时，如果函数定义接收的参数为 基类 类型的，则会把 子类对象给变成基类了。

	但是 如果 用引用传值，则不会出现此问题。


/*
	如果窥视 C++ 编译器的底层，你会发现，references 往往以指针实现出来，因此 pass by reference 通常意味真正传递的是 指针。

	因此如果你有个对象属于内置类型（例如 int）,pass-by-value 往往比 pass-by-reference-to-const 的效率高些.
*/


/* 	______________________   ______________________  */



/* 	______________________   ______________________  */



/* ______________________ 总结	______________________  */
/*
 	1 - 尽量以 pass-by-reference-to-const 替换 pass-by-value. 前者通常比较高效，并可避免切割问题（ slicing problem ）。

	2 - 以上规则并不适用于内置类型，以及STL的迭代器 和 函数对象。对它们而言， pass-by-value 往往比较恰当。
	【当然如果你是要交换 两个参数 的值，还是可以用 引用传参 ，这样代码比较清晰,易读】
*/
