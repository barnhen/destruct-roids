#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>


int main(){
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	int width = 640;
	int height = 480;
	bool done = false;
	
	const int maxFrame = 8; // 8 frames animation
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;

	
	//int imageWidth = 0;
	//int imageHeight = 0;

	int x=width/2;
	int y=height/2;

	//float scale = 2;

	//float degree = 0;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *image[maxFrame];

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
	
	/*
	image[0] = al_load_bitmap("Dude1.PNG");
	image[1] = al_load_bitmap("Dude2.PNG");
	image[2] = al_load_bitmap("Dude3.PNG");
	*/
	
	image[0] = al_load_bitmap("1.bmp");
	image[1] = al_load_bitmap("0.bmp");
	image[2] = al_load_bitmap("2.bmp");
	image[3] = al_load_bitmap("3.bmp");
	image[4] = al_load_bitmap("4.bmp");
	image[5] = al_load_bitmap("5.bmp");
	image[6] = al_load_bitmap("6.bmp");
	image[7] = al_load_bitmap("7.bmp");
	
	for (int i = 0; i < maxFrame; i++)
	{
		al_convert_mask_to_alpha(image[i], al_map_rgb(106,76,48));
	}

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_start_timer(timer);


	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input
	
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			
			case ALLEGRO_KEY_ESCAPE: 
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				
				break;
			case ALLEGRO_KEY_RIGHT:
				
				break;
			case ALLEGRO_KEY_DOWN:
				
				break;
			case ALLEGRO_KEY_UP:
				
				break;
			
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			if(++frameCount >= frameDelay){
				if(++curFrame >= maxFrame){
					curFrame = 0;

				}
				frameCount=0;
			}
			x -=10;
			if(x <= 0 - al_get_bitmap_width(image[curFrame])){
				x = width;
			}
		}
		 
		//make sure when exiting the program exit with esc button
	/* 	else if (ev.type == ALLEGRO_EVENT_KEY_UP){
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				done = true;
				break;
			}
		}

		*/
		//al_draw_rotated_bitmap(image, imageWidth/ 2,imageHeight/2, width /2, height/2, degree * 3.14159/180,0);
		
		//al_draw_scaled_bitmap(image,0,0,imageWidth, imageHeight,x,y, imageWidth * scale, imageHeight * scale, 0);

		//al_draw_bitmap(image, width / 2 - imageWidth, height / 2 - imageHeight, 0);
		// al_draw_tinted_bitmap(image, al_map_rgb(255,0,0),x,y,0); // will draw only the red the alpha channel of image, meaning it will be entirely red
		
		al_draw_bitmap(image[curFrame],x,y,0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style


	}

	//al_rest(5.0);
	for (int i = 0; i < maxFrame; i++)
	{
		al_destroy_bitmap(image[i]);
	}
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
	al_destroy_timer(timer);

//hey

return 0;
}