
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
//using namespace std;

// 03-第3章-字符串、向量和数组

//=========================================================================
//
//							3.1 命名空间的 using 声明
//
//=========================================================================

/*
	有了 using 声明就无须专门的前缀（形如命名空间::）也能使用所需的名字了。

	每个名字都需要独立的 using 声明

	头文件不应包含 using 声明。 -- 防止命名空间污染问题。

*/

//using namespace std;
using std::cin;


//=========================================================================
//
//							3.2 标准库类型 string
//
//=========================================================================

/*
	标准库类型 string 表示可变长 的字符序列， 使用 string 类型必须 首先包含 string头文件。
	作为标准库的一部分， string 定义在命名空间 std 中。
*/

#include <string>
using std::string;

// 3.2.1 定义和初始化 string 对象 __________________________
/*
	
*/


// 初始化 string 对象的方式
void string_study_init()
{
	string s1;				// 默认初始化，s1 是一个空串。
	string s2(s1);			// s2 是 s1 的副本。
	string s3 = s1;
	string s4("value");
	string s5 = "value";
	string s6(10, 'c');		// 把 s6 初始化为 由连续n个字符c组成的串
}

/*	【直接初始化和拷贝初始化】
	
	如果使用的 等号（=）初始化一个变量，实际上执行的是【拷贝初始化】，编译器把等会右侧的初始拷贝到新创建的对象中去。
	与之相反，如果不使用等会，则执行的是【直接初始化】。
*/ 


// 3.2.2 string 对象上的操作 __________________________
// 各种 操作符，P77
using namespace std;

// 读写 string 对象
/*
	在执行读取操作时，string 对象会自动忽略开头的空白（即空格符，换行符，制表符）
	并从第一个真正的字符开始读起,直到遇见下一处空白为止。
*/ 
void string_study_operational()
{
	string s;
	cin >> s;			
	cout << s << endl;
}

// 读取未知数量的 string 对象
void string_study_while()
{
	string word;
	while (cin >> word) {
		cout << word << endl;
	}
}

// 使用 getline 读取一整行
// p78


//=========================================================================
//
//							3.3 标准库类型 vector
//
//=========================================================================

/*
	标准库类型 vector 表示对象的集合，其中所有对象的类型都相同。集合中每个对象都有一个与之对应的索引，索引用于访问对象。
	因为 vector 容纳着其他对象，所以它也常称作容器。
*/
// 所需的头文件
#include <vector>
using std::vector;

/*
	C++ 语言既有 类模板，也有函数模板。 其中 vector 是一个【类模板】。
	模板本身不是类或函数，相反可以将 模板 看作为编译器生成类或函数编写的一份说明。
	编译器 根据模板创建类或函数的过程 称为 实例化。

	当使用模板时，需要指出编译器应把类或函数实例化成何种类型。
	以 vector 为例，提供的额外信息是 vector 内所存放对象的类型。
*/




// 3.3.1 定义和初始化 vector 对象 __________________________
/*
	vector 模板控制着 定义和初始化向量的方法。
*/

void vector_study_init()
{
	int n = 10, val = 20;

	vector<int> v1;
	vector<int> v2(v1);
	vector<int> v3 = v1;
	vector<int> v4 (n, val);		// v4 包含了n个重复的元素，每个元素的值都是 val
	vector<int> v5 (n);				// v5 包含了n个重复地执行了值初始化的对象
	// vector<int> v6 {1,2,3,4};		// VS2012 还不支持
	// vector<int> v6 = {1,2,3,4};		// VS2012 还不支持


	int a[9] = {1,2,3,4,5,6,7,8,9};
	vector<int> v(a, a+9);
}

/*	【列表初始化vector对象】
	P88 以后等编译器支持了 再学习。
*/ 

// 3.3.2 向 vector 对象中添加元素 __________________________
/*
	
*/

void vector_study_push()
{
	vector<int> v2;
	for (int i = 0; i < 100; ++i) {
		v2.push_back(i);
	}
}

/*
	如果 循环体内部包含 有向 vector 对象添加元素的语句，则不能使用范围 for 循环。 for (auto &i : v){}
	【因为改变vector大小后，for循环会越界】
	范围for语句体内不应改变其所遍历序列的大小
*/

// 3.3.3 其他 vector 操作 __________________________
/*
	
*/

// 表3.5： vector 支持的操作
void vector_study_other_operational()
{
	vector<int> v,v1,v2;
	bool isEmpty = v.empty();			// 如果 v 中含有任何元素，返回真，
	v.size();
	v.push_back(1);		// 向v的尾端 添加一个值为 t 的元素
	v[0];
	v1 = v2;
	bool isSame = (v1 == v2);			// v1 和 v2 相等【需要元素数量相等，且对应位置的元素值都相同】
	// <, <=, >, >=		// 顾名思义，以字典顺序进行比较
}

