
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

#include <algorithm>
#include <numeric>

// 10-第10章-泛型算法

//=========================================================================
//
//							10.1 概述
//
//=========================================================================

/*
	一般情况下，这些算法并不直接操作容器，而是遍历由两个迭代器指定的一个元素范围来进行操作。
*/

void algorithm_study_open()
{
	int val = 42;
	vector<int> vec (10, 42);
	auto result = find(vec.cbegin(), vec.cend(), val);
}

/*	关键概念：算法永远不会执行容器的操作
	泛型算法本身不会执行容器的操作，它们只会运行于迭代器之上，执行迭代器的操作。

	这样就可知： 算法永远不会改变底层容器的大小。
	算法可能改变容器中保存的元素的值，也可能在容器内移动元素，但永远不会直接添加或删除元素。
*/ 


//=========================================================================
//
//							10.2 初始泛型算法
//
//=========================================================================

/*
	除了少数例外，标准库算法都对 一个范围内的元素进行操作。我们将此元素范围称为“输入范围”。
	接受输入范围的算法总是使用前后两个参数来表示此范围，两个参数分别是指向要处理的第一个元素和尾元素之后位置的迭代器。

	虽然大多数算法 遍历输入范围的方式相似，但它们范围中元素的方式不同。
	理解算法的最基本的方法就是了解它们是否【读取元素】，【改变元素】或者【重排元素顺序】。
*/



// 10.2.1 只读算法 __________________________
/*
	一些算法只会读取输入范围内的元素，而从不改变元素。
	find 就是这样一种算法。
	accumulate 中需要求和范围的元素的和。
	equal 用于确定两个序列是否保存相同的值
*/  

void algorithm_study_read()
{
	int val = 42;
	vector<int> vec (10, 42);

	// 对 vec 中的 元素求和， 和 的初始值是 0,或者是其他精度的0
	float sum = accumulate(vec.cbegin(), vec.cend(), 0.0f);

	cout << sum << endl;
}


/*	【算法和元素类型】
	accumulate 的第3个参数的类型决定了 函数中使用 哪个加法运算符 以及返回值的 类型。
*/

void algorithm_study_accumulate()
{
	vector<string> v(10, "eri");

	// 对 vec 中的 元素求和， 和 的初始值是 0,或者是其他精度的0
	//string sum = accumulate(v.cbegin(), v.cend(), string(""));		// 这句话 有错误！！！

	//cout << sum.c_str() << endl;
}

/*	【操作两个序列的算法】
	equal 用于确定两个序列是否保存相同的值。

	那些只接受一个单一迭代器来表示第二个序列的算法，都假定第二个序列至少与第1个序列一样长。
*/

void algorithm_study_equal()
{
	vector<int> roster1(5, 42);
	vector<int> roster2(10, 42);
	bool isEqual = equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());

	cout << isEqual << endl;
}

 
// 10.2.2 写容器元素算法 __________________________
/*
	一些算法 将新赋值序列中的元素。【要注意 不要超出】

	一些算法会自己向输入范围写入元素。这些不会超出 容器范围的算法很安全。
	fill(roster1.begin(), roster1.end(), 10);		// 将每个元素重置为 10
	fill(roster1.begin(), roster1.begin() + roster1.size()/2, 10);		// 将容器的一个子序列设置为 10
*/  

void algorithm_study_fill()
{
	vector<int> roster1(5, 42);

	fill(roster1.begin(), roster1.end(), 10);

	for (int &i : roster1) {
		cout << i << endl;
	}
}

/*
	函数 fill_n 接受一个单迭代器，一个计数值，和一个值。
*/
void algorithm_study_fill_n()
{
	vector<int> roster1(10, 42);

	fill_n(roster1.begin(), 2, 10);		// 第2个参数是个计数值，把从第1个参数的 迭代器 往后几个元素 都重置为 10。

	for (int &i : roster1) {
		cout << i << endl;
	}
}

/*	【back_inserter】
	一种保证算法有足够元素空间来容纳输出数据的方法是 使用插入迭代器。

	插入迭代器 是一种向容器中添加元素的迭代器。
	back_inserter 接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。
	当我们通过此迭代器赋值时，赋值运算符会调用 push_back 将一个具有给定值的元素添加到容器中。 示例如下：
*/

void algorithm_study_back_inserter()
{
	vector<int> vec1;
	auto it = back_inserter(vec1);
	*it = 20;
	cout << vec1[0] << endl;

	vector<int> vec(2, 42);

	fill_n(back_inserter(vec), 3, 10);		//		// 在后面插入3个元素，值都是10

	for (int &i : vec) {
		cout << i << endl;
	}
}


/*	【拷贝算法】
	copy 可以 用 copy 实现内置数组的拷贝。

	copy 返回的是其目的位置迭代器（递增后）的值。
*/
void algorithm_study_back_copy()
{
	int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int a2[sizeof(a1)/sizeof(*a1)];					// a2 与 a1 一样大小。

	copy(begin(a1), end(a1), a2);		// 把 a1 的内容拷贝给 a2

	for (int &i : a2) {
		cout << i << endl;
	}
}

/*
	多个算法都提供所谓的“拷贝”版本。这些算法计算新元素的值，但不会将它们放置在输入序列的末尾，而是创建一个新序列保存这些结果。
*/
void algorithm_study_back_copy1()
{
	vector<int> ilst(5, 0);
	//replace(ilst.begin(), ilst.end(), 0, 42);				// 将所有值为0的元素改为42
	vector<int> ivec;
	replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 0, 42);		
	// 此调用后，ilst 并未改变，ivec 包含一份 ilst 的拷贝，不过 将所有值为0的元素改为42

	for (int &i : ilst) {
		cout << i << endl;
	}

	for (int &i : ivec) {
		cout << i << endl;
	}
}


// 10.2.3 重排容器元素的算法 __________________________
/*

*/  

// 去除容器中的 重复元素
void algorithm_study_sort_unique_erase()
{
	vector<int> words(4, 5);

	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());		// unique() 接受已经排序的容器的迭代器

	words.erase(end_unique, words.end());

	for (int &i : words) {			// 只会输出一个 5
		cout << i << endl;
	}
}


//=========================================================================
//
//							10.3 定制操作
//
//=========================================================================


/*
	很多算法都会比较输入序列中的元素。默认情况下，这类算法使用元素类型的 < 或 == 运算符完成比较。
	标准库 还 为这些算法 定义了额外的版本，允许我们提供自己定义的操作 来 代替默认 运算符。
*/

// 10.3.1 向算法传递函数 __________________________
/*
	
*/  





