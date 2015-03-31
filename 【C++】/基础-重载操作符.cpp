

// C++ 基础之 “重载操作符”
/*
	重载操作符是具有特殊名称的函数，保留字operator后接需定义的操作符符号，像其他函数一样，具有返回类型和形参表。比如下面的语句：
	Vector3 operator+(const Vector3 & a)；
	可以重载的操作符号很多：+，-，*，/，==等。
	其实我考虑的是为什么要用重载操作符，它就是特殊的函数，那直接用函数不就行了？重载操作符有什么好处？
	一个具体的例子：
*/

//Vector3.h
class Vector3{

public:
	float x,y,z;
	Vector3(){}
	Vector3(float X,float Y,float Z){
		x = X;
		y = Y;
		z = Z;
	}

	// 重载操作符+
	Vector3 operator+(const Vector3 &a){
		return Vector3(x+a.x,y+a.y,z+a.z);
	}

	// 重载操作符+=
	void operator+=(const Vector3 &a){
		x += a.x;
		y += a.y;
		z += a.z;
	}
};	

// 使用普通函数方式
Vector3 sum(const Vector3 &a,const Vector3 &b){
	return Vector3(a.x+b.x,a.y+b.y,a.z+b.z);
}


// 具体使用示例
#include "Vector3.h"
int main(int argc,char* argv[]){
	Vector3 a(1.0f,1.0f,1.0f);
	Vector3 b(1.0f,1.0f,1.0f);
	Vector3 c;
	Vector3 d;

	// 使用加法
	c = a + b;

	// 使用函数
	d = sum(a,b);

	// 使用+=
	a += b;

	return 0;
}

/*
	很简单的例子,一个3D中的向量，有x，y，z属性。使用了重载操作符后，两个向量的相加直接使用了+号即可，非常直观。
	使用sum函数相对来说需要记住函数名称，但也不错。
*/


// __________________________   __________________________


