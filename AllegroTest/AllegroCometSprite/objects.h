//Object ids

enum IDS{PLAYER,BULLET,ENEMY};

//Our Player
struct spaceShip{
	int id;
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	int animationRow;

	ALLEGRO_BITMAP *image;
	
};

struct Bullet{
	int id;
	int x;
	int y;
	int live;
	int speed;
};

struct Comet{
	int id;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;

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

struct Explosion{
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;

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