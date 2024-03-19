#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "star.h"
#include "util.h"
#include "enemy.h"
#include "spikes.h"
#include "gamestate.h"


/**
 * Updates the start screen of the level.
 * @param dt The time since the last update in milliseconds.
 */
void Level::updateStartScreen(float dt)
{
	// Update timer variables
	currenttimer = timer;
	timer = timer + dt / 1000.0f;
	timerpress2 = timerpress2 + dt / 1000.0f;

	// Check if Enter key is pressed to initiate the game
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		graphics::stopMusic(100);
		enter = true;
		currenttimer2 = timer;
		
	}
	// Perform animations on the start screen if Enter key is pressed
	if (enter) {
		// Determine animation frame based on time elapsed since Enter was pressed
		// and set the corresponding drawB value
		// This controls which image is displayed on the start screen
		// depending on the elapsed time since Enter was pressed
		if ((timer - currenttimer2) < 0.05f) {
			drawB = 1;
		}
		else if (((timer - currenttimer2) < 0.10f) && ((timer - currenttimer2) > 0.05f)) {
			drawB = 2;
		}
		else if (((timer - currenttimer2) < 0.15f) && ((timer - currenttimer2) > 0.10f)) {
			drawB = 3;
		}
		else if (((timer - currenttimer2) < 0.20f) && ((timer - currenttimer2) > 0.15f)) {
			drawB = 4;
		}
		else if (((timer - currenttimer2) < 0.25f) && ((timer - currenttimer2) > 0.20f)) {
			drawB = 5;
		}
		else if (((timer - currenttimer2) < 0.30f) && ((timer - currenttimer2) > 0.25f)){
			drawB = 6;
		}
		else if (((timer - currenttimer2) < 0.35f) && ((timer - currenttimer2) > 0.30f)) {
			drawB = 7;
		}
		else if (((timer - currenttimer2) < 0.40f) && ((timer - currenttimer2) > 0.35f)) {
			drawB = 8;
		}
		else if (((timer - currenttimer2) < 0.45f) && ((timer - currenttimer2) > 0.40f)) {
			drawB = 9;
		}
		else if (((timer - currenttimer2) < 0.50f) && ((timer - currenttimer2) > 0.45f)) {
			drawB = 10;
		}
		else if (((timer - currenttimer2) < 0.55f) && ((timer - currenttimer2) > 0.50f)) {
			drawB = 11;
		}
	}


	// Check if 'H' key is pressed to display help screen
	if (timerpress2 > 0.20f) {
		if (graphics::getKeyState(graphics::SCANCODE_H)) {
			timerpress2 = 0.0f;
			status = STATUS_HELP;
		}

	}

	// Increment timer count
	if ((int)timer!=(int)currenttimer) {
		timercount++;
		if (timercount == 3) {
			timercount = 0;
		}
	}

}
/**
 * Draws the start screen of the level.
 */
