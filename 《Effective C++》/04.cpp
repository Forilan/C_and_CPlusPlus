
// 条款04：确定对象初始化  ______  Make sure that objects are initialized before they're used.

/*
	现在，我们终于有了一些规则，描述“对象的初始化动作何时一定发生，何时不一定发生。”
	不幸的是这些规则很复杂，我认为对记忆力而言是太繁复了些。【这是在嘲讽C++么】
*/


如果你使用 C part of C++ 而且初始化可能招致运行期成本，那么就不保证发生初始化。
一旦进入 non-C parts of C++ ，规则有些变化。
这就很好地解释了为什么 array(来自C part of C++)不保证其内容被初始化，
而 vector(来自 STL part of C++)却有此保证。


/* 	______________________  内置类型 的初始化 ______________________  */
最佳处理办法就是：永远在使用对象之前先将它初始化。
对于无任何成员的内置类型，你必须手工完成此事。例如：

int x = 0;									// 对 int 进行手工初始化
const char* text = "A C-style string";		// 对指针进行手工初始化

double d;
std::cin >> d;								// 以读取 input stream 的方式完成初始化。


/* 	______________________ 非内置类型 的初始化 ______________________  */
至于内置类型以外的任何其他东西，初始化责任落在构造函数（constructors）身上。
规则很简单：确保每一个构造函数都将对象的每一个成员初始化。

这个规则很容易 奉行，重要的是别混淆了赋值 和 初始化。

先看下面这个了例子,一个用来表现通讯薄的 class：

class PhoneNumber{...};
class ABEntry
{
public:
	ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones);

private:
	std::string theName;
	std::string theAddress;
	std::list<PhoneNumber> thePhones;
	int numTimesConsulted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
{
	theName 			= name;			// 赋值，非初始化
	theAddress 			= address;		// 赋值，非初始化
	thePhones 			= phones;		// 赋值，非初始化
	numTimesConsulted	= 0;			// 不确定，因为int是 内置类型，应该是初始化。
}

/*
	这会导致 ABEntry 对象带有你期望的值，但不是最佳做法。C++规定，对象的成员变量的初始化动作发生在进入构造函数本体之前。

	在 ABEntry 构造函数内，theName,theAddress 和 thePhones 都不是被初始化，而是被赋值。初始化的发生时间更早，发生于这些成员的
	default构造函数被自动调用之时。
*/

/* 	______________________  member initialization list(成员初值列)  ______________________  */
// ABEntry 构造函数的一个较佳写法是，使用所谓的 member initialization list(成员初值列) 替换赋值动作：

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
   :theName(name),				// 现在，这些都是初始化
	theAddress(address),
	thePhones(phones),
	numTimesConsulted(0)
{
	// 现在，构造函数本体不必有任何动作
}

/*
	这个构造函数 和上一个的最终结果相同，但通常效率较高。

01-基于在构造赋值的那个版本 首先调用 default 构造函数为 theName,theAdress和thePhones 设初值，然后立即再对它们赋予新值。default 构造函数 的一切作为因此浪费了。
02-member initialization list(成员初值列) 的 做法 避免了这一问题，因为初值列中 针对各个成员变量而设的实参，被拿去作为各成员变量之构造函数的实参。
*/


/* 	______________________ 内置类型 使用 member initialization list 方式初始化  ______________________  */
/*
	有些情况下，即使面对的成员变量属于内置类型(那么其初始化与赋值的成本相同)，也一定得使用初值列。是的，如果成员变量是 const 或 references ，
	它们就一定需要初值，不能被赋值。为避免需要记住成员变量何时必须在成员初值列中初始化，何时不需要，最简单的做法就是：总是使用成员初值列。
*/


/* ______________________ 成员初始化次序	______________________  */
/*
	C++ 有着十分固定的“成员初始化次序”。
	base classes 更早于其 derived class(派生类；衍生类别),而class的成员变量 总是以其【声明】次序被初始化，而不是以它们在【成员初值列】中的次序。

	所以当两个成员变量的初始化带有次序性。例如初始化array时需要指定大小，因此代表大小的那个成员变量必须先有初值。
*/



/* ______________________  不同编译单元内定义之 non-local static 对象 的初始化次序	______________________  */	
所谓static对象，其寿命从被构造出来直到程序结束为止，因此 stack(栈) 和 heap-based(堆) 对象都被排除。
这种对象 包括 global 对象，定义于 namespace 作用域内的对象，在classes内、在函数内、以及在 file 作用域内被声明为 static 的对象。

函数内的 static 对象 被称为 local static 对象(因为它们对函数而言是 local),其他 static 对象称为 non-local static 对象。

程序结束时 static 对象会被自动销毁，也就是它们的析构函数会在 main() 结束时 被自动调用。

使用 单例模式 可以 解决 这种不同编译单元内定义 之 non-local static 对象 初始化次序 未定 的问题。


/* ______________________ 总结	______________________  */
/*
 	1，手工初始化内置 non-member 对象。
 	2，使用成员初值列对付对象的所有成分。
 	3，在“初始化次序不确定性”氛围下加强你的设计（单例模式）
*/


/* ______________________ 请记住	______________________  */
/*
 	1，为内置型对象进行手工初始化，因为C++不保证初始化它们。
 	2，构造函数最好使用成员初值列，而不要在构造函数本体内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在 class 中的声明次序相同。
 	3，为免除“跨编译单元之初始化次序”问题，请以 local static 对象替换 non-local static 对象。【单例模式 的 实现】