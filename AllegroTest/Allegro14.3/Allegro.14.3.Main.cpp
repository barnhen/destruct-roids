#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "objects.h"
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 10;
const int NUM_EXPLOSIONS =5;

enum STATE{TITLE, PLAYING, LOST};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};
spaceShip ship;
Bullet bullets[NUM_BULLETS];
Comet comets[NUM_COMETS];
Explosion explosions[NUM_EXPLOSIONS];
Background bg;
Background mg; // stands for middel-ground
Background fg; // stands for foreground

ALLEGRO_SAMPLE * shot = NULL;
ALLEGRO_SAMPLE * boom = NULL;
ALLEGRO_SAMPLE * song = NULL;
ALLEGRO_SAMPLE_INSTANCE * songInstance = NULL;
	

//prototypes
void InitShip(spaceShip &ship, ALLEGRO_BITMAP *image);
void DrawShip(spaceShip &ship);
void MoveShipUp(spaceShip &ship);
void MoveShipDown(spaceShip &ship);
void MoveShipLeft(spaceShip &ship);
void MoveShipRight(spaceShip &ship);

void InitBullet(Bullet bullet[], int size);
void ResetShipAnimation(spaceShip &ship, int position);
void DrawBullet(Bullet bullet[], int size);
void FireBullet(Bullet bullet[], int size, spaceShip &ship);
void UpdateBullet(Bullet bullet[], int size);
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, spaceShip &ship, Explosion explosions[], int eSize);

void InitComet(Comet comets[], int size, ALLEGRO_BITMAP *image);
void DrawComet(Comet comets[], int size);
void StartComet(Comet comets[], int size);
void UpdateComet(Comet comets[], int size);
void CollideComet(Comet comets[], int cSize, spaceShip &ship, Explosion explosion[], int eSize);

void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image);
void DrawExplosions(Explosion explosions[], int size);
void StartExplosions(Explosion explosions[], int size, int x, int y);
void UpdateExplosions(Explosion explosions[], int size);

