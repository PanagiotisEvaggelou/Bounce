#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "enemy.h"
#include "heart.h"

class Level : public GameObject
{
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_GAME_OVER, STATUS_WIN, STATUS_MAP, STATUS_LEVEL2, STATUS_HELP} status_t;

	status_t status = STATUS_START;

	std::vector<std::string> m_loadedBitmaps;

	void updateStartScreen(float dt);
	void updateLevelScreen(float dt);
	void updateGameOverScreen();
	void updateWinScreen();

	void drawStartScreen();
	void updateHelpScreen(float dt);
	void drawHelpScreen();
	void drawPlayer();
	void drawEnemies();
	void drawHearts();
	void drawSpikes();
	void drawStars();
	void drawBlocks();
	void drawLifeBar();
	void drawStarsCollected();
	void drawLevelScreen();
	void drawGameOverScreen();
	void drawWinScreen();
	void updateEnemies(float dt);
	void updatePlayer(float dt);
	void updateStars(float dt);
	void updateHearts(float dt);

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_start_background;
	graphics::Brush m_brush_game_over_background;
	graphics::Brush m_brush_win_background;
	graphics::Brush m_brush_life;
	graphics::Brush m_brush_star;
	graphics::Brush m_brush_star2;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;
	
	// add some collidable blocks
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	float m_grace_period_duration = 2.0f; // Duration of the grace period in seconds
	float m_grace_period_timer = 0.0f;    // Timer to keep track of the elapsed time in the grace period

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	bool play_sound;

	int drawB = 0;
	float currenttimer;
	float currenttimer2;
	float timer = 0.0f;
	float timer2 = 0.0f;
	int timercount = 0;
	int timer2count = 0;
	int timer3count = 0;
	bool music1 = false;
	bool music2 = false;

	bool enter = false;
	float timerpress1 = 0.0f;
	float timerpress2 = 0.0f;

	bool damaged = false;

	class Enemy* m_enemy = 0;
	class Enemy* m_enemy2 = 0;
	class Enemy* m_enemy3 = 0;
	class Enemy* m_enemy4 = 0;
	class Enemy* m_enemy5 = 0;
	class Enemy* m_enemy6 = 0;
	class Enemy* m_enemy7 = 0;
	class Enemy* m_enemy8 = 0;
	class Enemy* m_enemy9 = 0;
	class Star* m_star1 = 0;
	class Star* m_star2 = 0;
	class Star* m_star3 = 0;
	class Heart* m_heart1 = 0;
	class Heart* m_heart2 = 0;
	class Spikes* m_spikes1 = 0;
	class Spikes* m_spikes2 = 0;
	class Spikes* m_spikes3 = 0;
	class Spikes* m_spikes4 = 0;
	class Spikes* m_spikes5 = 0;
	class Spikes* m_spikes6 = 0;
	class Spikes* m_spikes7 = 0;

	class Spikes* m_spikes8 = 0;
	class Spikes* m_spikes9 = 0;
	class Spikes* m_spikes10 = 0;
	class Spikes* m_spikes11 = 0;
	class Spikes* m_spikes12 = 0;
	class Spikes* m_spikes13 = 0;
	class Spikes* m_spikes14 = 0;
	class Spikes* m_spikes15 = 0;
	class Spikes* m_spikes16 = 0;


	void spawnEnemy();
	void spawnStar();
	void spawnHeart();
	void spawnSpikes();

	bool collisionStar1;
	bool collisionStar2;
	bool collisionStar3;
	bool collisionHeart1;
	bool collisionHeart2;

	bool collisionSpikes1;
	bool collisionSpikes2;
	bool collisionSpikes3;
	bool collisionSpikes4;
	bool collisionSpikes5;
	bool collisionSpikes6;
	bool collisionSpikes7;
	bool collisionSpikes8;
	bool collisionSpikes9;
	bool collisionSpikes10;
	bool collisionSpikes11;
	bool collisionSpikes12;
	bool collisionSpikes13;
	bool collisionSpikes14;
	bool collisionSpikes15;
	bool collisionSpikes16;
	int StarsCollected = 0;

	// detect collisions
	bool checkCollisionsEnemy1();
	bool checkCollisionsEnemy2();
	bool checkCollisionsEnemy3();
	bool checkCollisionsEnemy4();
	bool checkCollisionsEnemy5();
	bool checkCollisionsEnemy6();
	bool checkCollisionsEnemy7();
	bool checkCollisionsEnemy8();
	bool checkCollisionsEnemy9();
	bool checkCollisionsStar1();
	bool checkCollisionsStar2();
	bool checkCollisionsStar3();
	bool checkCollisionsHeart1();
	bool checkCollisionsHeart2();

	bool checkCollisionsSpikes1();
	bool checkCollisionsSpikes2();
	bool checkCollisionsSpikes3();
	bool checkCollisionsSpikes4();
	bool checkCollisionsSpikes5();
	bool checkCollisionsSpikes6();
	bool checkCollisionsSpikes7();

	bool checkCollisionsSpikes8();
	bool checkCollisionsSpikes9();
	bool checkCollisionsSpikes10();
	bool checkCollisionsSpikes11();
	bool checkCollisionsSpikes12();
	bool checkCollisionsSpikes13();
	bool checkCollisionsSpikes14();
	bool checkCollisionsSpikes15();
	bool checkCollisionsSpikes16();

	void checkCollisionsPlayer();
	void checkCollisionsEnemies(float dt);
	void checkCollisionsSpikes(float dt);
	void checkCollisionsHearts(float dt);
	void checkCollisionsStars(float dt);

	void drawLevelBlocks();

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(const std::string & name = "Level0");
	~Level() override;
};