void vector_study_other_operational1()
{
	// 访问 vector 对象中元素的方法和访问 string 对象中字符的方法差不多，也是通过元素在 vector 对象中的位置。
	int a[9] = {1,2,3,4,5,6,7,8,9};
	vector<int> v(a, a+9);

	for (auto &i : v)	// 对于v中的每个元素（注意：i 是一个引用）
	{
		i *= i;
	}

	for (auto &i : v)
	{
		cout << i << " ";
	}

	cout << endl;
}

/*
	vector 对象 的小标运算符 可用于访问已存在的元素，而不能用于添加元素。

	确保下标合法的一种有效手段就是尽可能的使用【范围for语句】 for (auto &i : v)
	但是在 使用 【范围for语句】 的时候，不能够 进行修改容器大小的操作。
*/ 

void vector_study_test()
{
	// 练习 3.19
	vector<int> s1(10, 42);
	vector<int> s2;
	for (int i = 0; i < 10; ++i) {
		s2.push_back(42);
	}
	vector<int> s3(10);
	for (auto &i : s3) {
		i = 42;
	}

	// 练习 3.20
	vector<int> v2;
	for (int i = 0; i < 11; ++i) {
		v2.push_back(i);
	}

	for (auto s = v2.begin(),e = v2.end() - 1; s <= e; ++s, --e) {
		cout << *s + *e << endl;
	}
}


//=========================================================================
//
//							3.4 迭代器介绍
//
//=========================================================================

/*
	我们已经知道可以通过下标运算符来访问 string 对象的字符 或 vector 对象的元素，还有另外一种更通用的机制可以实现同样的目的。
	这就是 迭代器（iterator）
*/ 


// 3.4.1 使用迭代器 __________________________
/*
	和指针不一样的是，获取迭代器不是使用取地址符，拥有迭代器的类型同时拥有返回迭代器的成员。
	比如这些类型都拥有名为 begin() 和 end() 的成员。

	【end】成员负责返回 指向容器“尾元素的下一个位置”的迭代器，也就是说，该迭代器指示的是容器的一个本不存在的“最后”元素。
*/

void iterator_study_use()
{
	int a[9] = {1,2,3,4,5,6,7,8,9};
	vector<int> v(a, a+9);

	auto b = v.begin(), e = v.end();
	// 如果容器为空，则 begin 和 end 返回的是同一个迭代器，都是尾后迭代器。
}

// 迭代器运算符
/*
	
*/

// 表3.6 标准容器迭代器
#if 0
	*iter		// 返回迭代器 iter 所指元素的引用
	iter->mem	// 解引用iter并获取该元素的名为 mem 的成员，等价于(*iter).mem
	++iter
	--iter
	iter1 == iter2
	iter1 != iter2
#endif


/*	【将迭代器从一个元素移动到另外一个元素】
	迭代器使用 递增(++)运算符 来从一个元素移动到下一个元素。

	因为end返回的迭代器并不实际指示某个元素，所以不能对其进行递增或解引用的操作。
*/ 

void iterator_study_use1()
{
	string s("some string");
	// 依次处理 s 的字符直至我们处理完全部字符 或者 遇到空白
	for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it) {
		*it = toupper(*it);
	}

	cout << s << endl;		// SOME string
}

/*	【迭代器类型】
	拥有迭代器的标准库类型 使用 iterator 和 const_iterator 来表示迭代器的类型：
*/ 

void iterator_study_type()
{
	vector<int>::iterator it;			// it 能 读写 vector<int> 的元素
	string::iterator it2;				// it2 能 读写 string 对象中的元素

	vector<int>::const_iterator it3;	// it3 只能读元素，不能写元素
	string::const_iterator it4;			// it4 只能读元素，不能写元素
}

/*	【begin 和 end 运算符】
	begin 和 end 返回的具体类型 由 对象是否是常量决定，
	如果对象是常量，begin 和 end 返回 const_iterator;
	如果对象不是常量，begin 和 end 返回 iterator
*/ 

/*	【cbegin 和 cend 运算符】
	cbegin 和 cend 返回的具体类型 不由 对象是否是常量决定，
	不管对象是不是常量，cbegin 和 cend 都返回 const_iterator;
*/ 
void iterator_study_cbegin()
{
	int a[9] = {1,2,3,4,5,6,7,8,9};
	vector<int> v(a, a+9);

	vector<int>::const_iterator it3 = v.cbegin();
	vector<int>::const_iterator it4 = v.cend();
}

/*	【结合解引用 和 成员访问操作】
	解引用迭代器 可获得迭代器所指的对象，如果该对象的类型恰好是类，就有可能希望进一步访问它的成员。
*/ 

