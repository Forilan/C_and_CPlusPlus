

// CCAssert




// __________________________1 Cocos2dx 技巧断言CCAssert __________________________
/*

*/


/*

*/


// __________________________ 如何使用 宏 CCAssert(cond, msg) __________________________
switch (getStageBack())
{
case 0:
	if ( getObjInsecta() == EI_E_INSECTA_ID_Dragonfly ) nextScene = true;
	break;
case 1:
	if ( getObjInsecta() == EI_E_INSECTA_ID_Cockroach ) nextScene = true;
	break;
case 2:
	if ( getObjInsecta() == EI_E_INSECTA_ID_DungBettle ) nextScene = true;
	break;
default:
	CCAssert(false,"nextInsecta() switch run error");		// 断言，走到这里就 出错了。		
	break;
}



// __________________________ 宏 CCAssert(cond, msg)  定义 __________________________
// 
#ifndef CCAssert
#if COCOS2D_DEBUG > 0
extern bool CC_DLL cc_assert_script_compatible(const char *msg);

#define CCAssert(cond, msg) do {                              \
      if (!(cond)) {                                          \
        if (!cc_assert_script_compatible(msg) && strlen(msg)) \				
          cocos2d::CCLog("Assert failed: %s", msg);           \
        CC_ASSERT(cond);                                      \
      } \
    } while (0)

#else
#define CCAssert(cond, msg) ((void)(cond))
#endif
#endif  // CCAssert


// ~~~~~~~~~~~~~~~~~~~~~~~~~ 说明 ~~~~~~~~~~~~~~~~~~~~~~~~~
//  ①  \ 是续行符(反斜杠). 
//  ②   strlen(msg)，计算 msg 的长度，为0就不执行下面的语句
//	③   cc_assert_script_compatible(msg)  应该是显示到窗口的意思？



// __________________________ 宏 CC_ASSERT(cond)  定义 __________________________
#if CC_DISABLE_ASSERT > 0
#define CC_ASSERT(cond)
#else
#define CC_ASSERT(cond)    assert(cond)
#endif
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam




// __________________________ 宏 assert(_Expression)  定义 __________________________
#define assert(_Expression) (void)( (!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), __LINE__), 0) )

// ~~~~~~~~~~~~~~~~~~~~~~~~~ 说明 ~~~~~~~~~~~~~~~~~~~~~~~~~
/*
	下面的代码意思是定义如下函数（此函数用于打印出出错信息）：【看不懂啥意思】
*/    
(_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), __LINE__), 0)



// __________________________  C标准预定义宏  如何使用 __________________________
#include   <iostream> 
using   namespace   std; 

void   main(void) 
{ 
	cout   <<   __FILE__   		<<   endl;   			//   当前文件路径 
	cout   <<   __LINE__   		<<   endl;   			//   当前文件编译行数 
	cout   <<   __DATE__   		<<   endl;   			//   编译日期 
	cout   <<   __TIME__   		<<   endl;   			//   编译时间 
	cout   <<   __FUNCTION__   	<<   endl; 				//   函数名称
} 

/*
	我们可以在debug的时候输入更多有意义的调试信息
	如下面的：
*/
NSLog(@"%s:%d, %s",__FILE__, __LINE__, __FUNCTION__);     