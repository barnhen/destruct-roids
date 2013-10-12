#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

int main(void)
{
	// don't forget to put allegro-5.0.10-monolith-md-debug.lib

	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	int imageWidth = 0;
	int imageHeight = 0;

	const int arraySize = 8;


	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *image[arraySize];
	ALLEGRO_BITMAP *outImage;
	//ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//ALLEGRO_TIMER *timer;
	
	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();

	image[0] = al_load_bitmap("fliegt w0000.bmp");
	image[1] = al_load_bitmap("fliegt w0001.bmp");
	image[2] = al_load_bitmap("fliegt w0002.bmp");
	image[3] = al_load_bitmap("fliegt w0003.bmp");
	image[4] = al_load_bitmap("fliegt w0004.bmp");
	image[5] = al_load_bitmap("fliegt w0005.bmp");
	image[6] = al_load_bitmap("fliegt w0006.bmp");
	image[7] = al_load_bitmap("fliegt w0007.bmp");

	imageWidth = al_get_bitmap_width(image[0]);
	imageHeight = al_get_bitmap_height(image[0]);

	outImage = al_create_bitmap(imageWidth * arraySize, imageHeight);

	al_set_target_bitmap(outImage);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));

	for (int i = 0; i < arraySize; i++)
	{
		al_draw_bitmap(image[i], i * imageWidth,0,0);
	}


	//al_destroy_event_queue(event_queue);
	//al_destroy_timer(timer);
	al_save_bitmap("spritesheet_demo.bmp", outImage);

	al_set_target_bitmap(al_get_backbuffer(display));// clear the display 
	for (int i = 0; i < arraySize; i++)
	{
		al_destroy_bitmap(image[i]);
	}
	al_destroy_display(display);	//destroy our display object

	return 0;
}