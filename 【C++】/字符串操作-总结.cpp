

// 字符串操作总结
/*

*/

// __________________________01 字符串 __________________________
1. 字符串：
字符串有两种：C 类型的以及C++ 类型的

1.1. C 类型字符串
C Style的其实就是char *或者char[]类型。


// char * __________________________

有以下定义形式：
char c = 'a';
char *pc = &c;             					// 虽然是char *类型，其实代表的是指针，
char *str1 = "abc";            				// C 字符串
const char * str2 = "abc";     				// C 字符串
"abc";                         				// 字面类型常量，内存形态与C 字符串相同

如果代表的是char的指针，则sizeof返回指针的长度是4(x86)或者8(x64)。
所以，以上的pc, str1, str2, "abc"均返回4/8

strlen则不同，strlen的实现类似如下：
size_t strlen(const char *str)
{
    if (!str)	// 空指针
        // 实现异常处理
    size_t len = 0;
    while (*str++) ++len;
    return len;
}

所以，他是根据'\0'判断字符串结尾的，用于指向字符的指针是错误的，会导致Undefined Behavior。

结果如下：

char c = 'a';
char *pc = &c;                 sizeof(pc) -> 4/8         strlen(pc) -> Undefined Behavior
char *str1 = "abc";            sizeof(str1) -> 4/8       strlen(str1) -> 3
const char * str2 = "abc";     sizeof(str2) -> 4/8       strlen(str2) -> 3
"abc";                         sizeof("abc") -> 4/8      strlen(str3) -> 3

// 1.1.2. char[]类型字符串 __________________________

需要注意的不同容量的数组可能会容纳相同内容的字符串，以及隐式指定数组大小。

虽然数组名可以转换为对应的指针，但实际上数组名还包含了数组的大小，所以char *和char[]还是有区别的。

sizeof(char *)会返回指针的长度-> 4/8

sizeof(char[n])会返回数组的长度 -> n*1，这里不是数组的元素数，而是数组占用内存的长度=元素数*元素大小

而strlen只是单纯得去找'\0'，例子中的数组内容各不相同，结果却都相同。

char str1[] = "abc";           sizeof(str1) -> 4         strlen(str1) -> 3
char str2[] = "abc\0";         sizeof(str2) -> 5         strlen(str2) -> 3
char str3[10] = "abc";         sizeof(str3) -> 10        strlen(str3) -> 3
char str4[20] = "abc\0abc";    sizeof(str4) -> 20        strlen(str4) -> 3

// 1.2. C++ 类型字符串 __________________________

string对象除了包含字符串内容，还包含了很多其他的东西，sizeof(string 对象)远大于字符串的大小，
此外，strlen也不适用于string对象。

string的c_str()成员函数返回对应的C类型字符串，可以对其应用strlen。

string有内置的返回长度的成员函数size/length。

注意：内置的size/length的机制是基于vector的，返回内置vector的size，所以结果可能与strlen不同

string str1 = "abc";            sizeof(str1) -> 依赖于实现 strlen(str1.c_str()) -> 3   str1.size() -> 3

string str2 = "abc";
str2.push_back(0);
str2.push_back('a');
str2.push_back('b');            

sizeof(str2) -> 依赖于实现
strlen(str2.c_str()) -> 3
str2.length() -> 6



// __________________________ C/C++ strlen(str)和str.length()和str.size()的区别 __________________________
/*
	C/C++ strlen(str)和str.length()和str.size()都可以求字符串长度。
	其中str.length()和str.size()是用于求string类对象的成员函数
	strlen(str)是用于求字符数组的长度，其参数是char*。
*/

#include <string>
#include <iostream>
using namespace std;

int main()
{
	string name="babababa";
	cout<<name.length()<<endl;
	cout<<name.size()<<endl;

	char mail[100]="haha";
	cout<<strlen(mail)<<endl;

	char *psd;
	psd="lalala";
	cout<<strlen(psd)<<endl;

	return 0;
}

输出结果：
8
8
4
6


// __________________________ C语言 __________________________

/*
	在C语言中，字符串常量代表了一块包括字符串中所有字符以及一个空字符（'\0'）的内存区域的地址。
	因为C语言要求字符串常量以空字符作为结束标志。	
*/	

// 将两个字符串s,t连接成单个字符串r。我们可以借助常用的库函数strcpy()和strcat()。


// WRONG! 之所以不行的原因在于不能确定r指向何处。r没有被初始化。 __________________________ __________________________
char *r;	
strcpy(r,s);
strcat(r,t);

// warning! 我们不敢确保 r >= s + t + 1  __________________________ __________________________
char r[100];
strcpy(r,s);
strcat(r,t);		// 用于粘贴两个非空字符串

// 使用动态分配内存  __________________________ __________________________
char *r = malloc(strlen(s) + strlen(t) + 1);
if(r == NULL)
{
	exit(1);
}
strcpy(r,s);
strcat(r,t);

//如果不再使用了
free(r);


// 输出   ____________________________________________________ 
char hello[] = "hello";
printf("%s\n",hello);
// 等价于下面这句：
printf("%s\n",&hello[0]);	



// __________________________ C++语言 __________________________

// 只调用 sprintf() 一次的时候  __________________________
std::string EMQusetionManager::getValueFromString(int prefix,const char* suffix)
{
	char name[80];
	sprintf(name, "%i%s", prefix, suffix);
	std::string path = name;
	return path;
}


// for循环调用 sprintf() 的时候,不进行覆盖study_word  __________________________
void forSprintf()
{
	char study_word[200];

	int offset =0;
	for (int i = 0; i < m_eatFruit.size(); ++i )
	{
		int which = m_eatFruit[i];
		offset += sprintf(study_word + offset, "%s,",FRUIT_NAME[which].c_str());
	}
}
/*
	for循环中每次调用函数sprintf()往字符数组写数据的时候，study_word+foffset为每次写入数据的开始地址.
	最终的结果是所有产生的数据都被存入数组中。
*/



/*
	如果出现边界错误，程序会崩掉，但是会蹦在一个奇怪的地方	
*/

void strToFile()
{

	// 字符串通过Java传递
	std::string toJava = buffer.GetString();

	std::string testSTR = toJava;
	char str10[2]; 
	sprintf(str10, "%s",testSTR.c_str());			// 这里越界了


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  

	UseJNI::JNIManager()->sendStringToJava(toJava);

#endif 

#ifndef YM_BURN_ANDROID
	// 字符串写入文件---写到 F:\cocos2d-x-2.2.3-xtc-0.6\debug-win32文件夹里
	FILE* file = fopen(path.c_str(), "wb");  
	if (file)  
	{  
		fputs(toJava.c_str(), file); 				// 但是程序会在这里蹦掉，让人不好定位错误。
		fclose(file);  
	}  
#endif // YM_BURN_ANDROID

}	