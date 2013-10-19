#include <iostream>
#include "Volume.h"

using namespace std;

int main(){
	double depth, width, lenght;

	cout.precision(10);
	cout<<"Hoe deep do you want your pool?"<<endl; 
	cin>>depth;

	cout<<"And how wide?"<<endl;
	cin>>width;

	cout<<"And how long?"<<endl;
	cin>>lenght;

	cout<<"Your pool will hold "<<CalculateVolume(depth,width,lenght)<<endl;

	
	//
	//system("pause");
	return 0;
	

}