void Level::drawStartScreen()
{

	// Draw background and text for the start screen
	float w2 = m_state->getCanvasWidth();
	float h2 = m_state->getCanvasHeight();
	m_brush_start_background.outline_opacity = 0.0f;

	if (!enter) {
		const std::string m_asset_path = "assets\\";
		graphics::setFont(m_asset_path + "FONT5.ttf");
		graphics::Brush br;
		graphics::Brush br2;


		m_brush_start_background.texture = m_state->getMap()[1];

		graphics::drawRect(w2 / 2, h2 / 2, w2, h2, m_brush_start_background);
		
		char info2[40];
		br2.fill_color[0] = 0.0f;
		br2.fill_color[1] = 1.0f;
		br2.fill_color[2] = 0.0f;
		sprintf_s(info2, "Bounce");
		graphics::drawText(1.30f, 1.3f, 1.0, info2, br2);

		char info[40];
		sprintf_s(info, "Press <ENTER> to start");

		
		if (timercount == 0) {
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		else if (timercount == 1) {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 0.0f;
		}
		else if (timercount == 2) {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 1.0f;
		}

		graphics::drawText(1.0f, 5.5f, 0.35, info, br);
		

		char info5[40];
		sprintf_s(info5, "H  :  HELP");
		graphics::drawText(0.15f, 5.8f, 0.15, info5, br2);
	}
	else {

		if (drawB == 1) {
			m_brush_start_background.texture = m_state->getMap()[2];
		}
		else if (drawB == 2) {
			m_brush_start_background.texture = m_state->getMap()[4];
		}
		else if (drawB == 3) {
			m_brush_start_background.texture = m_state->getMap()[5];
		}
		else if (drawB == 4) {
			m_brush_start_background.texture = m_state->getMap()[6];
		}
		else if (drawB == 5) {
			m_brush_start_background.texture = m_state->getMap()[7];
		}
		else if (drawB == 6) {
			m_brush_start_background.texture = m_state->getMap()[8];
		}
		else if (drawB == 7) {
			m_brush_start_background.texture = m_state->getMap()[9];
		}
		else if (drawB == 8) {
			m_brush_start_background.texture = m_state->getMap()[10];
		}
		else if (drawB == 9) {
			m_brush_start_background.texture = m_state->getMap()[11];
		}
		else if (drawB == 10) {
			m_brush_start_background.texture = m_state->getMap()[12];
		}
		else if (drawB == 11) {
			m_brush_start_background.texture = m_state->getMap()[12];
			status = STATUS_PLAYING;
		}

		graphics::drawRect(w2 / 2, h2 / 2, w2, h2, m_brush_start_background);
	}



}



/**
 * Updates the help screen of the level.
 * @param dt The time since the last update in milliseconds.
 */
void Level::updateHelpScreen(float dt)
{
	// Update timer for help screen
	timerpress1 = timerpress1 + dt / 1000.0f;
	// Check if 'H' key is pressed to exit help screen
	if (timerpress1 > 0.20f) {
		if (graphics::getKeyState(graphics::SCANCODE_H)) {
			timerpress1 = 0.0f;
			status = STATUS_START;
		}
	}

}
/**
 * Draws the help screen of the level.
 */
void Level::drawHelpScreen()
{
	// Draw background and help information
	const std::string m_asset_path = "assets\\";
	graphics::setFont(m_asset_path + "FONT5.ttf");
	graphics::Brush br;
	graphics::Brush br2;
	br2.fill_color[0] = 0.0f;
	br2.fill_color[1] = 1.0f;
	br2.fill_color[2] = 0.0f;

	float w2 = m_state->getCanvasWidth();
	float h2 = m_state->getCanvasHeight();


	m_brush_start_background.outline_opacity = 0.0f;
	m_brush_start_background.texture = m_state->getMap()[25];

	graphics::drawRect(w2 / 2, h2 / 2, w2, h2, m_brush_start_background);

	char info0[40];
	sprintf_s(info0, "Collect  all   3   stars  to  win");
	graphics::drawText(0.5f, 1.2f, 0.25, info0, br);
	

	char info1[40];
	sprintf_s(info1, "COLLECT A HEART TO GAIN A LIFE");
	graphics::drawText(0.5f, 2.6f, 0.25, info1, br);


	char info2[60];
	sprintf_s(info2, "Use   A  W  D   to  move  LEFT  UP and  DOWN");
	graphics::drawText(0.5f, 3.6f, 0.25, info2, br);


	char info5[40];
	sprintf_s(info5, "H :  EXIT  HELP");
	graphics::drawText(0.15f, 5.8f, 0.15, info5, br2);
}



/**
 * Updates the main level screen.
 * @param dt The time since the last update in milliseconds.
 */
void Level::updateLevelScreen(float dt)
{
	// Update various game elements and perform collision detection
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		StarsCollected = 3;
	}

	float currenttimer = timer2;
	timer2 = timer2 + dt / 1000.0f;

	if ((int)timer != (int)currenttimer) {
		timer2count++;
	}

	if (graphics::getKeyState(graphics::SCANCODE_L)) {

		if (m_state->getPlayer()->life < 0.8f) {
			m_state->getPlayer()->addLife(0.21f);
			graphics::playSound(m_state->getFullAssetPath("heart.wav"), 1.0f);
		}
	}

	updatePlayer(dt);
	updateEnemies(dt);
	updateHearts(dt);
	updateStars(dt);

	checkCollisionsPlayer();
	checkCollisionsEnemies(dt);
	checkCollisionsHearts(dt);
	checkCollisionsStars(dt);
	checkCollisionsSpikes(dt);

	if (StarsCollected == 3) {
		status = STATUS_WIN;
	}

	GameObject::update(dt);

}
/**
 * Draws the main level screen.
 */
void Level::drawLevelScreen()
{
	// Draw background, player, enemies, stars, hearts, etc.
	play_sound = true;
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;


	graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);


	drawPlayer();

	drawBlocks();

	drawEnemies();
	
	drawStars();

	drawHearts();

	drawSpikes();

	drawLifeBar();

	drawStarsCollected();

}



/**
 * Updates the game over screen.
 */
void Level::updateGameOverScreen()
{
	// Check if Enter key is pressed to restart the game
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;

	}
}
/**
 * Draws the game over screen.
 */
