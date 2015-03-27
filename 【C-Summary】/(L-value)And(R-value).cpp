

#include "(L-value)And(R-value).h"




void LvalueAndRvalue::aboutaddadd( void )
{
	int i = 1;

	++i;		// 等价于下面这个函数
	addaddVar(i);

	i++;		// 等价于下面这个函数
	VarAddAdd(i);
}

int LvalueAndRvalue::addaddVar( int &i )
{
	i = i+1;
	return i;
}

int LvalueAndRvalue::VarAddAdd( int &i )
{	
	int temp;
	temp = i;
	i = i + 1;
	return temp;
}


