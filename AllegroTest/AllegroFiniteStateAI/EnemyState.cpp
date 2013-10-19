/*

		Allegro 5 Shell Application v1.1
			by Mike Geig

		This code is provided for education purposes and comes with no warantee
		either implicit or explicit.

		This code is free to use however you see fit.
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;

bool keys[] = {false, false, false, false, false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

enum STATE{IDLE, CHASING, RETREATING};

void ChangeState(int &state, int newState);
float CheckDistance(int x1, int y1, int x2, int y2);
float AngleToTarget(int x1, int y1, int x2, int y2);

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
	int state = -1;

	int playerx = 0;
	int playery = 0;

	const int cavex = WIDTH - 100;
	const int cavey = HEIGHT / 2;

	int badx = cavex;
	int bady = cavey;

	int threshold = 175;

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;
	
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

	al_install_mouse();

	ChangeState(state, IDLE);
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

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
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			playerx = ev.mouse.x;
			playery = ev.mouse.y;
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if(state == IDLE)
			{
				if(threshold > CheckDistance(playerx, playery, badx, bady))
					ChangeState(state, CHASING);
			}
			else if(state == CHASING)
			{
				if(threshold < CheckDistance(badx, bady, cavex, cavey))
					ChangeState(state, RETREATING);
				else
				{
					float angle = AngleToTarget(badx, bady, playerx, playery);
					bady += (2 * sin(angle));
					badx += (2 * cos(angle));

					if(threshold < CheckDistance(badx, bady, playerx, playery))
						ChangeState(state, RETREATING);
				}
			
			}
			else if(state == RETREATING)
			{
				if(5 >= CheckDistance(badx, bady, cavex, cavey))
				{
					badx = cavex;
					bady = cavey;
					ChangeState(state, IDLE);
				}
				else
				{
					float angle = AngleToTarget(badx, bady, cavex, cavey);
					bady += (2 * sin(angle));
					badx += (2 * cos(angle));

					if(threshold > CheckDistance(badx, bady, playerx, playery))
						ChangeState(state, CHASING);
				}
			}
			
		}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS);	//display FPS on screen

			//BEGIN PROJECT RENDER================
			al_draw_circle(cavex, cavey, threshold, al_map_rgba_f(.5, .5, .5, .5), 1);
			al_draw_circle(badx, bady, threshold, al_map_rgba_f(.5, 0, .5, .5), 1);

			al_draw_filled_rectangle(playerx - 10, playery - 10, playerx + 10, playery + 10, al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(badx - 10, bady - 10, badx + 10, bady + 10, al_map_rgb(255, 0, 255));

			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================

	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}

void ChangeState(int &state, int newState)
{
	if(state == IDLE)
	{
		std::cout << "Leaving the IDLE state\n";
	}
	else if(state == CHASING)
	{
		std::cout << "Leaving the CHASING state\n";
	}
	else if(state == RETREATING)
	{
		std::cout << "Leaving the RETREATING state\n";
	}

	state = newState;

	if(state == IDLE)
	{
		std::cout << "Now IDLING\n";
	}
	else if(state == CHASING)
	{
		std::cout << "Now CHASING the player\n";
	}
	else if(state == RETREATING)
	{
		std::cout << "Now RETREATING back to my cave\n";
	}
}

float CheckDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));
}

float AngleToTarget(int x1, int y1, int x2, int y2)
{
	float deltaX = (x2 - x1);
	float deltaY = (y2 - y1);
	return atan2(deltaY, deltaX);
}