void iterator_study_r()
{
	// 点解 操作符
	string s("some string");
	vector<string> er;
	er.push_back(s);

	vector<string>::iterator it = er.begin();
	(*it).empty();

	// 箭头运算符（->）
	it->empty();	// 等价于 (*it).empty();
}

void iterator_study_arrow()
{
	string s("some string");
	vector<string> text(3, s);
	text.push_back(s);

	// 依次输出 text 的每一行直至遇到第一个空白行 为止
	for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it) {
		cout << *it << endl;
	}
}

/*	【某些对 vector 对象的操作会使迭代器失效】
	1 - 不能在 范围for循环中向 vector 对象添加元素。  for (auto &i : v){}
	2 - 任何一种可能改变 vector 对象容器的操作【比如push_back】都会是该 vector 对象的迭代器失效。
*/ 


void iterator_study_text1()
{
	string s("some string");
	vector<string> text(3, s);
	text.push_back(s);

	// 练习 3.22 【这里与 iterator_study_arrow() 不一样的地方是，因为要改写值，所以不能用 auto it = text.cbegin(); 了，否则修改不了值了。】
	for (auto it = text.begin(); it != text.cend() && !it->empty(); ++it) {
		for (auto i = it->begin(); i != it->end() && !isspace(*i); ++i) {
			*i = toupper(*i);
		}
		cout << *it << endl;
	}

	// 练习 3.23
	vector<int> v(10,0);
	int j = 1;
	for (auto &i : v) {
		i = j++;
	}

	for (auto it = v.begin(); it != v.end(); ++it) {
		*it *= 2;
		cout << *it << endl;
	}
}


// 3.4.2 迭代器运算 __________________________
/*
	string 和 vector 的迭代器提供了更多额外的运算符，一方面可以使得迭代器的每次移动跨过多个元素，另外也支持迭代器进行关系运算。
	所有这些运算被称作迭代器运算。
*/

// 表3.7 string 和 vector 迭代器支持的运算
#if 0
	iter + n
	iter - n
	iter += n
	iter -= n
	iter1 - iter2	// 两个迭代器相减的结果是它们之间的距离
	>   >=  <  <=	// 迭代器的关系运算符
#endif

/*	【迭代器的算术运算】
	可以令迭代器和一个整数值相加(或相减)，其返回值是向前(或向后)移动了若干个位置的迭代器。
	执行这样的操作，结果迭代器或者指示原 vector对象内的一个元素，或者 指示原 vector对象 尾元素的下一个位置。
*/ 

void iterator_study_add()
{
	vector<int> v(10,0);
	int j = 1;
	for (auto &i : v) {
		i = j++;
	}

	auto it = v.begin();

	cout << *it << endl;

	int n = 10;		// n 值的范围只能在【0～10】： 10就是指向end
	it += n;		// 如果超过范围了，这里就会报错。【over offset range】
	if (it != v.end()) {
		cout << *it << endl;
	} else {
		cout << "NULL" << endl;
	}
}


void iterator_study_text2()
{
	// 练习 3.26 搞不懂 -P101
}


//=========================================================================
//
//							3.5 数 组
//
//=========================================================================

/*
	数组是一种类似于标准库类型 vector 的数据结构，但是在性能和灵活性的权衡上又与 vector 有所不同。

	【tip】如果不清楚 元素的确切个数，请使用 vector.
*/


// 3.5.1 定义和初始化内置数组 __________________________
/*
	【warning】和内置类型的变量一样，如果在函数内部定义了某种内置类型的数组，
	那么默认初始化会令数组含有 未定义的值。

	定义数组的时候必须指定数组的类型，不允许使用 auto 关键字 由初始值的列表推断类型。
*/

void array_study_init()
{
	// 显示初始化
	const int nums = 3;
	int ial[nums] = {0, 1, 2};
	int a2[] = {0, 1, 2};
	int a3[5] = {0, 1, 2};				// {0, 1, 2, 0, 0};
	string a4[3] = {"hi", "bye"};		//  {"hi", "bye", ""};
}

/*	【字符数组的特殊性】

	字符数组有一种额外的初始化形式，我们可以用字符串字面值对此类数组初始化。
	当使用这种方式时，一定要注意字符串字面值的结尾处还有一个空字符，这个空字符也会像字符串的其他字符一样被拷贝到字符数组中去。
	
*/ 

// P102 - 字符数组的特殊性
void array_study_char_init()
{
	char a1[] = {'c', '+', '+'};			// 列表初始化，没有空字符
	char a2[] = {'c', '+', '+', '\0'};		// 列表初始化，含有显式空字符
	char a3[] = "C++";						// 通过 字符串字面值 初始化。
	// char a4[3] = "C++";					// 错误：没有足够的空间可以存放字符。
}

// P102 - 不允许拷贝和赋值
void array_study_char_init1()
{
	int a[] = {0, 1, 2};
	//int a2[] = a;		// error: 不允许使用一个数组 初始化另一个数组
	int a3[3];
	// a3 = a;			// error: 不允许使用一个数组 直接赋值给另一个数组
}

