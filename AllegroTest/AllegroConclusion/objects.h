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
};