void Level::drawGameOverScreen()
{
	// Draw background and game over message
	graphics::stopMusic(100);
	music2 = false;

	m_state->getPlayer()->m_pos_x = -4.0f;
	m_state->getPlayer()->m_pos_y = 14.0f;
	m_state->getPlayer()->life = 0.8f;


	float w2 = m_state->getCanvasWidth();
	float h2 = m_state->getCanvasHeight();
	m_brush_game_over_background.texture = m_state->getMap()[17];

	graphics::drawRect(w2 / 2, h2 / 2, w2, h2, m_brush_game_over_background);

	if (play_sound) {
		graphics::playSound(m_state->getFullAssetPath("game_over2.wav"), 1.0f);
		play_sound = false;
	}


	const std::string m_asset_path = "assets\\";
	graphics::setFont(m_asset_path + "FONT5.ttf");
	graphics::Brush br;

	char info[40];
	sprintf_s(info, "GAME  OVER");
	graphics::drawText(1.0f, 3.2f, 0.70, info, br);

	char info2[40];
	sprintf_s(info2, "PRESS <ENTER> TO START OVER");
	graphics::drawText(1.0f, 3.5f, 0.20, info2, br);

}



/**
 * Updates the win screen.
 */
void Level::updateWinScreen()
{
	// Update win screen elements if needed
}
/**
 * Draws the win screen.
 */
void Level::drawWinScreen() {

	// Draw background and win message
	graphics::stopMusic(100);

	float w2 = m_state->getCanvasWidth();
	float h2 = m_state->getCanvasHeight();
	m_brush_win_background.texture = m_state->getMap()[48];

	graphics::drawRect(w2 / 2, h2 / 2, w2, h2, m_brush_win_background);


	if (play_sound) {
		graphics::playSound(m_state->getFullAssetPath("win.wav"), 1.0f);
		play_sound = false;
	}

	const std::string m_asset_path = "assets\\";
	graphics::setFont(m_asset_path + "FONT5.ttf");
	graphics::Brush br;

	char info[40];
	sprintf_s(info, "YOU WON");
	graphics::drawText(1.5f, 3.0f, 0.7, info, br);

	graphics::Brush br2;
	char info2[40];
	char buffer[20];
	sprintf_s(buffer, "SCORE : %d", timer2count);
	sprintf_s(info2, buffer);
	graphics::drawText(2.1f, 2.4f, 0.35, info2, br2);

}



/**
 * Updates the movement and behavior of the player, enemies, hearts, stars.
 * @param dt The time since the last update in milliseconds.
 */
void Level::updateEnemies(float dt) {
	// Update each enemy's movement and behavior

	if (m_enemy) {
		m_enemy->update(dt, 6.00f, true);
	}
	if (m_enemy2) {
		m_enemy2->update(dt, 5.00f, true);
	}
	if (m_enemy3) {
		m_enemy3->update(dt, 5.00f, false);
	}
	if (m_enemy4) {
		m_enemy4->update(dt, 3.00f, false);
	}
	if (m_enemy5) {
		m_enemy5->update(dt, 3.00f, false);
	}

	if (m_enemy6) {
		m_enemy6->update(dt, 4.00f, true);
	}

	if (m_enemy7) {
		m_enemy7->update(dt, 2.00f, true);
	}
	if (m_enemy8) {
		m_enemy8->update(dt, 2.00f, false);
	}

	if (m_enemy9) {
		m_enemy9->update(dt, 2.00f, false);
	}
}
void Level::updatePlayer(float dt) {

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

}
void Level::updateHearts(float dt) {

	if (m_heart1) {
		m_heart1->update(dt);
	}
	if (m_heart2) {
		m_heart2->update(dt);
	}

}
void Level::updateStars(float dt) {

	if (m_star1) {
		m_star1->update(dt);
	}
	if (m_star2) {
		m_star2->update(dt);
	}
	if (m_star3) {
		m_star3->update(dt);
	}

}



/**
 * Checks collisions between the player and various game elements.
 */
void Level::checkCollisionsPlayer()
{

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_on_ground = true;

			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("bounce.ogg"), 1.0f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}


	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}

	}

	Disk d1 = m_state->getPlayer()->getCollisionHull();

	for (auto& block : m_blocks)
	{
		if (block.m_pos_y < m_state->getPlayer()->m_pos_y) {

			if ((m_state->getPlayer()->m_pos_x > block.m_pos_x - block.m_width / 2) && (m_state->getPlayer()->m_pos_x < block.m_pos_x + block.m_width / 2)) {

				float dy1 = (m_state->getPlayer()->m_pos_y - d1.radius);
				float dy2 = (block.m_pos_y + block.m_height / 2);

				if (dy1 - dy2 < 0.0000001f) {


					m_state->getPlayer()->m_pos_y = block.m_pos_y + block.m_height / 2 + d1.radius + 0.00000001f;
					m_state->getPlayer()->m_vy = 0.0f;
				}

			}

		}
	}


}

