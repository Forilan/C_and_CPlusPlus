
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

enum BBK_Data_Attr{
	BBK_Data_Id,				//	数据ID
	BBK_Data_Title,				//	数据标题
	BBK_Data_Edition,			//	数据版本
	BBK_Data_Type,				//	数据类型
	BBK_Data_Grade,				//	数据年级
	BBK_Data_Subject,			//	数据科目
	BBK_Data_Publisher,			//	数据出版者
	BBK_Data_Extend,			//	数据扩展
	Enum_Max_Num,				//  枚举体最大个数-不要使用，新定义的 枚举体 就在 Enum_Max_Num 前面定义，这样就可以 统计出 枚举体的最大个数了。
};

typedef struct dataAttr {
	char* data[Enum_Max_Num];	// 
} DataAttr;


void coutEnumNum() 
{
	DataAttr er;
	int er1 = sizeof(BBK_Data_Attr);		//	这个输出来是4，不管 你 枚举体 里面有多少数据
	//cout << er1 << endl;
}