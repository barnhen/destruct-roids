#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include "objects.h" 

//GLOBALS
const int WIDTH = 800;
const int HEIGHT = 400;
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5] = {false,false,false,false,false};
// don't forget to put allegro-5.0.10-monolith-md-debug.lib


void initShip(spaceShip &ship);
void drawShip(spaceShip &ship);
void moveShipUp(spaceShip &ship);
void moveShipDown(spaceShip &ship);
void moveShipLeft(spaceShip &ship);
void moveShipRight(spaceShip &ship);


//prototype
int main(void){

	bool done = false;
	bool redraw = true;
	const int FPS = 60;

	//object variables
	spaceShip ship;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	
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
	al_install_keyboard();
	//to capture keyboard events
	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);


	initShip(ship);

	//register the keyboard to eventQueue
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue,al_get_timer_event_source(timer));
	al_register_event_source(eventQueue,al_get_display_event_source(display));

	al_start_timer(timer);

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue,&ev);
		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw=true;

			if(keys[UP]){
				moveShipUp(ship);
			}
			if(keys[DOWN]){
				moveShipDown(ship);
			}
			if(keys[LEFT]){
				moveShipLeft(ship);
			}
			if(keys[RIGHT]){
				moveShipRight(ship);
			}
		
		}
		else if(ev.type  == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;

			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(eventQueue)){
			redraw = false;
			drawShip(ship);
			// when clicling on red X icon to close the game
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style	
		}
		//make sure when exiting the program exit with esc button
		
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

void moveShipUp(spaceShip &ship){
	ship.y -=ship.speed;

	if(ship.y < 0){
		ship.y = 0;
	
	}
}

void moveShipDown(spaceShip &ship){
	ship.y +=ship.speed;

	if(ship.y > HEIGHT){
		ship.y = HEIGHT;
	
	}
}


void moveShipLeft(spaceShip &ship){
	ship.x -=ship.speed;

	if(ship.x < 0){
		ship.x = 0;
	}
}

void moveShipRight(spaceShip &ship){
	ship.x +=ship.speed;

	if(ship.x > 300){
		ship.x = 300;
	}
}