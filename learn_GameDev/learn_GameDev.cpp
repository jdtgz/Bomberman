// learn_GameDev.cpp : This is my fidling with creating a game on my own with sfml

// used to remove the console window --> to bring console window back, 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Game.h"

int main()
{
    Game game; 
    game.run(); 
}


