#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>


int main(){
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	int width = 640;
	int height = 480;
	bool done = false;
	int imageRad = 20; // radius of image

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_BITMAP *image = NULL;

	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		return -1;
	}

	display = al_create_display(width,height);
	

	//check if display was created
	if(!display){
		return -1;
	}

	al_install_keyboard();// will initialize keyboard events
	al_init_primitives_addon();

	image = al_create_bitmap(imageRad * 2,imageRad * 2);

	al_set_target_bitmap(image); //prepared to draw to screen
	
	al_clear_to_color(al_map_rgb(127,127,127));

	//turrets
	al_draw_filled_rectangle(imageRad,imageRad - 9,imageRad + 10,imageRad - 7,al_map_rgb(255,0,0));
	al_draw_filled_rectangle(imageRad,imageRad + 9,imageRad + 10,imageRad + 7,al_map_rgb(255,0,0));

	//ship body
	al_draw_filled_triangle(imageRad - 12,imageRad - 17,imageRad + 12,imageRad,imageRad - 12,imageRad + 17,al_map_rgb(0,255,0));
	al_draw_filled_rectangle(imageRad - 12, imageRad - 2,imageRad + 15, imageRad + 2, al_map_rgb(0,0,255));
	
	al_set_target_bitmap(al_get_backbuffer(display));

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input
	
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			
			case ALLEGRO_KEY_ESCAPE: 
				done = true;
				break;
			}
		}

		//make sure when exiting the program exit with esc button
		else if (ev.type == ALLEGRO_EVENT_KEY_UP){
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				done = true;
			}
		}
		al_draw_bitmap(image, width / 2, height / 2, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style


	}

	//al_rest(5.0);
	al_destroy_display(display);
//hey

return 0;
}