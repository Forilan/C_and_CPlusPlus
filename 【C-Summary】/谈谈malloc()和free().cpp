﻿

// 谈谈malloc()和free()		-	malloc()和free()里的学问
/*
	http://www.nowamagic.net/librarys/veda/detail/2427
	真正的原文：
	http://www.bccn.net/Article/kfyy/cyy/jszl/200608/4238_2.html

	比较深入的文章————浅析malloc（）的几种实现方式：
	http://www.cnblogs.com/dongzhiquan/archive/2009/06/27/1994838.html
*/


/*
	对于串的顺序存储，有些需要补充说明。串值的存储空间可在程序执行过程中动态分配而得。
比如在计算机中存在一个自由存储区，叫做“堆”。这个堆可由C语言的动态分配函数malloc()和free()来管理。
	那么今天就来点题外话，谈谈malloc()和free()
*/    


// __________________________ malloc()和free()的基本概念以及基本用法 __________________________
// 1. 函数原型及说明：
/*
	void *malloc(long NumBytes)：该函数分配了NumBytes个字节，并返回了指向这块内存的指针。
如果分配失败，则返回一个空指针（NULL）。

关于分配失败的原因，应该有多种，比如说空间不足就是一种。

void free(void *FirstByte)： 该函数是将之前用malloc分配的空间还给程序或者是操作系统，
也就是释放了这块内存，让它重新得到自由。
*/	


// 2. 函数的用法：
/*
	其实这两个函数用起来倒不是很难，也就是malloc()之后觉得用够了就甩了它把它给free()了，举个简单例子：
*/	

// Code...
char *Ptr = NULL;
Ptr = (char *)malloc(100 * sizeof(char));
if (NULL == Ptr)
{
	exit (1);
}
gets(Ptr);
// code...
free(Ptr);
Ptr = NULL;
// code...


/*
	就这样.当然，具体情况要具体分析以及具体解决。比如说，你定义了一个指针，
	在一个函数里申请了一块内存然后通过函数返回传递给这个指针，那么也许释放这块内存这项工作就应该留给其他函数了。
*/	


// 3. 关于函数使用需要注意的一些地方：
/*
		申请了内存空间后，必须检查是否分配成功。
	当不需要再使用申请的内存时，记得释放；释放后应该把指向这块内存的指针指向NULL，防止程序后面不小心使用了它。
	这两个函数应该是配对。如果申请后不释放就是内存泄露；如果无故释放那就是什么也没有做。释放只能一次，
	如果释放两次及两次以上会出现错误（释放空指针例外，释放空指针其实也等于啥也没做，所以释放空指针释放多少次都没有问题）。
	虽然malloc()函数的类型是(void *),任何类型的指针都可以转换成(void *),但是最好还是在前面进行强制类型转换，因为这样可以躲过一些编译器的检查。	
*/	

// __________________________ malloc()到底从哪里得来了内存空间？ __________________________

// 1. malloc()到底从哪里得到了内存空间？

typedef struct NODE
{
	int				value;			// 空间大小？
	void*			address;		// 空间初始地址? 【这个结构体是我猜的】
	struct NODE *	next;
}HeapNode,*LinkHead;					// LinkHead 是头指针，*LinkHead 是头结点

/*
	答案是从堆里面获得空间。也就是说函数返回的指针是指向堆里面的一块内存。操作系统中有一个记录空闲内存地址的链表。当操作系统收到程序的申请时，
	就会遍历该链表，然后就寻找第一个空间大于所申请空间的堆结点，然后就将该结点从空闲结点链表中删除，并将该结点的空间分配给程序。就是这样！

	说到这里，不得不另外插入一个小话题，相信大家也知道是什么话题了。
	什么是堆？说到堆，又忍不住说到了栈！什么是栈？下面就另外开个小部分专门而又简单地说一下这个题外话：

什么是堆：堆是大家共有的空间，分全局堆和局部堆。全局堆就是所有没有分配的空间，局部堆就是用户分配的空间。堆在操作系统对进程 初始化的时候分配，
运行过程中也可以向系统要额外的堆，但是记得用完了要还给操作系统，要不然就是内存泄漏。

什么是栈：栈是线程独有的，保存其运行状态和局部自动变量的。栈在线程开始的时候初始化，每个线程的栈互相独立。每个函数都有自己的栈，
栈被用来在函数之间传递参数。操作系统在切换线程的时候会自动的切换栈，就是切换SS/ESP寄存器。栈空间不需要在高级语言里面显式的分配和释放。

通过上面对概念的描述，可以知道：

栈是由编译器自动分配释放，存放函数的参数值、局部变量的值等。操作方式类似于数据结构中的栈。
堆一般由程序员分配释放，若不释放，程序结束时可能由OS回收。注意这里说是可能，并非一定。所以我想再强调一次，记得要释放。
注意它与数据结构中的堆是两回事，分配方式倒是类似于链表。（这点我上面稍微提过）

所以，举个例子，如果你在函数上面定义了一个指针变量，然后在这个函数里申请了一块内存让指针指向它。实际上，这个指针的地址是在栈上，
但是它所指向的内容却是在堆上面的。所以，再想想，在一个函数里申请了空间后，比如说下面这个函数：
*/	

void Function(void)
{
    char *p = (char *)malloc(100 * sizeof(char));
}

/*
	就这个例子，千万不要认为函数返回，函数所在的栈被销毁指针也跟着销毁，申请的内存也就一样跟着销毁了，这绝对是错误的。
	因为申请的内存在堆上，而函数所在的栈被销毁跟堆完全没有啥关系。所以，还是那句话：记得释放。
*/

