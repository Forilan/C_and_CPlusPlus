
#include "Chapter04.h"
#include "stdafx.h"



// __________________________override__________________________

struct B1 final { };
struct D1 : B1 { }; // 错误！不能从 final 类继承！

/*上面的代码是错误的，因为 D1 试图继承 B1，而 B1 则声明为 final。
很像 Java，不是吗？当然！还有另外的用法： */

struct B2
{
    virtual void f() final {} // final 函数
};

struct D2 : B2
{
    virtual void f() {}
};

/*
这段代码又会出错，因为D2::f重写了B2::f，但是B2::f却被声明为 final 的！

下面再看另外一段代码：
*/

struct B3
{
    virtual void f() {}
};

struct D3 : B3
{
    void f() {}
};

/*
	开发 D3 的程序员真的想重写B3::f函数吗？还是说，他只是不小心写了个与父类同名的函数，
	却在不经意间导致了覆盖？为了避免这种错误，C++ 11 引入了override关键字（多么像 C# 啊！）。
	于是，我们会发现，下面的一段代码是会出错的：
*/

struct B4
{
    virtual void g(int) {}
};

struct D4 : B4
{
    virtual void g(int) override {}         // OK
    virtual void g(double) override {}      // Error
};

/*
多亏了override关键字，我们可以让编译器帮我们检测到这个很难发现的程序错误。
这段代码的错误在于，override关键字表明，g(double)虽然想要进行override的操作，但实际父类并没有这么个函数。

值得注意的是，这些并不是一些语法糖，而是能确确实实地避免很多程序错误，
并且暗示编译器可以作出一些优化。调用标记了final的virtual函数，
例如上面的B2::f，GNU C++ 前端会识别出，这个函数不能被覆盖，因此会将其从类的虚表中删除。
而标记为final的类，例如上面的 B1，编译器则根本不会生成虚表。这样的代码显然更有效率。
*/	



// __________________________final__________________________

/*
C++11的关键字final有两个用途。
	第一，它阻止了从类继承；
	第二，阻止一个虚函数的重载。我们先来看看final类吧。
某些实现系统服务、基础功能和加密等的类通常是不允许有子类的；实现者不想客户端从这些类派生新类而修改他们。
标准库容器，如std:: vector和std:: list的无子类化类型就是另一个很好的例子。这些容器没有虚拟析构函数或者确切地说没有任何虚成员函数。
*/

// 然而，程序员常常在没有意识到风险的情况下坚持从std::vector派生。在C++11中，无子类类型将被声明为如下所示：
class TaskManager {/*..*/} final; 
class PrioritizedTaskManager: public TaskManager {
};  //compilation error: base class TaskManager is final

// 同样，你可以通过声明它为final来禁止一个虚函数被进一步重载。如果一个派生类试图重载一个final函数，编译器就会报错：
struct A
{
  virtual void func() const;		//在函数后加const是什么意思?   说明这个函数不改变类中的成员变量。
};
struct B: A
{
  void func() const override final; //OK
};
struct C: B
{
 void func()const; //error, B::func is final
};
// C::func()是否声明为override没关系，一旦一个虚函数被声明为final，派生类不能再重载它。





// __________________________一些常见的 继承错误__________________________

/*
签名不匹配是一个更为常见的情景。这导致意外创建一个新的虚函数（而不是重载一个已存在的虚函数），正如以下例子所示：
*/
struct G
{
 virtual void func(int);
};
struct H: G
{
 virtual void func(double); //accidentally creates a new virtual function
};
/*
	这种情况下，程序员本打算在类H中重载G::func()的。然而，由于H::func()拥有不同的签名，结果创建了一个新的虚函数，而非对基类函数的重载：
*/
H *p=new H;
p->func(5); //calls G::f
p->func(5.0); // calls H::f

/*
碰到这种情况，不是所有的编译器都会给个警告，有时那样做会被设置成抑制这种警告。在C++11中，通过使用新关键字override可以消除这两个bugs。
override明确地表示一个函数是对基类中一个虚函数的重载。更重要的是，它会检查基类虚函数和派生类中重载函数的签名不匹配问题。
如果签名不匹配，编译器会发出错误信息。
*/

// 一些常见的 使用 override 后 可以避免的错误
struct Base {
    virtual void Turing() = 0;
    virtual void Dijkstra() = 0;
    virtual void VNeumann(int g) = 0;
    virtual void DKnuth() const;
    void Print();
};

