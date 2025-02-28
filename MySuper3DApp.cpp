// MySuper3DApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <iostream>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>
#include "Game.h"
#include "TriangleComponent.h"
#include "GameComponent.h"


int main()
{
	Game * MyGame = new Game(L"My3DApp", 800, 800);

	MyGame->gameComponents.push_back(new TriangleComponent(MyGame));

	MyGame->Run();

    std::cout << "Hello World!\n";
}
