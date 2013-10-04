#include<allegro5\allegro.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>



int main(void){
	int width = 640;
	int height = 480;

	bool done = false;
	int count = 0;

	 int fps = 60;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER * timer = NULL;

	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		return -1;
	}

	display = al_create_display(width,height);
	

	//check if display was created
	if(!display){
		return -1;
	}

	al_init_font_addon(); // initialize font
	al_init_ttf_addon();
	
	ALLEGRO_FONT *font18 = al_load_font("arial.ttf",18,0);
	
	timer = al_create_timer(1.0/fps); // to run n frames per 1 (one) second
	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
		count++;

		al_draw_textf(font18, al_map_rgb(255,255,255), width/2, height/2, ALLEGRO_ALIGN_CENTRE,
			"Frames: %i", count); // print frames per second

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style
	}
	//al_rest(5.0);
	al_destroy_display(display);
//shoryuken

return 0;
}