

// 字符串操作总结
/*

*/


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


std::string EMQusetionManager::getValueFromString(int prefix,const char* suffix)
{
	char name[80];
	sprintf(name, "%i%s", prefix, suffix);
	path = name;
	return path;
}