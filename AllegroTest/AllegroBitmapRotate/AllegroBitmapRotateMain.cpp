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

	int x=0;
	int y=0;

	//float scale = 2;

	//float degree = 0;

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
	
	x=width/2 - imageWidth/2;
	y = height /2 - imageHeight/2;
	
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
			case ALLEGRO_KEY_LEFT:
				/*degree -= 10;
				if(degree <= 0)
					degree = 360;
					*/
				x -= 10;

				//scale -= .5f; // f forces the number to be float
				break;
			case ALLEGRO_KEY_RIGHT:
				/*degree += 10;
				if(degree >= 360)
					degree = 0;
				*/
				//scale += .5f; // f forces the number to be float
				x += 10;
				break;
			case ALLEGRO_KEY_DOWN:
				y += 10;
				break;
			case ALLEGRO_KEY_UP:
				y -= 10;
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
		//al_draw_rotated_bitmap(image, imageWidth/ 2,imageHeight/2, width /2, height/2, degree * 3.14159/180,0);
		
		//al_draw_scaled_bitmap(image,0,0,imageWidth, imageHeight,x,y, imageWidth * scale, imageHeight * scale, 0);

		//al_draw_bitmap(image, width / 2 - imageWidth, height / 2 - imageHeight, 0);
		// al_draw_tinted_bitmap(image, al_map_rgb(255,0,0),x,y,0); // will draw only the red the alpha channel of image, meaning it will be entirely red
		
		al_draw_bitmap(image, width / 2 - imageWidth / 2, height / 2 - imageHeight / 2, 0);
		al_draw_tinted_bitmap(image, al_map_rgba(255,100,100,.5),x,y,0); // same as above example, only will be half tranparent
		
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