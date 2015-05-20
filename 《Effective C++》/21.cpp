
// 条款21：必须返回对象时，别妄想返回其 reference  ______  Don't try to return a reference when you must return an object.


/*
	一旦程序员 领悟了 pass-by-value 的效率牵连层面(条款 20)，就会开始追求 pass-by-reference-to-const  。
	这时会犯下一个致命错误：开始传递一些 refereneces 指向其实并不存在的对象。这可不是件好事。

*/ 

/* 	______________________  返回 local 对象  ______________________  */
函数内部，创建新对象的途径有二：在 stack 空间 或在 heap 空间创建之。
如果定义一个local变量，就是在 stack 空间创建对象。

事情的真相是，任何函数 如果返回一个 refereneces 指向某个 local 对象，都将一败涂地。( 如果函数返回指针指向一个 local 对象，也是一样的。 )


/* 	______________________  返回 heap 对象  ______________________  */
好吧，那让我们在 heap 内创建对象，然后返回  一个 refereneces 指向某个 heap 对象。那谁负责 delete 这个 heap 对象呢？

如何保证不会 内存泄露呢？

/* 	______________________  返回 static 对象 ，函数内的static对象称为【local static】对象  ______________________  */
// 好吧那我们改成下面这样写呢,我们使用 static 对象。
const Rational& fun()
{

	static  Rational result;
	... ... 

	return result;
}

就像所有用上 static 对象的设计一样，这一个也立刻造成我们对多线程安全性的疑虑。不过这还只是它显而易见的弱点。
在函数内部使用 static 还有很多深层次性的问题。

/* 	______________________   ______________________  */


/* 	______________________  讨论  ______________________  */
/*
	我们把上述讨论 总结为：当你必须在“ 返回一个reference 和 返回一个 object ”之间抉择时，你的工作就是挑出行为正确的那个。
*/


/* ______________________ 总结	______________________  */
/*
 	绝不要返回 pointer 或 reference 指向一个 local stack 对象，或返回 reference 指向一个 heap-allocated 对象，
 	或返回 pointer 或 reference 指向一个 local static  对象 而有可能同时需要多个这样的对象。
*/


/* 	______________________ 题外话：这几个对象的区别 stack，heap,static ______________________  */	
/*
	所谓static对象，其寿命从被构造出来直到程序结束为止，因此stack和heap-based对象都被排除。

	这种对象包括global对象、定义于namespace作用域内的对象，classes内、在函数内、以及在file作用域内被声明为static的对象。

	函数内的static对象称为【local static】对象（因为它们对函数而言是local），其他static对象成为non-local static对象，

	在程序结束时static对象会被自动销毁，也就是他们的析构函数会在main()结束时被调用.

    c++对“定义于不同的编译单元内的non-local static对象”的初始化次序并无明确定义。
*/

