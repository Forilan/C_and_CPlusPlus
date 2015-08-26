
#include "Chapter01.h"
#include "stdafx.h"



// lambda表达式
// [][=][&][ad][&ad][&ad,ers] 之间的区别
void chapter02::equalLambda( void )
{
  int ad = 4,ers = 6;
  //第1次使用
  listener1->onTouchBegan = [](Touch* touch, Event* event){
    5 == ad;  // 会报错，Error:封闭函数局部变量不能在 lambda 体中引用，除非其位于捕获列表中
    asd = 12;
  };

  //第2次使用【直接写局部变量名字，默认为 =ad】
  listener1->onTouchBegan = [ad](Touch* touch, Event* event){
    5 == ad;  
    ad = 3;   // 会报错，Error:表达式必须是可修改的左值
    asd = 12;
  };

  //第3次使用
  listener1->onTouchBegan = [=](Touch* touch, Event* event){
    5 == ad;  
    ad = 3;   // 会报错，Error:表达式必须是可修改的左值
    asd = 12;
  };

  //第4次使用
  listener1->onTouchBegan = [&ad](Touch* touch, Event* event){
    5 == ad;  
    ad = 3;   
    asd = 12;
  };

  //第5次使用
  listener1->onTouchBegan = [&ad,ers](Touch* touch, Event* event){
    5 == ad;  
    ad = 3;   
    34 == ers;
    asd = 12;
  };

  /*
    [] 表示不引用【所在函数中】的任何对象
    [=] 表示可以引用【所在函数中】出现过的任何对象
    [Node1,Node2,...] 表示引用【所在函数中】特定的对象
    [&] 表示引用【所在函数中】的对象，并可以对其进行修改 
  */
}
   
void chapter02::Lambda( void )
{
  int ad = 4;
	//第1次使用
 	listener1->onTouchBegan = [](Touch* touch, Event* event){
 		auto target = static_cast<Sprite*>(event->getCurrentTarget());

 		Point locationInNode = target->converToNodeSpace(touch->getLocation());
 		Size s = target->getContenSize();
 		Rect rect = Rect(0,0,s.width,s.height);
 	};

 	//第3次使用
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
 		auto target = static_cast<Sprite*>(event->getCurrentTarget());

 		if(target == sprite2)
 		{
 			containerForSprite1->setlocalZOrder(100);
 		}
 		else if(target == sprite1)
 		{
 			containForSprite1->setLocatZOrder(0);
 		}
 	};
}


