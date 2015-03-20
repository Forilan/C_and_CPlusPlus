

//#include "Chapter12.h"


// 第12章 使用结构和指针
/*
	本章我们将深入讨论一些使用结构和指针的技巧。我们将花许多时间讨论一种称为链表的数据结构，
	这不仅因为它非常有用，而且许多用于操纵链表的技巧也适用于其他数据结构。
*/

// __________________________12.1链表__________________________
/*
	链表（linked list）就是一些包含数据的独立数据结构(通常称为节点)的集合。链表中的每个节点通过链表或指针连接在一起。
	程序通过指针访问链表中的节点。通常节点是动态分配的，但有时你也能看到由节点数组构建的链表。
	既使在这种情况下，程序也是通过指针来遍历链表的。
*/


// __________________________12.2单链表__________________________
/*
	在单链表中，每个节点包含一个指向链表下一节点的指针。链表最后一个节点的指针字段的值为NULL，
	提示链表后面不再有其他节点。在你找到链表的第1个节点后，指针就可以带你访问剩余的所有节点。
	为了记住链表的起始位置，可以使用一个根指针。根指针指向链表的第1个节点。注意根指针只是一个指针，它不包含任何数据。

	本例中的节点是用下面的声明创建的结构
*/
typedef struct NODE
{
	struct NODE *link;
	int			value;
}Node;

/*
	存储于每个节点的数据是一个整型值。
	单链表可以通过链从开始位置遍历链表直到结束位置，但链表无法从相反的方向进行遍历。
*/

// 12.2.1 在单链表中插入
/*
	我们怎样才能把一个新节点插入到一个有序的单链表中呢？假定我们有一个新值，比如12，
	想把它插入到前面那个链表中。概念上说：
	从链表的起始位置开始，跟随指针直到找到第1个值大于12的节点，
	然后把这个新值插入到那个节点之前的位置。

	但是当我们找到要插入的节点时，我们已经越过了这个节点，无法返回去。
	解决这个问题的办法就是始终保存一个指向链表当前节点之前的那个节点的指针。
*/


#define FALSE 	0
#define TRUE    1

// 程序12.1 是我们的第1次尝试____________________________________________________
int fir_insert(Node *current, int new_value)
{
	Node *previous;
	Node *newNode;

	// 寻找正确的插入位置，方法是按顺序访问链表，直到到达其值大于或等于新插入值的节点
	while(current->value < new_value)
	{
		previous = current;
		current = current->link;
	}

	// 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，函数返回 false.
	newNode = (Node *)malloc(sizeof(Node));
	if ( newNode == NULL)
	{
		return FALSE;		
	}
	newNode->value = new_value;

	// 把新节点插入到链表中，并返回TRUE
	newNode->link = current;
	previous->link = newNode;
	
	return TRUE;
} 
// BUG问题1，如果第1个节点的数值就比 12 大呢，
// BUG问题2，如果到最后1个节点都没有找到 比12大的呢。那就插入到最后一个节点。

// 程序12.2 是我们的第2次尝试____________________________________________________
int sec_insert(Node  **proot, int new_value)
{
	Node *current = *proot;			// 这条语句对根指针参数执行间接访问操作，得到的结果是root的值
	Node *previous = NULL;
	Node *newNode;


	// 寻找正确的插入位置，方法是按顺序访问链表，直到到达其值大于或等于新插入值的节点
	while( ( NULL != current )&&	// 如果到达 尾节点了。
		( current->value < new_value ) )
	{
		previous = current;
		current = current->link;
	}


	// 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，函数返回 false.
	newNode = (Node *)malloc(sizeof(Node));
	if ( newNode == NULL)return FALSE;
	newNode->value = new_value;

	// 把新节点插入到链表中，并返回TRUE
	newNode->link = current;

	// 如果第1个节点的数值就比 new_value 大。那么 previous 的值就没有改变过。
	if( NULL == previous )
	{
		*proot = newNode;
	}else{
		previous->link = newNode;
	}

	return TRUE;
} 

result = sec_insert(&root,12);

// 优化1，里面变量太多，可不可以把 previous取消掉。

// 程序12.3 插入到一个有序的单链表：最终版本____________________________________________________
int thr_insert(Node  **pRoot, int new_value)
{
	Node *current = *pRoot;			// 这条语句对根指针参数执行间接访问操作，得到的结果是root的值
	Node *newNode;


	// 寻找正确的插入位置，方法是按顺序访问链表，直到到达其值大于或等于新插入值的节点
	while( ( NULL != current )&&	// 如果到达 尾节点了。
		( current->value < new_value ) )
	{
		pRoot = &current->link;
		current = *pRoot;
	}

	// 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，函数返回 false.
	newNode = (Node *)malloc(sizeof(Node));
	if ( newNode == NULL)return FALSE;
	newNode->value = new_value;

	// 把新节点插入到链表中，并返回TRUE
	newNode->link = current;		// 即使 current 是NULL也没有关系了
	*pRoot = newNode;
	return TRUE;
} 

