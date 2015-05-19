
// 条款05：了解C++默默编写并调用哪些函数  ______  Know what functions C++ silently writes and calls

什么时候 empty class  空类 不再是个 empty class 呢？当C++处理过它之后。
当你自己没有进行声明时，编译器就会为它声明（编译器版本的）一个 copy构造函数，一个 copy assignment操作符 和 一个析构函数。

此外，如果你没有声明任何构造函数，编译器也会为你声明一个 default 构造函数。所有这些函数都是 public 且 inline .

//因此如果你写下：
class Empty{};

// 这就好像你写下这样的代码：
class Empty{
public:
	Empty(){ ... };								// default 构造函数
	Empty(const Empty& rhs){ ... };				// copy 构造函数
	~Empty(){ ... };							// 析构函数

	Empty& operator = (const Empty& rhs){};		// copy assignment 操作符
};


// 上面这些 函数被调用时的情形：
Empty e1;			// default 构造函数
					// 析构函数
Empty e2(e1);		// copy 构造函数
e2 = e1;			// copy assignment 操作符

P57
/* 	______________________   ______________________  */

/* 	______________________   ______________________  */


/* 	______________________   ______________________  */



/* ______________________ 总结	______________________  */
/*
 
*/