void InitBackground(Background &backGround, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(Background &backGround);
void DrawBackground(Background &backGround);

void ChangeState(int &state, int newState);

int main(void)
{
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib
	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int state = -1;

	//object variables
	
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_BITMAP *shipImage;
	ALLEGRO_BITMAP *cometImage;
	ALLEGRO_BITMAP *expImage;
	ALLEGRO_BITMAP *bgImage=NULL;
	ALLEGRO_BITMAP *mgImage=NULL;
	ALLEGRO_BITMAP *fgImage=NULL;
	ALLEGRO_BITMAP *title = NULL;
	ALLEGRO_BITMAP *lost = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio(); // always initialize audio before the codecs
	al_init_acodec_addon();

	bgImage = al_load_bitmap("starBG.png");
	mgImage = al_load_bitmap("starMG.png");
	fgImage = al_load_bitmap("starFG.png");


	

	al_reserve_samples(10); // reserves numbers of samples/ channels or voices

	shot = al_load_sample("shot.ogg");
	boom = al_load_sample("boom.ogg");
	song = al_load_sample("03 - OPENING STAGE X.ogg");

	songInstance = al_create_sample_instance(song);	
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	cometImage = al_load_bitmap("asteroid-1-96.png");
	//above does not need convert_mask_to_alpha because it is tranparent background in sprite sheet
	shipImage = al_load_bitmap("Spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage,al_map_rgb(255,0,255));
	expImage = al_load_bitmap("explosion_3_40_128.png");
	title = al_load_bitmap("Shooter_Title.png");
	lost = al_load_bitmap("Shooter_Lose.png");

	srand(time(NULL));
	
	ChangeState(state, TITLE);

	InitShip(ship, shipImage);
	InitBullet(bullets, NUM_BULLETS);
	InitComet(comets, NUM_COMETS, cometImage);
	InitExplosions(explosions, NUM_EXPLOSIONS, expImage);
	InitBackground(bg, 0, 0, 1, 0, 800,600, -1, 1, bgImage );
	InitBackground(mg, 0, 0, 3, 0, 1600,600, -1, 1, mgImage );
	InitBackground(fg, 0, 0, 5, 0, 800,600, -1, 1, fgImage );
	

	font18 = al_load_font("arial.ttf", 18, 0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//al_play_sample_instance(songInstance);

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			
			int soundX = ship.x;
			int soundY = ship.y;
			
			if(keys[UP])
				MoveShipUp(ship);
			else if(keys[DOWN])
				MoveShipDown(ship);
			else
				ResetShipAnimation(ship,1);
			if(keys[LEFT])
				MoveShipLeft(ship);
			else if(keys[RIGHT])
				MoveShipRight(ship);
			else
				ResetShipAnimation(ship, 2);
			

			if(state == TITLE){
	
			}
			else if (state == PLAYING){
			UpdateBackground(bg);
			UpdateBackground(mg);
			UpdateBackground(fg);

			UpdateExplosions(explosions, NUM_EXPLOSIONS);
			UpdateBullet(bullets, NUM_BULLETS);
			StartComet(comets, NUM_COMETS);
			UpdateComet(comets, NUM_COMETS);
			CollideBullet(bullets, NUM_BULLETS, comets, NUM_COMETS, ship, explosions, NUM_EXPLOSIONS);
			CollideComet(comets, NUM_COMETS, ship, explosions, NUM_BULLETS);

			if(ship.lives <= 0)
				ChangeState(state, LOST);
			
			}
			else if (state == LOST){
	
			}

			
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				if(state == TITLE){
					ChangeState(state, PLAYING);
				}
				else if (state == PLAYING){
					FireBullet(bullets, NUM_BULLETS, ship);
				}
				else if (state == LOST){
					ChangeState(state, PLAYING);
				}
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
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 

			if(state == TITLE){
				al_draw_bitmap(title,0,0,0);
			}
			else if (state == PLAYING){
				//pay atention on the order the background images are created to prevent one overlap the other wrongly
				DrawBackground(bg);
				DrawBackground(mg);
				DrawBackground(fg);

				//al_play_sample_instance(songInstance);

				DrawShip(ship);
				
				if(al_get_sample_instance_playing(songInstance)){
					al_draw_textf(font18, al_map_rgb(255,255,255),5,HEIGHT - 30,0, "Instance 3 is playing: %.1f %%", al_get_sample_instance_position(songInstance) / (float)al_get_sample_instance_length(songInstance) * 100);
				}

				DrawBullet(bullets, NUM_BULLETS);
				DrawComet(comets, NUM_COMETS);
				DrawExplosions(explosions, NUM_EXPLOSIONS);

				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects", ship.lives, ship.score);

			}
			else if (state == LOST){
				al_draw_bitmap(lost,0,0,0);

				al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH - 10, 20, ALLEGRO_ALIGN_RIGHT, "Final Score: %i", ship.score);
				//al_stop_sample_instance(songInstance);

			}
		
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_sample(shot);
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_bitmap(expImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(title);
	al_destroy_bitmap(lost);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void InitShip(spaceShip &ship, ALLEGRO_BITMAP *image = NULL)
{
	ship.x = 20;
	ship.y = HEIGHT / 2;
	ship.id = PLAYER;
	ship.lives = 3;
	ship.speed = 6;
	ship.boundx = 10;
	ship.boundy = 12;
	ship.score = 0;

	ship.maxFrame = 3;
	ship.curFrame = 0;
	ship.frameCount = 0;
	ship.frameDelay = 50;
	ship.frameWidth = 46;
	ship.frameHeight = 41;
	ship.animationColumns = 3;
	ship.animationDirection = 1;

	ship.animationRow = 1;

	if (image != NULL){
		ship.image = image;
	}
}

void ResetShipAnimation(spaceShip &ship, int position){
	if (position ==1)
		ship.animationRow = 1;
	else
		ship.curFrame = 0;
}

void DrawShip(spaceShip &ship)
{
	int frameX = (ship.curFrame % ship.animationColumns) * ship.frameWidth;
	int frameY = (ship.animationRow * ship.frameHeight);

	al_draw_bitmap_region(ship.image, frameX, frameY, ship.frameWidth,
		ship.frameHeight, ship.x - ship.frameWidth / 2, ship.y - ship.frameHeight / 2, 0 );

	/*
	al_draw_filled_rectangle(ship.x - ship.boundx,ship.y - ship.boundy,ship.x + ship.boundx,
		ship.y + ship.boundy, al_map_rgba(255,0,255,100));
		*/
}
void MoveShipUp(spaceShip &ship)
{
	ship.animationRow = 0;
	ship.y -= ship.speed;
	if(ship.y < 0)
		ship.y = 0;
}
void MoveShipDown(spaceShip &ship)
{
	ship.animationRow = 2;
	ship.y += ship.speed;
	if(ship.y > HEIGHT)
		ship.y = HEIGHT;
}
void MoveShipLeft(spaceShip &ship)
{
	ship.curFrame = 2;
	ship.x -= ship.speed;
	if(ship.x < 0)
		ship.x = 0;
}
void MoveShipRight(spaceShip &ship)
{
	ship.curFrame = 1;
	ship.x += ship.speed;
	if(ship.x > 300)
		ship.x = 300;
}

void InitBullet(Bullet bullet[], int size)
{
	for(int i = 0; i < size; i++)
	{
		bullet[i].id = BULLET;
		bullet[i].speed = 10;
		bullet[i].live = false;
	}
}
void DrawBullet(Bullet bullet[], int size)
{
	for( int i = 0; i < size; i++)
	{
		if(bullet[i].live)
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255, 255, 255));
	}
}
void FireBullet(Bullet bullet[], int size, spaceShip &ship)
{
	for( int i = 0; i < size; i++)
	{
		if(!bullet[i].live)
		{
			bullet[i].x = ship.x + 17;
			bullet[i].y = ship.y;
			bullet[i].live = true;

			al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

			break;
		}
	}
}
void UpdateBullet(Bullet bullet[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(bullet[i].live)
		{
			bullet[i].x += bullet[i].speed;
			if(bullet[i].x > WIDTH)
				bullet[i].live = false;
		}
	}
}
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, spaceShip &ship, Explosion explosions[], int eSize)
{
	for(int i = 0; i < bSize; i++)
	{
		if(bullet[i].live)
		{
			for(int j =0; j < cSize; j++)
			{
				if(comets[j].live)
				{
					if(bullet[i].x > (comets[j].x - comets[j].boundx) &&
						bullet[i].x < (comets[j].x + comets[j].boundx) &&
						bullet[i].y > (comets[j].y - comets[j].boundy) &&
						bullet[i].y < (comets[j].y + comets[j].boundy))
					{
						bullet[i].live = false;
						comets[j].live = false;

						ship.score++;

						StartExplosions(explosions, eSize, bullet[i].x, bullet[i].y);
					
						al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

					}
				}
			}
		}
	}
}

void InitComet(Comet comets[], int size, ALLEGRO_BITMAP *image = NULL)
{
	for(int i = 0; i < size; i++)
	{
		comets[i].id = ENEMY;
		comets[i].live = false;
		comets[i].speed = 5;
		comets[i].boundx = 35;
		comets[i].boundy = 35;

		comets[i].maxFrame = 143; // the are 143 frames animation
		comets[i].curFrame = 0;
		comets[i].frameCount = 0;
		comets[i].frameDelay = 2;
		comets[i].frameWidth = 96;
		comets[i].frameHeight = 96;
		comets[i].animationColumns = 21;
		if(rand() % 2)
			comets[i].animationDirection = 1;
		else
			comets[i].animationDirection = -1;
		
		if(image != NULL){
			comets[i].image = image;
		}
	}
}
void DrawComet(Comet comets[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(comets[i].live)
		{
			int frameX = (comets[i].curFrame % comets[i].animationColumns) * comets[i].frameWidth;
			int frameY = (comets[i].curFrame / comets[i].animationColumns) * comets[i].frameHeight;

			al_draw_bitmap_region(comets[i].image, frameX, frameY, comets[i].frameWidth,
				comets[i].frameHeight,comets[i].x - comets[i].frameWidth / 2, comets[i].y - comets[i].frameHeight / 2, 0);
			/*
			al_draw_filled_rectangle(comets[i].x - comets[i].boundx, comets[i].y - comets[i].boundy, comets[i].x + comets[i].boundx,
				comets[i].y + comets[i].boundy, al_map_rgba(255,0,255,100));
		*/
		}
	}
}
void StartComet(Comet comets[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!comets[i].live)
		{
			if(rand() % 500 == 0)
			{
				comets[i].live = true;
				comets[i].x = WIDTH;
				comets[i].y = 30 + rand() % (HEIGHT - 60);

				break;
			}
		}
	}
}
void UpdateComet(Comet comets[], int size)
{
	for(int i = 0; i < size; i++)
	{
		if(comets[i].live)
		{
			if (++comets[i].frameCount >= comets[i].frameDelay){
				comets[i].curFrame += comets[i].animationDirection;
				
				if(comets[i].curFrame >= comets[i].maxFrame){
					comets[i].curFrame = 0;
				}
				else if(comets[i].curFrame <= 0 )
					comets[i].curFrame = comets[i].maxFrame - 1;

				comets[i].frameCount = 0;
			}

			comets[i].x -= comets[i].speed;
		}
	}
}

