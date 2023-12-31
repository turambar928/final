#include "GameManager.h"

GameManager *GameManager::_gInstance;


bool GameManager::init()
{
    _bIsPause = false;
    return true;
}
