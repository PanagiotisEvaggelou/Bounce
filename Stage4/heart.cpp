#include "heart.h"
#include <sgg/graphics.h>
#include <random>
#include "util.h"

bool Heart::floatEquals(float x, float y, float epsilon = 0.01f) {
	if (fabs(x - y) < epsilon)
		return true; //they are same
	return false; //they are not same
}

Disk Heart::getCollisionHull() const
{
	Disk disk{};
	disk.cx = pos_x + m_state->m_global_offset_x;
	disk.cy = pos_y + m_state->m_global_offset_y;
	disk.radius = 0.35f;
	return disk;
}

void Heart::update(float dt)
{
	timer -= dt / 150.0f;
	if (timer <= 0.0f) {
		if (nextSprite <= 5) {
			nextSprite++;
		}
		else {
			nextSprite = 0;
		}
		timer = 1.0f;
	}

}

void Heart::draw()
{


	m_brush_star.texture = m_star_sprites[nextSprite];
	graphics::drawRect(pos_x + m_state->m_global_offset_x, pos_y + m_state->m_global_offset_y, 1.0f, 1.0f, m_brush_star);


	if (m_state->m_debugging)
		debugDraw();

}

void Heart::init(float w, float h)
{
	pos_x = w;
	pos_y = h;
	size = 100.0f;

	m_brush_star.fill_opacity = 1.0f;
	m_brush_star.outline_opacity = 0.0f;
	m_brush_star.texture = m_state->getFullAssetPath("heart.png");

	m_star_sprites.push_back(m_state->getFullAssetPath("heart.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart0.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart1.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart2.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart3.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart4.png"));
	m_star_sprites.push_back(m_state->getFullAssetPath("heart5.png"));

}

void Heart::debugDraw()
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

Heart::Heart()
{
	init(w, h);
}

Heart::~Heart()
{
}