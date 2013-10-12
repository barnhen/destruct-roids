#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>


int width = 640;
int height = 480;
	

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

void initSprites(Sprite &sprite, ALLEGRO_BITMAP *image);
void updateSprites(Sprite &sprite);
void drawSprite(Sprite &sprite);

int main(void){
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	bool done = false;
	bool render = false;
	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	const int numSprites = 100;

	Sprite orbs[numSprites];

	
	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_FONT *font18 = NULL;
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
	al_init_font_addon();
	al_init_ttf_addon();

	font18 = al_load_font("arial.ttf",18,0);

	image = al_load_bitmap("space-core.png");
	al_convert_mask_to_alpha(image, al_map_rgb(106,76,48));

	for (int i = 0; i < numSprites; i++)
	{
		initSprites(orbs[i], image);
	}

	//dragon.image = image;
	
	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input
	
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			
			case ALLEGRO_KEY_ESCAPE: 
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				//dragon.animationDirection = 1; // 
				//dragon.dirX = - 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				//dragon.animationDirection = -1; // 
				//dragon.dirX = 1;
				break;
			case ALLEGRO_KEY_DOWN:
				
				break;
			case ALLEGRO_KEY_UP:
				
				break;
			
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			
			frames++;
			if (al_current_time()- gameTime >= 1){
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			} 

			for (int i = 0; i < numSprites; i++)
			{
				updateSprites(orbs[i]);
			}
			render = true;
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
		
		//al_draw_bitmap_region(dragon.image, dragon.curFrame * dragon.frameWidth,0, dragon.frameWidth, dragon.frameHeight, dragon.x,dragon.y,0);

		if(render && al_is_event_queue_empty(eventQueue)){
			render = false;

			for (int i = 0; i < numSprites; i++)
			{
				drawSprite(orbs[i]);
			}

		
			al_draw_textf(font18, al_map_rgb(255,0,255),5,5,0, "FPS: %i", gameFPS);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style
		}

	}

	//al_rest(5.0);
	/*
	for (int i = 0; i < maxFrame; i++)
	{
		al_destroy_bitmap(image[i]);
	}
	*/
	al_destroy_bitmap(image);
	al_destroy_font(font18);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
	al_destroy_timer(timer);

//hey

return 0;
}

void initSprites(Sprite &sprite, ALLEGRO_BITMAP *image){
	sprite.x = rand() % (width - 20) + 20;
	sprite.y = rand() % (height -20) + 20;
	sprite.velX = rand() % 7 + 2;
	sprite.velY = rand() % 7 + 2;
	sprite.dirX = -1;
	sprite.dirY = -1;

	sprite.maxFrame = 71;
	sprite.curFrame = 0;
	sprite.frameCount = 0;
	sprite.frameDelay = 5;
	sprite.frameWidth = 64;
	sprite.frameHeight = 64;
	sprite.animationColumns = 16;
	sprite. animationDirection = 1;

	sprite.image = image;
}

void updateSprites(Sprite &sprite){
	if(++sprite.frameCount >= sprite.frameDelay){
		sprite.curFrame += sprite.animationDirection;
		if(sprite.curFrame >= sprite.maxFrame){
			sprite.curFrame = 0;		
		}
		else if(sprite.curFrame <= 0){
			sprite.curFrame = sprite.maxFrame - 1;
		}
		sprite.frameCount = 0;
	}
	sprite.x += sprite.velX * sprite.dirX;
	sprite.y += sprite.velY * sprite.dirY;

	//boucing the walls
	if ((sprite.x <= 0 && sprite.dirX == -1) ||
		(sprite.x >= width - sprite.frameWidth && sprite.dirX ==1))
	{
		sprite.dirX *= -1;
		sprite.animationDirection *= -1;
	}
	if((sprite.y <= 0 && sprite.dirY == -1) ||
		(sprite.y >= height - sprite.frameHeight && sprite.dirY == 1))
	{
		sprite.dirY *= -1;
		sprite.animationDirection *= -1;
		
	}
}

void drawSprite(Sprite &sprite){
	int frameX = (sprite.curFrame % sprite.animationColumns) * sprite.frameWidth;
	int frameY = (sprite.curFrame / sprite.animationColumns) * sprite.frameHeight;

	al_draw_bitmap_region(sprite.image, frameX, frameY, sprite.frameWidth,
		sprite.frameHeight, sprite.x, sprite.y, 0);
}