result = thr_insert(&root,12);

/*	提示
	消除了对1个节点 进行插入了这个特殊情况使这个函数更为简单。这个改进之所以可行是由两方面的因素。
	
	第1个因素是 我们正确解释问题的能力。除非你可以在看上去不同的操作中总结出共性，
不然你只能编写额外的代码来处理特殊情况。通常，这种知识只有在你学习了一阵数据结构并对其有进一步的理解之后才能获得。
	第2个因素是C语言提供了正确的工具帮助你归纳问题的共性。

	这个改进的函数依赖于C能够取得现存对象的地址这一能力。和许多C语言特性一样，这个能力既威力巨大，又暗藏凶险。
*/

/*	警告
	C的指针限制要少得多，这也是我们能改进插入函数的原因所在。另一方面，C程序员在使用指针时必须加倍小心，
	以避免产生错误。
	Pascal语言的指针哲学有点类似下面这样的说法：“使用锤子可能会伤着你自己，所以我们不给你锤子”
	C语言的指针哲学则是：“给你锤子，实际上你可以使用好几种锤子。祝你好运！”

	有了这个能力之后，C程序较之Pascal程序员更容易陷入麻烦，但优秀的C程序员可以比他们的Pascal和Modula同行产生体积
	更小，效率更高，可维护性更佳的代码。

	这也是C语言在业界为何如此流行以及经验丰富的C程序员为何如此受欢迎的原因之一。
*/

// 12.2.2 其他链表操作
/*
	为了让单链表更加有用，我们需要增加更多的操作，如查找和删除。但是用于这些操作的算法非常直截了当，很容易用插入函数所说明的技巧来实现。
	因此，我把这些函数留作练习。
*/	

// 练习题：查找____________________________________________________
Node * fir_find(Node  **pRoot, int find_value)
{
	Node *current = *pRoot;			// 这条语句对根指针参数执行间接访问操作，得到的结果是root的值

	// 寻找 值相同的 节点
	while( ( NULL != current )&&	// 如果到达 尾节点了。
		( current->value != find_value ) )
	{
		pRoot = &current->link;
		current = *pRoot;
	}

	return current;			// current 有可能为NULL，表示到尾节点了都没有找到，正好就返回NULL
} 

// 练习题：删除
int fir_delete(Node  **pRoot, int delete_value)
{
	Node *current = *pRoot;			// 这条语句对根指针参数执行间接访问操作，得到的结果是root的值
	Node *delete;

	// 寻找 值相同的 节点____________________________________________________
	while( ( NULL != current )&&	// 如果到达 尾节点了。
		( current->value != delete_value) )
	{
		pRoot = &current->link;
		current = *pRoot;
	}

	// 没有找到要删除的值
	if( NULL == current ) return FALSE;

	//
	delete = *pRoot;
	*pRoot = current->link;

	// 把删除节点释放，并返回TRUE,这样free到底可不可以啊
	free(delete);
	return TRUE;
} 


// __________________________12.3双链表__________________________
/*
	单链表的替代方案就是双链表，在一个双链表中，每个节点都包含两个指针————指向前一个节点的指针和指向后一个节点的指针。
	这可以使我们以任何方向遍历双链表，甚至可以忽前忽后地在双链表中访问。

	下面是节点类型的声明
*/
typedef struct NODE
{
	struct NODE *fwd;
	struct NODE *bwd;
	int 		value;
} Node;	

/*
	现在，存在两个根指针：一个指向链表的第一个节点，另一个指向最后一个节点。
	这两个指针允许我们从链表的任何一端开始遍历链表。然后这不是个循环双向链表。
	只是个双链表。
*/

//12.3.1 在双链表中插入
/*
	这一次，我们要编写一个函数，把一个值插入到一个有序的双链表中。fir_insert函数接受两个参数：
	一个指向根节点的指针和一个整型值。

	当我们把一个节点插入到一个双链表时，可能出现4种情况：
	1 新值可能插入到链表的中间位置
	2 新值可能插入到链表的起始位置
	3 新值可能插入到链表的结束位置
	4 新值可能必须插入到链表的起始位置，又插入到链表的结束位置（即原链表为空）
*/