// 2. free()到底释放了什么?
/*
	这个问题比较简单，其实我是想和第二大部分的题目相呼应而已。free()释放的是指针指向的内存。注意，释放的是内存，不是指针。
	这点非常非常重要。指针是一个变量，只有程序结束时才被销毁。释放了内存空间后，原来指向这块空间的指针还是存在。只不过现在指针指向的内容的垃圾，
	是未定义的，所以说是垃圾。因此，前面我已经说过了，释放内存后把指针指向NULL，防止指针在后面不小心又被解引用了。
*/	

// __________________________ malloc()以及free()的机制 __________________________	


/*
	仔细看一下free()的函数原型，也许也会发现似乎很神奇，free()函数非常简单，只有一个参数，只要把指向申请空间的指针传递给free()中的参数就可以完成释放工作。
	这里要追踪到malloc()的申请问题了。申请的时候实际上占用的内存要比申请的大。因为超出的空间是用来记录对这块内存的管理信息。
	先看一下在《UNIX环境高级编程》中第七章的一段话：
*/	

/*
	大多数实现所分配的存储空间比所要求的要稍大一些，额外的空间用来记录管理信息——分配块的长度，指向下一个分配块的指针等等。
	这就意味着如果写过一个已分配区的尾端，则会改写后一块的管理信息。这种类型的错误是灾难性的，但是因为这种错误不会很快就暴露出来，
	所以也就很难发现。将指向分配块的指针向后移动也可能会改写本块的管理信息。
*/	

/*
	以上这段话已经给了我们一些信息了。malloc()申请的空间实际我觉得就是分了两个不同性质的空间。一个就是用来记录管理信息的空间，
	另外一个就是可用空间了。而用来记录管理信息的实际上是一个结构体。在C语言中，用结构体来记录同一个对象的不同信息是天经地义的事。
	下面看看这个结构体的原型：
*/		

struct mem_control_block
{
    int is_available;    //这是一个标记？
    int size;            //这是实际空间的大小
};

/*
	free()就是根据这个结构体的信息来释放malloc()申请的空间。而结构体的两个成员的大小我想应该是操作系统的事了。
	但是这里有一个问题，malloc()申请空间后返回一个指针应该是指向第二种空间，也就是可用空间。
	不然，如果指向管理信息空间的话，写入的内容和结构体的类型有可能不一致，或者会把管理信息屏蔽掉，那就没法释放内存空间了，所以会发生错误。

	下面看看free()的源代码，我自己分析了一下，觉得比起malloc()的源代码倒是容易简单很多。
*/	

void free(void *ptr)
{
    struct mem_control_block *free;
    free = ptr - sizeof(struct mem_control_block);
    free->is_available = 1;
    return;
}

// free 多少空间由malloc决定，在malloc时相关信息其中包括长度都已建立，malloc并不仅仅分配你所指定的大小的内存，还建立一系相关的数据
// 也就是说free(void *p)里的参数只能是申请时返回的指针了。

/*
看一下函数第二句，这句非常重要和关键。其实这句就是把指向可用空间的指针倒回去，让它指向管理信息的那块空间，因为这里是在值上减去了一个结构体的大小。

后面那一句free->is_available = 1; 我的想法是：这里is_available应该只是一个标记而已，因为从这个变量的名称上来看，

is_available 翻译过来就是“是可以用”。 我觉得变量名字可以反映一个变量的作用，特别是严谨的代码。这是源代码，所以我觉得绝对是严谨的。

这个变量的值是1，表明是可以用的空间。只是这里我想了想，如果把它改为0或者是其他值不知道会发生什么事？但是有一点我可以肯定，

就是释放绝对不会那么顺利进行。因为这是一个标记。

当然，这里可能还是有人会有疑问，为什么这样就可以释放呢？我刚才也有这个疑问。后来我想到，释放是操作系统的事，那么就free()这个源代码来看，

什么也没有释放，对吧？但是它确实是确定了管理信息的那块内存的内容。所以，free()只是记录了一些信息，然后告诉操作系统那块内存可以去释放，

具体怎么告诉操作系统的我不清楚，但我觉得这个已经超出了我这篇文章的讨论范围了。

那么，我之前有个错误的认识，就是认为指向那块内存的指针不管移到那块内存中的哪个位置都可以释放那块内存。

但是，这是错的。释放是不可以释放一部分的。首先这点应该要明白。而且，从free()的源代码看，ptr只能指向可用空间的首地址，不然，

减去结构体大小之后一定不是指向管理信息空间的首地址。所以，要确保指针指向可用空间的首地址。

自己可以写一个程序然后移动指向可用空间的指针，看程序会有会崩。

最后可能想到malloc()的源代码看看malloc()到底是怎么分配空间的，这里面涉及到很多其他方面的知识。

总结：free()其实只是将分配的内存归还给操作系统，让其可以再malloc。但是对于其原先malloc时的指针不会有任何影响。

free()后一定要将指针置为NULL。
*/	


/*
http://www.bccn.net/Article/kfyy/cyy/jszl/200608/4238_2.html
四、关于其他：

    关于C中的malloc()和free()的讨论就写到这里吧！写了三个钟头，感觉有点累！希望对大家有所帮助！有不对的地方欢迎大家指出！最后
，谢谢参与这个帖子讨论的所有朋友，帖子：http://bbs.bccn.net/thread-81781-1-1.html 。也谈到版权问题，如果哪位想转载这篇文章（如果我有这个荣幸的话），最起码请标明“来自bccn C语言论坛”这几个字眼，我的ID可以不用写上！谢谢合作！


五、参考文献：（只写书名）

——《UNIX环境高级编程》

——《计算机组成原理》

——《高质量C/C++编程指南》

                                                                                                    ID：lj_860603(键键)

                                                                                                    2006.8.4   初稿
*/		