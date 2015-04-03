

// ____________________________________________________ 模板函数____________________________________________________

// 0-引子-历史-来源____________________________________________________
/*
	如果说模板类定义的是一种数据类型，那么模板函数定义的就是一种函数。既然是函数，那么就有输入数据和输出数据。
	和模板类的概念差不多，模板函数的初衷也是为了在函数操作上抽取共同的特性，屏蔽的是类型的不同和差异。
	我们可以通过下面一个简单的代码说明问题：
*/

int int_compare(int a, int b)
{
	return a > b ? a : b;
}

double double_compare(double a, double b)
{
	return a > b ? a : b;
}


// 1-解决方案-横空出世____________________________________________________
/*
	上面的一段代码是取较大值的一段代码。两个函数之间最大的差别就是输入数据类型和输出数据类型之间的差别，
	那我们有没有一种办法可以屏蔽这种数据类型之间的差别呢？
	有。那就是函数模板：
*/
template <typename type>
type compare(type a, type b)
{
	return a > b ? a : b;
}
/*
	typename和class关键字作用都是用来表示它们之后的参数是一个类型的参数。只不过class是早期C++版本中所使用的，
	后来为了不与类产生混淆，所以增加个关键字typename。

	可以看到，用函数模板比函数重载更方便，程序更简洁。
	但应注意它只适用于函数的参数个数相同而类型不同，且函数体相同的情况，
	如果参数的个数不同，则不能用函数模板。
*/



/*	概述:所谓泛型编程就是以独立于任何特定类型的方式编写代码。使用泛型程序时，我们需要提供具体程序实例所操作的类型或值。
	第二部分中描述的标准库的容器、迭代器和算法都是泛型编程的例子。在 C++ 中，【模板是泛型编程的基础】。【模板是创建类或函数的蓝图或公式】。
*/

// 2.定义函数模板 ______________________________________________________________________________

//compare 的模板版本：
// implement strcmp-like generic compare function
// returns 0 if the values are equal, 1 if v1 is larger, -1 if v1 is smaller
template <typename T>		// 函数的声明和实现之前都要有template<typename t>
int compare(const T &v1, const T &v2)
{
 if (v1 < v2) return -1;
 if (v2 < v1) return 1;
 return 0;
}
/*
       a. 模板定义以关键字 template 开始，后接模板形参表，模板形参表是用尖括号括住的一个或多个模板形参的列表，形参之间以逗号分隔。 模板形参表不能为空。

       b.模板形参表很像函数形参表，函数形参表定义了特定类型的局部变量但并不初始化那些变量，在运行时再提供实参来初始化形参。

       c.模板形参可以是表示类型的类型形参，也可以是表示常量表达式的非类型形参。非类型形参跟在类型说明符之后声明,
       类型形参跟在关键字 class 或 typename 之后定义，例如，class T 是名为 T 的类型形参，在这里 class 和 typename 没有区别。

       2.使用函数模板:使用函数模板时，编译器会推断哪个（或哪些）模板实参绑定到模板形参。一旦编译器确定了实际的模板实参，
       就称它实例化了函数模板的一个实例。实质上，编译器将确定用什么类型代替每个类型形参，以及用什么值代替每个非类型形参。
       推导出实际模板实参后，编译器使用实参代替相应的模板形参产生编译该版本的函数。
       编译器承担了为我们使用的每种类型而编写函数的单调工作。
*/


// ____________________________________________________ 2.类模板 ____________________________________________________
/*
	类模板也是模板，因此必须以关键字 template 开头，后接模板形参表。

    a.除了模板形参表外，类模板的定义看起来与任意其他类问相似。类模板可以定义数据成员、函数成员和类型成员，也可以使用访问标号控制对成员的访问，
    还可以定义构造函数和析构函数等等。在类和类成员的定义中，可以使用模板形参作为类型或值的占位符，在使用类时再提供那些类型或值。

    b.与调用函数模板形成对比，使用类模板时，必须为模板形参显式指定实参.编译器使用实参来实例化这个类的特定类型版本。
*/

// 0-引子-历史-来源____________________________________________________
// 有时，有两个或多个类，其功能是相同的，仅仅是数据类型不同，如下面语句声明了一个类：

class Compare_int
{
public :
   Compare(int a,int b)
   {
      x=a;
      y=b;
   }
   int max( ) {	return (x>y)?x:y;  }
   int min( ) {	return (x<y)?x:y;  }
private :
   int x,y;
};
/*
	其作用是对两个整数作比较，可以通过调用成员函数max和min得到两个整数中的大者和小者。
	如果想对两个浮点数(float型)作比较，需要另外声明一个类：
*/
class Compare_float
{
public :
   Compare(float a,float b)
   {
      x=a;
      y=b;
   }
   float max( ) {	return (x>y)?x:y;  }
   float min( ) {	return (x<y)?x:y;  }
private :
   float x,y;
};