/*
	《Cocos2d-x v3.0 新的事件调度方法 lambda表达式的使用》

	下面我们来看一段TestCpp中的代码：


在上图的触摸事件的回调函数中，共使用了三次Lambda表达式:
                                     [ ](Touch * touch,Event * event){ };
下面我们就来介绍一下Lambda表达式的使用方法。

正常情况下，如果我们需要在很多地方使用相同的操作，通常应该定义一个函数来实现这个功能。
而有些时候，我们只需要在一两个地方使用到一些简单的操作，而又不想去定义这个函数名，那么此时便可以Lambda表达式来实现我们的功能。
一个完整的lambda表达式的表达形式如下：
                                    [capture list](parameter list)->return type (function body) 
                                    [捕获列表]   (参数列表)        ->返回类型    (函数体) 

那么为什么图中的Lambda表达式的形式与上述的形式不一样呢?
原因是 Lambda表达式的参数列表和返回类型是可以忽略的，但是捕获列表和函数体一定要包含。

也就是说，Lambda表达式实际上就是一个匿名函数，它的优点与内联函数(又称内嵌函数、内置函数)类似,但Lambda表达式可能会定义在函数内部。
那么内联函数的优点是什么呢？我们举个例子来说明，比如我们的程序中有这样一段代码：
void A(){
       ....//函数体略
}
void main(){
        ....  //省略
        A( ); //调用A函数
       ....   //省略
}
上述代码执行的主要过程如下:
1.主调函数main执行完调用A函数前的语句后，在转去调用A函数前，首先需要记录当前执行的指令地址，也就是做一个“保护现场”的操作，
用于执行完A函数后继续执行后续代码。
2.然后流程的控制会被转移到A函数的入口，并且执行A函数中的函数体内的语句.
3.执行完成后，流程才会返回到之前记录的地址处，并且根据之前所记录的信息做"恢复现场"操作，保证程序正常执行。

上述过程的每一个操作都需要花费一定的时间，如果A函数需要被频繁的使用，那么我们花费的时间就会很长，从而造成效率降低。
为了解决这个问题,C++为我们提供的了内联函数，所谓内联函数，就是通过将一个函数声明为inline function,从而达到在编译的过程中，
直接将所调用的函数的函数体部分直接拷贝到主调函数，而不需要将流程转到这个函数中去,以此来减少程序的运行时间。
这是因为当一个函数的函数体规模很小的时候，函数调用过程中的时间开销会超过执行函数所需要的时间。

这就是使用内联函数的好处，而对于Lambda表达式，我们可以将它理解为一个未命名的内联函数。

下面我们对lambda表达式的形式进行逐一分析：
1.“  [捕获列表]  ”
首先我们观察一下上图中的第一个lambda表达式与第三个lambda表达式的捕获列表部分的区别。
可以看到，上图的第一个表达式中捕获列表为空 [ ]，而第三个表达式中的捕获列表中包含了一个等号 [=]。

下面我们再观察一下上图中第一个与第三个lambda表达式的函数体内都使用到了哪些变量。
可以看到，第一个表达式中所有的变量，均是在Lambda表达式中定义的(log除外,因为log函数包含在头文件中)，
而在第三个表达式中所使用到的sprite1,sprite2等变量，并不是在lambda表达式中定义的，而是当前函数中或是当前类中的变量。
那么我们就可以总结出，在Lambda表达式的函数体内，是不能够访问到外部的变量的，如果想要使用函数体外定义的变量，就需要将它们进行"捕获"，上图第三个lambda表达式采用的正是“值捕获”，与它对应的另外一种为“引用捕获”。
[ ]:空捕获列表，即lambda表达式不能够使用所在函数中的变量
[=]:值捕获，即lambda表达式可以以拷贝的方式访问到函数中变量的值
[&]:引用捕获，即lambda表达式中所使用的其所在函数中的变量均是引用方式
当我们不希望在捕获的时候将所有的变量都捕获的时候，我们可以使用如下的方式进行捕获，例如：
[=sprite1,&sprite2]
这里我们仅仅捕获了两个变量，第一个变量是以值拷贝的方式捕获，第二个是以引用方式捕获，变量与变量之间用逗号分隔。

正常情况下，如果一个变量是值拷贝，Lambda不能改变它的值，如果我们希望改变一个值拷贝的变量的值，就需要在参数列表前加上关键字mutable
例如：*/

         auto s1=10;
         auto s2=[=s1](){return ++s1};			//错误，因为s1是值拷贝,不能改变s1的值
         auto s2=[=s1]() mutable {return ++s1};	//正确 


/* 2.(参数列表)
Lambda表达式传递参数时需要注意的是，Lambda表达式不能有默认参数，也就是说Lambda表达式的实参数与形参数必须相等。
其他情况Lambda表达式的参数部分与普通函数并无区别，一般会结合STL使用。
例如:*/
void Test(){
      vector<int> myVec;   //创建一个int 类型容器
      myVec.push_back(1);  //插入数据 1
      myVec.push_back(2);  //插入数据 2
      
      int a=10;                   //创建局部变量 a
      for_each(myVec.begin(),myVec.end(),[&](int v)mutable(cout<<v+a<<endl;a++)); //将容器中元素作为参数传到lambda表达式 输出a+v结果为 11 13
       cout<<a<<endl;      //输出a 结果为12
}

/* 3.->return type
之间我们已经提到，Lambda的返回值是可以省略的。
原因是编译器会根据return的类型来推导返回值，但是如果需要return后再做一个类型转换，我们就可以通过写一个返回类型来完成。
例如：*/
cout<<[](float f){return f;}(1.5); //这里我们将1.5作为参数传入并打印，返回结果就是实参的值1.5
cout<<[](float f)->int{return f;}(1.5); //我们将返回值强制转换为int 输出结果为1


/*	4.函数体
   函数体部分与普通函数并无区别，我们只需要注意以上几点，在函数体部分就不会出现问题。

   现在再回头看看TestCpp中的触摸事件,我们就可以明白其中的道理了。
*/
