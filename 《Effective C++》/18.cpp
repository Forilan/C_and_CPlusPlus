
// 条款18：让接口容易被正确使用，不易被误用  ______  Make interfaces easy to use correctly and hard to use incorrectly


// 假设你为一个用来表现日期的 class 设计构造函数：
class Date{
public:
	Date(int month,int day,int year);
	// ... 
};

// 用户可能往里面输入各种各样的错误来。
Date d(30,3,1995);
Date d(2,30,1995);

// 许多客户端错误 可以因导入新类型而获得预防。让我们导入简单的外覆类型 ( wrapper types )来区别天数，月份和年份。
struct Day
{
	explicit Day(int d):val(d){}
	int val;
};

struct Month
{
	explicit Month(int m):val(m){}
	int val;
};

struct Year
{
	explicit Year(int y):val(y){}
	int val;
};


class Date{
public:
	Date( const Month& m,const Day& d,const Year& y );
	// ... 
};

Date d(30,3,1995);							// wrong
Date d(Day(30),Month(3),Year(1995));		// wrong
Date d(Month(3),Day(30),Year(1995));		// right

// P101 剩下的看不懂了。

/* 	______________________   ______________________  */

/* 	______________________   ______________________  */


/* 	______________________   ______________________  */



/* ______________________ 总结	______________________  */
/*
 
*/
