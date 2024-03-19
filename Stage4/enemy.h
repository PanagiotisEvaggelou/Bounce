#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject, public Collidable {

	std::vector<std::string> m_enemy_sprites;

	float pos_x, pos_y, pos_w, pos_h, w, h;
	float frequency = 0.01f;
	float m_width = 1.0f;
	float m_height = 1.0f;
	float speed = 0.3f;
	float size;
	const float m_max_velocity_enemy = 5.0f;
	const float m_gravity_enemy = 10.0f;
	graphics::Brush m_brush_enemy;
	bool state = 0;



public:
	Disk getCollisionHull() const override;
	bool floatEquals(float a, float b, float epsilon);
	void update(float dt, float dist, bool vertical);
	void drawhorizontal();
	void drawvertical();
	void init(float w, float h);
	//bool isActive() { return active; }
	Enemy();
	~Enemy();

protected:
	void debugDraw();
};