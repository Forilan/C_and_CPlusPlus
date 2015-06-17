
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;



// ____________________________________________________  unique() ____________________________________________________ 

/*
	类属性算法unique的作用是从输入序列中“删除”所有相邻的重复元素。

	该算法删除相邻的重复元素，然后重新排列输入范围内的元素，并且返回一个迭代器（容器的长度没变，只是元素顺序改变了），
	表示无重复的值范围得结束。
*/

/*
	在STL中unique函数是一个去重函数， unique的功能是去除相邻的重复元素(只保留一个),其实它并不真正把重复的元素删除，
	是把重复的元素移到后面去了，然后依然保存到了原数组中，然后 返回去重后最后一个元素的地址，
	因为unique去除的是相邻的重复元素，所以一般用之前都会要排一下序。
*/

// 示例1:
class Solution {
public:
    int removeDuplicates(vector<int> &A) {
        return distance(A.begin(), unique(A.begin(), A.end()));
    }
};


/*
	调用unique“删除”了相邻的重复值。给“删除”加上引号是因为unique实际上并没有删除任何元素，
	而是将无重复的元素复制到序列的前段，从而覆盖相邻的重复元素。
	unique返回的迭代器指向超出无重复的元素范围末端的下一个位置。	
*/

注意：算法不直接修改容器的大小。如果需要添加或删除元素，则必须使用容器操作。


// ____________________________________________________ unique_copy()  ____________________________________________________ 
/*
	算法标准库定义了一个名为unique_copy的函数，其操作类似于unique。

	唯一的区别在于：前者接受第三个迭代器实参，用于指定复制不重复元素的目标序列。

	unique_copy根据字面意思就是去除重复元素再执行copy运算。

	编写程序使用unique_copy将一个list对象中不重复的元素赋值到一个空的vector对象中。
*/

//使用unique_copy算法
//将一个list对象中不重复的元素赋值到一个空的vector对象中
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int ia[7] = {5 , 2 , 2 , 2 , 100 , 5 , 2};
    list<int> ilst(ia , ia + 7);
    vector<int> ivec;

    //将list对象ilst中不重复的元素复制到空的vector对象ivec中
    //sort(ilst.begin() , ilst.end());  //不能用此种排序，会报错
    ilst.sort();  //在进行复制之前要先排序，切记
    unique_copy(ilst.begin() , ilst.end() , back_inserter(ivec));

    //输出vector容器
    cout<<"vector: "<<endl;
    for(vector<int>::iterator iter = ivec.begin() ; iter != ivec.end() ; ++iter)
        cout<<*iter<<" ";
    cout<<endl;

    return 0;
}

