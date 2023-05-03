/*
Names: Daniel, Owen, Thomas, Benjamin
Written: May 3, 2023
Last Edited: May 3, 2023
Program: Recreate the arcade game Bomberman

I hereby certify that this program represents my
work and that the design and logic was completed
without outside assistance.

used to remove the console window--> to bring console window back,
put this in linker-->system: Windows (/SUBSYSTEM:WINDOWS)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
*/
#include "Game/Game.h"
#include <iostream>


int main()
{
    // run the game
    Game game;
    game.run();
}