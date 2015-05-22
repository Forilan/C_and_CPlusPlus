
// 条款 45  弄清C++ 在幕后为你所写，所调用的函数  ______  

// 如果你这么写：
class Empty{};

// 和你这么写是一样的：
class Empty{
public:
	Empty();								// 缺省构造函数
	Empty(const Empty& rhs);				// 拷贝构造函数

	~Empty();								// 析构函数 --- 

	Empty& operator = (const Empty& rhs);	// 赋值运算符

	Empty* operator &();					// 取址运算符
	const Empty* operator&() const;
};


// 下面的代码 将使得 每个函数被生成：
const Empty e1;				// 缺省构造函数

Empty e2(e1);				// 拷贝构造函数

e2 = e1;					// 赋值运算符

Empty *pe2 = &e2;			// 取址运算符 (非 const)

const Empty *pe1 = &e1;		// 取址运算符 ( const )

// 其实这些函数 实际上 就如同下面所定义的那样：

inline Empty::Empty(){}

inline Empty::~Empty(){}

inline Empty* Empty::operator&(){ return this; }

inline const Empty* Empty::operator&() const { return this; }


/* 	______________________   ______________________  */


/* 	______________________   ______________________  */



/* 	______________________   ______________________  */




/* ______________________ 总结	______________________  */
/*
 
*/
