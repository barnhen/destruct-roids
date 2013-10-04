#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>

enum KEYS{UP,DOWN,LEFT,RIGHT};

int main(){
	int width = 640;
	int height = 480;

	bool done = false;
	bool draw = true;

	int posX = width/2;
	int posY = height/2;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue;

	

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
	al_install_mouse();
	

	eventQueue = al_create_event_queue();
	
	al_register_event_source(eventQueue, al_get_display_event_source(display)); //event os display resize closing, moving
	al_register_event_source(eventQueue, al_get_mouse_event_source()); // initialize mouse event

	//al_hide_mouse_cursor(display); // hides the mouse cursor

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input
	
		
		// when clicling on red X icon to close the game
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done=true;
		
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			posX = ev.mouse.x;
			posY = ev.mouse.y;
		}
		else if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(ev.mouse.button & 2) //number 2 equals to right click
				done=true;
			else if(ev.mouse.button & 1) //number 1 equals to left click
				draw = !draw;
		}

		if (draw){
			al_draw_filled_rectangle(posX,posY, posX+30, posY+30,al_map_rgb(255,0,255));
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style


	}

	//al_rest(5.0);
	al_destroy_display(display);
//hadouken

return 0;
}