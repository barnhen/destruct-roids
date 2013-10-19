// GuessGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int difficult=10;
char input='n'; // user's input
int lowerBound=0; // lowest possible number 
int upperBound=difficult +1; // highest possible number left
int myGuess=0; //my current guess
int lastGuess= -1; //my last guess

bool MainMenu(){
	cout <<"Welcome to the game"<<endl<<endl;
	while(true){
		cout<<"1. Play the Game"<<endl;
		cout<<"2. Exit"<<endl;
		cout<<">";
		cin>>input;

		if (input=='1')
			return true; // this play the game
		else if (input=='2')
			return false; // this will quit
	}

}


// this could show a little cutscene intro story.
// I've used to dsiplay some instructions.
void ShowStory(){
	input='n'; // just to make sure the input is not 'y'
	cout<<"Once upon a time..."<<endl;
	cout<<"You thought a number between 0 and "<<difficult<<endl;
	while (input!='y'){
		cout<<"Have you got one (y/n)";
		cin>>input;
		if(input!='y') 
			cout<<"Ok, I'll wait a bit..."<<endl;
	}
	cout<<endl;
}

void ResetGame(){
	lowerBound=0; 
	upperBound=difficult+1;
	input='n';

}

bool UpdateWorld(){
	myGuess = (lowerBound + upperBound)/2; // generaets the next guess

	if(lastGuess == myGuess){
		cout<<"You've cheated :("<<endl;
		return false; //quit
	}
	lastGuess = myGuess;
	return true;//all godd keep going
}

void DrawGraphics(){
	cout<<"I think it's "<<myGuess<<"! Am I right?"<<endl;
	cout<<"l. lower"<<endl;
	cout<<"h. higher"<<endl;
	cout<<"y. yes"<<endl;
}

void GetInput(){
	cin>>input; // read something from the keyboard

	//act on input:

	switch(input){
	case 'l' : 
		upperBound = myGuess; 
		break;
	case 'h':
		lowerBound = myGuess;
		break;
	case 'y':
		cout<<"Yay!!!"<<endl;
		break;
	}
}

bool GameOverScreen(){
	cout<<endl;
	cout<<"That was pretty cool, play again (y/n)?"<<endl;
	cin>>input;

	if (input =='y')
		return true;
	else
		return false;
}


bool PlayGame(){
	ShowStory(); //show the game story
	ResetGame(); // reset all variable to their original values
	while(input!='y'){ // this is the main game loop
		UpdateWorld();

		DrawGraphics();

		GetInput();
	}

	return GameOverScreen();

}
int main()
{
	while(MainMenu()){ // while they say they want to play
		while(PlayGame()); // repeatdly run the game loop
	}
	return 0;
}

