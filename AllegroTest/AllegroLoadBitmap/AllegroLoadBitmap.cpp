#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>


int main(){
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	int width = 640;
	int height = 480;
	bool done = false;
	
	int imageWidth = 0;
	int imageHeight = 0;

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
	al_init_image_addon();
	image = al_load_bitmap("ufo1.gif");

	imageWidth = al_get_bitmap_width(image);
	imageHeight= al_get_bitmap_height(image);
	
	
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
				break;
			}
		}
		al_draw_bitmap(image, width / 2 - imageWidth, height / 2 - imageHeight, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style


	}

	//al_rest(5.0);
	al_destroy_bitmap(image);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

//hey

return 0;
}