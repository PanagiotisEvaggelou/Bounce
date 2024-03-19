#include <sgg/graphics.h>

#include "gamestate.h"
#include <vector>
#include <string>
#include <sgg/graphics.h>
#include <iostream>

void draw()
{
    GameState::getInstance()->draw();
}

void update(float dt)
{
    GameState::getInstance()->update(dt);
}


int main(int argc, char** argv)
{
    graphics::createWindow(800, 800, "Bounce");

    std::string dir = "assets\\";
    // Preload bitmaps
    std::vector<std::string> loadedBitmaps = graphics::preloadBitmaps(dir);

    // Check if bitmaps were loaded successfully
    if (!loadedBitmaps.empty()) {
        std::cout << "Bitmaps loaded successfully:\n";
        for (size_t i = 0; i < loadedBitmaps.size(); ++i) {
            std::cout << "Position " << i << ": " << loadedBitmaps[i] << std::endl;
        }
    }
    else {
        std::cout << "No bitmaps were loaded.\n";
    }

    GameState::getInstance()->init();
    GameState::getInstance()->setMap(loadedBitmaps);




    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
	return 0;
}

