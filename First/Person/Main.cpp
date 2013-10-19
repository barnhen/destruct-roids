#include <iostream>
#include<stdlib.h>

class Person{
public:
	int age;
	float height,weight;
	Person();
};

Person::Person(){
	age=(rand() % 76) +25; //mean between 25 to 100
	weight=(rand() % 50) +50; //mean between 25 to 100
	height=(rand() % 50) +50; //mean between 25 to 100
}

class House{
public:
	Person* people;
	House(); //constructor
	~House();// destructor
};

House::House(){
	people = new Person[rand() % 5+1];
};

House::~House(){
	delete[] people; // finishing constructed people object
};

class Town{
public:
	House* houses;

	Town(){
		houses = new House[1000];
	}

	~Town(){
		delete[] houses;
	}
};

using namespace std;
int main (){
	Town t;
	// if you wann use new() you have always to use pointer
	//Person* person = new Person[5]; // 5 persons
	/*
	for (int i =0; i < 5; i++){
		cout<<"person age"<<person[i].age();
	}
	for (int i =0; i < 5; i++){
		person[i].fly();
	}
	*/
	//delete[] person;


return 0;
}