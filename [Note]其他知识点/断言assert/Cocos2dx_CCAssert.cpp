

// CCAssert




// __________________________1 Cocos2dx 技巧断言CCAssert __________________________
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



