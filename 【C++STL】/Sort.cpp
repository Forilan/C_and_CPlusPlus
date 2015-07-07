
// 使用容器
#include <vector>

// 使用打乱算法
#include <algorithm>

using std::vector;
using std::random_shuffle;


/// << =============宏定义============= >>
#define ArrLen( ARRAY ) (sizeof (ARRAY) / sizeof (ARRAY[0]))
// 用来计算数组大小的。		// int Arr_MAX_WORD =  ArrLen(wordPool);

#define FM_C_MAX_WORD 12
wordPool[FM_C_MAX_WORD];

vector<int> vi;

void initArray()
{
	// 初始化数组
	for (int i = 0;i<FM_C_MAX_WORD;i++)
	{
		wordPool[i] = i;
	}

	/*生成向量包含了  0~(FM_C_MAX_WORD-1) 之间的整数并且按升序排列*/
	for (int i = 0; i < FM_C_MAX_WORD; i++)
	{
		vi.push_back(i);
	}
}

// ____________________________________________________  1 打乱排序 random_shuffle()  ____________________________________________________
/*
	打乱排序算法

	random_shuffle()算法打乱了先前填充到向量中的元素
	random_shuffle()有两个参数，
	第一个参数是指向序列首元素的迭代器，
	第二个参数则指向序列最后一个元素的下一个位置。
*/
void randomSortBySTL()
{
	// 初始化随机种子【要不然random_shuffle()每次随机的结果都一样】		
	srand ((unsigned)time(nullptr));		// 这个函数在整个进程中只能初始化1次

	// 使用 random_shuffle 打乱 容器里的排序
	random_shuffle(vi.begin(), vi.end());

	// 使用 random_shuffle 打乱 内置数组，
	random_shuffle(wordPool, wordPool+ArrLen(wordPool));
/*
	只是要注意random_shuffle()的第二个参数要指向数组下界的下一个元素位
	wordPool 可以是 任何数组类型。
*/ 
}


// ____________________________________________________  2 排序 sort()  ____________________________________________________





/*
STL sort源码剖析
http://www.cnblogs.com/imAkaka/articles/2407877.html

STL的sort()算法，数据量大时采用Quick Sort，分段递归排序，一旦分段后的数据量小于某个门槛，为避免Quick Sort的递归调用带来过大的额外负荷，
就改用Insertion Sort。如果递归层次过深，还会改用Heap Sort。本文先分别介绍这个三个Sort，再整合分析STL sort算法(以上三种算法的综合) 
-- Introspective Sorting(内省式排序)。

详细解说 STL 排序(Sort)
http://www.cppblog.com/mzty/archive/2005/12/15/1770.html


*/

// 对容器进行排序
vector<int> nums1;
sort(nums1.begin(), nums1.end());

// 对数组进行排序


sort(wordPool, wordPool+ArrLen(wordPool));