struct DerivedMid: public Base {
    // void VNeumann(double g);
    // 接口被隔离了，曾想多一个版本的VNeumann函数
};

struct DerivedTop : public DerivedMid {
    void Turing() override;
    void Dikjstra() override;           // 无法通过编译，拼写错误，并非重载	【 Dijkstra 拼写错误】
    void VNeumann(double g) override;   // 无法通过编译，参数不一致，并非重载
    void DKnuth() override;             // 无法通过编译，常量性不一致，并非重载 【缺少 const】
    void Print() override;              // 无法通过编译，非虚函数重载
};
// 编译选项:g++ -c -std=c++11 2-10-3.cpp

/*
在代码清单2-25中，我们在基类Base中定义了一些virtual的函数（接口）以及一个非virtual的函数Print。
其派生类DerivedMid中，基类的Base的接口都没有重载。
*/



// __________________________声明的位置-不是保留关键字-而是上下文关键字__________________________
/*
还有值得注意的是，如我们在第1章中提到的，final/override也可以定义为正常变量名，
只有在其出现在函数后时才是能够控制继承/派生的关键字。通过这样的设计，
很多含有final/override变量或者函数名的C++98代码就能够被C++编译器编译通过了。
但出于安全考虑，建议读者在C++11代码中应该尽可能地避免这样的变量名称或将其定义在宏中，以防发生不必要的错误。
*/

/*
迄今为止，我已经避免了两个有关override和final的次要问题。第一个是它们独特的位置。
与virtual、inline、explicit extern以及一些类似的函数说明符不同的是，这两个关键字放在函数参数列表右括号之后，
或者（对于无子类的类来说）一个类声明的右大括号之后。
这些关键字的特殊位置是由另一个不同寻常的性质决定的：override和final不是普通关键字。
事实上官方地说，它们根本不是关键字。C++11把它们作为只是为了在特定上下文和位置下获取特殊意义的标示符。
在任何其他位置或上下文，它们都被当成标示符。因此，一个完全有效的C++11代码如下：
*/
//valid C++11 code
int final=0;
bool override=false;
if (override==true){
 cout<<”override is: “<<override<<endl;}
struct D{} final;
struct A
{virtual bool func(); };
struct B:A
{ bool func() override final; };

/*
这似乎有点不可思议，final和override酷似PL/ 1的上下文敏感关键词（CSK）。自1972年以来，C和后来的C+ +一直都很抵触CSK坚持保留关键字的做法。

那为什么委员会将final和override另外处理呢？选择CSK只是一种妥协方案。将override和final作为保留关键字可能对现有C++代码造成破坏。
如果委员会已经引入了新的保留关键字，他们可能会选择像final_declor_Override这样时髦的，
且不太可能与传统C++代码中用户声明的标示符相冲突的字符串等。
然而，没有谁喜欢这么丑的关键字（比如，问问C使用者对C99的s_Bool的看法）。这是为什么最终采用CSK方法的原因。

override和final在C++11中作为关键字，但只在特定的上下文使用。不然它们只被当成普通标示符。
虽然委员会不愿称override和final为“上下文敏感关键字”（事实上它们就是），
作为替代，它们被官方地称为“具有特殊意义的标示符”。的确很特别。
*/


// __________________________总结__________________________

/*
这两个新的上下文敏感的关键字override和final对类层次结构的更严格的控制，让你摆脱一些继承相关的刺激性错误和设计失误。
override保证重载虚拟函数匹配它的基类副本。final阻止进一步派生一个类或对一个虚函数进一步重载。
关于编译器支持方面,GCC 4.7、英特尔的C++12、MSVC 11和Clang 2.9都支持这些新的关键词。

关于部分摘选内容的作者
Danny Kalev是一名专注于C + +的，通过认证的系统分析师和软件工程师。Kalev已经写了一些C++的教科书，并定期在各种软件开发网站发布C++知识。
他是C++标准委员会的成员，并获得语言学硕士学位。
*/



// __________________________const在函数声明后面的意思__________________________
//有下面的函数声明：
double  d() const;
//其中的“const“有什么用？是什么意思？请举例说明下什么时候用这种形式？

/*
这儿的const就是说这个函数操作不会对变量或是对象之类的值有影响 比如你有一个human类 
你现在要得到某个human类对象A的age 那么肯定是不会因为你想得到这个值而改变了age的大小 对吧 
那么你就可以写一个函数int getAge（）const这样就好 这么做是为了防止你在函数中对不应该在这里改变的量不小心进行了改变
*/
