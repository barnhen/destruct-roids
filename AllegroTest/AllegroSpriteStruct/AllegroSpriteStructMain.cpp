#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>

struct Sprite{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP *image;
	
};

int main(void){
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	int width = 640;
	int height = 480;
	bool done = false;

	Sprite dragon;
	dragon.x = width/2;
	dragon.y = height/2;
	dragon.velX = 5;
	dragon.velY = 0;
	dragon.dirX = -1; //will move from the right end of screen to left end of screen
	dragon.dirY = 0;

	dragon.maxFrame = 8;
	dragon.curFrame = 0;
	dragon.frameCount = 0;
	dragon.frameDelay = 5;
	dragon.frameWidth=128;
	dragon.frameHeight =128;
	dragon.animationColumns = 8;
	dragon.animationDirection = 1;




	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *image;
	
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
	
	image = al_load_bitmap("spritesheet_demo.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(106,76,48));

	dragon.image = image;
	
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
				dragon.animationDirection = 1; // 
				dragon.dirX = - 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				dragon.animationDirection = -1; // 
				dragon.dirX = 1;
				break;
			case ALLEGRO_KEY_DOWN:
				
				break;
			case ALLEGRO_KEY_UP:
				
				break;
			
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			
			if(++dragon.frameCount >= dragon.frameDelay){
				dragon.curFrame += dragon.animationDirection;
				if(dragon.curFrame >= dragon.maxFrame){
					dragon.curFrame = 0;
				}
				else if (dragon.curFrame <= 0){
					dragon.curFrame = dragon.maxFrame - 1;
				}
				dragon.frameCount=0;
			}
			dragon.x += dragon.velX * dragon.dirX;
			
			if (dragon.x <= 0 - dragon.frameWidth){
				dragon.x = width;
			}
			else if (dragon.x > width){
				dragon.x = 0 - dragon.frameWidth;
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
		/*
			the below will create the sprite sheet
			image = the sprite sheet
			sx = the size x starting point of sprite sheet i.3 0 to 128 pixels, so that's why we're multipliyng it by curFrame which will add ++ each frame
			sy = the size y starting point of sprite sheet
			sw = how width is the image
			sh = how tall is the image
			dx = where it is gonna put x
			dy = where it is gonna put y
		*/
		
		al_draw_bitmap_region(dragon.image, dragon.curFrame * dragon.frameWidth,0, dragon.frameWidth, dragon.frameHeight, dragon.x,dragon.y,0);

		al_flip_display();

		
		al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style


	}

	//al_rest(5.0);
	/*
	for (int i = 0; i < maxFrame; i++)
	{
		al_destroy_bitmap(image[i]);
	}
	*/
	al_destroy_bitmap(image);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
	al_destroy_timer(timer);

//hey

return 0;
}