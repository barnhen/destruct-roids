#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include "PPCD.h"

const int WIDTH = 800;
const int HEIGHT = 600;
// don't forget to put allegro-5.0.10-monolith-md-debug.lib

bool keys[] = {false, false, false, false, false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
enum COLSTATE{BR, D, PPCD}; // BR- rectangule, D- Distance, PPCD - perfect collision detection

struct Sprite
{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int bx;
	int by;

	int r;
	int w;
	int h;

	ALLEGRO_BITMAP *image;
	mask_t *mask;
};

int main(int argc, char **argv)
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done = false;
	bool render = false;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	
	//==============================================
	//PROJECT VARIABLES
	//==============================================
	bool bound = false;
	bool collision = false;
	int colState = BR;

	const int NUM_SPRITES = 9;

	Sprite ball[NUM_SPRITES];

	ALLEGRO_BITMAP *orb = NULL;
	/*
	bool bound = false;
	bool collision = false;

	Sprite ball1;
	Sprite ball2;

	ball1.x = 0;
	ball1.y = 0;

	ball2.x = WIDTH / 2;
	ball2.y = HEIGHT / 2;
	*/

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18 = NULL;
	
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();


	//==============================================
	//PROJECT INIT
	//==============================================
	font18 = al_load_font("arial.ttf", 18, 0);

	orb = al_load_bitmap("orb.png");

	for (int i = 0; i < NUM_SPRITES; i++)
	{
		ball[i].image = orb;

		ball[i].x = 100 + (i % 3) * 110;
		ball[i].y = 100 + (i / 3) * 110;

		ball[i].w = al_get_bitmap_width(ball[i].image);
		ball[i].h = al_get_bitmap_height(ball[i].image);

		ball[i].mask = Mask_New(ball[i].image);

		ball[i].bx = ball[i].w /2 - 10;
		ball[i].by = ball[i].h / 2 - 20;

		ball[i].r = ball[i].w / 2 - 10;
	}

	/*
	ball1.image = al_load_bitmap("orb.png");
	ball2.image = al_load_bitmap("orb.png");

	ball1.w = al_get_bitmap_width(ball1.image);
	ball1.h = al_get_bitmap_height(ball1.image);

	ball2.w = al_get_bitmap_width(ball2.image);
	ball2.h = al_get_bitmap_height(ball2.image);

	ball1.mask = Mask_New(ball1.image);
	ball2.mask = Mask_New(ball2.image);
	*/
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//INPUT
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_1:
				colState = BR;
				break;
			case ALLEGRO_KEY_2:
				colState = D;
				break;
			case ALLEGRO_KEY_3:
				colState = PPCD;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS============
			frames ++;
			if (al_current_time() - gameTime >= 1){
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//============

			collision = false;

			if (keys[UP]){
				ball[0].y -= 5;
			}
			else if (keys[DOWN]){
				ball[0].y += 5;
			}

			if (keys[LEFT]){
				ball[0].x -= 5;
			}
			else if (keys[RIGHT]) {
				ball[0].x += 5;
			}

			if (keys[SPACE]){
				bound = true;
			}
			else{
				bound = false;
			}
			
			if(colState == BR){
				//gonna be 1 because 0 Sprites can't climb itself
				for (int i = 1; i < NUM_SPRITES; i++)
				{
					if( ball[0].x + ball[0].bx > ball[i].x - ball[i].bx &&
						ball[0].x - ball[0].bx < ball[i].x + ball[i].bx &&
						ball[0].y + ball[0].by > ball[i].y - ball[i].by &&
						ball[0].y - ball[0].by < ball[i].y + ball[i].by)
					{
						collision = true;
					}
				}
			}
			else if (colState == D){
				for (int i = 1; i < NUM_SPRITES; i++)
				{
					float distance = sqrt(pow(ball[0].x - ball[i].x,2) + pow(ball[0].y - ball[i].y,2));
				
					if (distance < ball[0].r + ball[i].r){
						collision = true;
					}
				}
			}
			else{
				for (int i = 1; i < NUM_SPRITES; i++)
				{
					if(Mask_Collide(ball[0].mask, ball[i].mask, ball[0].x - ball[i].x, ball[0].y - ball[i].y)){
						collision = true;
					}
				}
			}
			

			

			/*
			if(keys[UP])
				ball1.y -= 5;
			else if(keys[DOWN])
				ball1.y += 5;

			if(keys[LEFT])
				ball1.x -= 5;
			else if(keys[RIGHT])
				ball1.x += 5;

			if(keys[SPACE])
				bound = true;
			else
				bound = false;

			

			if(Mask_Collide(ball1.mask, ball2.mask, ball1.x - ball2.x, ball1.y - ball2.y))
			{
				collision = true;
			}
			else
				collision = false;
		*/
		}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS); // display game FPS on screen


			/*
			al_draw_bitmap(ball2.image, ball2.x - ball2.w / 2, ball2.y - ball2.h / 2, 0);
			al_draw_bitmap(ball1.image, ball1.x - ball1.w / 2, ball1.y - ball1.h / 2, 0);

			
			if(bound)
			{
				Mask_Draw(ball1.mask, ball1.x, ball1.y);
				Mask_Draw(ball2.mask, ball2.x, ball2.y);
			}

			if(collision)
				al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, 20, ALLEGRO_ALIGN_CENTRE, "Collision!");

			*/

			//BEGIN PROJECT RENDER=============
			for (int i = 0; i < NUM_SPRITES; i++)
			{
				al_draw_bitmap(ball[i].image, ball[i].x - ball[i].w / 2, ball[i].y - ball[i].h / 2, 0);
			}
			
			if(bound){
			
				if(colState == BR){
					for (int i = 0; i < NUM_SPRITES; i++)
					{
						al_draw_filled_rectangle(ball[i].x - ball[i].bx, ball[i].y - ball[i].by, ball[i].x + ball[i].bx, ball[i].y + ball[i].by, al_map_rgba_f(.6, 0, .6, .6));	
					}
				}
				else if (colState == D){
					for (int i = 0; i < NUM_SPRITES; i++)
					{
						al_draw_filled_circle(ball[i].x, ball[i].y, ball[i].r, al_map_rgba_f(.6, 0, .6, .6));
					}
				}
				else{
					for (int i = 0; i < NUM_SPRITES; i++)
					{
						Mask_Draw(ball[i].mask, ball[i].x, ball[i].y);
					}
			
				}
			}

			if (collision){
				al_draw_text(font18, al_map_rgb(255,255,255),WIDTH / 2, 20, ALLEGRO_ALIGN_CENTRE, "Collision!");
			}

			//FLIP BUFFERS=============
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	//==============================================
	//DESTROY ALLEGRO OBJECTS
	//==============================================
	/*
	Mask_Delete(ball1.mask);
	Mask_Delete(ball2.mask);
	al_destroy_bitmap(ball1.image);
	al_destroy_bitmap(ball2.image);
	*/
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		Mask_Delete(ball[i].mask);
	}
	al_destroy_bitmap(orb);
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}
