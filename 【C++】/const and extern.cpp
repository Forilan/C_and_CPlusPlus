

// const and extern


// __________________________1 用extern型【定义】或【声明】一个变量的区分 __________________________

/*
	注意变量的声明和定义是不一样的。
	用int gInt是定义了一个变量，不使用关键字定义存储类型的话，这个变量就是extern型的。
	但是这个 "用extern型定义一个变量和用extern关键字引用性声明一个变量是不一样的。"
	之前你在int gInt = 1;这里也是定义了一个变量，这个外部变量是extern型的，所以就是重复定义。

	一个变量是声明，必须同时满足两个条件，否则就是定义： 
	(1)声明必须使用extern关键字；(2)不能给变量赋初值

	头文件被预处理过程是直接将头文件的全部内容直接插入到#include所在的地方。	
*/


// 下面为声明，只要有一个条件不满足就是定义。
extern int gInt;	




// __________________________2 用 const 时，可以省略 static  __________________________
/*
	“非const变量默认为extern”——————《C++ Primer》
	
	原话是 函数外定义的非const变量默认为extern,意思就是 int gInt; 相当于 extern int gInt = 0;

	上面这里的变量说的是 全局非const变量。

	非const变量在定义时不需指定extern，而const变量则必须指定extern，这样变量才能在其他文件被访问。
*/


// c 与 c++ 在这方面的区别
/*
	c中，在函数外部定义的变量是具有外部链接的静态变量(即extern变量)，在定义具有外部链的静态变量的文件外的声明该变量时要使用关键字extern。
	在外链接的静态变量定义时加关键字static，可将其链接性转换为内部链接。

	在c++中，这一点与c不同，const限定符对外部链接的静态变量(即extern变量)有影响，加上const的extern变量的链接性将转换为内部链接。
	如果要声明const型的具有外部链接的静态变量，则需要显式的加上extern，比如 
*/
extern const int a;			// 这是声明


//mian.cpp
int gInt =1;
extern const int gconstInt = 5; 	//定义时同时指定extern

//file1.cpp
extern int gInt;
extern const int gconstInt;


/*
	VC2010编译通过，file1.cpp里gInt和 gconstInt 都可以访问
	若改写为下面这样：
*/


//mian.cpp
int gInt =1;
const int gconstInt = 5; 			//未指定extern

//file1.cpp
extern int gInt;
extern const int gconstInt;

// 则vc2010编译链接时出错：error LNK2001: 无法解析的外部符号 "int const gconstInt" (?gconstInt@@3HB)
