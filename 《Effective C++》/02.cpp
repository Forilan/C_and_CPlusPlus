
#include "02.h"


#define ASPECT_RATIO 1.653
const double AspectRatio = 1.653;

/* 	原因 

01 	因为 define 未进入 记号表，调试时 是 看不到 ASPECT_RATIO 的。
02 	替换 ASPECT_RATIO 为 1.653 可能 导致 最后生成的代码量 比只 使用常量 增大 
	因为 盲目的 替换可能导致 目标码 出现多份1.653，
	若改用常量  AspectRatio  绝不会出现 此情况。
*/

/* 	注意事项	*/
// 01 常量指针
const char* const authorName = "Scott Meyers";

// 但是 String 通常 比 char* 更适合
using namespace std;
const string authorName("Scott Meyers");

// calss 专属常量
class GamePlayer
{
private:
	static const int NumTurns = 5;	// 常量声明式
	int scores[NumTurns];			// 使用该常量

};


const int GamePlayer::NumTurns;


/* 	使用内联函数 代替 宏函数	*/

#define CALL_WITH_MAX(a,b) 	f( (a) > (b) ? (a) : (b) )

template<typename T>
inline void callWithMax(const T& a,	const T& b)
{
	f( a > b ? a : b );
}
