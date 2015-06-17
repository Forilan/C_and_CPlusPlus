
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;



// ____________________________________________________  remove() ____________________________________________________ 

算法描述：查找的得到第一个元素的位置，然后从此位置开始遍历容器，将后面的元素依次前移，跳过和value相同值的元素，
也就是说，所有和value相同值的元素都会被覆盖，而其他的元素都会依次前移。
最后remove返回"指向最后一个   '有用'   元素的iterator",但是在remove算法过程中，并没有修改原容器的size,以及end()。
但是从逻辑角度看，最后的[   从remove得到的iterator---_result,   容器的结尾end()   )   
这个区间里面的元素已经没有意义了。所以这些元素不应该属于该容器了。

remove算法能做的仅此而已，并没有删除这些无用的元素。     

结论：移除容器里面的元素不应该使用remove算法，而是容器自己的方法erase()。 

/*
	条款32：如果你真的想删除东西的话就在类似remove的算法后接上erase
*/


// ____________________________________________________  remove_if() ____________________________________________________ 
/*
	remove_if 方法的第三个参数是一个过滤条件，即我们要使用何种清除规则来清楚容器中的元素

	如，我们要删除容器中所有为3的倍数的元素:
*/

//该方法实现对3的倍数的元素的过滤
//参数是容器中的元素，注意返回值类型
bool RemoveItem(int item)
{
    if (item%3 == 0) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[])
{
    std::vector<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(33);
    vec.push_back(22);
//第三个参数是使用函数指针的方法调用，参数由系统自动传递
//返回值为真则清除，假则不清除
   vec.erase( std::remove_if(vec.begin(),vec.end(),RemoveItem), vec.end() );

    std::vector<int>::iterator iter;
    for (iter = vec.begin(); iter != vec.end(); iter++)
    {
        printf("%d\n",(*iter));
    }

    return 0;
}

打印结果为：

2 4 8 22


