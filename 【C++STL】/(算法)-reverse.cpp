
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;



// ____________________________________________________  reverse ____________________________________________________ 

/*
	reverse ，翻转一个容器里面元素的排序。

	好像只支持 翻转 <vector>，并不支持 翻转 栈，有待实验。
*/

// 示例1:
class Solution {
public:
    void reverseElement(vector<int>& nums) {
        reverse(nums.begin(),nums.end());
    }
};

// 示例2:


// ____________________________________________________   ____________________________________________________ 
