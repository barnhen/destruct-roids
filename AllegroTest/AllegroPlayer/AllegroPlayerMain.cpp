#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include "objects.h"

//GLOBALS
const int WIDTH = 800;
const int HEIGHT = 400;
// don't forget to put allegro-5.0.10-monolith-md-debug.lib


void initShip(spaceShip &ship);
void drawShip(spaceShip &ship);



//prototype
int main(void){

	bool done = false;
	
	//object variables
	spaceShip ship;

	ALLEGRO_DISPLAY *display = NULL;
	

	
	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		return -1;
	}

	display = al_create_display(WIDTH,HEIGHT);
	

	//check if display was created
	if(!display){
		return -1;
	}

	al_init_primitives_addon();
	initShip(ship);

	while(!done){
	
		drawShip(ship);
		//make sure when exiting the program exit with esc button
		
		// when clicling on red X icon to close the game
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style	
	}

	//al_rest(5.0);
	al_destroy_display(display);
//hadouken

return 0;
}

void initShip(spaceShip &ship){
	ship.x = 20;
	ship.y = HEIGHT/2; // starts in the middle of screen 
	ship.id = PLAYER;
	ship.lives = 3;
	ship.speed = 7;
	ship.boundx = 6;
	ship.boundy = 7;
	ship.score = 0;
}

void drawShip(spaceShip &ship){
	//turrets
	al_draw_filled_rectangle(ship.x,ship.y - 9,ship.x + 10,ship.y - 7,al_map_rgb(255,0,0));
	al_draw_filled_rectangle(ship.x,ship.y + 9,ship.x + 10,ship.y + 7,al_map_rgb(255,0,0));

	//ship body
	al_draw_filled_triangle(ship.x - 12,ship.y - 17,ship.x + 12,ship.y,ship.x - 12,ship.y + 17,al_map_rgb(0,255,0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2,ship.x + 15, ship.y + 2, al_map_rgb(0,0,255));
	
}