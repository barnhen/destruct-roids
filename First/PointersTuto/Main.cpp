#include <iostream>
using namespace std;

/*
void Add25(int a){
	a= a+25; // although here it will be 35
}

int main (){
	int a=10;
	Add25(a);
	cout<<a<<endl;// this way  a will remain 10
	system("pause");
	return 0;
}
*/

/*
//passing by pointer
void Add25(int *a){
	*a= *a+25; // 
}

int main (){
	int a=10;
	Add25(&a);
	cout<<a<<endl;// 
	system("pause");
	return 0;
}
*/

// pass by reference
void Add25(int &a){
	a= a+25; // 
}

int main (){
	int a=10;
	Add25(a);
	cout<<a<<endl;// 
	system("pause");
	return 0;
}

