#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>


int main(){
	int width = 640;
	int height = 480;

	ALLEGRO_DISPLAY *display = NULL;

	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		return -1;
	}

	display = al_create_display(width,height);
	

	//check if display was created
	if(!display){
		return -1;
	}


	al_init_primitives_addon(); //initialize
	
	float points[] = {0,0,400,100,50,200,width,height};
	al_draw_spline(points, al_map_rgb(255,0,255),1);

	float points2[] = {0,height,200,100,400,200,width,height};
	al_draw_spline(points2,al_map_rgb(0,255,0),3);
	
	
	/*
	al_draw_circle(100,100,50,al_map_rgb(255,0,255),7);
	al_draw_filled_circle(400,400,70,al_map_rgb(255,255,255));
	*/
	
	/*
	al_draw_ellipse(150,100,100,50,al_map_rgb(127,3,34),6);
	al_draw_filled_ellipse(400,250,100,200,al_map_rgb(0,255,255));
	*/
	
	/*
	// draw a hollow triangule
	al_draw_triangle(10,200,100,10,190,200,al_map_rgb(255,0,255),5);
	//draw a filled triangule
	al_draw_filled_triangle(300,400,400,200,500,400,al_map_rgb(0,0,255));
	*/
	/*
	//hollow
	al_draw_rectangle(10,10,250,250,al_map_rgb(255,0,255),5);
	//round rectangle
	al_draw_rounded_rectangle(width-200,10,width-10,50,5,5,al_map_rgb(0,0,255),15);
	
	al_draw_filled_rectangle(10,280,250,height-10,al_map_rgb(255,255,255));
	
	al_draw_filled_rounded_rectangle(width-200,180,width-10,height-10,10,5,al_map_rgb(0,255,0));
	*/

	/*
	//draw a red line
	al_draw_line(100,100,width-100,100,al_map_rgb(255,0,0),1);

	// draw a thicker blue line
	al_draw_line(50,200,width-50,200,al_map_rgb(0,0,255), 5 );

	//draw a even ticker pink line across the board
	al_draw_line(0,300,width,300,al_map_rgb(255,0,2555),10);
	 
	al_draw_line(50,50,50,400,al_map_rgb(0,255,0),3);

	al_draw_line(50,200,width-50,400,al_map_rgb(0,0,255), 5 );

	//diaonal blue line to join the other blue ones
	al_draw_pixel(100,100,al_map_rgb(255,0,255));
	//s
	*/
	al_flip_display();
	al_rest(5.0);
	al_destroy_display(display);


return 0;
}