bool Level::checkCollisionsEnemy1()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy2()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy2->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy3()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy3->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy4()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy4->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy5()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy5->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy6()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy6->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy7()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy7->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy8()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy8->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsEnemy9()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_enemy9->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
void Level::checkCollisionsEnemies(float dt)
{

	bool collision = checkCollisionsEnemy1();
	//printf("%s\n", collision ? "true" : "false");
	if (collision) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision2 = checkCollisionsEnemy2();
	//printf("%s\n", collision ? "true" : "false");
	if (collision2) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision3 = checkCollisionsEnemy3();
	//printf("%s\n", collision ? "true" : "false");
	if (collision3) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision4 = checkCollisionsEnemy4();
	//printf("%s\n", collision ? "true" : "false");
	if (collision4) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision5 = checkCollisionsEnemy5();
	//printf("%s\n", collision ? "true" : "false");
	if (collision5) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision6 = checkCollisionsEnemy6();
	//printf("%s\n", collision ? "true" : "false");
	if (collision6) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision7 = checkCollisionsEnemy7();
	//printf("%s\n", collision ? "true" : "false");
	if (collision7) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision8 = checkCollisionsEnemy8();
	//printf("%s\n", collision ? "true" : "false");
	if (collision8) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	bool collision9 = checkCollisionsEnemy9();
	//printf("%s\n", collision ? "true" : "false");
	if (collision9) {
		if (m_grace_period_timer == 0.0f) {
			//printf("%s\n", "m_grace_period_timer == 0.0f");
			m_state->getPlayer()->drainLife(0.21f);

			if (m_state->getPlayer()->life <= 0.0f) {
				status = STATUS_GAME_OVER;
			}

			if (status != STATUS_GAME_OVER) {
				graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
			}

			damaged = true;
			m_grace_period_timer = m_grace_period_duration;
			//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
		}
	}

	// Update the grace period timer
	if (m_grace_period_timer > 0.0f) {
		m_grace_period_timer -= dt / 1000.0f; // Update timer in seconds
		//printf("m_grace_period_timer AFTER = (%.2f)\n\n", m_grace_period_timer);
	}

	if (m_grace_period_timer <= 0.0f) {
		m_grace_period_timer = +0.0f;
		damaged = false;
	}

}

bool Level::checkCollisionsSpikes1()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes1->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes2()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes2->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes3()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes3->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes4()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes4->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes5()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes5->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes6()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes6->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes7()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes7->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes8()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes8->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes9()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes9->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes10()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes10->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes11()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes11->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes12()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes12->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes13()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes13->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes14()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes14->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes15()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes15->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsSpikes16()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_spikes16->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
void Level::checkCollisionsSpikes(float dt) {

	if (m_spikes1) {
		collisionSpikes1 = checkCollisionsSpikes1();
		if (collisionSpikes1) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes2) {
		collisionSpikes2 = checkCollisionsSpikes2();
		if (collisionSpikes2) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes3) {
		collisionSpikes3 = checkCollisionsSpikes3();
		if (collisionSpikes3) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes4) {
		collisionSpikes4 = checkCollisionsSpikes4();
		if (collisionSpikes4) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes5) {
		collisionSpikes5 = checkCollisionsSpikes5();
		if (collisionSpikes5) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes6) {
		collisionSpikes6 = checkCollisionsSpikes6();
		if (collisionSpikes6) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes7) {
		collisionSpikes7 = checkCollisionsSpikes7();
		if (collisionSpikes7) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes8) {
		collisionSpikes8 = checkCollisionsSpikes8();
		if (collisionSpikes8) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes9) {
		collisionSpikes9 = checkCollisionsSpikes9();
		if (collisionSpikes9) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes10) {
		collisionSpikes10 = checkCollisionsSpikes10();
		if (collisionSpikes10) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes11) {
		collisionSpikes11 = checkCollisionsSpikes11();
		if (collisionSpikes11) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes12) {
		collisionSpikes12 = checkCollisionsSpikes12();
		if (collisionSpikes12) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_spikes13) {
		collisionSpikes13 = checkCollisionsSpikes13();
		if (collisionSpikes13) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes14) {
		collisionSpikes14 = checkCollisionsSpikes14();
		if (collisionSpikes14) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}
	if (m_spikes15) {
		collisionSpikes15 = checkCollisionsSpikes15();
		if (collisionSpikes15) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}


	if (m_spikes16) {
		collisionSpikes16 = checkCollisionsSpikes16();
		if (collisionSpikes16) {

			if (m_grace_period_timer == 0.0f) {
				//printf("%s\n", "m_grace_period_timer == 0.0f");
				m_state->getPlayer()->drainLife(0.21f);

				if (m_state->getPlayer()->life <= 0.0f) {
					status = STATUS_GAME_OVER;
				}

				if (status != STATUS_GAME_OVER) {
					graphics::playSound(m_state->getFullAssetPath("damage.wav"), 1.0f);
				}

				damaged = true;
				m_grace_period_timer = m_grace_period_duration;
				//printf("m_grace_period_timer = (%.2f)\n\n", m_grace_period_timer);
			}
		}
	}

	if (m_grace_period_timer > 0.0f) {
		m_grace_period_timer -= dt / 1000.0f; // Update timer in seconds
		//printf("m_grace_period_timer AFTER = (%.2f)\n\n", m_grace_period_timer);
	}
	if (m_grace_period_timer <= 0.0f) {
		m_grace_period_timer = +0.0f;
		damaged = false;
	}

}

