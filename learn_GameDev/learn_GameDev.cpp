// learn_GameDev.cpp : This is my fidling with creating a game on my own with sfml

// used to remove the console window --> to bring console window back, 
// put this in linker-->system: Windows (/SUBSYSTEM:WINDOWS)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Game.h"
#include <iostream>


int main()
{
    Game game;
    game.run();
}