void CollideComet(Comet comets[], int cSize, spaceShip &ship, Explosion explosions[], int eSize)
{
	for(int i = 0; i < cSize; i++)
	{
		if(comets[i].live)
		{
			if(comets[i].x - comets[i].boundx < ship.x + ship.boundx &&
				comets[i].x + comets[i].boundx > ship.x - ship.boundx &&
				comets[i].y - comets[i].boundy < ship.y + ship.boundy &&
				comets[i].y + comets[i].boundy > ship.y - ship.boundy)
			{
				ship.lives--;
				comets[i].live = false;
				StartExplosions(explosions, eSize, ship.x, ship.y);
			
				al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

			}
			else if(comets[i].x < 0)
			{
				comets[i].live = false;
				ship.lives--;
			}
		}
	}
}

void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP *image = NULL){
	for (int i = 0; i < size; i++)
	{
		explosions[i].live = false;
		
		explosions[i].maxFrame = 31;
		explosions[i].curFrame = 0;
		explosions[i].frameCount = 0;
		explosions[i].frameDelay = 1;
		explosions[i].frameWidth = 128;
		explosions[i].frameHeight = 128;
		explosions[i].animationColumns = 8;
		explosions[i].animationDirection = 1;

		if(image!= NULL){
			explosions[i].image = image;
		}

	}
}
void DrawExplosions(Explosion explosions[], int size){
	for (int i = 0; i < size; i++)
	{
		if(explosions[i].live){
			int frameX = (explosions[i].curFrame % explosions[i].animationColumns) * explosions[i].frameWidth;
			int frameY = (explosions[i].curFrame / explosions[i].animationColumns) * explosions[i].frameHeight;
			
			al_draw_bitmap_region(explosions[i].image, frameX, frameY, explosions[i].frameWidth,
				explosions[i].frameHeight, explosions[i].x - explosions[i].frameWidth / 2, explosions[i].y - explosions[i].frameHeight / 2, 0);
		}
	}
}

