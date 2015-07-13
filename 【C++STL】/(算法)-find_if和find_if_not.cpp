
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;




// ____________________________________________________  find_if ____________________________________________________ 

/*
	The elements within the container are compared for equality with the specified binary operation. 

	If a match is found, the search ends. find_if() returns an iterator to the element. 

	If no match is found, container.end() is returned.

#include <algorithm> 
find_if( vec.begin(), vec.end(), LessThanVal(ival) ); 

*/

// 示例1: 寻找倒数最后一个单词的 长度。
class Solution {
public:
    int lengthOfLastWord(string& str) {
        // Write your code here
        auto first = find_if(str.rbegin(), str.rend(), ::isalpha);
        auto last = find_if_not(first, str.rend(), ::isalpha);
        return distance(first, last);
    }
};

// 示例2:


// ____________________________________________________  find_if_not ____________________________________________________ 
