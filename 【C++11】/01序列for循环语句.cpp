
#include "Chapter01.h"
#include "stdafx.h"



// 序列for循环
/*
	序列for循环 
	在C++中for循环可以使用类似java的简化的for循环，
	可以用于遍历数组，容器，string以及由begin和end函数定义的序列（即有Iterator），示例代码如下：
*/
void chapter01::Listfor( void )
{
	map<string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};  
	for (auto p : m){  
	cout<<p.first<<" : "<<p.second<<endl;  
	}  

	// 这里 item 是指针
	for (auto &item: touches)       //遍历容器中的各个成员！！！多点触摸时将显示同时显示多个精灵
    {
        auto touch = item;
        auto location = touch->getLocation();
        //加载一个精灵
        auto sprite = Sprite::create("Icon.png");
        sprite->setPosition(location);
        addChild(sprite);
    }

    /* 关键掌握对容器touches中成员的遍历。
    C++11新特性中，for 语句将允许简单的范围迭代：第一部分定义被用来做范围迭代的变量，
    就像被声明在一般for循环的变量一样，其作用域仅只于循环的范围。
    而在":"之后的第二区块，代表将被迭代的范围。
    这样一来，就有了能够允许C-style数组被转换成范围概念的概念图。
    这可以是std::vector，或是其他符合范围概念的对象。 */
}