// 1-解决方案-横空出世____________________________________________________
/*
	显然这基本上是重复性的工作，应该有办法减少重复的工作。

	C++在发展的后期增加了模板(template )的功能，提供了解决这类问题的途径。
	可以声明一个通用的类模板，它可以有一个或多个虚拟的类型参数，如对以上两个类可以综合写出以下的类模板：
*/
template <class numtype> //声明一个模板，虚拟类型名为numtype
class Compare //类模板名为Compare
{
public :
   Compare(numtype a,numtype b)
   {
      x=a;
      y=b;
   }
   numtype max( ) {	return (x>y)?x:y;  }
   numtype min( ) {	return (x<y)?x:y;  }
private :
   numtype x,y;
};

/*
	请将此类模板和前面第一个Compare_int类作一比较，可以看到有两处不同。

1) 声明类模板时要增加一行
    template <class 类型参数名>
	template意思是“模板”，是声明类模板时必须写的关键字。在template后面的尖括号内的内容为模板的参数表列，关键字class表示其后面的是类型参数。
	在本例中numtype就是一个类型参数名。这个名宇是可以任意取的，只要是合法的标识符即可。这里取numtype只是表示“数据类型”的意思而已。
	此时，numtype并不是一个已存在的实际类型名，它只是一个虚拟类型参数名。在以后将被一个实际的类型名取代。

2) 原有的类型名int换成虚拟类型参数名numtype。
	在建立类对象时，如果将实际类型指定为int型，编译系统就会用int取代所有的numtype，如果指定为float型，就用float取代所有的numtype。这样就能实现“一类多用”。

	由于类模板包含类型参数，因此又称为【参数化的类】。如果说【类是对象的抽象，对象是类的实例，则类模板是类的抽象，类是类模板的实例】。
	利用类模板可以建立含各种数据类型的类。

	那么，在声明了一个类模板后，怎样使用它呢？怎样使它变成一个实际的类？

先回顾一下用类来定义对象的方法：
    Compare_int cmp1(4,7); // Compare_int是已声明的类
	其作用是建立一个Compare_int类的对象，并将实参4和7分别赋给形参a和b，作为进 行比较的两个整数。

	用类模板定义对象的方法与此相似，但是不能直接写成
   Compare cmp(4,7); // Compare是类模板名
	Compare是类模板名，而不是一个具体的类，类模板体中的类型numtype并不是一个实际的类型，只是一个虚拟的类型，无法用它去定义对象。
	必须用实际类型名去取代虚拟的类型，具体的做法是：
    Compare <int> cmp(4,7);
	即在类模板名之后在尖括号内指定实际的类型名，在进行编译时，编译系统就用int取代类模板中的类型参数numtype，这样就把类模板具体化了，
	或者说实例化了。这时Compare<int>就相当于前面介绍的Compare_int类。

	编译器-实例化的过程：
	类模板===>>>类===>>>对象
*/


// 一个建立,使用 类模版 的例子-例9.14：
// 	Compare.h
template <class numtype>
//定义类模版
class Compare
{
   public :
       Compare(numtype a,numtype b)
       {x=a;y=b;}
       numtype max( )
       {return (x>y)?x:y;}
       numtype min( )
       {return (x<y)?x:y;}
   private :
       numtype x,y;
};

// Compare.cpp
int main( )
{
    Compare<int> cmp1(3,7);//比较整数
    cout<<cmp1.max( )<< "is the Maximum of two integer numbers."<<endl;
    cout<<cmp1.min( )<<" is the Minimum of two integer numbers."<<endl<<endl;
    Compare<float> cmp2(45.78,93.6); //比较浮点数
    cout<<cmp2.max( )<<" is the Maximum of two float numbers."<<endl;
    cout<<cmp2.min( )<<" is the Minimum of two float numbers."<<endl<<endl;
    Compare<char> cmp3('a','A'); //比较字符
    cout<<cmp3.max( )<<" is the Maximum of two characters."<<endl;
    cout<<cmp3.min( )<<" is the Minimum of two characters."<<endl;
    return 0;
}

// 运行结果如下：
7 is the Maximum of two integers.
3 is the Minimum of two integers.

93.6 is the Maximum of two float numbers.
45.78 is the Minimum of two float numbers.

