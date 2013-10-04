#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include "objects.h"

// don't forget to put allegro-5.0.10-monolith-md-debug.lib
//GLOBALS
const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 10;
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5]= {false,false,false,false,false};


//prototypes
void initShip(spaceShip &ship);
void drawShip(spaceShip &ship);
void moveShipUp(spaceShip &ship);
void moveShipDown(spaceShip &ship);
void moveShipLeft(spaceShip &ship);
void moveShipRight(spaceShip &ship);

void initBullet(Bullet bullet[], int size);
void drawBullet(Bullet bullet[], int size);
void fireBullet(Bullet bullet[], int size, spaceShip &ship);
void updateBullet(Bullet bullet[], int size);
void collideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize);


void initComet(Comet comets[], int size);
void drawComet(Comet comets[], int size);
void startComet(Comet comets[], int size);
void updateComet(Comet comets[], int size);
void collideComet(Comet comets[], int cSize, spaceShip &ship);

//prototype
int main(void){

	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	
	//object variables
	spaceShip ship;
	Bullet bullets[NUM_BULLETS];
	Comet comets[NUM_COMETS];

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

	eventQueue = al_create_event_queue();
	timer= al_create_timer(1.0/FPS);

	srand(time(NULL)); // gives the rand() some value
	initShip(ship);
	initBullet(bullets, NUM_BULLETS);
	initComet(comets, NUM_COMETS);

	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_display_event_source(display)); //event os display resize closing, moving

	al_start_timer(timer);

	while(!done){
	
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		if (ev.type==ALLEGRO_EVENT_TIMER){
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

			updateBullet(bullets,NUM_BULLETS);
			startComet(comets, NUM_COMETS);
			updateComet(comets, NUM_COMETS);
			collideBullet(bullets,NUM_BULLETS, comets, NUM_BULLETS);
			collideComet(comets, NUM_COMETS, ship);
		}
		// when clicling on red X icon to close the game
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		
		}
		else if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done=true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP]=true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN]=true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT]=true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT]=true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE]=true;
					fireBullet(bullets, NUM_BULLETS, ship);
					break;
			}
		}
		else if (ev.type==ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				//make sure when exiting the program exit with esc button
				case ALLEGRO_KEY_ESCAPE:
					done=true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP]=false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN]=false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT]=false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT]=false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE]=false;
					break;
			}
		}
		if (redraw && al_is_event_queue_empty(eventQueue)){ // I only draw the screen if there no more event
			redraw=false;
			drawShip(ship);
			drawBullet(bullets,NUM_BULLETS);
			drawComet(comets, NUM_COMETS);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style	
	
		}
		
		//make sure when exiting the program exit with esc button
		
		// when clicling on red X icon to close the game
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

void initBullet(Bullet bullet[], int size){
	for (int i = 0; i < size; i++){
		bullet[i].id = BULLET;
		bullet[i].speed = 10;
		bullet[i].live = false; // means the bullet is not fired up

	}
}

void drawBullet(Bullet bullet[], int size){
	for (int i = 0; i < size; i++){
		if(bullet[i].live){
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255,255,255));
		}
	}
}

void fireBullet(Bullet bullet[], int size, spaceShip &ship){
	for (int i = 0; i < size; i++){
		if(!bullet[i].live){
			bullet[i].x = ship.x +17;
			bullet[i].y = ship.y;
			bullet[i].live = true;
			break; // to prevent firing all the n bullets at the same time
		}

	}
}

void updateBullet(Bullet bullet[], int size){
	for (int i = 0; i < size; i++){
		if(bullet[i].live){
			bullet[i].x += bullet[i].speed;

			if(bullet[i].x > WIDTH){
				bullet[i].live = false;
			}
		}

	}
}


void initComet(Comet comets[], int size){
	for(int i=0; i < size; i++){
		comets[i].id = ENEMY;
		comets[i].live = false;
		comets[i].speed = 5;
		comets[i].boundx = 18;
		comets[i].boundy = 18;
	}
}

void drawComet(Comet comets[], int size){
	for (int i = 0; i < size; i++){
		if (comets[i].live){
			al_draw_filled_circle(comets[i].x,comets[i].y,20,al_map_rgb(255,0,0));	
		}

	}
}

//similar to fire bullets
void startComet(Comet comets[], int size){
	for (int i = 0; i < size; i++){
		if(!comets[i].live){
			if(rand() % 500 == 0){
				comets[i].live = true;
				comets[i].x = WIDTH;
				comets[i].y = 30 + rand() % (HEIGHT -  60); // makes the comets to spawn no closer than 30 pixels from top nor closer than 30 pixels from the bottom 
				break;
			}	  
		}
	}
}

void updateComet(Comet comets[], int size){
	for (int i = 0; i < size; i++){
		if(comets[i].live){
			comets[i].x -= comets[i].speed; //they're coming from the right to left of screen
		}

	}
}


void collideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize){
	for (int i = 0; i < bSize; i++){
		if(bullet[i].live){
			for (int j = 0; j < cSize; j++){
				if(comets[j].live){
					if(bullet[i].x > (comets[j].x - comets[j].boundx) &&  // that bullet x coordinate has to be grater than the lfet side of comet
						bullet[i].x < (comets[j].x + comets[j].boundx) && // the x coordinate has to be smaller than the x coordinate of comet plus the bounding box of the comet -> the right side of comet
						bullet[i].y > (comets[j].y - comets[j].boundy) && // the bullet have to be lower than the top of the comet
						bullet[i].y	< (comets[j].y + comets[j].boundy)) // the y values has to be smaler or higher than the y of comet plus the bounding box of the comet
					{
						bullet[i].live = false;
						comets[j].live = false;
					}
				}	
			}					
		}
	}
	
}


void collideComet(Comet comets[], int cSize, spaceShip &ship){
	for (int i = 0; i < cSize; i++)
	{
		if(comets[i].live){
			if(comets[i].x - comets[i].boundx < ship.x + ship.boundx && // if the left side of comet is more left that the right side of ship
				comets[i].x + comets[i].boundx > ship.x - ship.boundx && // if the right side of the comet is more right than the left side of ship
				comets[i].y - comets[i].boundy < ship.y + ship.boundy && // if the comet's top is higher than the ship's bottom
				comets[i].y + comets[i].boundy > ship.y - ship.boundy) // if the comet's bottom is lower than the ship's top
			{
				ship.lives--;
				comets[i].live = false;
			
			}
			else if(comets[i].x < 0){
				comets[i].live = false; // every time the comets escapes, takes on HP 
				ship.lives--;
			}
		}
	}
}
