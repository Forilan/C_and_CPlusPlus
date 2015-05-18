
// 条款02：尽量以 const,enum,inline 替换 #define  ______  Perfer consts,enums,and inlines to #defines

#include "02.h"

/* 	______________________ 使用 常量 代替 宏 ______________________  */
#define ASPECT_RATIO 1.653
const double AspectRatio = 1.653;

/* 	原因 

01 	因为 define 未进入 记号表，调试时 是 看不到 ASPECT_RATIO 的。
02 	替换 ASPECT_RATIO 为 1.653 可能 导致 最后生成的代码量 比只 使用常量 增大 
	因为 盲目的 替换可能导致 目标码 出现多份1.653，
	若改用常量  AspectRatio  绝不会出现 此情况。
*/

/* 	注意事项	*/
// ______________________  常量指针 ______________________
const char* const authorName = "Scott Meyers";

// 但是 String 通常 比 char* 更适合
// using namespace std;
const std::string authorName("Scott Meyers");		// 括号初始化方法

// ______________________ calss 专属常量 ______________________
// 【@位于头文件中】
class GamePlayer
{
private:
	static const int NumTurns = 5;	// 常量声明式
	int scores[NumTurns];			// 使用该常量

};

// 下面这个才是 定义式 【@位于实现文件中】
const int GamePlayer::NumTurns;
// 【放入实现文件中，而非头文件中,由于 class 常量已在声明时获得初值（例如先前声明 NumTurns 时为它设初值5），因此定义时不可以再设初值】


/*	如果你的编译器 不支持这种写法，那么可以按如下方法来写  ______________________ */
// 【@位于头文件中】
class GamePlayer
{
private:
	static const int NumTurns ;		// 常量声明式
	// int scores[NumTurns];		// 使用该常量-这里就不能这样使用了。
};

// 【@位于实现文件中】
const int GamePlayer::NumTurns = 5;


//  ______________________  the enum hack ______________________
// 【@位于头文件中】
class GamePlayer
{
private:
	enum { NumTurns = 5 };
	int scores[NumTurns];		//  这里就没有问题了。
};

/*
	但是当你在 class 编译期间 需要一个 class 常量值时，上面的定义方法就没有用了.
	可改用所谓的“the enum hack”补偿做法。
	其理论基础是：“一个属于枚举类型 的数值 可权充 ints 被使用”
使用 the enum hack 的理由： 	
	理由一： enum hack 的行为某方面说 比较像 #define而不像const，有时候这正是你想要的。例如取一个const的地址是合法的，
但取一个enum的地址就不合法，而取一个 #define 的地址通常也不合法。如果你不想让别人获得一个 pointer 或 reference 指向你的某个整数常量，
enum 可以帮助你实现这个约束。
	理由二：虽然有些编译器不会为“整数型const对象”设定另外的存储空间(除非你创建一个pointer或reference指向该对象)不够优秀的编译器确有这个可能，
而这可能是你不想要的。Enums 和 #define 一样绝不会导致非必要的内存分配。
	理由三：许多代码用了这个技术，所以看到它时，你必须认识它。“the enum hack” 是 模板元编程 的基础技术。
*/ 



/* 	______________________ 使用 template inline 函数 代替 宏函数	______________________  */
/*
	宏看起来像函数，但不会招致函数调用(function call)带来的额外开销。
*/
#define CALL_WITH_MAX(a,b) 	f( (a) > (b) ? (a) : (b) )
// 无论何时当你写出这种宏，你必须记住为宏中的所有实参加上小括号，否则某些人在表达式中调用这个宏时可能会遭遇麻烦。	


/*
	但是你不需要对这种无聊事情提供温床。你可以获得宏带来的效率以及一般函数的所有可预料性行为和类型安全性，
	只需要你写出 template inline 函数
*/ 
template<typename T>
inline void callWithMax(const T& a,	const T& b)
{
	f( a > b ? a : b );
}

/* ______________________ 总结	______________________  */
/*
	有了 const,enum,inline，我们对预处理(特别是#define)的需求降低了，但并非完全消除。

	#include 仍然是必需品，而 #ifdef/#ifndef 也继续扮演控制编译的重要角色。
	目前还不到预处理器全面引退的时候，但你应该明确地给予它更长更频繁的假期。

请记住：
	1，对于单纯常量，最好以 const 对象或 enums 替换 #defines
	2, 对于形似函数的宏，最好改用 inline 函数替换 #defines		 
*/
