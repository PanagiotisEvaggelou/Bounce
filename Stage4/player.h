#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

class Player : public Box, public GameObject, public Collidable
{
	// animated player
	std::vector<std::string> m_sprites;
	std::vector<Box> m_blocks;

	graphics::Brush m_brush_player;
	graphics::Brush m_brush_damaged_player;

	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 300.1f;
	const float m_max_velocity = 5.0f;
	const float m_gravity = 15.0f;

public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	float life = 0.8f;

	bool m_on_ground;


public:
	Disk getCollisionHull() const override;
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	void addLife(float amount) { life += amount; }
	float getRemainingLife() const { return life; }
	void update(float dt) override;
	void draw() override;
	void drawDamaged();
	void init() override;
	Player(std::string name) : GameObject(name) {}

	
protected:
	void debugDraw();
	
	// dynamic motion control
	void movePlayer(float dt);
};
