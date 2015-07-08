
// 使用容器
#include <vector>

// 使用算法
#include <algorithm>

using std::vector;



// ____________________________________________________  erase() ____________________________________________________ 
/*
	如果你阅读过 erase() 源码或了解它是如何工作的，性能问题就显而易见：
	erase() 删除一个元素的操作是被删除元素后面的所有元素依次,向前移动一个元素的位置，
	然后删除最后一个元素,时间复杂度为O(n^2)。
*/
	
// C++ 想要删除一个vector中某一个对象。 知道该v[]的下标。 怎么做 ？
Vector.erase(Vector.begin() + 下标);


vector<int> v;						// 正如从前
v.erase(remove(v.begin(), v.end(), 99), v.end());		// 真的删除所有  等于99的元素

cout << v.size();


//  删除 一个排序数组 里面相邻的重复元素

sort(nums.begin(), nums.end());		// 排序
nums.erase(unique(nums.begin(), nums.end()), nums.end());


/*
	把remove的返回值作为erase区间形式第一个实参传递很常见，这是个惯用法。
	事实上，remove和erase是亲密联盟，这两个整合到list成员函数remove中。
	这是STL中唯一名叫remove又能从容器中除去元素的函数：
*/
[注意：算法不直接修改容器的大小。如果需要添加或删除元素，则必须使用容器操作。]	
容器操作：  vector.XX();
算法：      XX(vector.A(),  vector.B());

list<int> li;			// 建立一个list
						// 放一些值进去
li.remove(99);			// // 除去所有等于99的元素：


/*
	坦白地说，调用这个remove函数是一个STL中的矛盾。在关联容器中类似的函数叫erase，list的remove也可以叫做erase。
	但它没有，所以我们都必须习惯它。我们所处于的世界不是所有可能中最好的世界，但却是我们所处的。
	（附加一点，条款44指出，对于list，调用remove成员函数比应用erase-remove惯用法更高效。）

一旦你知道了remove不能“真的”从一个容器中删除东西，和erase联合使用就变成理所当然了。
你要记住的唯一其他的东西是remove不是唯一这种情况的算法。另外有两种“类似remove”的算法：remove_if和unique。

remove和remove_if之间的相似性很直截了当。所以我不会细讲，但unique行为也像remove。
它用来从一个区间删除东西（邻近的重复值）而不用访问持有区间元素的容器。
结果，如果你真的要从容器中删除元素，你也必须成对调用unique和erase，unique在list中也类似于remove。
正像list::remove真的删除东西（而且比erase-remove惯用法高效得多）。
list::unique也真的删除邻近的重复值（也比erase-unique高效）。
*/



// ____________________________________________________ 删除心得  ____________________________________________________ 

// http://mingxinglai.com/cn/2012/09/delete-operation-in-stl/
总结如下

删除容器中具有特定值的元素：

如果容器是vector、string或者deque，使用erase-remove的惯用法。如果容器是list，使用list::remove。
如果容器是标准关联容器，使用它的erase成员函数。

删除容器中满足某些条件的元素：

如果容器是vector、string或者deque，使用erase-remove_if的惯用法。如果容器是list，
使用list::remove_if。如果容器是标准关联容器，使用remove_copy_if&swap 组合算法，或者自己设计个遍历删除算法。
参考资料：李健《编写高质量C++代码》第七章，用好STL这个大轮子