#include <iostream>

using namespace std;

class Bird{
private:
	int height;
	void flapWings();
public:
	void reset();
	void fly();
};

void Bird::flapWings(){
	height += rand() % 100;
}

void Bird::reset(){
	height=0;
}

void Bird::fly(){
	flapWings();
}

int main (){
/*
	Bird Sparrow;

	Sparrow.reset();

	Sparrow.fly();
*/

	Bird FlockOfSparrows[1024];

	for (int i =0; i < 1024; i++){
		FlockOfSparrows[i].reset();
	}
	for (int i =0; i < 1024; i++){
		FlockOfSparrows[i].fly();
	}

	return 0;
}