
#include "Chapter03.h"
#include "stdafx.h"



// auto的使用


/* auto
C++11中引入auto第一种作用是为了自动类型推导
auto的自动类型推导，用于从初始化表达式中推断出变量的数据类型。通过auto的自动类型推导，
可以大大简化我们的编程工作。auto实际上实在编译时对变量进行了类型推导，
所以不会对程序的运行效率造成不良影响。另外，似乎auto并不会影响编译速度，
因为编译时本来也要右侧推导然后判断与左侧是否匹配。如果没有auto关键字 写个迭代器要写很长长，
这也算是节省了我们的脑细胞吧，~~~~(>_<)~~~~ ！！ */

auto a; // 错误，auto是通过初始化表达式进⾏行类型推导，如果没有初始化表达式，就⽆无法确定a 的类型  
auto i = 1;  
auto d = 1.0;  
auto str = "Hello World";  
auto ch = 'A';  
auto func = less<int>();  
vector<int> iv;  
auto ite = iv.begin();  
auto p = new foo() // 对⾃自定义类型进⾏行类型推导  

/* auto不光有以上的应用，它在模板中也是大显身手，比如下例这个加工产品的例子中，
如果不使用auto就必须声明Product这一模板参数：*/
template <typename Product, typename Creator>  
void processProduct(const Creator& creator) {  
Product* val = creator.makeObject();  
// do somthing with val  
}  

/* 如果使用auto，则可以这样写：*/

template <typename Creator>  
void processProduct(const Creator& creator) {  
auto val = creator.makeObject();  
// do somthing with val  
}  

/* 抛弃了麻烦的模板参数，整个代码变得更加正解了。*/