void StartExplosions(Explosion explosions[], int size, int x, int y){
	for (int i = 0; i < size; i++)
	{
		if(!explosions[i].live){
			explosions[i].live = true;
			explosions[i].x = x;
			explosions[i].y = y;
			break;
		}
	}	
}
void UpdateExplosions(Explosion explosions[], int size){
	for (int i = 0; i < size; i++)
	{
		if(explosions[i].live){
			if(++explosions[i].frameCount >= explosions[i].frameDelay){
				explosions[i].curFrame += explosions[i].animationDirection;
				
				if (explosions[i].curFrame >= explosions[i].maxFrame){
					explosions[i].curFrame = 0;
					explosions[i].live = false;
				}
				explosions[i].frameCount = 0;
			}
		}
	}
}

void InitBackground(Background &backGround, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image){
	backGround.x = x;
	backGround.y = y;
	backGround.velX = velx;
	backGround.VelY = vely;
	backGround.width = width;
	backGround.height = height;
	backGround.dirX = dirX;
	backGround.dirY = dirY;
	backGround.image = image;
}

void UpdateBackground(Background &backGround){
	backGround.x += backGround.velX * backGround.dirX;
	if(backGround.x + backGround.width <= 0){
		backGround.x =0;
	}
}

void DrawBackground(Background &backGround){
	al_draw_bitmap(backGround.image, backGround.x, backGround.y, 0);
	
	//to avoid gaps between repeating backgrounds
	if(backGround.x + backGround.width < WIDTH){
		al_draw_bitmap(backGround.image, backGround.x + backGround.width, backGround.y,0);

	}
}


void ChangeState(int &state, int newState){
	if(state == TITLE){
	
	}
	else if (state == PLAYING){
		al_stop_sample_instance(songInstance);
	}
	else if (state == LOST){
	
	}

	state = newState;
	
	if(state == TITLE){
	
	}
	else if (state == PLAYING){
		InitShip(ship);
		InitBullet(bullets, NUM_BULLETS);
		InitComet(comets, NUM_COMETS);
		InitExplosions(explosions, NUM_EXPLOSIONS);
	
		al_play_sample_instance(songInstance);
	}
	else if (state == LOST){
	
	}
}