a is the Maximum of two characters.
A is the Minimum of two characters.

/*
	还有一个问题要说明： 上面列出的类模板中的成员函数是在类模板内定义的。如果改为在类模板外定义，不能用一般定义类成员函数的形式：
    numtype Compare::max( ) {…} //不能这样定义类模板中的成员函数

而应当写成类模板的形式：
*/
// Compare.cpp
template <class numtype>
numtype Compare<numtype>::max( )
{
    return (x>y)?x:y;
}
/*    
	上面第一行表示是类模板，第二行左端的numtype是虚拟类型名，后面的Compare <numtype>是一个整体，是带参的类。表示所定义的max函数是在类Compare <numtype>的作用域内的。
	在定义对象时，用户当然要指定实际的类型（如int），进行编译时就会将类模板中的虚拟类型名numtype全部用实际的类型代替。
	这样Compare <numtype >就相当于一个实际的类。大家可以将例9.14改写为在类模板外定义各成员 函数。
*/

// 	Compare.h ===================================================
template <class numtype>
//定义类模版
class Compare
{
   public :
       Compare(numtype a,numtype b);
       numtype max();
       numtype min();

   private :
       numtype x,y;
};

// Compare.cpp ===================================================
template <class numtype>
Compare<numtype>::Compare(numtype a,numtype b)
{
    x=a;
    y=b;
}

template <class numtype>
numtype Compare<numtype>::max( )
{
    return (x>y)?x:y;
}

template <class numtype>
numtype Compare<numtype>::min( )
{
    return (x<y)?x:y;
}

// 归纳以上的介绍，可以这样声明和使用类模板：
/* 
	1) 先写出一个实际的类。由于其语义明确，含义清楚，一般不会出错。

	2) 将此类中准备改变的类型名(如int要改变为float或char)改用一个自己指定的虚拟类型名(如上例中的numtype)。

	3) 在类声明前面加入一行，格式为：
	    template <class 虚拟类型参数>
	如：
	    template <class numtype> //注意本行末尾无分号
	    class Compare
	    {…}; //类体

	4) 用类模板定义对象时用以下形式：
	    类模板名<实际类型名> 对象名;
	    类模板名<实际类型名> 对象名(实参表列);
	如：
	    Compare<int> cmp;
	    Compare<int> cmp(3,7);

	5) 如果在类模板外定义成员函数，应写成类模板形式：
	   template <class 虚拟类型参数>
	   函数类型 类模板名<虚拟类型参数>::成员函数名(函数形参表列) {…}
*/

// 关于类模板的几点说明：
/*    
	1) 类模板的类型参数可以有一个或多个，每个类型前面都必须加class，如：
	    template <class T1,class T2>
	    class someclass
	    {…};
	在定义对象时分别代入实际的类型名，如：
	    someclass<int,double> obj;

	2) 和使用类一样，使用类模板时要注意其作用域，只能在其有效作用域内用它定义对象。

	3) 模板可以有层次，一个类模板可以作为基类，派生出派生模板类。有关这方面的知识实际应用较少，本教程暂不作介绍，感兴趣的同学可以自行学习。
*/


// 模板形参作用域:
/*     
    a.模板形参的名字可以在声明为模板形参之后直到模板声明或定义的末尾处使用。

    b.模板形参遵循常规名字屏蔽规则。与全局作用域中声明的对象、函数或类型同名的模板形参会屏蔽全局名字.

    c.使用模板形参名字的限制: 用作模板形参的名字不能在模板内部重用(不能再次作为类型来使用)。


    template <class T> T calc(const T &a, const T &b)
     {
         typedef double T; // error: redeclares template parameter T
         T tmp = a;
         // ...
         return tmp;
     }

    d.这一限制还意味着模板形参的名字只能在同一模板形参表中使用一次：

     // error: illegal reuse of template parameter name V
     template <class V, class V> V calc(const V&, const V&) ;
       e.当然，正如可以重用函数形参名字一样，模板形参的名字也能在不同模板中重用. 
            f.同一模板的声明和定义中，模板形参的名字不必相同。

     // all three uses of calc refer to the same function template
     // forward declarations of the template
     template <class T> T calc(const T&, const T&) ;
     template <class U> U calc(const U&, const U&) ;
     // actual definition of the template
     template <class Type>
     Type calc(const Type& a, const Type& b) {  }

    g.每个模板类型形参前面必须带上关键字 class 或 typename，每个非类型形参前面必须带上类型名字，省略关键字或类型说明符是错误的
*/


// __________________________ 用汇编的眼光看c++（之模板函数）__________________________


