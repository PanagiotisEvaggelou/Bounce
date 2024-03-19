#include "spikes.h"
#include <sgg/graphics.h>
#include <random>
#include "util.h"


Rect Spikes::getCollisionHullRect() const
{
	Rect rect{};
	/*
	rect.xleft = pos_x - 0.5f + m_state->m_global_offset_x;
	rect.xright = pos_x + 0.5f + m_state->m_global_offset_x;
	rect.yup = pos_y - 0.5f + m_state->m_global_offset_y;
	rect.ydown = pos_y + 0.5f + m_state->m_global_offset_y;*/
	rect.x = pos_x + m_state->m_global_offset_x;
	rect.y = pos_y + m_state->m_global_offset_x;
	rect.w = 1.0f;
	rect.h = 0.15f;

	return rect;
}
Disk Spikes::getCollisionHull() const
{
	Disk disk{};
	disk.cx = pos_x + m_state->m_global_offset_x;
	disk.cy = pos_y + 0.2f + m_state->m_global_offset_y;
	disk.radius = 0.45f;
	return disk;
}


void Spikes::update()
{
	
}

void Spikes::draw()
{
	graphics::drawRect(pos_x + m_state->m_global_offset_x, pos_y + m_state->m_global_offset_y, 1.0f, 0.15f, m_brush_enemy);

	// Debug print
	//printf("Enemy Position: (%.2f, %.2f)\n", pos_x + m_state->m_global_offset_x, pos_y + m_state->m_global_offset_y);
	//printf("Actual Position: (%.2f, %.2f)\n\n", pos_x, pos_y);

	if (m_state->m_debugging)
		debugDraw();

}

void Spikes::init(float w, float h)
{
	speed = 0.001f;
	pos_x = w;
	pos_y = h;
	pos_w = w;
	pos_h = h;
	size = 100.0f;

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("Spikes2.png");

}

void Spikes::debugDraw()
{
	graphics::Brush debug_brush;

	debug_brush.outline_opacity = 1.0f;
	debug_brush.texture = "";
	debug_brush.fill_color[0] = 1.0f;
	debug_brush.fill_color[1] = 0.3f;
	debug_brush.fill_color[2] = 0.3f;
	debug_brush.fill_opacity = 0.3f;
	debug_brush.gradient = false;
	//Rect hull = getCollisionHullRect();
	//graphics::drawRect(hull.x, hull.y, hull.w, hull.h, debug_brush);
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy, hull.radius, debug_brush);
}

Spikes::Spikes()
{
	init(w, h);
}

Spikes::~Spikes()
{
}