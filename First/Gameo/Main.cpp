#include <iostream>
#include <ctime> //generate  time
#include <stdlib.h> //generate random 
#include <conio.h> //for _getch
using namespace std;

struct Map_Tile{
	char tileCharacter;
	bool walkable;
};

//what about the player?
struct Point{
	int x,y;
} playerPos; //you can declare instances of your struct just like this playerPos

int const MapWidth=20;
int const MapHeight=20;

Map_Tile map [MapWidth][MapHeight];

void generateMap(){
	srand(time(NULL));
	for(int y =0; y < MapHeight;y++){
		for(int x =0; x < MapWidth;x++){
			int t = rand() % 20; // rand generates random number/even number gets 0;odd number gets 1
			if (t == 0){
				map[x][y].tileCharacter = '#'; // implies you hit a wall for example
				map[x][y].walkable = false;
			}else{
				map[x][y].tileCharacter = '.'; // implies you can move
				map[x][y].walkable = true;
			}
		}	
	}
	map[0][0].tileCharacter = '.';
	map[0][0].walkable = true;
}

void printMap(){
	for(int y =0; y < MapHeight;y++){
		for(int x =0; x < MapWidth;x++){
			if (x == playerPos.x && y == playerPos.y)
				cout<<"@";
			else
				cout<<map[x][y].tileCharacter;
		}
		cout<<endl;
	}

}

int main (){
	//m.tileCharacter = '%';
	//m.walkable =false;
	playerPos.x=0;
	playerPos.y=0;

	generateMap();

	char option = 'n';

	while(true){
		printMap();
		cout<<"N, S, E or W or Q for Quit"<<endl;
		cout<<">";
		cin>>option;

		/*
		if the player hit 'N' AND the y value is something 
		other than the value of top AND if when they try to walk 
		there is a wall

		*/
		if (option=='N' && playerPos.y > 0 && map[playerPos.x][playerPos.y-1].walkable !=0){
			playerPos.y--;
		}
		if (option=='S' && playerPos.y < MapHeight - 1 && map[playerPos.x][playerPos.y+1].walkable !=0){
			playerPos.y++;
		}
		if (option=='E' && playerPos.x < MapWidth - 1 && map[playerPos.x+1][playerPos.y].walkable !=0){
			playerPos.x++;
		}
		if (option=='W' && playerPos.x > 0 && map[playerPos.x-1][playerPos.y].walkable !=0){
			playerPos.x--;
		}
		if (option=='Q'){
			break;
		}

	}
	//_getch();

	return 0;
}