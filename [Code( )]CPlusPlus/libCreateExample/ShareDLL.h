#ifndef SHARED_DLL
#define SHARED_DLL

//在 DLL 项目中设置 DLL_API 为导出类型 extern "C" _declspec(dllimport)
//在 Test 项目中则无需设置该 DLL_API ， 直接使用这个 CalculateDLL.h 文件即可

#ifdef DLL_API
#else 
#define DLL_API extern "C" _declspec(dllimport)
#endif

DLL_API void	SetData(int tmpData, int i, int j, int k);
DLL_API int		GetData(int i, int j, int k);
DLL_API int*	GetDataPoint();


/// int 的版本，已经验证成功。
#if 0
//在 DLL 项目中设置 DLL_API 为导出类型 extern "C" _declspec(dllimport)
//在 Test 项目中则无需设置该 DLL_API ， 直接使用这个 CalculateDLL.h 文件即可

#ifdef DLL_API
#else 
#define DLL_API extern "C" _declspec(dllimport)
#endif

DLL_API void SetData(int tmpData);
DLL_API int GetData();
#endif


#endif	// SHARED_DLL