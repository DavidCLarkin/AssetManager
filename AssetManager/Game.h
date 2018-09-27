#pragma once

#include <stdio.h>
#include "Window.h"
#include "Textbox.h"
#include "AssetManager.hpp"
#include "TileMap.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "tinyxml2.h"
#include "TextureHolder.h"

using namespace tinyxml2;

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	bool mouseClicked = false;

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
 
	std::vector<sf::RectangleShape> rects;

	int space = 40;

	sf::Clock m_clock;
	float m_elapsed;
    TileMap map;
    sf::Sprite mapSprite_;
	const int level[256] = 
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	



};