bool Level::checkCollisionsStar1()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_star1->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsStar2()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_star2->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsStar3()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_star3->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
void Level::checkCollisionsStars(float dt) {

	if (m_star1) {
		collisionStar1 = checkCollisionsStar1();
		if (collisionStar1) {
			graphics::playSound(m_state->getFullAssetPath("star.wav"), 1.0f);
			delete m_star1;
			m_star1 = nullptr;

			//starAnim();

			StarsCollected++;
		}
	}
	if (m_star2) {
		collisionStar2 = checkCollisionsStar2();
		if (collisionStar2) {
			graphics::playSound(m_state->getFullAssetPath("star.wav"), 1.0f);
			delete m_star2;
			m_star2 = nullptr;
			StarsCollected++;
		}
	}
	if (m_star3) {
		collisionStar3 = checkCollisionsStar3();
		if (collisionStar3) {
			graphics::playSound(m_state->getFullAssetPath("star.wav"), 1.0f);
			delete m_star3;
			m_star3 = nullptr;
			StarsCollected++;
		}
	}
	
}

bool Level::checkCollisionsHeart1()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_heart1->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Level::checkCollisionsHeart2()
{
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = m_heart2->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		return true;
	}
	else
	{
		return false;
	}
}
void Level::checkCollisionsHearts(float dt) {

	if (m_heart1) {
		collisionHeart1 = checkCollisionsHeart1();
		if (collisionHeart1) {
			graphics::playSound(m_state->getFullAssetPath("heart.wav"), 1.0f);
			if (m_state->getPlayer()->life < 0.8f) {
				m_state->getPlayer()->addLife(0.21f);
			}
			delete m_heart1;
			m_heart1 = nullptr;
		}
	}
	if (m_heart2) {
		collisionHeart2 = checkCollisionsHeart2();
		if (collisionHeart2) {
			graphics::playSound(m_state->getFullAssetPath("heart.wav"), 1.0f);
			if (m_state->getPlayer()->life < 0.8f) {
				m_state->getPlayer()->addLife(0.21f);
			}
			delete m_heart2;
			m_heart2 = nullptr;
		}
	}

}



/**
 * Draw the player, enemies, stars, spikes and hearts in the level.
 */
void Level::drawPlayer() {

	if (m_state->getPlayer()->isActive())
		if (damaged == false) {
			m_state->getPlayer()->draw();
		}
		else {
			if (m_grace_period_timer <= 2.00f and m_grace_period_timer >= 1.70f)
				m_state->getPlayer()->drawDamaged();
			else if (m_grace_period_timer <= 1.70f and m_grace_period_timer >= 1.40f)
				m_state->getPlayer()->draw();
			else if (m_grace_period_timer <= 1.40f and m_grace_period_timer >= 1.10f)
				m_state->getPlayer()->drawDamaged();
			else if (m_grace_period_timer <= 1.10f and m_grace_period_timer >= 0.80f)
				m_state->getPlayer()->draw();
			else if (m_grace_period_timer <= 0.80f and m_grace_period_timer >= 0.50f)
				m_state->getPlayer()->drawDamaged();
			else if (m_grace_period_timer <= 0.50f and m_grace_period_timer >= 0.20f)
				m_state->getPlayer()->draw();
			else if (m_grace_period_timer <= 0.20f and m_grace_period_timer >= 0.0f)
				m_state->getPlayer()->drawDamaged();
		}
}

void Level::drawEnemies() {

	if (m_enemy) {
		m_enemy->drawvertical();
	}
	if (m_enemy2) {
		m_enemy2->drawvertical();
	}
	if (m_enemy3) {
		m_enemy3->drawhorizontal();
	}
	if (m_enemy4) {
		m_enemy4->drawhorizontal();
	}
	if (m_enemy5) {
		m_enemy5->drawhorizontal();
	}
	if (m_enemy6) {
		m_enemy6->drawvertical();
	}
	if (m_enemy7) {
		m_enemy7->drawvertical();
	}
	if (m_enemy8) {
		m_enemy8->drawhorizontal();
	}
	if (m_enemy9) {
		m_enemy9->drawhorizontal();
	}

}

