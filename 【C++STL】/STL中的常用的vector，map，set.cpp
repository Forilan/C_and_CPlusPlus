

// STL中的常用的vector，map，set 用法
/*
	C++的标准模板库（Standard Template Library，简称STL）是一个容器和算法的类库。容器往往包含同一类型的数据。
	STL中比较常用的【容器】是vector，set和map，比较常用的【算法】有Sort等。
*/


// ____________________________________________________  一. vector  ____________________________________________________
// 1.声明： 

#include <vector>
using namespace std;

/*
 一个vector类似于一个动态的一维数组。
 这里的声明的a包含0个元素，既a.size()的值为0，但它是动态的，其大小会随着数据的插入和删除改变而改变。
 */

std::vector<int> a; //声明一个元素为int类型的vector a
std::vectot<MyType> a; //声明一个元素为MyType类型的vector a       
vector<int> a(100, 0); //这里声明的是一已经个存放了100个0的整数vector

// 2.向量操作

// 常用函数-【感觉 vector 很像栈啊】

		size_t size();             // 返回vector的大小，即包含的元素个数
        void pop_back();           // 删除vector末尾的元素，vector大小相应减一
        void push_back();          // 用于在vector的末尾添加元素
        T back();                  // 返回vector末尾的元素
        void clear();              // 将vector清空，vector大小变为0
/*       
其他访问方式：
          cout<<a[5]<<endl;
          cout<<a.at(5)<<endl;
以上区别在于后者在访问越界时会抛出异常，而前者不会。

*/

int intarray[10];   
vector<int>   first_vector(intarray,intarray + 10);   
vector<int>   second_vector(first_vector.begin(),first_vector.end()); 

class man   
{   
      public:   
      AnsiStirng         id;   
      AnsiString         mc;   
};   

vector<man>  manList;

man  thisman;   
thisman.id="2001";   
thisman.name="yourname";  

manList.push_back(thisman);           //加入第一个元素  

thisman.id="2002";   
thisman.name="myname";   
manList.push_back(thisman);           //加入第二个元素   

manList.clear();           //清空


// 3.遍历
// 第1种方法
for(vector<datatype>::iterator it=a.begin(); it!=a.end();it++)
{
	cout<<*it<<endl;
}
    
// 第2种方法
for(int i=0;i<a.size;i++)
{
	cout<<a[i]<<endl;
}
     
// 第3种方法-  C++11 才支持
for (auto &item: a)       //遍历容器中的各个成员！
{
	cout<<item<<endl;
}   

// ____________________________________________________  二. map  ____________________________________________________

/*
Map是STL的一个关联容器，它提供一对一（其中第一个可以称为关键字，每个关键字只能在map中出现一次，第二个可能称为该关键字的值）的数据处理能力，
由于这个特性，map内部的实现自建一颗红黑树(一种非严格意义上的平衡二叉树)，这颗树具有对数据自动排序的功能。
下面举例说明什么是一对一的数据映射。比如一个班级中，每个学生的学号跟他的姓名就存在着一一映射的关系，这个模型用map可能轻易描述，
很明显学号用int描述，姓名用字符串描述(本篇文章中不用char *来描述字符串，而是采用STL中string来描述),
下面给出map描述代码：
*/

// 1.	声明方式：
Map<int, string> mapStudent;

// 2.	数据的插入
/*
在构造map容器后，我们就可以往里面插入数据了。这里讲三种插入数据的方法：
*/
// 第一种：用insert函数插入pair数据
Map<int, string> mapStudent;
mapStudent.insert(pair<int, string>(1, “student_one”));

// 第二种：用insert函数插入value_type数据
Map<int, string> mapStudent;
mapStudent.insert(map<int, string>::value_type (1, “student_one”));

// 第三种：用数组方式插入数据
Map<int, string> mapStudent;
mapStudent[1] = “student_one”;
mapStudent[2] = “student_two”;

// 3.	map的大小
// 在往map里面插入了数据，我们怎么知道当前已经插入了多少数据呢，可以用size函数：
int nSize = mapStudent.size();

// 4.	数据的遍历
// 第一种：应用前向迭代器
map<int, string>::iterator iter;
for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
 	Cout<<iter->first<<”        ”<<iter->second<<end;

// 第二种：应用反相迭代器
map<int, string>::reverse_iterator iter;
for(iter = mapStudent.rbegin(); iter != mapStudent.rend(); iter++)
      Cout<<iter->first<<”        ”<<iter->second<<end;
// 第三种：用数组方式
int nSize = mapStudent.size()
for(int nIndex = 1; nIndex <= nSize; nIndex++) 
      Cout<<mapStudent[nIndex]<<end;

// 5.	 数据的查找（包括判定这个关键字是否在map中出现）
/*
	这里给出三种数据查找方法
第一种：用count函数来判定关键字是否出现，但是无法定位数据出现位置
第二种：用find函数来定位数据出现位置它返回的一个迭代器，
当数据出现时，它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器
*/

Int main()
{
    Map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1, “student_one”));
    mapStudent.insert(pair<int, string>(2, “student_two”));
    mapStudent.insert(pair<int, string>(3, “student_three”));
    map<int, string>::iterator iter;
    iter = mapStudent.find(1);
    if(iter != mapStudent.end())
    {
           Cout<<”Find, the value is ”<<iter->second<<endl;
    }
    Else
    {
       Cout<<”Do not Find”<<endl;
    }
}

/*
	第三种：这个方法用来判定数据是否出现
Lower_bound函数用法，这个函数用来返回要查找关键字的下界(是一个迭代器)
Upper_bound函数用法，这个函数用来返回要查找关键字的上界(是一个迭代器)
例如：map中已经插入了1，2，3，4的话，如果lower_bound(2)的话，返回的2，而upper-bound（2）的话，返回的就是3
Equal_range函数返回一个pair，pair里面第一个变量是Lower_bound返回的迭代器，pair里面第二个迭代器是Upper_bound返回的迭代器，
如果这两个迭代器相等的话，则说明map中不出现这个关键字，程序说明
mapPair = mapStudent.equal_range(2);
if(mapPair.first == mapPair.second)
    cout<<”Do not Find”<<endl;
*/


// 6.	数据的清空与判空
// 清空map中的数据可以用clear()函数，判定map中是否有数据可以用empty()函数，它返回true则说明是空map

// 7.	数据的删除
/*
这里要用到erase函数，它有三个重载了的函数
迭代器删除 
            iter = mapStudent.find(1);
            mapStudent.erase(iter);
用关键字删除
            Int n = mapStudent.erase(1);//如果删除了会返回1，否则返回0
用迭代器，成片的删除
            一下代码把整个map清空
            mapStudent.earse(mapStudent.begin(), mapStudent.end());
            //成片删除要注意的是，也是STL的特性，删除区间是一个前闭后开的集合
*/

// 8.	其他一些函数用法
// 这里有swap,key_comp,value_comp,get_allocator等函数，有兴趣的话可以自个研究          

/*

*/

// ____________________________________________________  三. set  ____________________________________________________

/*

*/

/*

*/

