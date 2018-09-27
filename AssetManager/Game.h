#pragma once

#include <stdio.h>
#include "Window.h"
//#include "Textbox.h"
#include "AssetManager.hpp"
#include "TileMap.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "tinyxml2.h"
#include "TextureHolder.h"

using namespace tinyxml2;

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();


	sf::Time GetElapsed();
	void RestartClock();
	void placeTile();
	void setTilables();
	void chooseTile();
	void eraseTile();
	bool loadXML();
	void saveXML();

	int chosenTile;

	Window* GetWindow();
private:
	Window m_window;
	std::map<int, TextureHolder> spriteHolder;
	std::vector<TextureHolder> placedSprites;
	std::map<int, TextureHolder> tilesToChoose;

	sf::Clock m_clock;
	float m_elapsed;
    TileMap map;

};