void Level::drawHearts() {

	if (m_heart1) {
		m_heart1->draw();
	}
	if (m_heart2) {
		m_heart2->draw();
	}

}

void Level::drawSpikes() {

	if (m_spikes1) {
		m_spikes1->draw();
	}
	if (m_spikes2) {
		m_spikes2->draw();
	}
	if (m_spikes3) {
		m_spikes3->draw();
	}
	if (m_spikes4) {
		m_spikes4->draw();
	}
	if (m_spikes5) {
		m_spikes5->draw();
	}
	if (m_spikes6) {
		m_spikes6->draw();
	}
	if (m_spikes7) {
		m_spikes7->draw();
	}
	if (m_spikes8) {
		m_spikes8->draw();
	}
	if (m_spikes9) {
		m_spikes9->draw();
	}
	if (m_spikes10) {
		m_spikes10->draw();
	}
	if (m_spikes11) {
		m_spikes11->draw();
	}
	if (m_spikes12) {
		m_spikes12->draw();
	}
	if (m_spikes13) {
		m_spikes13->draw();
	}
	if (m_spikes14) {
		m_spikes14->draw();
	}
	if (m_spikes15) {
		m_spikes15->draw();
	}
	if (m_spikes16) {
		m_spikes16->draw();
	}

}

void Level::drawStars() {

	if (m_star1) {
		m_star1->draw();
	}
	if (m_star2) {
		m_star2->draw();
	}
	if (m_star3) {
		m_star3->draw();
	}

}

void Level::drawBlocks() {

	for (int i = 0; i < m_blocks.size(); i++)
	{
		Box& box = m_blocks[i];
		std::string& name = m_block_names[i];

		float x = box.m_pos_x + m_state->m_global_offset_x;
		float y = box.m_pos_y + m_state->m_global_offset_y;

		m_block_brush.texture = m_state->getFullAssetPath(name);

		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush);

		if (m_state->m_debugging)
			graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
	}

}



/**
 * Draw the player's life, stars collected and score.
 */
void Level::drawLifeBar() {

	float player_life = m_state->getPlayer()->getRemainingLife();

	m_brush_life.outline_opacity = 1.0f;
	m_brush_life.fill_opacity = 1.0f;
	m_brush_life.fill_color[0] = 1.0f;
	m_brush_life.fill_color[1] = 0.2f;
	m_brush_life.fill_color[2] = 0.2f;
	m_brush_life.fill_secondary_color[0] = 0.2f;
	m_brush_life.fill_secondary_color[1] = 0.2f;
	m_brush_life.fill_secondary_color[2] = 1.0f;
	m_brush_life.gradient = true;
	graphics::drawRect(5.75f, 0.5f + 0.5f * (0.8f - player_life), 0.2f, 0.8f - (0.8f - player_life), m_brush_life);

	m_brush_life.outline_opacity = 1.0f;
	m_brush_life.gradient = false;
	m_brush_life.fill_opacity = 0.0f;
	m_brush_life.fill_color[0] = 0.0f;
	m_brush_life.fill_color[1] = 0.0f;
	m_brush_life.fill_color[2] = 0.0f;
	graphics::drawRect(5.75f, 0.5f, 0.2f, 0.8f, m_brush_life);

}

void Level::drawStarsCollected() {

	m_brush_star.fill_opacity = 1.0f;
	m_brush_star.outline_opacity = 0.0f;
	m_brush_star.texture = m_state->getMap()[46];
	graphics::drawRect(5.40f, 0.2f, 0.2f, 0.2f, m_brush_star);
	graphics::drawRect(5.15f, 0.2f, 0.2f, 0.2f, m_brush_star);
	graphics::drawRect(4.90f, 0.2f, 0.2f, 0.2f, m_brush_star);

	m_brush_star2.fill_opacity = 1.0f;
	m_brush_star2.outline_opacity = 0.0f;
	m_brush_star2.texture = m_state->getMap()[38];

	if (StarsCollected == 1) {
		graphics::drawRect(5.40f, 0.2f, 0.2f, 0.2f, m_brush_star2);

	}
	if (StarsCollected == 2) {
		graphics::drawRect(5.40f, 0.2f, 0.2f, 0.2f, m_brush_star2);
		graphics::drawRect(5.15f, 0.2f, 0.2f, 0.2f, m_brush_star2);
	}
	if (StarsCollected == 3) {
		graphics::drawRect(5.40f, 0.2f, 0.2f, 0.2f, m_brush_star2);
		graphics::drawRect(5.15f, 0.2f, 0.2f, 0.2f, m_brush_star2);
		graphics::drawRect(4.90f, 0.2f, 0.2f, 0.2f, m_brush_star2);
	}
	

	//Score
	const std::string m_asset_path = "assets\\";
	graphics::setFont(m_asset_path + "FONT5.ttf");
	graphics::Brush br2;
	char info[40];
	char buffer[20];
	sprintf_s(buffer, "%d", timer2count);
	sprintf_s(info, buffer);
	graphics::drawText(0.10f, 0.20f, 0.17, info, br2);

}



