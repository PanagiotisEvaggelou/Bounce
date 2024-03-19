#include "enemy.h"
#include <sgg/graphics.h>
#include <random>
#include "util.h"

bool Enemy::floatEquals(float x, float y, float epsilon = 0.02f) {
	if (fabs(x - y) < epsilon)
		return true; //they are same
	return false; //they are not same
}

Disk Enemy::getCollisionHull() const
{
	Disk disk{};
	disk.cx = pos_x + m_state->m_global_offset_x;
	disk.cy = pos_y + m_state->m_global_offset_y;
	disk.radius = 0.45f;
	return disk;
}

void Enemy::update(float dt, float dist, bool vertical)
{

	
	if (vertical == true) {
		if (floatEquals(pos_x, pos_w)) {
			pos_x = pos_x + 0.02f;
			if (dist == 6.00f) {
			}
			state = 0;
		}
		else if (pos_x > pos_w and pos_x < pos_w + dist and state == 0) {
			pos_x = pos_x + 0.02f;
			if (dist == 6.00f) {
			}
		}
		else if (floatEquals(pos_x, pos_w + dist)) {
			pos_x = pos_x - 0.02f;
			if (dist == 6.00f) {
			}
			state = 1;
		}
		else if (pos_x > pos_w and pos_x < pos_w + dist and state == 1) {
			pos_x = pos_x - 0.02f;
			if (dist == 6.00f) {
			}
		}
	}
	else {
		if (floatEquals(pos_y, pos_h)) {
			pos_y = pos_y + 0.02f;
			state = 0;
		}
		else if (pos_y > pos_h and pos_y < pos_h + dist and state == 0) {
			pos_y = pos_y + 0.02f;
		}
		else if (floatEquals(pos_y, pos_h + dist)) {
			pos_y = pos_y - 0.02f;
			state = 1;
		}
		else if (pos_y > pos_h and pos_y < pos_h + dist and state == 1) {
			pos_y = pos_y - 0.02f;
		}
	}




}

void Enemy::drawhorizontal()
{
	int sprite;
	sprite = (int)fmod(110.0f - pos_y * 8.0f, m_enemy_sprites.size());
	float fs = (float)sprite;


	m_brush_enemy.texture = m_enemy_sprites[sprite];
	graphics::drawRect(pos_x + m_state->m_global_offset_x, pos_y + m_state->m_global_offset_y, 1.0f, 1.0f, m_brush_enemy);


	if (m_state->m_debugging)
		debugDraw();

}

void Enemy::drawvertical()
{
	int sprite;
	sprite = (int)fmod(100.0f - pos_x * 8.0f, m_enemy_sprites.size());

	m_brush_enemy.texture = m_enemy_sprites[sprite];
	graphics::drawRect(pos_x + m_state->m_global_offset_x, pos_y + m_state->m_global_offset_y, 1.0f, 1.0f, m_brush_enemy);



	if (m_state->m_debugging)
		debugDraw();

}

void Enemy::init(float w, float h)
{
	speed = 0.001f;
	pos_x = w;
	pos_y = h;
	pos_w = w;
	pos_h = h;
	size = 100.0f;

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("spikedgear.png");

	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(1).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(2).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(3).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(4).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(5).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(6).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(7).png"));
	m_enemy_sprites.push_back(m_state->getFullAssetPath("spikedgear(8).png"));

}

void Enemy::debugDraw()
{
	graphics::Brush debug_brush;
	
	debug_brush.outline_opacity = 1.0f;
	debug_brush.texture = "";
	debug_brush.fill_color[0] = 1.0f;
	debug_brush.fill_color[1] = 0.3f;
	debug_brush.fill_color[2] = 0.3f;
	debug_brush.fill_opacity = 0.3f;
	debug_brush.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, debug_brush);
}

Enemy::Enemy()
{
	init(w, h);
}

Enemy::~Enemy()
{
}