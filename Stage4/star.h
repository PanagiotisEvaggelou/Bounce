#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>

class Star : public GameObject, public Collidable {

	std::vector<std::string> m_star_sprites;

	float pos_x, pos_y, w, h;
	float frequency = 0.01f;
	float m_width = 1.0f;
	float m_height = 1.0f;
	float speed = 0.3f;
	float size;
	const float m_max_velocity_enemy = 5.0f;
	const float m_gravity_enemy = 10.0f;
	graphics::Brush m_brush_star;
	bool state = 0;

	float timer = 0.01f;
	int currentSpriteIndex = 0;
	int nextSprite = 0;



public:
	Disk getCollisionHull() const override;
	bool floatEquals(float a, float b, float epsilon);
	void update(float dt) override;
	void draw() override;
	void init(float w, float h);
	//bool isActive() { return active; }
	Star();
	~Star();

protected:
	void debugDraw();
};