int txt_size() { return 1;}

// 理解复杂的数组声明
/*
	要想理解数组声明的含义，最好的办法是从数组的名字开始按照由内向外的顺序阅读。
*/
void array_study_declare()
{
	int arr[10];
	int *ptrs[10];				// ptrs 是含有 10个整型指针 的数组
	//int &refs[10];			// error: 不存在引用的数组
	int (*parray)[10] = &arr;	// parray 指向一个含有 10个整数的数组
	int (&arrRef)[10] = arr;	// arrRef 引用一个含有 10个整数的数组

	// 对修饰符 的数量没有限制
	int *(&arry)[10] = ptrs;	// arry 是数组的引用，该数组含有10个指针。

	// 练习 3.27
	//int ia[txt_size()];			// 常量表达式 中 不允许 函数调用
}


// 3.5.2 访问数组元素 __________________________
/*
	在使用数组下标的时候，通常将其定义为 size_t 类型。
	size_t 是一种机器相关的无符号类型，它被设计的足够大 以便能表示内存中任意对象的大小。
*/

/*
	因为 维度 是数组类型的一部分，所以系统知道数组 scores 中有多少个元素，
	使用范围 for语句可以 减轻人为控制遍历过程的负担。
*/
void array_study_visit()
{
	unsigned scores[11] = { };
	for (auto i : scores) {
		cout << i << " ";
	}
	cout << endl;
}

// 3.5.3 指针和数组 __________________________
/*
	数组有一个特性：在很多用到数组名字的地方，编译器都会自动地将其替换为一个指向数组首元素的指针。
*/

void pointer_array_study()
{
	string nums[] = {"one", "two", "three"};
	string *p = &nums[0];

	string *p2 = nums;		// 等价于 p2 = &nums[0];

	// 在大多数表达式中，使用数组类型的对象其实是使用一个指向该数组首元素的指针。
	int ia[] = {0,1,2,3,4,5,6,7,8,9};
	auto ia2(ia);			// 等价于
	int * ia3 = ia;
}

/*	【指针也是迭代器】
	迭代器支持的运算，指针也支持。
*/ 

void pointer_array_study1()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	int *p = arr;		// 指向第1个元素
	++p;				// 指向 arr[1]

	int *e = &arr[10];	// 指向 arr 尾元素的下一位置的指针
	for (int *b = arr; b != e; ++b) {
		cout << *b << endl;		// 输出 arr 的元素
	}
}


/*	【标准库函数 begin 和 end】
	
*/ 

void array_begin_end_study()
{
	int ia[]	= {0,1,2,3,4,5,6,7,8,9};
	int *beg	= begin(ia);
	int *last	= end(ia);
}

/*	【指针运算】
	如果两个指针分别指向不相关的对象，则不能比较它们
*/ 

/*	【解引用和指针运算的交互】
	指针加上一个整数所得的结果还是一个指针。假设结果指针指向了一个元素，则允许解引用该结果指针。
*/ 

/*	【下标和指针】
	
*/ 

void array_index_pointer_study()
{
	int ia[] = {0, 2, 4, 6, 8};		// 含有5个整数的数组

	int i = ia[2];

	int *p = ia;			// p 指向 ia 的首元素
	i = *(p + 2);			// p 指向 ia[2]

	int *q = &ia[2];		// q 指向索引为2的元素
	int j = q[1];			// q[1] 等价于 *(q+1), 就是 ia[3] 那个元素。
	int k = q[-2];			// q[-2]是 ia[0] 表示的那个元素。

	// 【warning】 内置的下标运算符 所用的索引值不是无符号类型，这一点与 vector 和 string 不一样。
}

// 3.5.4 C风格字符串 __________________________
/*
	P109
*/

/*	【C标准库 String 函数】
	
*/ 

// 表3.8 C风格字符串的函数
#if 0
	strlen(p)			// 返回 p 的长度，空字符不计算在内
	strcmp(p1, p2)		// 比较 p1 和 p2 的相等性。
	strcat(p1, p2)		// 将p2 附加到 p1 之后，返回p1
	strcpy(p1, p2)		// 将p2 拷贝给 p1,返回 p1
#endif

// P109
void string_c_style_function()
{
	char ca[] = {'c', '+', '+'};		// 不以空字符结束
	cout << strlen(ca) << endl;			// 严重错误：ca 没有以空字符结束。
	// 上面的程序将 产生未定义的结果。strlen 函数将有可能沿着 ca 在内存中的位置不断向前寻找，直到遇到空字符才停下来。
}


// 3.5.5 与旧代码的接口 __________________________
/*
*/

//=========================================================================
//
//							3.6  多维 数组
//
//=========================================================================