/**
 * Spawns enemies, spikes, stars and hearts at predefined positions if they don't already exist.
 */
void Level::spawnEnemy()
{
	if (!m_enemy) {
		m_enemy = new Enemy();
		m_enemy->init(-4.00f, 9.00f);
	}
	if (!m_enemy2) {
		m_enemy2 = new Enemy();
		m_enemy2->init(6.00f, 12.00f);
	}
	if (!m_enemy3) {
		m_enemy3 = new Enemy();
		m_enemy3->init(7.00f, 8.00f);
	}
	if (!m_enemy4) {
		m_enemy4 = new Enemy();
		m_enemy4->init(7.00f, 2.00f);
	}
	if (!m_enemy5) {
		m_enemy5 = new Enemy();
		m_enemy5->init(-1.00f, 2.00f);
	}
	if (!m_enemy6) {
		m_enemy6 = new Enemy();
		m_enemy6->init(-4.00f, 2.00f);
	}
	if (!m_enemy7) {
		m_enemy7 = new Enemy();
		m_enemy7->init(2.00f, 2.00f);
	}
	if (!m_enemy8) {
		m_enemy8 = new Enemy();
		m_enemy8->init(1.00f, 3.00f);
	}
	if (!m_enemy9) {
		m_enemy9 = new Enemy();
		m_enemy9->init(5.00f, 3.00f);
	}
	
}

void Level::spawnSpikes()
{
	if (!m_spikes1) {
		m_spikes1 = new Spikes();
		m_spikes1->init(0.00f, 14.435f);
	}
	if (!m_spikes2) {
		m_spikes2 = new Spikes();
		m_spikes2->init(2.00f, 14.435f);
	}
	if (!m_spikes3) {
		m_spikes3 = new Spikes();
		m_spikes3->init(4.00f, 14.435f);
	}
	if (!m_spikes4) {
		m_spikes4 = new Spikes();
		m_spikes4->init(6.00f, 14.435f);
	}
	if (!m_spikes5) {
		m_spikes5 = new Spikes();
		m_spikes5->init(8.00f, 14.435f);
	}
	if (!m_spikes6) {
		m_spikes6 = new Spikes();
		m_spikes6->init(9.00f, 14.435f);
	}
	if (!m_spikes7) {
		m_spikes7 = new Spikes();
		m_spikes7->init(11.00f, 14.435f);
	}


	if (!m_spikes8) {
		m_spikes8 = new Spikes();
		m_spikes8->init(8.00f, 6.435f);
	}
	if (!m_spikes9) {
		m_spikes9 = new Spikes();
		m_spikes9->init(6.00f, 6.435f);
	}
	if (!m_spikes10) {
		m_spikes10 = new Spikes();
		m_spikes10->init(4.00f, 6.435f);
	}
	if (!m_spikes11) {
		m_spikes11 = new Spikes();
		m_spikes11->init(3.00f, 6.435f);
	}
	if (!m_spikes12) {
		m_spikes12 = new Spikes();
		m_spikes12->init(2.00f, 6.435f);
	}
	if (!m_spikes13) {
		m_spikes13 = new Spikes();
		m_spikes13->init(0.00f, 6.435f);
	}
	if (!m_spikes14) {
		m_spikes14 = new Spikes();
		m_spikes14->init(-2.00f, 6.435f);
	}
	if (!m_spikes15) {
		m_spikes15 = new Spikes();
		m_spikes15->init(-3.00f, 6.435f);
	}
	if (!m_spikes16) {
		m_spikes16 = new Spikes();
		m_spikes16->init(-4.00f, 6.435f);
	}


}

void Level::spawnStar()
{
	if (!m_star1) {
		m_star1 = new Star();
		m_star1->init(-3.00f, 1.00f);
	}
	if (!m_star2) {
		m_star2 = new Star();
		m_star2->init(3.00f, 1.00f);
	}
	if (!m_star3) {
		m_star3 = new Star();
		m_star3->init(10.00f, 11.00f);
	}

}

void Level::spawnHeart()
{
	if (!m_heart1) {
		m_heart1 = new Heart();
		m_heart1->init(5.00f, 9.00f);
	}
	if (!m_heart2) {
		m_heart2 = new Heart();
		m_heart2->init(10.00f, 2.00f);
	}

}



/**
 * Updates the current state of the level based on the time elapsed since the last update.
 *
 * @param dt Time elapsed since the last update.
 */
