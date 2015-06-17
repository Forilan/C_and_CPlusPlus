
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;



// ____________________________________________________  distance ____________________________________________________ 

/*
	distance是计算两个iterator直接的距离
*/

// 示例1:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        return distance(nums.begin(), remove(nums.begin(), nums.end(), val));
    }
};

// 示例2:
class Solution {
public:
    int removeDuplicates(vector<int> &A) {
        return distance(A.begin(), unique(A.begin(), A.end()));
    }
};

// ____________________________________________________   ____________________________________________________ 
