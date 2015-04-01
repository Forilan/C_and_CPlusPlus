﻿

// const引用与非const引用
/*	文章来源： 
	c++ const引用与非const引用介绍
	http://www.jb51.net/article/33674.htm

	关于引用与临时变量  
	http://blog.163.com/shengxi_286/blog/static/3874831420081012114638348/
*/ 


// __________________________ 1 const引用与非const引用 __________________________

// const引用是指向const对象的引用。 
const int i = 10; 
const int &ref = i; 
/*
	可以读取ref，但不能修改。这样做是有意义的，因为i本身就不可修改，当然也不能通过ref来修改了。
	所以也就有将const变量赋值给非const引用是非法的。 
*/
int &ref1 = i; // error: nonconst reference to a const object 	


/*
	非const引用是指向非const类型变量的引用。 
	【const引用可以初始化为不同类型的对象或者右值（如字面值常量）】，但非const引用不可以。 
*/
// legal for const references only 
int i = 10; 
const int & ref = 42; 
const int & ref1 = 1.618 + i; 
double d = 3.14; 
const int &ref2 = d; 

// 以绑定到不同类型的ref2为例解释原因，编译器会把ref2相关的代码转换如下： 
int temp = d; 
const int &ref2 = temp; // bind ref2 to temporary 

/*
	ref2实际上是绑定到一个临时变量上，如果ref2不为const，那么按道理就可以通过修改ref2而修改d的值，但实际上d并不会改变。
	所以为了避免这个问题，ref2只能是const。 

	非const引用只能绑定到与该引用同类型的对象，【const引用则可以绑定到不同但相关的类型的对象或绑定到右值】。
*/	


// __________________________ 2 引用与临时对象 __________________________
/*

*/




// 3 关于 临时对象 的生命周期 __________________________
/*
	问：如果一个函数返回一个临时变量，const引用绑定这个临时变量，那么它会延长这个临时变量的寿命与自己一样？

	答：返回的是临时变量而不是临时变量的地址，所以会复制生成一个临时对象，引用绑定的实际是那个临时对象，和函数内的临时变量没有关系了
*/	


//  可以如下验证：   
  int   x   =   1,   y   =   1;   
  const   int   &i   =   x   +   y;  
/*   
  表达式“x   +   y”产生一个临时变量。【临时变量的生命周期是该语句的结束】（语句结束以后就会自动析构）——C++语言里面就是这么界定的。
  不过，有一个例外（考虑到操作符重载等因素，C++引入了引用这个概念），【引用可以让被引用的临时对象的生命周期延迟到该引用的析构处】。
  而，指针就没有被赋予这么好的待遇了。   
*/	

//  如：   
  int x = 1, y = 1;   
  const int &i  = x + y;   
  const int *pi = &i;   
    
/*
  这里的pi（指向的是一个临时对象的地址）所指对象的生命周期是与指针本身的生命周期无关的，由被指的对象的生命周期决定。  
*/


 /*
	1、“&”运算符必须要求被运算的对象是一个左值（可以被修改的变量）。   
  	所以有这一说法：hinking   in   C++书中说无法将临时变量的地址传递给指针的函数。   
  	2、由于上面的原因，不能为一个临时变量取地址。机器层面来说临时变量是能取地址的，而语法层面，C++是不允许对临时变量取地址的，编译将无法通过	
*/	