void Level::update(float dt)
{
	// Handle different game statuses and update accordingly.
	if (status == STATUS_START) {
		updateStartScreen(dt);
	}
	else if (status == STATUS_PLAYING) {
		updateLevelScreen(dt);
	}
	else if (status == STATUS_GAME_OVER) {
		updateGameOverScreen();
	}
	else if (status == STATUS_WIN) {
		updateWinScreen();
	}
	else if (status == STATUS_HELP) {
		updateHelpScreen(dt);
	}
	
}



/**
 * Draws the current state of the level.
 */
void Level::draw()
{
	// Draw different screens based on the game status.
	if (status == STATUS_START) {
		if (music1 == false) {
			graphics::playMusic(m_state->getFullAssetPath("startmusic.mp3"), 0.6f, true);
			music1 = true;
		}
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING){
		if (music2 == false) {
			graphics::playMusic(m_state->getFullAssetPath("music2.mp3"), 0.6f, true);
			music2 = true;
		}
		drawLevelScreen();
	}
	else if (status == STATUS_GAME_OVER) {
		drawGameOverScreen();
	}
	else if (status == STATUS_WIN) {
		drawWinScreen();
	}
	else if (status = STATUS_HELP) {
		drawHelpScreen();
	}

}



/**
 * Draws the blocks composing the level layout.
 */
void Level::drawLevelBlocks() {

	for (int i = -7; i <= 14; i++) {
		for (int j = -3; j <= 0; j++) {
			m_blocks.push_back(Box(i, j, 1, 1));
		}
		for (int j = 15; j <= 17; j++) {
			m_blocks.push_back(Box(i, j, 1, 1));
		}
	}
	for (int j = -3; j <= 17; j++) {
		for (int i = -7; i <= -5; i++) {
			m_blocks.push_back(Box(i, j, 1, 1));
		}
		for (int i = 12; i <= 14; i++) {
			m_blocks.push_back(Box(i, j, 1, 1));
		}
	}

	for (int i = -1; i <= 7; i = i + 2) {
		m_blocks.push_back(Box(i, 14, 1, 1));
	}
	for (int i = 1; i <= 5; i = i + 2) {
		m_blocks.push_back(Box(i, 13, 1, 1));

	}
	for (int i = -4; i <= 7; i++) {
		m_blocks.push_back(Box(i, 7, 1, 1));
	}

	m_blocks.push_back(Box(-4, 12, 1, 1));
	m_blocks.push_back(Box(-4, -1, 1, 1));

	m_blocks.push_back(Box(-3, 4, 1, 1));

	m_blocks.push_back(Box(-1, 6, 1, 1));
	m_blocks.push_back(Box(-1, 1, 1, 1));
	m_blocks.push_back(Box(-1, 0, 1, 1));
	m_blocks.push_back(Box(-1, -1, 1, 1));
	m_blocks.push_back(Box(-1, 11, 1, 1));

	m_blocks.push_back(Box(1, 12, 1, 1));
	m_blocks.push_back(Box(1, 11, 1, 1));
	m_blocks.push_back(Box(1, 2, 1, 1));
	m_blocks.push_back(Box(1, 6, 1, 1));

	m_blocks.push_back(Box(3, 9, 1, 1));
	m_blocks.push_back(Box(3, 8, 1, 1));
	m_blocks.push_back(Box(3, 4, 1, 1));

	m_blocks.push_back(Box(5, 12, 1, 1));
	m_blocks.push_back(Box(5, 2, 1, 1));
	m_blocks.push_back(Box(5, 6, 1, 1));

	m_blocks.push_back(Box(7, 6, 1, 1));
	m_blocks.push_back(Box(7, 0, 1, 1));
	m_blocks.push_back(Box(7, 1, 1, 1));

	m_blocks.push_back(Box(8, 7, 1, 1));
	m_blocks.push_back(Box(8, 10, 1, 1));

	m_blocks.push_back(Box(9, 10, 1, 1));

	m_blocks.push_back(Box(10, 8, 1, 1));
	m_blocks.push_back(Box(10, 4, 1, 1));
	m_blocks.push_back(Box(10, 14, 1, 1));
	m_blocks.push_back(Box(10, 10, 1, 1));

	m_blocks.push_back(Box(11, 10, 1, 1));
	m_blocks.push_back(Box(11, -1, 1, 1));

	for (int i = 1; i <= 600; ++i) {
		m_block_names.push_back("wall.png");
	}


	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

}



/**
 * Initializes the level by initializing its components and spawning objects.
 */
void Level::init()
{

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	drawLevelBlocks();

	spawnEnemy();
	spawnStar();
	spawnHeart();
	spawnSpikes();
}

Level::Level(const std::string & name)
	: GameObject(name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("cave3.png");

}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}
