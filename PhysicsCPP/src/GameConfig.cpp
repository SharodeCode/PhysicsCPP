#include "GameConfig.h"

int GameConfig::windowWidth = 800;
int GameConfig::windowHeight = 800;

void GameConfig::setWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}
