#include "GameConfig.h"

int GameConfig::WINDOW_WIDTH = 1800;
int GameConfig::WINDOW_HEIGHT = 900;

void GameConfig::setWindowSize(int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}