// 程序12.4 简明的双链表插入函数____________________________________________________
int fir_insert(Node * pRoot,int new_value)
{
	Node *this;
	Node *next;
	Node *newNode;

	/*
		循环查找，如果有值与要插入的值相等，就返回失败。
		this 指向应该在新节点之前的那个节点。
		next 指向应该在新节点之后的那个节点。
	*/ 
	for( this = pRoot; (next = this->fwd ) != NULL ;this = next)
	{
		if( this->value ==  new_value ) return FALSE;
		
		if (next->value<new_value) break;
	}


	// 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，函数返回 false.
	newNode = (Node *)malloc(sizeof(Node));
	if ( newNode == NULL )return FALSE;
	newNode->value = new_value;

	// 把新节点插入到链表中，并返回TRUE
	if( pRoot->fwd == NULL )		//对空链表的插入。
	{
		pRoot->fwd = newNode;
		pRoot->bwd = newNode;

		newNode->fwd = NULL;
		newNode->bwd = NULL;
	}else if( pRoot == this )		//插入到链表的起始位置
	{
		pRoot->fwd = newNode;
		newNode->fwd = next;
		newNode->bwd = NULL;
		next->bwd = newNode;

	}else if( (NULL == next)&&(pRoot != this) )		//插入到链表的结束位置.
	{
		this->fwd = newNode;
		newNode->fwd = next;
		newNode->bwd = this;
		pRoot->bwd = newNode;
	}else{							//在中间插入这种情况。好像和上面可以合并起来
		this->fwd = newNode;
		newNode->fwd = next;
		newNode->bwd = this;
		next->bwd = newNode;
	}

	return TRUE;
}


/*
	优化1，各个if语句群存在大量的相似之处，而优秀的程序将会对程序中出现这么多的重复代码感到厌烦。
	所以下面使用两个技巧消除这些重复的代码。
	优化2，逻辑
	第1个技巧：语句提炼。
	第1个技巧：逻辑提炼。
*/ 

// 程序12.5 优化的双链表插入函数____________________________________________________
int fir_insert(Node * pRoot,int new_value)
{
	Node *this;
	Node *next;
	Node *newNode;

	/*
		循环查找，如果有值与要插入的值相等，就返回失败。
		this 指向应该在新节点之前的那个节点。
		next 指向应该在新节点之后的那个节点。
	*/ 
	for( this = pRoot; (next = this->fwd ) != NULL ;this = next)
	{
		if( this->value ==  new_value ) return FALSE;
		
		if (next->value<new_value) break;
	}


	// 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，函数返回 false.
	newNode = (Node *)malloc(sizeof(Node));
	if ( newNode == NULL )return FALSE;
	newNode->value = new_value;

	// 把新节点插入到链表中，并返回TRUE

	newNode->fwd = next;
	this->fwd = newNode;


	if( pRoot != this ){
		newNode->bwd = this;
	}else{
		newNode->bwd = NULL;
	}

	if( NULL != next){
		next->bwd = newNode;
	}else{
		pRoot->bwd = newNode;
	}

/* 上面为提炼了逻辑的版本
	if( pRoot->fwd == NULL )		//对空链表的插入。
	{
		pRoot->bwd = newNode;
		newNode->bwd = NULL;
		return TRUE;
	}else if( pRoot == this )		//插入到链表的起始位置
	{	
		newNode->bwd = NULL;
	}else if( (NULL == next)&&(pRoot != this) )		//插入到链表的结束位置.
	{
		next = pRoot;
		newNode->bwd = this;
	}else{							//在中间插入这种情况。好像和上面可以合并起来
		newNode->bwd = this;
	}
	next->bwd = newNode;
*/

	return TRUE;
}	


//12.3.2 其他链表操作
/*
	和单链表一样，双链表也需要更多的操作。本章的编程练习将给你更多的实践机会来编写它们。
*/

// __________________________12.4总结__________________________
/*
	单链表只能以一个方向进行遍历。
*/


// __________________________12.8编程练习__________________________

/*
	☆1.编写一个函数，用于计数一个单链表的节点数。它的唯一参数就是一个指向链表第1个节点的指针。
	    编写这个函数时，你必须知道哪些信息？这个函数还能用于执行其他任务吗？
*/
typedef struct NODE
{
	struct NODE *link;
	int			value;
}Node;

int sum_node(Node * pRoot)
{
	int sum;
	for( sum = 0; pRoot != NULL; sum++ )
	{
		pRoot = pRoot->link;
	}
	return sum;
}


/*
	☆2.编写一个函数，在一个无序的单链表中寻找一个特定的值，并返回一个指向该节点的指针。
	如果想让这个函数适用于有序的单链表，需不需要对它作些修改。
*/

/*
	☆☆☆☆4.编写一个函数，反序排列一个单链表的所有节点。
	函数的参数指向链表的第1个节点。当链表被重新排之后，函数返回一个指向链表新头节点的指针。
	链表最后一个节点的link字段的值应设置为NULL，在空链表（first == NULL）上执行这个函数将返回NULL.
*/