#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>

enum KEYS{UP,DOWN,LEFT,RIGHT};
// don't forget to put allegro-5.0.10-monolith-md-debug.lib
int main(){
	int width = 640;
	int height = 480;

	int posX = width/2;
	int posY = height/2;

	int fps = 60;


	bool keys[4]= {false,false,false,false};

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER *timer = NULL;

	bool done = false;
	bool redraw = true;

	
	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		return -1;
	}

	display = al_create_display(width,height);
	

	//check if display was created
	if(!display){
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard();// will initialize keyboard events

	eventQueue = al_create_event_queue();

	timer = al_create_timer(1.0/fps);

	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display)); //event os display resize closing, moving

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input
	
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					keys[UP]=true;
					//posY -=10;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN]=true;
					//posY +=10;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT]=true;
					//posX -=10;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT]=true;
					//posX +=10;
					break;
			}
		}

		if (ev.type==ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					keys[UP]=false;
					//posY -=10;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN]=false;
					//posY +=10;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT]=false;
					//posX -=10;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT]=false;
					//posX +=10;
					break;
				//make sure when exiting the program exit with esc button
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}

		//make sure when exiting the program exit with esc button
		
		// when clicling on red X icon to close the game
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		}
		else if (ev.type==ALLEGRO_EVENT_TIMER){
			posY -= keys[UP] * 10;
			posY += keys[DOWN] * 10;
			posX -= keys[LEFT] * 10;
			posX += keys[RIGHT] * 10;

			redraw=true;
		}

		if (redraw && al_is_event_queue_empty(eventQueue)){ // I only draw the screen if there no more event
			redraw=false;
			al_draw_filled_rectangle(posX,posY, posX+30, posY+30,al_map_rgb(255,0,255));
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style

		}


		

	}

	//al_rest(5.0);
	al_destroy_display(display);
//hadouken

return 0;
}